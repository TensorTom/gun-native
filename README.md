# gun-native

#### The Gun decentralized graph database as a native library.

## Rationale

For most people reading this, I probably don't have to tell you how great [Gun](https://github.com/amark/gun) is. I
found myself wanting (Badly) to use Gun in Python. While there exists [pygundb](https://github.com/xmonader/pygundb)
(A huge thanks to xmonader for that), I couldn't help but realize how much better it would be to not rely on node
or a Javascript engine. What if we had a native library?

There are a few different ways to go about this, in order of difficulty (Most to least):

* Port Gun to an entirely separate language that compiles natively (C, Nim, Rust, Go, etc.).
* Port Gun to TypeScript.
* Use a Javascript compiler or JS to \<SomethingNative> transpiler.

We will therefor work up this list, from bottom to top, until success is had.

## Attempt #1 - NectarJS

I found [NectarJS](https://github.com/NectarJS/nectarjs) researching for this port. It was started in 2017 and appears
to be in active development. Its ways are largely unknown to me but it promises "Javascript's God Mode. No VM. No
Bytecode. No GC. Just native binaries."

Let's find out if it can deliver or if it can't, how much contribution it might take to catch it up to
where we need it to be. Each different tech/attempt will live in its own branch.

Nectar branch has been started [here](https://github.com/TensorTom/gun-native/tree/nectar).

#### NECTAR LOG

------------------------
* 6/9/2020: First basic attempt was had of: `nectar --verbose gun_src/gun.js` Many errors did happen which live in
[build_debug](build_debug/) and it looks like we have some C output to [njs.h](.nectar/uuuvr/njs.h).
