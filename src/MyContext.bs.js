// Generated by BUCKLESCRIPT VERSION 5.0.4, PLEASE EDIT WITH CARE
'use strict';

var React = require("react");

var initialState = /* record */[/* map */undefined];

var context = React.createContext(/* tuple */[
      initialState,
      (function (param) {
          return /* () */0;
        })
    ]);

function makeProps(value, children, param) {
  return {
          value: value,
          children: children
        };
}

var make = context.Provider;

var Provider = /* module */[
  /* makeProps */makeProps,
  /* make */make
];

exports.initialState = initialState;
exports.context = context;
exports.Provider = Provider;
/* context Not a pure module */
