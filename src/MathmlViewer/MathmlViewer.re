open MathmlParser;
// This is the ReactJS documentation's useReducer example, directly ported over
// https://reactjs.org/docs/hooks-reference.html#usereducer

// A little extra we've put, because the ReactJS example has no styling
let leftButtonStyle =
  ReactDOMRe.Style.make(~borderRadius="4px 0px 0px 4px", ~width="48px", ());
let rightButtonStyle =
  ReactDOMRe.Style.make(~borderRadius="0px 4px 4px 0px", ~width="48px", ());
let containerStyle =
  ReactDOMRe.Style.make(
    ~display="flex",
    ~alignItems="center",
    ~justifyContent="space-between",
    (),
  );

// Record and variant need explicit declarations.
type state = {
  show: bool,
  mathml: string,
};

type action =
  | Set(string);

let initialState: state = {show: false, mathml: ""};

let reducer = (_state, action) => {
  switch (action) {
  | Set(s) =>
    let out = mathml_of_string(s);
    let st =
      switch (out) {
      | ParseSuccess(mathml) => {
          mathml: mathmlstring_of_mathml(mathml),
          show: true,
        }
      | ParseFailure(msg) => {show: false, mathml: {j|ERROR: $(msg)|j}}
      };
    st;
  };
};

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(reducer, initialState);

  // We can use a fragment here, but we don't, because we want to style the counter
  <div style=containerStyle>
    <div>
      <input
        onChange={event =>
          dispatch(Set(ReactEvent.Form.target(event)##value))
        }
      />
    </div>
    {switch (state) {
     | {show: true, mathml} => <pre> {React.string(mathml)} </pre>
     | {show: false, mathml} => <h4> {React.string(mathml)} </h4>
     }}
  </div>;
};
