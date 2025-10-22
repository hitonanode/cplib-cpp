---
title: Custom hash functions （各種データ構造のためのハッシュ関数）
documentation_of: ./custom_hash.hpp
---

Codeforces 等で `std::unordered_set<>` や `std::unordered_map<>` を使用した場合のハッシュ衝突攻撃を防止するハッシュ関数．また，任意の構造体をこれらのキーとして与えるための `std::hash` の特殊化のテンプレートを含む．

## Link

- [Blowing up unordered_map, and how to stop getting hacked on it - Codeforces](https://codeforces.com/blog/entry/62393)
- [<unordered_set> [🟢C++20 対応]｜競プロのための標準 C++](https://zenn.dev/reputeless/books/standard-cpp-for-competitive-programming/viewer/unordered_set)
