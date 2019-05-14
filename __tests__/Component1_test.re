open Jest;
 
describe("Component1", () => {
  open ExpectJs;
 
  test("renders", () => {
    let foo: list(OurTypes.colorMap) = [{name: "string"}];
    let component = ReactShallowRenderer.renderWithRenderer(<Component1 list=foo />);
 
    expect(Js.Undefined.return(component)) |> toBeDefined;
  });
});
