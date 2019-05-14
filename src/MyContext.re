type stateApp = {map: option(OurTypes.colorMap)};

type actionApp =
  | SetColorMap(OurTypes.colorMap)
  | RemoveColorMap;
type dispatchApp = actionApp => unit


let initialState = {map: None};


let context: React.Context.t((stateApp, dispatchApp)) = React.createContext((initialState, _ => ()));

module Provider = {
  let makeProps = (~value, ~children, ()) => {"value": value, "children": children}
  let make = React.Context.provider(context);
}
