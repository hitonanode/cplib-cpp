---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: data_structure/test/assosiative_array.test.cpp
    title: data_structure/test/assosiative_array.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - http://xorshift.di.unimi.it/splitmix64.c
    - https://codeforces.com/blog/entry/62393
  bundledCode: "#line 2 \"random/custom_hash.hpp\"\n#include <chrono>\n#include <cstdlib>\n\
    #include <functional>\n\nstruct custom_hash {\n    // https://codeforces.com/blog/entry/62393\n\
    \    static uint64_t splitmix64(uint64_t x) {\n        // http://xorshift.di.unimi.it/splitmix64.c\n\
    \        x += 0x9e3779b97f4a7c15;\n        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;\n\
    \        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;\n        return x ^ (x >> 31);\n\
    \    }\n\n    size_t operator()(uint64_t x) const {\n        static const uint64_t\
    \ FIXED_RANDOM =\n            std::chrono::steady_clock::now().time_since_epoch().count();\n\
    \        return splitmix64(x + FIXED_RANDOM);\n    }\n};\n\n// Template of std::hash\
    \ for arbitrary structs\n// template <> struct std::hash<T> {\n//     std::size_t\
    \ operator()(const T &x) const noexcept {\n//         static custom_hash h;\n\
    //         return h(/* */);\n//     }\n// };\n\n// robust unordered_map\n// #include\
    \ <unordered_map>\n// std::unordered_map<int, int, custom_hash> robust_unordered_map;\n\
    \n// fast unordered_set / unordered_map\n// #include <ext/pb_ds/assoc_container.hpp>\n\
    // using namespace __gnu_pbds;\n// gp_hash_table<int, null_type, custom_hash>\
    \ fast_hash_table;\n"
  code: "#pragma once\n#include <chrono>\n#include <cstdlib>\n#include <functional>\n\
    \nstruct custom_hash {\n    // https://codeforces.com/blog/entry/62393\n    static\
    \ uint64_t splitmix64(uint64_t x) {\n        // http://xorshift.di.unimi.it/splitmix64.c\n\
    \        x += 0x9e3779b97f4a7c15;\n        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;\n\
    \        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;\n        return x ^ (x >> 31);\n\
    \    }\n\n    size_t operator()(uint64_t x) const {\n        static const uint64_t\
    \ FIXED_RANDOM =\n            std::chrono::steady_clock::now().time_since_epoch().count();\n\
    \        return splitmix64(x + FIXED_RANDOM);\n    }\n};\n\n// Template of std::hash\
    \ for arbitrary structs\n// template <> struct std::hash<T> {\n//     std::size_t\
    \ operator()(const T &x) const noexcept {\n//         static custom_hash h;\n\
    //         return h(/* */);\n//     }\n// };\n\n// robust unordered_map\n// #include\
    \ <unordered_map>\n// std::unordered_map<int, int, custom_hash> robust_unordered_map;\n\
    \n// fast unordered_set / unordered_map\n// #include <ext/pb_ds/assoc_container.hpp>\n\
    // using namespace __gnu_pbds;\n// gp_hash_table<int, null_type, custom_hash>\
    \ fast_hash_table;\n"
  dependsOn: []
  isVerificationFile: false
  path: random/custom_hash.hpp
  requiredBy: []
  timestamp: '2025-10-23 00:38:21+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - data_structure/test/assosiative_array.test.cpp
documentation_of: random/custom_hash.hpp
layout: document
title: "Custom hash functions \uFF08\u5404\u7A2E\u30C7\u30FC\u30BF\u69CB\u9020\u306E\
  \u305F\u3081\u306E\u30CF\u30C3\u30B7\u30E5\u95A2\u6570\uFF09"
---

Codeforces 等で `std::unordered_set<>` や `std::unordered_map<>` を使用した場合のハッシュ衝突攻撃を防止するハッシュ関数．また，任意の構造体をこれらのキーとして与えるための `std::hash` の特殊化のテンプレートを含む．

## Link

- [Blowing up unordered_map, and how to stop getting hacked on it - Codeforces](https://codeforces.com/blog/entry/62393)
- [<unordered_set> [🟢C++20 対応]｜競プロのための標準 C++](https://zenn.dev/reputeless/books/standard-cpp-for-competitive-programming/viewer/unordered_set)
