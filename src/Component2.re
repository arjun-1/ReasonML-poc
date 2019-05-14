external castErrorUnsafe: Js.Promise.error => Js.t('a) = "%identity";

/* State declaration */
type stateUI = {
  count: int,
  show: bool,
  colorMapQuery: option(string),
};
/* Action declaration */
type actionUI =
  | Click
  | Toggle
  | SetColorMapQuery(string);

type stateAPI = {map: option(OurTypes.colorMap)};

type actionAPI =
  | SetColorMap(OurTypes.colorMap)
  | RemoveColorMap;

let decodeColorMap = (json: Js.Json.t): Belt.Result.t(OurTypes.colorMap, string) =>
  try (Json.Decode.{name: json |> field("name", string)}->Belt.Result.Ok) {
  | Json.Decode.DecodeError(error) => error->Belt.Result.Error
  };

module ColorMapApi = {
  let fetch = (query: string) =>
    Js.Promise.(
      Axios.get("http://www.mocky.io/v2/5cd9298a3000008320c01440" ++ "/" ++ query)
      |> then_(response => response##data->decodeColorMap->resolve)
      |> catch(error => error->castErrorUnsafe##response##status->Belt.Result.Error->resolve)
    );
};

[@react.component]
let make = (~greeting) => {
  let (stateAPI, dispatchAPI) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | SetColorMap(colorMap) => {map: colorMap->Some}
        | RemoveColorMap => {map: None}
        },
      {map: None},
    );

  let (stateUI, dispatchUI) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | Click => {...state, count: state.count + 1}
        | Toggle => {...state, show: !state.show}
        | SetColorMapQuery(colorMapQuery) => {...state, colorMapQuery: colorMapQuery->Some}
        },
      {count: 0, show: true, colorMapQuery: None},
    );

  let setColorMap = (colorMapQuery: string) =>
    Js.Promise.(
      ColorMapApi.fetch(colorMapQuery)
      |> then_(result =>
           switch (result) {
           | Belt.Result.Ok(colorMap) => colorMap->SetColorMap->dispatchAPI->resolve
           | Belt.Result.Error(error) => Js.log(error)->resolve
           }
         )
    );

  React.useEffect1(
    () =>
      switch (stateUI.colorMapQuery) {
      | None =>
        RemoveColorMap->dispatchAPI;
        None;
      | Some(query) =>
        setColorMap(query)->ignore;
        None;
      },
    [|stateUI.colorMapQuery|],
  );

  let themeConfig = ReactUwp.Theme.themeConfig(
    ~themeName="light", // set custom theme
    ~accent="#0078D7", // set accent color
    ~useFluentDesign=true, // sure you want use new fluent design.
    ()
  );

  let message = "You've clicked this";
  <div>
    <ReactUwp.Theme.Theme
      theme={ReactUwp.Theme.getTheme(themeConfig)}
    >
      <ReactUwp.Button tooltip="test" />
      <button onClick={_event => Click->dispatchUI}> message->ReasonReact.string </button>
      <button onClick={_event => Toggle->dispatchUI}>
        {ReasonReact.string("Toggle greeting")}
      </button>
      <button onClick={_event => "from input element"->SetColorMapQuery->dispatchUI}>
        {ReasonReact.string("Fetch")}
      </button>
      {stateUI.show ? greeting->ReasonReact.string : ReasonReact.null}
      {
        switch (stateAPI.map) {
        | Some(map) => map.name->ReasonReact.string
        | None => ReasonReact.null
        }
      }
    </ReactUwp.Theme.Theme>
  </div>;
};
