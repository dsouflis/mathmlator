# Mathmlator
You find yourself wanting to up your math game, but admit it, MathML is not the easiest 
thing to write. XML syntax? What is it? 2000? If only there was someone who could come
from the future and terminate your MathML problems, with the brutal efficiency only a
machine could have.

![MathMLator][screenshot]

Mathmlator is a small ReasonML React example program illustrating mostly the strong points
of ReasonML as a language, rather than any particular advantage it has for writing React
programs. The latter is an open question I might revisit some other time.

## Why ReasonML?
ReasonML is really OCaml transpiled to JavaScript. OCaml is a hybrid language combining 
both the functional and the imperative paradigm. In reality, OCaml is also incorporating
the OO paradigm, but I didn't see anything transferring to ReasonML, and it's 2021. I don't
believe people should invest a lot on OO.

Even though it is useful to keep in mind the OCaml origins, I couldn't try out 
leveraging any OCaml library (OCaml has a code repository called OPAN).
This needs more ReasonML-fu than I have. And people don't 
usually learn anything else than Java, nowadays, so I'll just treat it as a new and 
interesting language (myself, I have had the opportunity to play a lot with many
functional languages of that era, and have recently took a [course][ocaml course] 
out of nostalgia). So let's answer the question: why bother with ReasonML? Isn't modern
JavaScript good enough?

Truth be told, JavaScript is almost good enough. It's not an expression-based language like
ReasonML, so sometimes I find myself having to declare "vars" and later do some
conditional logic to give them values, but I can live with that. ReasonML is strongly-typed,
but so is TypeScript. ReasonML's type inferencer is probably better than TypeScript
s (IIRC, OCaml's type inferencer could actually typecheck a whole program from start to
finish without needing a single type annotation), but this is not a make-or-break feature.

The one characteristic which, in my opinion, distinguishes ReasonML from any language 
that has evolved from plain C/C++, is its abundant support for variant types. This is 
something it shares with any language having a strong functional character (these are 
called "case objects" in Scala, for example). All these languages, ReasonML included,
provide features to construct, deconstruct and pattern-match on variant types, and
this is actually the one feature I keep missing when I'm using a language that
lacks it.

## The code



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
