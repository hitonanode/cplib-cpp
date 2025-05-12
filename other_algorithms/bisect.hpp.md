---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: other_algorithms/test/bisect_yuki2352.test.cpp
    title: other_algorithms/test/bisect_yuki2352.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"other_algorithms/bisect.hpp\"\n#include <bit>\n#include\
    \ <functional>\n#include <numeric>\n\n// Calculate next point to check in floating\
    \ point \"binary\" search\ndouble bisect_mid_fp(double a, double b) {\n    auto\
    \ encode = [&](double x) -> unsigned long long {\n        auto tmp = std::bit_cast<unsigned\
    \ long long>(x);\n        return x >= 0 ? (tmp ^ (1ULL << 63)) : ~tmp;\n    };\n\
    \n    auto decode = [&](unsigned long long x) -> double {\n        auto tmp =\
    \ (x >> 63) ? (x ^ (1ULL << 63)) : ~x;\n        return std::bit_cast<double>(tmp);\n\
    \    };\n\n    unsigned long long tmp = std::midpoint(encode(a), encode(b));\n\
    \n    return decode(tmp);\n}\n\n// Binary search\n// Maintain f(ok) = true and\
    \ f(ng) = false and return (ok, ng)\n// Final (ok, ng) satisfies |ok - ng| <=\
    \ abs_tol\ntemplate <class T> auto bisect(T ok, T ng, const std::function<bool(T)>\
    \ &f, T abs_tol = T()) {\n    struct Result {\n        T ok, ng;\n    };\n\n \
    \   while (true) {\n        T mid = std::is_floating_point<T>::value ? bisect_mid_fp(ok,\
    \ ng) : std::midpoint(ok, ng);\n        if (mid == ok or mid == ng) break;\n \
    \       (f(mid) ? ok : ng) = mid;\n        if (ok - ng <= abs_tol and ng - ok\
    \ <= abs_tol) break;\n    }\n\n    return Result{ok, ng};\n}\n"
  code: "#pragma once\n#include <bit>\n#include <functional>\n#include <numeric>\n\
    \n// Calculate next point to check in floating point \"binary\" search\ndouble\
    \ bisect_mid_fp(double a, double b) {\n    auto encode = [&](double x) -> unsigned\
    \ long long {\n        auto tmp = std::bit_cast<unsigned long long>(x);\n    \
    \    return x >= 0 ? (tmp ^ (1ULL << 63)) : ~tmp;\n    };\n\n    auto decode =\
    \ [&](unsigned long long x) -> double {\n        auto tmp = (x >> 63) ? (x ^ (1ULL\
    \ << 63)) : ~x;\n        return std::bit_cast<double>(tmp);\n    };\n\n    unsigned\
    \ long long tmp = std::midpoint(encode(a), encode(b));\n\n    return decode(tmp);\n\
    }\n\n// Binary search\n// Maintain f(ok) = true and f(ng) = false and return (ok,\
    \ ng)\n// Final (ok, ng) satisfies |ok - ng| <= abs_tol\ntemplate <class T> auto\
    \ bisect(T ok, T ng, const std::function<bool(T)> &f, T abs_tol = T()) {\n   \
    \ struct Result {\n        T ok, ng;\n    };\n\n    while (true) {\n        T\
    \ mid = std::is_floating_point<T>::value ? bisect_mid_fp(ok, ng) : std::midpoint(ok,\
    \ ng);\n        if (mid == ok or mid == ng) break;\n        (f(mid) ? ok : ng)\
    \ = mid;\n        if (ok - ng <= abs_tol and ng - ok <= abs_tol) break;\n    }\n\
    \n    return Result{ok, ng};\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: other_algorithms/bisect.hpp
  requiredBy: []
  timestamp: '2025-05-06 20:50:55+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - other_algorithms/test/bisect_yuki2352.test.cpp
documentation_of: other_algorithms/bisect.hpp
layout: document
title: "Binary search \uFF08\u4E8C\u5206\u63A2\u7D22\uFF09"
---

二分探索を行う．
探索範囲が浮動小数点数で与えられた場合は， IEEE 754 の binary64 形式を 64 bit 整数だと思って上の桁から順に値を定めていくような挙動を示す（よって必ず 64 回以下のループで実行が完了する）．

## 使用方法

### `double bisect_mid_fp(double a, double b)`

64 bit 浮動小数点数の区間に対する二分探索で，現在の探索範囲の両端の値をもとに次に探索すべき値を返す．
引数 `a` や `b` は NaN でなければよい（非正規化数や無限でもよい）．
動作のイメージとして `ok` と `ng` がともに正の場合は幾何平均くらいのオーダーの値を返す．

### `template <class T> auto bisect(T ok, T ng, const std::function<bool(T)> &f, T abs_tol = T())`

二分探索を行い，条件を満たす値を求める関数．

- `ok` : `f(x) == true` を満たすことがわかっている `x` の値．
- `ng` : `f(x) == false` を満たすことがわかっている `x` の値．
- `f` : `T` 型の引数をとり，条件を満たす場合 `true` を返す判定関数．
- `abs_tol` : 許容絶対誤差． `ok` と `ng` の差がこの値以下になったら探索を打ち切る（デフォルトは `T()` ）．
- 戻り値 : `ok` および `ng` の最終値を含む `Result` 構造体．

## 問題例

- [No.2352 Sharpened Knife in Fall - yukicoder](https://yukicoder.me/problems/no/2352)
