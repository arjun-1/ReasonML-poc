// Generated by BUCKLESCRIPT VERSION 5.0.4, PLEASE EDIT WITH CARE
'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Axios = require("axios");
var React = require("react");
var Json_decode = require("@glennsl/bs-json/src/Json_decode.bs.js");
var Caml_js_exceptions = require("bs-platform/lib/js/caml_js_exceptions.js");

function decodeColorMap(json) {
  return /* record */[/* name */Json_decode.field("name", Json_decode.string, json)];
}

function $$fetch(query) {
  return Axios.get("http://www.mocky.io/v2/5cd9298a3000008320c01440/" + query).then((function (response) {
                  var tmp;
                  try {
                    tmp = /* Ok */Block.__(0, [decodeColorMap(response.data)]);
                  }
                  catch (raw_exn){
                    var exn = Caml_js_exceptions.internalToOCamlException(raw_exn);
                    if (exn[0] === Json_decode.DecodeError) {
                      tmp = /* Error */Block.__(1, [exn[1]]);
                    } else {
                      throw exn;
                    }
                  }
                  return Promise.resolve(tmp);
                })).catch((function (error) {
                return Promise.resolve(/* Error */Block.__(1, [error.response.status]));
              }));
}

var ColorMapApi = /* module */[/* fetch */$$fetch];

function Component2(Props) {
  var greeting = Props.greeting;
  var match = React.useReducer((function (state, action) {
          if (action) {
            return /* record */[/* map */action[0]];
          } else {
            return /* record */[/* map */undefined];
          }
        }), /* record */[/* map */undefined]);
  var dispatchAPI = match[1];
  var match$1 = React.useReducer((function (state, action) {
          if (typeof action === "number") {
            if (action !== 0) {
              return /* record */[
                      /* count */state[/* count */0],
                      /* show */!state[/* show */1],
                      /* colorMapQuery */state[/* colorMapQuery */2]
                    ];
            } else {
              return /* record */[
                      /* count */state[/* count */0] + 1 | 0,
                      /* show */state[/* show */1],
                      /* colorMapQuery */state[/* colorMapQuery */2]
                    ];
            }
          } else {
            return /* record */[
                    /* count */state[/* count */0],
                    /* show */state[/* show */1],
                    /* colorMapQuery */action[0]
                  ];
          }
        }), /* record */[
        /* count */0,
        /* show */true,
        /* colorMapQuery */undefined
      ]);
  var dispatchUI = match$1[1];
  var stateUI = match$1[0];
  var setColorMap = function (colorMapQuery) {
    return $$fetch(colorMapQuery).then((function (result) {
                  if (result.tag) {
                    return Promise.resolve((console.log(result[0]), /* () */0));
                  } else {
                    return Promise.resolve(Curry._1(dispatchAPI, /* SetColorMap */[result[0]]));
                  }
                }));
  };
  React.useEffect((function () {
          var match = stateUI[/* colorMapQuery */2];
          if (match !== undefined) {
            setColorMap(match);
            return undefined;
          } else {
            Curry._1(dispatchAPI, /* RemoveColorMap */0);
            return undefined;
          }
        }), /* array */[stateUI[/* colorMapQuery */2]]);
  var match$2 = stateUI[/* show */1];
  var match$3 = match[0][/* map */0];
  return React.createElement("div", undefined, React.createElement("button", {
                  onClick: (function (_event) {
                      return Curry._1(dispatchUI, /* Click */0);
                    })
                }, "You've clicked this"), React.createElement("button", {
                  onClick: (function (_event) {
                      return Curry._1(dispatchUI, /* Toggle */1);
                    })
                }, "Toggle greeting"), React.createElement("button", {
                  onClick: (function (_event) {
                      return Curry._1(dispatchUI, /* SetColorMapQuery */["from input element"]);
                    })
                }, "Fetch"), match$2 ? greeting : null, match$3 !== undefined ? match$3[/* name */0] : null);
}

var make = Component2;

exports.decodeColorMap = decodeColorMap;
exports.ColorMapApi = ColorMapApi;
exports.make = make;
/* axios Not a pure module */
