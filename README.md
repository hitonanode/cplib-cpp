# C++ Algorithm/Data Structure Library for Competitive Programming

[![Actions Status](https://github.com/rsm9/cplib-cpp/workflows/verify/badge.svg)](https://github.com/rsm9/cplib-cpp/actions)

[Library Document](https://hitonanode.github.io/cplib-cpp/)

## Policy

- "Copy-and-paste-then-run" in any platforms
  - C++11-friendly (for topcoder SRM)
  - No macro such as `REP(i, n)`
- Easy to remember usage of codes which have not been used for long time
  - Concise usage on `.hpp` files
  - Less code length
- Proactively introducing non-essential codes (such as UnionFind for 2D grids) to realize fast AC

## Environments:

GitHub Actions-based CI is run for the environments below:

- C++11 (GCC): `g++ -std=c++11 -Wall -O2 -fsplit-stack`
- C++14 (GCC): `g++`
- C++17 (Clang): `clang++ -std=c++17 -O2 -Wall`
 
## Installation

You can easily insert the snippets using [Clipboard History](https://blank-note.sakura.ne.jp/topics/clipboard_history.html). The script `generate_snippet_conf.py` generates the configuration file for it.

## License

Some files in this repo (such as `network-simplex.hpp`) contains peculiar license statements. These files are under the particular license.

Except such snippets, the programs written by the owner of the repo is under the MIT License, but you can freely use or modify C++ codes without any notice for programming contests or online judges.

## Format

Settings of `clang-format`:

```
{ BasedOnStyle: LLVM, IndentWidth: 4, AccessModifierOffset: -4, AllowShortBlocksOnASingleLine: true, AllowShortCaseLabelsOnASingleLine: true, AllowShortFunctionsOnASingleLine: All, AllowShortIfStatementsOnASingleLine: true, AllowShortLoopsOnASingleLine: true, AlwaysBreakBeforeMultilineStrings: false, AlwaysBreakTemplateDeclarations: false, ColumnLimit: 120 }
```
