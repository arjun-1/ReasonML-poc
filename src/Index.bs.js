// Generated by BUCKLESCRIPT VERSION 5.0.4, PLEASE EDIT WITH CARE
'use strict';

var React = require("react");
var ReactDOMRe = require("reason-react/src/ReactDOMRe.js");
var Component1$ReactHooksTemplate = require("./Component1.bs.js");
var Component2$ReactHooksTemplate = require("./Component2.bs.js");

var foo = /* :: */[
  /* record */[/* name */"string"],
  /* [] */0
];

ReactDOMRe.renderToElementWithId(React.createElement(Component1$ReactHooksTemplate.make, {
          list: foo
        }), "index1");

ReactDOMRe.renderToElementWithId(React.createElement(Component2$ReactHooksTemplate.make, {
          greeting: "Hello!"
        }), "index2");

exports.foo = foo;
/*  Not a pure module */
