---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/test/upper_trinaglular_matrix.yuki3530.test.cpp
    title: linear_algebra_matrix/test/upper_trinaglular_matrix.yuki3530.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"linear_algebra_matrix/upper_triangular_matrix.hpp\"\n\n\
    #include <compare>\n\ntemplate <class T> struct UpperTriangular3d {\nprivate:\n\
    \    struct DesignatedInitializationOnly {\n    private:\n        constexpr DesignatedInitializationOnly()\
    \ = default;\n        constexpr DesignatedInitializationOnly(const DesignatedInitializationOnly\
    \ &) = default;\n        DesignatedInitializationOnly &operator=(const DesignatedInitializationOnly\
    \ &) = default;\n        friend UpperTriangular3d;\n\n    public:\n        auto\
    \ operator<=>(const DesignatedInitializationOnly &) const = default;\n    };\n\
    \n    template <class U> static constexpr U explicit_init_required() {\n     \
    \   static_assert(sizeof(U) == 0, \"all matrix entries must be explicitly initialized\"\
    );\n        return U{};\n    }\n\npublic:\n    [[no_unique_address]] DesignatedInitializationOnly\
    \ designated_initialization_only{};\n    T a00 = explicit_init_required<T>(),\
    \ a01 = explicit_init_required<T>(),\n      a02 = explicit_init_required<T>();\n\
    \    T a11 = explicit_init_required<T>(), a12 = explicit_init_required<T>();\n\
    \    T a22 = explicit_init_required<T>();\n\n    UpperTriangular3d operator*(const\
    \ UpperTriangular3d &r) const {\n        return UpperTriangular3d{\n         \
    \   .a00 = this->a00 * r.a00,\n            .a01 = this->a00 * r.a01 + this->a01\
    \ * r.a11,\n            .a02 = this->a00 * r.a02 + this->a01 * r.a12 + this->a02\
    \ * r.a22,\n            .a11 = this->a11 * r.a11,\n            .a12 = this->a11\
    \ * r.a12 + this->a12 * r.a22,\n            .a22 = this->a22 * r.a22,\n      \
    \  };\n    }\n\n    UpperTriangular3d operator-() const {\n        return UpperTriangular3d{\n\
    \            .a00 = -this->a00,\n            .a01 = -this->a01,\n            .a02\
    \ = -this->a02,\n            .a11 = -this->a11,\n            .a12 = -this->a12,\n\
    \            .a22 = -this->a22,\n        };\n    }\n\n    UpperTriangular3d operator+(const\
    \ UpperTriangular3d &r) const {\n        return UpperTriangular3d{\n         \
    \   .a00 = this->a00 + r.a00,\n            .a01 = this->a01 + r.a01,\n       \
    \     .a02 = this->a02 + r.a02,\n            .a11 = this->a11 + r.a11,\n     \
    \       .a12 = this->a12 + r.a12,\n            .a22 = this->a22 + r.a22,\n   \
    \     };\n    }\n\n    auto operator<=>(const UpperTriangular3d &) const = default;\n\
    };\n"
  code: "#pragma once\n\n#include <compare>\n\ntemplate <class T> struct UpperTriangular3d\
    \ {\nprivate:\n    struct DesignatedInitializationOnly {\n    private:\n     \
    \   constexpr DesignatedInitializationOnly() = default;\n        constexpr DesignatedInitializationOnly(const\
    \ DesignatedInitializationOnly &) = default;\n        DesignatedInitializationOnly\
    \ &operator=(const DesignatedInitializationOnly &) = default;\n        friend\
    \ UpperTriangular3d;\n\n    public:\n        auto operator<=>(const DesignatedInitializationOnly\
    \ &) const = default;\n    };\n\n    template <class U> static constexpr U explicit_init_required()\
    \ {\n        static_assert(sizeof(U) == 0, \"all matrix entries must be explicitly\
    \ initialized\");\n        return U{};\n    }\n\npublic:\n    [[no_unique_address]]\
    \ DesignatedInitializationOnly designated_initialization_only{};\n    T a00 =\
    \ explicit_init_required<T>(), a01 = explicit_init_required<T>(),\n      a02 =\
    \ explicit_init_required<T>();\n    T a11 = explicit_init_required<T>(), a12 =\
    \ explicit_init_required<T>();\n    T a22 = explicit_init_required<T>();\n\n \
    \   UpperTriangular3d operator*(const UpperTriangular3d &r) const {\n        return\
    \ UpperTriangular3d{\n            .a00 = this->a00 * r.a00,\n            .a01\
    \ = this->a00 * r.a01 + this->a01 * r.a11,\n            .a02 = this->a00 * r.a02\
    \ + this->a01 * r.a12 + this->a02 * r.a22,\n            .a11 = this->a11 * r.a11,\n\
    \            .a12 = this->a11 * r.a12 + this->a12 * r.a22,\n            .a22 =\
    \ this->a22 * r.a22,\n        };\n    }\n\n    UpperTriangular3d operator-() const\
    \ {\n        return UpperTriangular3d{\n            .a00 = -this->a00,\n     \
    \       .a01 = -this->a01,\n            .a02 = -this->a02,\n            .a11 =\
    \ -this->a11,\n            .a12 = -this->a12,\n            .a22 = -this->a22,\n\
    \        };\n    }\n\n    UpperTriangular3d operator+(const UpperTriangular3d\
    \ &r) const {\n        return UpperTriangular3d{\n            .a00 = this->a00\
    \ + r.a00,\n            .a01 = this->a01 + r.a01,\n            .a02 = this->a02\
    \ + r.a02,\n            .a11 = this->a11 + r.a11,\n            .a12 = this->a12\
    \ + r.a12,\n            .a22 = this->a22 + r.a22,\n        };\n    }\n\n    auto\
    \ operator<=>(const UpperTriangular3d &) const = default;\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: linear_algebra_matrix/upper_triangular_matrix.hpp
  requiredBy: []
  timestamp: '2026-09-05 15:19:25+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - linear_algebra_matrix/test/upper_trinaglular_matrix.yuki3530.test.cpp
documentation_of: linear_algebra_matrix/upper_triangular_matrix.hpp
layout: document
title: "Upper triangular matrix \uFF08\u5B9A\u6570\u6B21\u5143\u4E0A\u4E09\u89D2\u884C\
  \u5217\uFF09"
---

一定次元の上三角行列を表す構造体の実装．現時点では、特に $3 \times 3$ 上三角行列

$\displaystyle
\begin{pmatrix}
a_{00} & a_{01} & a_{02} \\
0      & a_{11} & a_{12} \\
0      & 0      & a_{22}
\end{pmatrix}
$

が実装されている．乗算（行列積），単項マイナス，加算，大小比較が定義されている．乗算の実装を毎回手で行わなくて済み，また一般次元の行列を使いまわすより高速に動作する．

## 使用方法

```cpp
using mint = atcoder::modint998244353;

UpperTriangular3d<mint> A{
    .a00 = 1,
    .a01 = 2,
    .a02 = 3,
    .a11 = 4,
    .a12 = 5,
    .a22 = 6,
};

UpperTriangular3d<mint> B{
    .a00 = 7,
    .a01 = 8,
    .a02 = 9,
    .a11 = 10,
    .a12 = 11,
    .a22 = 12,
};

auto C = A * B;
auto D = A + B;
auto E = -A;
```

## 問題例

- [No.3530 「」 - yukicoder](https://yukicoder.me/problems/no/3530)
