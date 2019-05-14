[@react.component]
let make = (~greeting: string) => {
  let (stateApp, dispatchApp) = React.useContext(MyContext.context);
  <div>
    {React.string(greeting)}
    {
      switch (stateApp.map) {
      | Some(map) => map.name->ReasonReact.string
      | None => "Nothing to be seen here"->React.string
      }
    }
  </div>;
};
