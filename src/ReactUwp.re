module Theme = {
  [@bs.deriving abstract]
  type themeConfig = {
    [@bs.optional] themeName: string,
    [@bs.optional] accent: string,
    [@bs.optional] useFluentDesign: bool,
    [@bs.optional] desktopBackgroundImage: string,
  };

  type themeType = {
    themeName: string,
  };
  
  [@bs.module "react-uwp/Theme"] external getTheme: themeConfig => themeType = "getTheme";

  module Theme = {
    [@bs.module "react-uwp/Theme" ] external reactComponent: React.component('a) = "Theme";
    [@bs.obj]
    external makeProps:
      (
        ~theme: themeConfig=?,
        ~style: ReactDOMRe.Style.t=?,
        ~children: React.element=?,
        unit
      ) =>
      _ =
      "";

    [@react.component]
    let make =
        (
          ~theme: option(themeType)=?,
          ~style: option(ReactDOMRe.Style.t)=?,
          ~children: option(React.element)=?,
        ) =>
      React.createElement(
        reactComponent,
        makeProps(~theme?, ~style?, ~children?, ()),
      );

  }
};

module Button = {
  [@bs.module "react-uwp/Button"] external reactComponent: React.component('a) = "default";
  [@bs.obj]
  external makeProps:
    (~tooltip: string=?, ~style: ReactDOMRe.Style.t=?, ~children: React.element=?, unit) => _ =
    "";

  [@react.component]
  let make =
      (
        ~tooltip: option(string)=?,
        ~style: option(ReactDOMRe.Style.t)=?,
        ~children: option(React.element)=?,
      ) =>
    React.createElement(
      reactComponent,
      makeProps(~tooltip?, ~style?, ~children?, ()),
    );
};
