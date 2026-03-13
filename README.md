# pkzo

pkzo is a collection of functionality for building games and game engines.

It is written in C++ and assumes you know how to program. This is a code-first
library.

## Features

pkzo is probably not for you. Go use [Godot](https://godotengine.org/).

**Seriously.**

Key characteristics of pkzo:

- written in C++, if you cannot program you cannot use it
- minimal documentation
- missing exactly the feature you currently need
- no beginner support
- no welcoming community
- no concern for your feelings, C++ is not a gentle language

## Documentation

Still here? If you want to learn to use pkzo, here are a few 
pointers:

Documentation currently lives in the headers. It will continue to live in the
headers. There are no plans for a polished documentation website.

Start with `pkzo.h`. If a header is not reachable from there you probably
should not be using it.

Rough stability rule:

- functions with doc strings are *probably* semi-stable
- functions without doc strings are fair game for change

Even documented functions may change.

If you want an example, look at **pkzo-lab**. It is a working example of one
possible way to assemble a game or game engine with pkzo. It is not a framework,
a template or a recommended architecture. It is simply code that works.

## Contributing

Don't. 

The design decisions are intentional and not up for committee discussion.

However, pull requests that are useful, align with the design and meet the
project's quality standards may be merged. Don't forget to update ChangeLog.md

## AI Policy

AI assistants may be used for programming-adjacent tasks such as:

- code reviews
- improving documentation
- rubber ducking
- personal Stack Overflow

AI-generated production code is not allowed.

If detected, the contributor will be permanently banned without discussion.
This is your warning. 

## License

pkzo is licensed under the MIT license. See `LICENSE.txt` or the file headers.

Some small utilities are licensed under the WTFPL. Since the license terms are
effectively "do whatever you want", the entire project can be treated as MIT.
