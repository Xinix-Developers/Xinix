# Xinix - Community OS project

## Building

Building is as simple as `just build`! Presently, this just forwards to `make`, but it might do fancy things later.

To get a clean build, run `just clean`.

## IDE Setup

If you want to get better code suggestions in something like VS Code (or anything that uses clangd as a language server), you can use [`bear`](https://github.com/rizsotto/bear) to help! Simply run `bear -- just clean build`, and a `compile_commands.json` will be generated!
