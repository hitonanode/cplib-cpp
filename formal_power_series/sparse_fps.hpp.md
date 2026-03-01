---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/sparse_fps_exp.test.cpp
    title: formal_power_series/test/sparse_fps_exp.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/sparse_fps_inv.test.cpp
    title: formal_power_series/test/sparse_fps_inv.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/sparse_fps_log.test.cpp
    title: formal_power_series/test/sparse_fps_log.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/sparse_fps_pow.stress.test.cpp
    title: formal_power_series/test/sparse_fps_pow.stress.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/sparse_fps_pow.test.cpp
    title: formal_power_series/test/sparse_fps_pow.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/sparse_fps_pow.yuki1939.test.cpp
    title: formal_power_series/test/sparse_fps_pow.yuki1939.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/sparse_fps_sqrt.test.cpp
    title: formal_power_series/test/sparse_fps_sqrt.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://github.com/yosupo06/library-checker-problems/issues/767#issuecomment-1166414020
  bundledCode: "#line 2 \"formal_power_series/sparse_fps.hpp\"\n#include <algorithm>\n\
    #include <cassert>\n#include <concepts>\n#include <optional>\n#include <utility>\n\
    #include <vector>\n\nnamespace sparse_fps {\n// https://github.com/yosupo06/library-checker-problems/issues/767#issuecomment-1166414020\n\
    \n// Calculate f(x)^k up to x^max_deg\ntemplate <typename Vec>\n    requires std::derived_from<Vec,\
    \ std::vector<typename Vec::value_type>>\nVec pow(const Vec &f, int max_deg, long\
    \ long k) {\n    using T = typename Vec::value_type;\n    assert(k >= 0);\n\n\
    \    Vec ret(max_deg + 1);\n\n    if (k == 0) {\n        ret[0] = T{1};\n    \
    \    return ret;\n    }\n\n    std::vector<std::pair<int, T>> terms;\n    int\
    \ d0 = 0;\n    while (d0 < int(f.size()) and d0 <= max_deg and f[d0] == T()) ++d0;\n\
    \    if (d0 == int(f.size()) or d0 > max_deg) return ret;\n\n    if (d0 and max_deg\
    \ / d0 < k) return ret;\n\n    for (int d = d0 + 1; d < std::min<int>(max_deg\
    \ + 1, f.size()); ++d) {\n        if (f[d] != T{}) terms.emplace_back(d - d0,\
    \ f[d]);\n    }\n\n    const int bias = d0 * k;\n    ret[bias] = f[d0].pow(k);\n\
    \    const T fd0inv = 1 / f[d0];\n    for (int d = 0; bias + d + 1 < int(ret.size());\
    \ ++d) {\n        // Compare [x^d](k f'g - fg')\n        T tmp{0};\n        for\
    \ (auto [i, fi] : terms) {\n            int j = d - i;\n            if (0 <= j)\
    \ tmp -= fi * ret[bias + j + 1] * (j + 1);\n            j = d - (i - 1);\n   \
    \         if (0 <= j) tmp += fi * i * ret[bias + j] * T(k);\n        }\n     \
    \   ret[bias + d + 1] = tmp * fd0inv / (d + 1);\n    }\n\n    return ret;\n}\n\
    \ntemplate <typename Vec>\n    requires std::derived_from<Vec, std::vector<typename\
    \ Vec::value_type>>\nVec inv(const Vec &f, int max_deg) {\n    using T = typename\
    \ Vec::value_type;\n    assert(!f.empty() and f[0] != T{0});\n\n    Vec ret(max_deg\
    \ + 1);\n\n    std::vector<std::pair<int, T>> terms;\n    for (int d = 1; d <\
    \ (int)f.size() and d <= max_deg; ++d) {\n        if (f[d] != T{}) terms.emplace_back(d,\
    \ f[d]);\n    }\n\n    const T f0inv = f[0].inv();\n    ret[0] = f0inv;\n\n  \
    \  for (int d = 1; d <= max_deg; ++d) {\n        T tmp{0};\n        for (auto\
    \ [i, fi] : terms) {\n            if (i > d) break;\n            tmp -= fi * ret[d\
    \ - i];\n        }\n        ret[d] = tmp * f0inv;\n    }\n\n    return ret;\n\
    }\n\ntemplate <typename Vec>\n    requires std::derived_from<Vec, std::vector<typename\
    \ Vec::value_type>>\nVec log(const Vec &f, int max_deg) {\n    using T = typename\
    \ Vec::value_type;\n    assert(!f.empty() and f[0] != T{0});\n\n    const auto\
    \ inv = sparse_fps::inv(f, max_deg);\n\n    std::vector<std::pair<int, T>> df_terms;\n\
    \    for (int d = 1; d < (int)f.size() and d <= max_deg; ++d) {\n        if (f[d]\
    \ != T{}) df_terms.emplace_back(d - 1, f[d] * T{d});\n    }\n\n    Vec ret(max_deg\
    \ + 1);\n\n    for (int d = 0; d < max_deg; ++d) {\n        for (auto [i, fi]\
    \ : df_terms) {\n            const int j = d + i + 1;\n            if (j > max_deg)\
    \ break;\n            ret[j] += inv[d] * fi * T{j}.inv();\n        }\n    }\n\n\
    \    return ret;\n}\n\ntemplate <typename Vec>\n    requires std::derived_from<Vec,\
    \ std::vector<typename Vec::value_type>>\nVec exp(const Vec &f, int max_deg) {\n\
    \    using T = typename Vec::value_type;\n    assert(f.empty() or f[0] == T{0});\n\
    \n    std::vector<std::pair<int, T>> df_terms;\n    for (int d = 1; d < (int)f.size()\
    \ and d <= max_deg; ++d) {\n        if (f[d] != T{}) df_terms.emplace_back(d -\
    \ 1, f[d] * T{d});\n    }\n\n    Vec ret(max_deg + 1);\n    ret[0] = T{1};\n \
    \   // F' = F * f'\n    for (int d = 1; d <= max_deg; ++d) {\n        T tmp{0};\n\
    \        for (auto [i, dfi] : df_terms) {\n            if (i > d - 1) break;\n\
    \            tmp += dfi * ret[d - 1 - i];\n        }\n        ret[d] = tmp * T{d}.inv();\n\
    \    }\n\n    return ret;\n}\n\ntemplate <typename Vec>\n    requires std::derived_from<Vec,\
    \ std::vector<typename Vec::value_type>>\nstd::optional<Vec> sqrt(const Vec &f,\
    \ int max_deg) {\n    using T = typename Vec::value_type;\n\n    Vec ret(max_deg\
    \ + 1);\n\n    int d0 = 0;\n    while (d0 < int(f.size()) and d0 <= max_deg and\
    \ f[d0] == T{}) ++d0;\n    if (d0 == int(f.size()) or d0 > max_deg) return ret;\n\
    \    if (d0 & 1) return std::nullopt;\n\n    const T sqrtf0 = f[d0].sqrt();\n\
    \    if (sqrtf0 == T{}) return std::nullopt;\n\n    std::vector<std::pair<int,\
    \ T>> terms;\n    const T fd0inv = 1 / f[d0];\n    for (int d = d0 + 1; d < std::min<int>(max_deg\
    \ + 1, f.size()); ++d) {\n        if (f[d] != T{}) terms.emplace_back(d - d0,\
    \ f[d] * fd0inv);\n    }\n\n    const int bias = d0 / 2;\n    const T inv2 = T{2}.inv();\n\
    \    ret[bias] = sqrtf0;\n    for (int d = 0; bias + d + 1 < int(ret.size());\
    \ ++d) {\n        T tmp{0};\n        for (auto [i, fi] : terms) {\n          \
    \  if (i > d + 1) break;\n            int j = d - i;\n            if (0 <= j)\
    \ tmp -= fi * ret[bias + j + 1] * (j + 1);\n            j = d - (i - 1);\n   \
    \         if (0 <= j) tmp += fi * i * ret[bias + j] * inv2;\n        }\n     \
    \   ret[bias + d + 1] = tmp / (d + 1);\n    }\n\n    return ret;\n}\n\n} // namespace\
    \ sparse_fps\n"
  code: "#pragma once\n#include <algorithm>\n#include <cassert>\n#include <concepts>\n\
    #include <optional>\n#include <utility>\n#include <vector>\n\nnamespace sparse_fps\
    \ {\n// https://github.com/yosupo06/library-checker-problems/issues/767#issuecomment-1166414020\n\
    \n// Calculate f(x)^k up to x^max_deg\ntemplate <typename Vec>\n    requires std::derived_from<Vec,\
    \ std::vector<typename Vec::value_type>>\nVec pow(const Vec &f, int max_deg, long\
    \ long k) {\n    using T = typename Vec::value_type;\n    assert(k >= 0);\n\n\
    \    Vec ret(max_deg + 1);\n\n    if (k == 0) {\n        ret[0] = T{1};\n    \
    \    return ret;\n    }\n\n    std::vector<std::pair<int, T>> terms;\n    int\
    \ d0 = 0;\n    while (d0 < int(f.size()) and d0 <= max_deg and f[d0] == T()) ++d0;\n\
    \    if (d0 == int(f.size()) or d0 > max_deg) return ret;\n\n    if (d0 and max_deg\
    \ / d0 < k) return ret;\n\n    for (int d = d0 + 1; d < std::min<int>(max_deg\
    \ + 1, f.size()); ++d) {\n        if (f[d] != T{}) terms.emplace_back(d - d0,\
    \ f[d]);\n    }\n\n    const int bias = d0 * k;\n    ret[bias] = f[d0].pow(k);\n\
    \    const T fd0inv = 1 / f[d0];\n    for (int d = 0; bias + d + 1 < int(ret.size());\
    \ ++d) {\n        // Compare [x^d](k f'g - fg')\n        T tmp{0};\n        for\
    \ (auto [i, fi] : terms) {\n            int j = d - i;\n            if (0 <= j)\
    \ tmp -= fi * ret[bias + j + 1] * (j + 1);\n            j = d - (i - 1);\n   \
    \         if (0 <= j) tmp += fi * i * ret[bias + j] * T(k);\n        }\n     \
    \   ret[bias + d + 1] = tmp * fd0inv / (d + 1);\n    }\n\n    return ret;\n}\n\
    \ntemplate <typename Vec>\n    requires std::derived_from<Vec, std::vector<typename\
    \ Vec::value_type>>\nVec inv(const Vec &f, int max_deg) {\n    using T = typename\
    \ Vec::value_type;\n    assert(!f.empty() and f[0] != T{0});\n\n    Vec ret(max_deg\
    \ + 1);\n\n    std::vector<std::pair<int, T>> terms;\n    for (int d = 1; d <\
    \ (int)f.size() and d <= max_deg; ++d) {\n        if (f[d] != T{}) terms.emplace_back(d,\
    \ f[d]);\n    }\n\n    const T f0inv = f[0].inv();\n    ret[0] = f0inv;\n\n  \
    \  for (int d = 1; d <= max_deg; ++d) {\n        T tmp{0};\n        for (auto\
    \ [i, fi] : terms) {\n            if (i > d) break;\n            tmp -= fi * ret[d\
    \ - i];\n        }\n        ret[d] = tmp * f0inv;\n    }\n\n    return ret;\n\
    }\n\ntemplate <typename Vec>\n    requires std::derived_from<Vec, std::vector<typename\
    \ Vec::value_type>>\nVec log(const Vec &f, int max_deg) {\n    using T = typename\
    \ Vec::value_type;\n    assert(!f.empty() and f[0] != T{0});\n\n    const auto\
    \ inv = sparse_fps::inv(f, max_deg);\n\n    std::vector<std::pair<int, T>> df_terms;\n\
    \    for (int d = 1; d < (int)f.size() and d <= max_deg; ++d) {\n        if (f[d]\
    \ != T{}) df_terms.emplace_back(d - 1, f[d] * T{d});\n    }\n\n    Vec ret(max_deg\
    \ + 1);\n\n    for (int d = 0; d < max_deg; ++d) {\n        for (auto [i, fi]\
    \ : df_terms) {\n            const int j = d + i + 1;\n            if (j > max_deg)\
    \ break;\n            ret[j] += inv[d] * fi * T{j}.inv();\n        }\n    }\n\n\
    \    return ret;\n}\n\ntemplate <typename Vec>\n    requires std::derived_from<Vec,\
    \ std::vector<typename Vec::value_type>>\nVec exp(const Vec &f, int max_deg) {\n\
    \    using T = typename Vec::value_type;\n    assert(f.empty() or f[0] == T{0});\n\
    \n    std::vector<std::pair<int, T>> df_terms;\n    for (int d = 1; d < (int)f.size()\
    \ and d <= max_deg; ++d) {\n        if (f[d] != T{}) df_terms.emplace_back(d -\
    \ 1, f[d] * T{d});\n    }\n\n    Vec ret(max_deg + 1);\n    ret[0] = T{1};\n \
    \   // F' = F * f'\n    for (int d = 1; d <= max_deg; ++d) {\n        T tmp{0};\n\
    \        for (auto [i, dfi] : df_terms) {\n            if (i > d - 1) break;\n\
    \            tmp += dfi * ret[d - 1 - i];\n        }\n        ret[d] = tmp * T{d}.inv();\n\
    \    }\n\n    return ret;\n}\n\ntemplate <typename Vec>\n    requires std::derived_from<Vec,\
    \ std::vector<typename Vec::value_type>>\nstd::optional<Vec> sqrt(const Vec &f,\
    \ int max_deg) {\n    using T = typename Vec::value_type;\n\n    Vec ret(max_deg\
    \ + 1);\n\n    int d0 = 0;\n    while (d0 < int(f.size()) and d0 <= max_deg and\
    \ f[d0] == T{}) ++d0;\n    if (d0 == int(f.size()) or d0 > max_deg) return ret;\n\
    \    if (d0 & 1) return std::nullopt;\n\n    const T sqrtf0 = f[d0].sqrt();\n\
    \    if (sqrtf0 == T{}) return std::nullopt;\n\n    std::vector<std::pair<int,\
    \ T>> terms;\n    const T fd0inv = 1 / f[d0];\n    for (int d = d0 + 1; d < std::min<int>(max_deg\
    \ + 1, f.size()); ++d) {\n        if (f[d] != T{}) terms.emplace_back(d - d0,\
    \ f[d] * fd0inv);\n    }\n\n    const int bias = d0 / 2;\n    const T inv2 = T{2}.inv();\n\
    \    ret[bias] = sqrtf0;\n    for (int d = 0; bias + d + 1 < int(ret.size());\
    \ ++d) {\n        T tmp{0};\n        for (auto [i, fi] : terms) {\n          \
    \  if (i > d + 1) break;\n            int j = d - i;\n            if (0 <= j)\
    \ tmp -= fi * ret[bias + j + 1] * (j + 1);\n            j = d - (i - 1);\n   \
    \         if (0 <= j) tmp += fi * i * ret[bias + j] * inv2;\n        }\n     \
    \   ret[bias + d + 1] = tmp / (d + 1);\n    }\n\n    return ret;\n}\n\n} // namespace\
    \ sparse_fps\n"
  dependsOn: []
  isVerificationFile: false
  path: formal_power_series/sparse_fps.hpp
  requiredBy: []
  timestamp: '2026-03-01 22:00:22+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - formal_power_series/test/sparse_fps_inv.test.cpp
  - formal_power_series/test/sparse_fps_pow.stress.test.cpp
  - formal_power_series/test/sparse_fps_log.test.cpp
  - formal_power_series/test/sparse_fps_pow.test.cpp
  - formal_power_series/test/sparse_fps_exp.test.cpp
  - formal_power_series/test/sparse_fps_pow.yuki1939.test.cpp
  - formal_power_series/test/sparse_fps_sqrt.test.cpp
documentation_of: formal_power_series/sparse_fps.hpp
layout: document
title: "Sparse formal power series \uFF08\u758E\u306A\u5F62\u5F0F\u7684\u51AA\u7D1A\
  \u6570\u306E\u6F14\u7B97\uFF09"
---

疎な形式的冪級数 $f(x)$ に対して，$x^N$ までの累乗・逆元・対数・指数関数・平方根を計算する．$f(x)$ の非零項数を $K$ として，いずれも $O(NK)$ で動作する．

## 使用方法

名前空間 `sparse_fps` に以下の関数が定義されている．テンプレート引数 `Vec` は `std::vector<T>` を継承した型で，`T` は体の元として `+`, `-`, `*`, `/`, `pow`, `inv` 等をサポートする必要がある（典型的には ModInt）．

### `sparse_fps::pow`

```cpp
Vec sparse_fps::pow(const Vec &f, int max_deg, long long k);
```

$f(x)^k \bmod x^{\mathrm{max\\_deg}+1}$ を計算する．$k \ge 0$．

### `sparse_fps::inv`

```cpp
Vec sparse_fps::inv(const Vec &f, int max_deg);
```

$1 / f(x) \bmod x^{\mathrm{max\\_deg}+1}$ を計算する．$f_0 \neq 0$ が必要．

### `sparse_fps::log`

```cpp
Vec sparse_fps::log(const Vec &f, int max_deg);
```

$\log f(x) \bmod x^{\mathrm{max\\_deg}+1}$ を計算する．$f_0 \neq 0$ が必要．

### `sparse_fps::exp`

```cpp
Vec sparse_fps::exp(const Vec &f, int max_deg);
```

$\exp f(x) \bmod x^{\mathrm{max\\_deg}+1}$ を計算する．$f_0 = 0$ が必要．

### `sparse_fps::sqrt`

```cpp
std::optional<Vec> sparse_fps::sqrt(const Vec &f, int max_deg);
```

$\sqrt{f(x)} \bmod x^{\mathrm{max\\_deg}+1}$ を計算する．最小次数の非零項 $f_{d_0}$ について $d_0$ が偶数かつ $f_{d_0}$ が平方根を持つ必要がある．解が存在しない場合は `std::nullopt` を返す．

## 問題例

- [Pow of Formal Power Series (Sparse) - Library Checker](https://judge.yosupo.jp/problem/pow_of_formal_power_series_sparse)
- [No.1939 Numbered Colorful Balls - yukicoder](https://yukicoder.me/problems/no/1939)
- [Codeforces Round 1058 (Div. 1) E. Super-Short-Polynomial-San](https://codeforces.com/contest/2159/problem/E)
- [Inv of Formal Power Series (Sparse) - Library Checker](https://judge.yosupo.jp/problem/inv_of_formal_power_series_sparse)
- [Log of Formal Power Series (Sparse) - Library Checker](https://judge.yosupo.jp/problem/log_of_formal_power_series_sparse)
- [Exp of Formal Power Series (Sparse) - Library Checker](https://judge.yosupo.jp/problem/exp_of_formal_power_series_sparse)
- [Sqrt of Formal Power Series (Sparse) - Library Checker](https://judge.yosupo.jp/problem/sqrt_of_formal_power_series_sparse)

## リンク

- [A problem collection of ODE and differential technique - Codeforces](https://codeforces.com/blog/entry/76447)
- [library-checker-problems #767 (comment)](https://github.com/yosupo06/library-checker-problems/issues/767#issuecomment-1166414020)
