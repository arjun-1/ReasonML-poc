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

let decodeColorMap = (json: Js.Json.t): OurTypes.colorMap =>
  Json.Decode.{name: json |> (string |> field("name"))};

module ColorMapApi = {
  let fetch = (query: string) =>
    Js.Promise.(
      Axios.get("http://www.mocky.io/v2/5cd56c622e0000b8185276c3" ++ "/" ++ query)
      |> then_(response =>
           (
             try (response##data->decodeColorMap->Belt.Result.Ok) {
             | Json.Decode.DecodeError(error) => Belt.Result.Error(error)
             }
           )
           |> resolve
         )
      |> catch(error => castErrorUnsafe(error)##response##status->Belt.Result.Error->resolve)
    );
};

[@react.component]
let make = (~greeting) => {
  let (stateAPI, dispatchAPI) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | SetColorMap(colorMap) => {map: Some(colorMap)}
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
        | SetColorMapQuery(colorMapQuery) => {...state, colorMapQuery: Some(colorMapQuery)}
        },
      {count: 0, show: true, colorMapQuery: None},
    );

  let setColorMap = (colorMapQuery: string) =>
    Js.Promise.(
      ColorMapApi.fetch(colorMapQuery)
      |> then_(result =>
           switch (result) {
           | Belt.Result.Ok(colorMap) => SetColorMap(colorMap) |> dispatchAPI |> resolve
           | Belt.Result.Error(error) => Js.log(error) |> resolve
           }
         )
    );

  React.useEffect1(
    () =>
      switch (stateUI.colorMapQuery) {
      | None => Some((() => RemoveColorMap |> dispatchAPI))
      | Some(query) => Some((() => setColorMap(query) |> ignore))
      },
    [|stateUI.colorMapQuery|],
  );

  let message = "You've clicked this";
  <div>
    <button onClick={_event => Click |> dispatchUI}> {ReasonReact.string(message)} </button>
    <button onClick={_event => Toggle |> dispatchUI}>
      {ReasonReact.string("Toggle greeting")}
    </button>
    <button onClick={_event => SetColorMapQuery("from input element") |> dispatchUI}>
      {ReasonReact.string("Fetch")}
    </button>
    {stateUI.show ? ReasonReact.string(greeting) : ReasonReact.null}
    {
      switch (stateAPI.map) {
      | Some(map) => map.name |> ReasonReact.string
      | None => ReasonReact.null
      }
    }
  </div>;
};
