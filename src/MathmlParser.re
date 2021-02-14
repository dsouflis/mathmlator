open BsLittleParser.Parser;

type mathmlPrim =
  | Mo(string)
  | Mn(string)
  | Mi(string)
  | Msup(string, string);
type mathml = list(mathmlPrim);

type parseResult =
  | ParseSuccess(mathml)
  | ParseFailure(string);

// Parser
let num = regexParser(Js.Re.fromString("\\d*"));
let expnum = regexParser(Js.Re.fromString("\\d+"));

let var = regexParser(Js.Re.fromString("[a-z]"));

let monomial =
  regexParser(Js.Re.fromString("[-+ ]?"))
  <*> num
  <*> var
  <*> opt(charParser('^') <*> expnum);

type exp = option((char, string));
type mono = (((string, string), string), exp);
type poly = list(mono);

let polynomial = rep(monomial);

// MathML rendering
let mathmlstring_of_mathmlPrim = (p: mathmlPrim): string =>
  switch (p) {
  | Mo(pm) => {j|
     <mo>$(pm)</mo>|j}
  | Mn(n) => {j|
     <mn>$(n)</mn>|j}
  | Mi(v) => {j|
     <mi>$(v)</mi>|j}
  | Msup(v, ex) => {j|
     <msup>
       <mi>$(v)</mi>
       <mn>$(ex)</mn>
     </msup>|j}
  };

let mathmlstring_of_mathml = (m: mathml): string => {
  let s = String.concat("", List.map(mathmlstring_of_mathmlPrim, m));
  {j|
<math xmlns="http://www.w3.org/1998/Math/MathML">$(s)
</math>
  |j};
};

//Parser artifacts to mathml
let mathml_of_exp = (v: string, e: exp): mathml =>
  switch (e) {
  | Some((_e, ex)) => [Msup(v, ex)]
  | None => [Mi(v)]
  };

let mathml_of_monomial = (m: mono): mathml =>
  switch (m) {
  | (((pm, n), v), e) =>
    let es = mathml_of_exp(v, e);
    let pms =
      if (pm == "") {
        [];
      } else {
        [Mo(pm)];
      };
    let ns =
      if (n == "") {
        [];
      } else {
        [Mn(n)];
      };
    let s = List.concat([pms, ns, es]);
    s;
  };

let rec mathml_of_polynomial = (p: poly): mathml =>
  switch (p) {
  | [] => []
  | [hd, ...tl] =>
    List.append(mathml_of_monomial(hd), mathml_of_polynomial(tl))
  };

let mathml_of_string = (s: string): parseResult => {
  let input = BsLittleParser.Input.{text: s, index: 0, whitespace: " "};

  let out: BsLittleParser.ParseResult.t(poly) = input |> polynomial;

  switch (out) {
  | BsLittleParser.ParseResult.ParseSuccess(e, _i) =>
    ParseSuccess(mathml_of_polynomial(e))
  | BsLittleParser.ParseResult.ParseFailure(m, _i) => ParseFailure(m)
  };
};
