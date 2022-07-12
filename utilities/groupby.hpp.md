---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://atcoder.jp/contests/abc259/tasks/abc259_h
  bundledCode: "#line 2 \"utilities/groupby.hpp\"\n#include <algorithm>\n#include\
    \ <utility>\n#include <vector>\n\n// Key class must be comparable\n// Example:\
    \ [(2, 3), (1, 5), (2, 2), (2, 3), (1, 4)] -> [(1, [5, 4]), (2, [3, 2, 3])]\n\
    // Verified: https://atcoder.jp/contests/abc259/tasks/abc259_h\ntemplate <class\
    \ Key, class Value>\nstd::vector<std::pair<Key, std::vector<Value>>> groupby(std::vector<std::pair<Key,\
    \ Value>> xs) {\n    using KV = std::pair<Key, Value>;\n    std::stable_sort(\n\
    \        xs.begin(), xs.end(), [&](const KV &l, const KV &r) { return l.first\
    \ < r.first; });\n\n    std::vector<std::pair<Key, std::vector<Value>>> ret;\n\
    \    for (const auto &x : xs) {\n        if (ret.empty() or ret.back().first !=\
    \ x.first) {\n            ret.emplace_back(x.first, std::vector<Value>());\n \
    \       }\n        ret.back().second.push_back(x.second);\n    }\n    return ret;\n\
    }\n"
  code: "#pragma once\n#include <algorithm>\n#include <utility>\n#include <vector>\n\
    \n// Key class must be comparable\n// Example: [(2, 3), (1, 5), (2, 2), (2, 3),\
    \ (1, 4)] -> [(1, [5, 4]), (2, [3, 2, 3])]\n// Verified: https://atcoder.jp/contests/abc259/tasks/abc259_h\n\
    template <class Key, class Value>\nstd::vector<std::pair<Key, std::vector<Value>>>\
    \ groupby(std::vector<std::pair<Key, Value>> xs) {\n    using KV = std::pair<Key,\
    \ Value>;\n    std::stable_sort(\n        xs.begin(), xs.end(), [&](const KV &l,\
    \ const KV &r) { return l.first < r.first; });\n\n    std::vector<std::pair<Key,\
    \ std::vector<Value>>> ret;\n    for (const auto &x : xs) {\n        if (ret.empty()\
    \ or ret.back().first != x.first) {\n            ret.emplace_back(x.first, std::vector<Value>());\n\
    \        }\n        ret.back().second.push_back(x.second);\n    }\n    return\
    \ ret;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/groupby.hpp
  requiredBy: []
  timestamp: '2022-07-10 23:01:04+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utilities/groupby.hpp
layout: document
title: groupby
---

`Key` と `Value` のペアからなる値の列を，`Key` の値に基づいて分類する．`std::map` などを使用しても同様のことは実現できるが，本実装では `std::vector` に対する `std::stable_sort` のみを用いているため定数倍が良い可能性がある．

## 問題例

- [AtCoder Beginner Contest 259 Ex - Yet Another Path Counting](https://atcoder.jp/contests/abc259/tasks/abc259_h)
