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
    - https://codeforces.com/blog/entry/143059
  bundledCode: "#line 2 \"utilities/static_bitset_size_dispatch.hpp\"\n\n// https://codeforces.com/blog/entry/143059\n\
    template <unsigned long long sz = 1>\nvoid static_bitset_size_dispatch(unsigned\
    \ long long n, auto &&callback) {\n    if constexpr (sz > (1ULL << 30)) {\n  \
    \      return;\n    } else if (n > sz) {\n        static_bitset_size_dispatch<((sz\
    \ * 3 + 1) / 2)>(n, callback); // tune here\n    } else {\n        callback.template\
    \ operator()<sz>();\n    }\n}\n/* Usage:\nint ret = 0;\nstatic_bitset_size_dispatch(n,\
    \ [&]<size_t BS_SIZE>() {\n    std::bitset<BS_SIZE> bs;\n    // do something...\n\
    \    // ret = ...;\n});\n*/\n"
  code: "#pragma once\n\n// https://codeforces.com/blog/entry/143059\ntemplate <unsigned\
    \ long long sz = 1>\nvoid static_bitset_size_dispatch(unsigned long long n, auto\
    \ &&callback) {\n    if constexpr (sz > (1ULL << 30)) {\n        return;\n   \
    \ } else if (n > sz) {\n        static_bitset_size_dispatch<((sz * 3 + 1) / 2)>(n,\
    \ callback); // tune here\n    } else {\n        callback.template operator()<sz>();\n\
    \    }\n}\n/* Usage:\nint ret = 0;\nstatic_bitset_size_dispatch(n, [&]<size_t\
    \ BS_SIZE>() {\n    std::bitset<BS_SIZE> bs;\n    // do something...\n    // ret\
    \ = ...;\n});\n*/\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/static_bitset_size_dispatch.hpp
  requiredBy: []
  timestamp: '2026-03-01 21:22:12+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utilities/static_bitset_size_dispatch.hpp
layout: document
title: "Static bitset size dispatch \uFF08\u30B3\u30F3\u30D1\u30A4\u30EB\u6642 bitset\
  \ \u30B5\u30A4\u30BA\u306E\u5B9F\u884C\u6642\u5206\u5C90\uFF09"
---

実行時に決まるサイズ $n$ に対して，$n$ 以上の最小のコンパイル時定数をテンプレート引数として `std::bitset` 等を利用できるようにするユーティリティ．サイズの候補は $1$ から約 $\alpha = 1.5$ 倍ずつ増加し，$2^{30}$ を上限とする．

## 使用方法

```cpp
static_bitset_size_dispatch(n, [&]<size_t BS_SIZE>() {
    std::bitset<BS_SIZE> bs;
    // BS_SIZE >= n が保証される
});
```

- `n`: 必要なビットサイズ（`unsigned long long`）．
- `callback`: テンプレート引数 `BS_SIZE`（`n` 以上のコンパイル時定数）を受け取るジェネリックラムダ．

コンパイル時にサイズ候補ごとのインスタンスが生成される．増加率を $\alpha$ として， `n` がおおよそ $2^{30} / \alpha$ 以上の場合は何も実行されない可能性がある．

## 問題例

- [Codeforces Round 1079 (Div. 1) E2. Fuzzy Concatenation (Hard version)](https://codeforces.com/contest/2196/problem/E2)
  - [Submission #362639741 - Codeforces](https://codeforces.com/contest/2196/submission/362639741)

## リンク

- [Variable size bitset (kind of) - Codeforces](https://codeforces.com/blog/entry/143059)
