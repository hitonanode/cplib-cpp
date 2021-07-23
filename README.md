# C++ Algorithm/Data Structure Library for Competitive Programming

[![Actions Status](https://github.com/rsm9/cplib-cpp/workflows/verify/badge.svg)](https://github.com/rsm9/cplib-cpp/actions)
[![hitonanode](https://img.shields.io/endpoint?url=https%3A%2F%2Fatcoder-badges.now.sh%2Fapi%2Fatcoder%2Fjson%2Fhitonanode)](https://atcoder.jp/users/hitonanode)
[![hitonanode](https://img.shields.io/endpoint?url=https%3A%2F%2Fatcoder-badges.now.sh%2Fapi%2Fcodeforces%2Fjson%2Fhitonanode)](https://codeforces.com/profile/hitonanode)

[Library Document](https://hitonanode.github.io/cplib-cpp/)

## Policy

- "Copy-and-paste-then-run" in any platforms
  - C++11-friendly (for topcoder SRM)
  - No macro such as `REP(i, n)`
- Easy to remember usage of codes which have not been used for long time
  - Concise instruction is written directly on `.hpp` / `.h` files
  - Less lines preferred
- Proactively introducing non-essential codes (such as UnionFind specialized for 2D grids) for fast AC in real contests

## Environments:

GitHub Actions-based CI is run for the environments below:

- C++11 (GCC): `g++ -std=c++11 -Wall -O2 -fsplit-stack`
- C++14 (GCC): `g++`
- C++17 (Clang): `clang++ -std=c++17 -O2 -Wall`
 
## Installation

You can easily insert the snippets using the tools such as [Clipboard History](https://blank-note.sakura.ne.jp/topics/clipboard_history.html) and [snippet-from-file
](https://marketplace.visualstudio.com/items?itemName=morioprog.snippet-from-file). The script `generate_snippet_conf.py` generates the configuration file for them.

## License

Some files in this repo (such as `network-simplex.hpp`) contains peculiar license statements. These files are under the particular license.

Except such snippets, the programs written by the owner of the repo is under the MIT License, but you can freely use or modify C++ codes without any notice for programming contests or online judges.

## Format

Settings of `clang-format`:

```
{ BasedOnStyle: LLVM, IndentWidth: 4, AccessModifierOffset: -4, AllowShortBlocksOnASingleLine: true, AllowShortCaseLabelsOnASingleLine: true, AllowShortFunctionsOnASingleLine: All, AllowShortIfStatementsOnASingleLine: true, AllowShortLoopsOnASingleLine: true, AlwaysBreakBeforeMultilineStrings: false, AlwaysBreakTemplateDeclarations: false, ColumnLimit: 110 }
```
