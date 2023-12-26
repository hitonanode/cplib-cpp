---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: number/test/stern_brocot_tree.test.cpp
    title: number/test/stern_brocot_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://miscalc.hatenablog.com/entry/2023/12/22/213007
  bundledCode: "#line 2 \"number/stern_brocot_tree.hpp\"\n\n#include <algorithm>\n\
    #include <utility>\n#include <vector>\n\n// Stern\u2013Brocot tree\n// Implementation\
    \ based on https://miscalc.hatenablog.com/entry/2023/12/22/213007\nnamespace SternBrocotTree\
    \ {\n\nusing T = long long;\n\nstruct Node {\n    // Subtree contains all rational\
    \ numbers in (p/q, r/s)\n    T p = 0, q = 1, r = 1, s = 0; // root is (0, \\infty)\n\
    \n    // (p + r) / (q + s)\n    T num() const { return p + r; }\n    T den() const\
    \ { return q + s; }\n};\n\nenum class Direction { Left, Right };\n\nstruct Move\
    \ {\n    Direction dir;\n    T steps;\n};\n\nNode apply(Node node, const Move\
    \ &mv) {\n    if (mv.dir == Direction::Left) {\n        node.r += node.p * mv.steps;\n\
    \        node.s += node.q * mv.steps;\n    } else {\n        node.p += node.r\
    \ * mv.steps;\n        node.q += node.s * mv.steps;\n    }\n    return node;\n\
    }\n\n// path from root to num/den\nstd::vector<Move> encode_path(T num, T den)\
    \ {\n    std::vector<Move> ret;\n    bool left = false;\n\n    while (num != den)\
    \ {\n        T steps = num / den;\n        if (den * steps == num) --steps;\n\
    \        num -= steps * den;\n        if (steps) ret.push_back({left ? Direction::Left\
    \ : Direction::Right, steps});\n\n        std::swap(num, den);\n        left =\
    \ !left;\n    }\n\n    return ret;\n}\n\nNode decode_path(const std::vector<Move>\
    \ &path) {\n    Node ret{0, 1, 1, 0};\n    for (const Move &mv : path) ret = apply(ret,\
    \ mv);\n\n    return ret;\n}\n\nstd::vector<Move> lca_path(const std::vector<Move>\
    \ &path1, const std::vector<Move> &path2) {\n    std::vector<Move> ret_path;\n\
    \n    int i1 = 0, i2 = 0;\n    T step1 = path1.empty() ? 0 : path1.front().steps;\n\
    \    T step2 = path2.empty() ? 0 : path2.front().steps;\n\n    while (i1 < (int)path1.size()\
    \ and i2 < (int)path2.size()) {\n        if (!step1) {\n            ++i1;\n  \
    \          if (i1 < (int)path1.size()) step1 = path1.at(i1).steps;\n        }\
    \ else if (!step2) {\n            ++i2;\n            if (i2 < (int)path2.size())\
    \ step2 = path2.at(i2).steps;\n        } else {\n            if (path1.at(i1).dir\
    \ != path2.at(i2).dir) break;\n            T steps = std::min(step1, step2);\n\
    \            step1 -= steps;\n            step2 -= steps;\n\n            if (ret_path.empty()\
    \ or ret_path.back().dir != path1.at(i1).dir) {\n                Move move{path1.at(i1).dir,\
    \ steps};\n                ret_path.push_back(move);\n            } else {\n \
    \               ret_path.back().steps += steps;\n            }\n        }\n  \
    \  }\n\n    return ret_path;\n}\n\n} // namespace SternBrocotTree\n"
  code: "#pragma once\n\n#include <algorithm>\n#include <utility>\n#include <vector>\n\
    \n// Stern\u2013Brocot tree\n// Implementation based on https://miscalc.hatenablog.com/entry/2023/12/22/213007\n\
    namespace SternBrocotTree {\n\nusing T = long long;\n\nstruct Node {\n    // Subtree\
    \ contains all rational numbers in (p/q, r/s)\n    T p = 0, q = 1, r = 1, s =\
    \ 0; // root is (0, \\infty)\n\n    // (p + r) / (q + s)\n    T num() const {\
    \ return p + r; }\n    T den() const { return q + s; }\n};\n\nenum class Direction\
    \ { Left, Right };\n\nstruct Move {\n    Direction dir;\n    T steps;\n};\n\n\
    Node apply(Node node, const Move &mv) {\n    if (mv.dir == Direction::Left) {\n\
    \        node.r += node.p * mv.steps;\n        node.s += node.q * mv.steps;\n\
    \    } else {\n        node.p += node.r * mv.steps;\n        node.q += node.s\
    \ * mv.steps;\n    }\n    return node;\n}\n\n// path from root to num/den\nstd::vector<Move>\
    \ encode_path(T num, T den) {\n    std::vector<Move> ret;\n    bool left = false;\n\
    \n    while (num != den) {\n        T steps = num / den;\n        if (den * steps\
    \ == num) --steps;\n        num -= steps * den;\n        if (steps) ret.push_back({left\
    \ ? Direction::Left : Direction::Right, steps});\n\n        std::swap(num, den);\n\
    \        left = !left;\n    }\n\n    return ret;\n}\n\nNode decode_path(const\
    \ std::vector<Move> &path) {\n    Node ret{0, 1, 1, 0};\n    for (const Move &mv\
    \ : path) ret = apply(ret, mv);\n\n    return ret;\n}\n\nstd::vector<Move> lca_path(const\
    \ std::vector<Move> &path1, const std::vector<Move> &path2) {\n    std::vector<Move>\
    \ ret_path;\n\n    int i1 = 0, i2 = 0;\n    T step1 = path1.empty() ? 0 : path1.front().steps;\n\
    \    T step2 = path2.empty() ? 0 : path2.front().steps;\n\n    while (i1 < (int)path1.size()\
    \ and i2 < (int)path2.size()) {\n        if (!step1) {\n            ++i1;\n  \
    \          if (i1 < (int)path1.size()) step1 = path1.at(i1).steps;\n        }\
    \ else if (!step2) {\n            ++i2;\n            if (i2 < (int)path2.size())\
    \ step2 = path2.at(i2).steps;\n        } else {\n            if (path1.at(i1).dir\
    \ != path2.at(i2).dir) break;\n            T steps = std::min(step1, step2);\n\
    \            step1 -= steps;\n            step2 -= steps;\n\n            if (ret_path.empty()\
    \ or ret_path.back().dir != path1.at(i1).dir) {\n                Move move{path1.at(i1).dir,\
    \ steps};\n                ret_path.push_back(move);\n            } else {\n \
    \               ret_path.back().steps += steps;\n            }\n        }\n  \
    \  }\n\n    return ret_path;\n}\n\n} // namespace SternBrocotTree\n"
  dependsOn: []
  isVerificationFile: false
  path: number/stern_brocot_tree.hpp
  requiredBy: []
  timestamp: '2023-12-26 22:44:49+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - number/test/stern_brocot_tree.test.cpp
documentation_of: number/stern_brocot_tree.hpp
layout: document
title: "Stern\u2013Brocot tree"
---

Stern–Brocot tree に関連する処理・探索アルゴリズム．大半の関数は与えられる整数の対数時間で動作する．

## 使用方法

```cpp
long long a, b;  // coprime
auto path = SternBrocotTree::encode_path(a, b);  // path from root (= 1) to a/b

auto node = SternBrocotTree::decode_path(path);  // path to rational number
assert(node.num() == a);
assert(node.den() == b);

long long c, d;
auto path2 = SternBrocotTree::encode_path(c, d);
auto path_lca = SternBrocotTree::lca_path(path, path2);  // path to LCA
```

## 問題例

- [Library Checker: Stern–Brocot Tree](https://judge.yosupo.jp/problem/stern_brocot_tree)
