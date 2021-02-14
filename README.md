# Mathmlator
You find yourself wanting to up your math game, but admit it, MathML is not the easiest 
thing to write. XML syntax? What is it? 2000? If only there was someone who could come
from the future and terminate your MathML problems, with the brutal efficiency only a
machine could have.

![MathMLator][screenshot]

Mathmlator is a small Reason React example program illustrating mostly the strong points
of Reason as a language, rather than any particular advantage it has for writing React
programs. The latter is an open question I might revisit some other time.

## Why Reason?
Reason is really OCaml transpiled to JavaScript. OCaml is a hybrid language combining 
both the functional and the imperative paradigm. In reality, OCaml is also incorporating
the OO paradigm, but I didn't see anything transferring to Reason, and it's 2021. I don't
believe people should invest a lot on OO.

Even though it is useful to keep in mind the OCaml origins, I couldn't try out 
leveraging any OCaml library (OCaml has a code repository called OPAN).
This needs more Reason-fu than I have. And people don't 
usually learn anything else than Java, nowadays, so I'll just treat it as a new and 
interesting language (myself, I have had the opportunity to play a lot with many
functional languages of that era, and have recently took a [course][ocaml course] 
out of nostalgia). So let's answer the question: why bother with Reason? Isn't modern
JavaScript good enough?

Truth be told, JavaScript is almost good enough. It's not an expression-based language like
Reason, so sometimes I find myself having to declare "vars" and later do some
conditional logic to give them values, but I can live with that. Reason is strongly-typed,
but so is TypeScript. Reason's type inferencer is probably better than TypeScript
s (IIRC, OCaml's type inferencer could actually typecheck a whole program from start to
finish without needing a single type annotation), but this is not a make-or-break feature.

The one characteristic which, in my opinion, distinguishes Reason from any language 
that has evolved from plain C/C++, is its abundant support for union types. This is 
something it shares with any language having a strong functional character (these are 
called "case objects" in Scala, for example). All these languages, Reason included,
provide features to construct, deconstruct and pattern-match on union types, and
this is actually the one feature I keep missing when I'm using a language that
lacks it. Union types are called variant types in Reason.

## The code
This is not a Reason tutorial, so I'll focus on just the points I want to make. And 
it's neither a MathML tutorial, nor a completely general MathML tool.

The algorithmic part is in `MathmlParser.re` and the React component in `MathmlViewer.re`.
The parser uses a parser combinator library to parse simple polynomials, of the form
`x^2+6y^3` and such. The grammar is of no importance, and it's probably wrong, because 
that was not my point. However, the constructor of the composite combinators is of some
importance because it demonstrates another cool characteristic of Reason/OCaml, being
able to define custom operators and use them in expressions. For example, one of the
combinators follows.

```reason
let monomial =
  regexParser(Js.Re.fromString("[-+ ]?"))
  <*> num
  <*> var
  <*> opt(charParser('^') <*> expnum);
```
Parsing with a combinator library is quite easy, but what you get back as result is ugly
and depends on the shape of the compositions used to construct the grammar. Not useful to
work with, and not stable, since it changes with any rearrangement of the grammar.
That's why an AST for the polynomials is defined.

```reason
type mathmlPrim =
  | Mo(string)
  | Mn(string)
  | Mi(string)
  | Msup(string, string);
type mathml = list(mathmlPrim);

type parseResult =
  | ParseSuccess(mathml)
  | ParseFailure(string);
```
These variant types allow someone to define ASTs and any kind of structured data with 
extreme ease. Deconstructing them is also very easy, like what modern JavaScript can do
for deconstructing objects. However, JavaScript cannot do pattern matching to the extent 
that Reason does.

```reason
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
```
Notice how deconstructing is used not just for extracting values, but for pattern matching
of values belonging to variant types. Pattern matching can use nested patterns to reach 
deep inside complex values and, once you get accustomed to it, you'll really miss it in
languages that lack it. Pattern matching also works for basic types like tuples,
lists and arrays.

```reason
let rec mathml_of_polynomial = (p: poly): mathml =>
  switch (p) {
  | [] => []
  | [hd, ...tl] =>
    List.append(mathml_of_monomial(hd), mathml_of_polynomial(tl))
  };
```
Fun fact: square brackets denote lists, not arrays. Arrays, like in OCaml, are written 
between composite brackets, like this `[|a, b, c |]`. But OCaml actually uses semicolons
as separators, and Reason opted for more familiar syntax. In fact, there's a fork called
[ReScript][rescript] that tries to go even closer to JavaScript syntax.

Another fun fact, also coming from OCaml: recursive functions must be denoted with the 
`rec` keyword. This is done to inform the type inferencer.

## Happy Reasoning!
I hope I have intrigued you a little with this small example. Even if one does not use
Reason in everyday work, it is still something fascinating and could be the path by
which one discovers functional programming, which I encourage everyone to explore.

Happy Reasoning!

## Run

First of all, you must install the BuckleScript toolchain.

```shell
# you can use yarn too (yarn global add bs-platform)
npm install --global bs-platform
```

The easiest way to run it is in dev mode, where you can make changes and see them on-the-fly.
```shell
npm install
npm run start
# in a new tab
npm run server
```

Open a new web page on `http://localhost:8000/`.

## Bundle for Production
(This section comes directly from the Reason-React template)
We've included a convenience `UNUSED_webpack.config.js`, in case you want to ship your project to production. You can rename and/or remove that in favor of other bundlers, e.g. Rollup.

We've also provided a barebone `indexProduction.html`, to serve your bundle.

```sh
npm install webpack webpack-cli
# rename file
mv UNUSED_webpack.config.js webpack.config.js
# call webpack to bundle for production
./node_modules/.bin/webpack
open indexProduction.html
```

## Handle Routing Yourself
(This section also comes directly from the Reason-React template)
To serve the files, this template uses a minimal dependency called `moduleserve`. A URL such as `localhost:8000/scores/john` resolves to the file `scores/john.html`. If you'd like to override this and handle URL resolution yourself, change the `server` command in `package.json` from `moduleserve ./ --port 8000` to `moduleserve ./ --port 8000 --spa` (for "single page application"). This will make `moduleserve` serve the default `index.html` for any URL. Since `index.html` loads `Index.bs.js`, you can grab hold of the URL in the corresponding `Index.re` and do whatever you want.

By the way, ReasonReact comes with a small [router](https://reasonml.github.io/reason-react/docs/en/router) you might be interested in.

[screenshot]: ./screenshot.jpg
[ocaml course]: https://www.fun-mooc.fr/courses/course-v1:parisdiderot+56002+session04/about
[rescript]: https://rescript-lang.org/
