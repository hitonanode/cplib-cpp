# C++ Algorithm/Data Structure Library for Competitive Programming

[![Actions Status](https://github.com/rsm9/cplib-cpp/workflows/verify/badge.svg)](https://github.com/rsm9/cplib-cpp/actions)

## Environments:

GitHub Actions-based CI is run for the environments below:

- C++17 (GCC): `g++ `
- C++11 (GCC): `g++ -std=c++11 -Wall -O2 -fsplit-stack`
- C++17 (Clang): `clang++ -std=c++17 -O2 -Wall`
 
## Installation

You can easily insert the snippets using [Clipboard History](https://blank-note.sakura.ne.jp/topics/clipboard_history.html). The script `generate_snippet_conf.py` generates the configuration file for it.

## License

The programs written by the owner of the repo is under the MIT License, but you can freely use or modify C++ codes without any notice for programming contests or online judges.

Some scripts for CI are borrowed from https://github.com/kmyk/online-judge-verify-helper.

## Format

Settings of `clang-format`:

```
{ BasedOnStyle: LLVM, IndentWidth: 4, AccessModifierOffset: -4, AllowShortBlocksOnASingleLine: true, AllowShortCaseLabelsOnASingleLine: true, AllowShortFunctionsOnASingleLine: All, AllowShortIfStatementsOnASingleLine: true, AllowShortLoopsOnASingleLine: true, AlwaysBreakBeforeMultilineStrings: false, AlwaysBreakTemplateDeclarations: false, ColumnLimit: 120 }
```
