let bla: OurTypes.colorMap = {name: "123"};

let foo = {OurTypes.name: "123"};
let foo2 = OurTypes.{name: "123"};

[@react.component]
let make = (~list: list(OurTypes.colorMap)) =>
  <div>
    {
      list
      |> List.map((e: OurTypes.colorMap) => e.name)
      |> List.map(React.string)
      |> Array.of_list
      |> React.array
    }
  </div>;
