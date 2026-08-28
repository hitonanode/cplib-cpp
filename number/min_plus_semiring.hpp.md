---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/test/linalg_min_plus_semiring.yuki1780.test.cpp
    title: linear_algebra_matrix/test/linalg_min_plus_semiring.yuki1780.test.cpp
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/test/linalg_semirings.yuki1340.test.cpp
    title: linear_algebra_matrix/test/linalg_semirings.yuki1340.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://yukicoder.me/problems/no/1340
  bundledCode: "#line 1 \"number/min_plus_semiring.hpp\"\n#include <limits>\n\n//\
    \ min-plus \u534A\u74B0\u30FB\u30C8\u30ED\u30D4\u30AB\u30EB\u534A\u74B0\uFF08\u52A0\
    \u6CD5\u304C min, \u4E57\u6CD5\u304C plus, \u96F6\u5143\u304C INF, \u5358\u4F4D\
    \u5143\u304C 0\uFF09\n// INF = numeric_limits<T>::max() / 2 \u3092\u8D85\u3048\
    \u305F\u3089 INF \u306B clamp \u3059\u308B\n// Verified: https://yukicoder.me/problems/no/1340\n\
    template <class T> struct min_plus_semiring {\n    T val;\n    static const T\
    \ _T_inf() {\n        static_assert(std::numeric_limits<T>::max() > 0,\n     \
    \                 \"std::numeric_limits<>::max() must be properly defined\");\n\
    \        return std::numeric_limits<T>::max() / 2;\n    }\n    min_plus_semiring()\
    \ : val(_T_inf()) {}\n    min_plus_semiring(T x) : val(x) {}\n    static min_plus_semiring\
    \ id() { return min_plus_semiring(0); }\n    min_plus_semiring operator+(const\
    \ min_plus_semiring &r) const {\n        return (this->val > r.val ? r.val : this->val);\n\
    \    }\n    min_plus_semiring &operator+=(const min_plus_semiring &r) { return\
    \ *this = *this + r; }\n    min_plus_semiring operator*(const min_plus_semiring\
    \ &r) const {\n        if (this->val == _T_inf() or r.val == _T_inf()) return\
    \ min_plus_semiring();\n        T tmp = this->val + r.val; // Watch out for overflow\n\
    \        return _T_inf() < tmp ? min_plus_semiring() : min_plus_semiring(tmp);\n\
    \    }\n    min_plus_semiring &operator*=(const min_plus_semiring &r) { return\
    \ *this = *this * r; }\n    bool operator==(const min_plus_semiring &r) const\
    \ { return this->val == r.val; }\n    bool operator!=(const min_plus_semiring\
    \ &r) const { return !(*this == r); }\n    bool operator<(const min_plus_semiring\
    \ &x) const { return this->val < x.val; }\n    bool operator>(const min_plus_semiring\
    \ &x) const { return this->val > x.val; }\n    template <class OStream> friend\
    \ OStream &operator<<(OStream &os, const min_plus_semiring &x) {\n        return\
    \ os << x.val;\n    }\n};\n"
  code: "#include <limits>\n\n// min-plus \u534A\u74B0\u30FB\u30C8\u30ED\u30D4\u30AB\
    \u30EB\u534A\u74B0\uFF08\u52A0\u6CD5\u304C min, \u4E57\u6CD5\u304C plus, \u96F6\
    \u5143\u304C INF, \u5358\u4F4D\u5143\u304C 0\uFF09\n// INF = numeric_limits<T>::max()\
    \ / 2 \u3092\u8D85\u3048\u305F\u3089 INF \u306B clamp \u3059\u308B\n// Verified:\
    \ https://yukicoder.me/problems/no/1340\ntemplate <class T> struct min_plus_semiring\
    \ {\n    T val;\n    static const T _T_inf() {\n        static_assert(std::numeric_limits<T>::max()\
    \ > 0,\n                      \"std::numeric_limits<>::max() must be properly\
    \ defined\");\n        return std::numeric_limits<T>::max() / 2;\n    }\n    min_plus_semiring()\
    \ : val(_T_inf()) {}\n    min_plus_semiring(T x) : val(x) {}\n    static min_plus_semiring\
    \ id() { return min_plus_semiring(0); }\n    min_plus_semiring operator+(const\
    \ min_plus_semiring &r) const {\n        return (this->val > r.val ? r.val : this->val);\n\
    \    }\n    min_plus_semiring &operator+=(const min_plus_semiring &r) { return\
    \ *this = *this + r; }\n    min_plus_semiring operator*(const min_plus_semiring\
    \ &r) const {\n        if (this->val == _T_inf() or r.val == _T_inf()) return\
    \ min_plus_semiring();\n        T tmp = this->val + r.val; // Watch out for overflow\n\
    \        return _T_inf() < tmp ? min_plus_semiring() : min_plus_semiring(tmp);\n\
    \    }\n    min_plus_semiring &operator*=(const min_plus_semiring &r) { return\
    \ *this = *this * r; }\n    bool operator==(const min_plus_semiring &r) const\
    \ { return this->val == r.val; }\n    bool operator!=(const min_plus_semiring\
    \ &r) const { return !(*this == r); }\n    bool operator<(const min_plus_semiring\
    \ &x) const { return this->val < x.val; }\n    bool operator>(const min_plus_semiring\
    \ &x) const { return this->val > x.val; }\n    template <class OStream> friend\
    \ OStream &operator<<(OStream &os, const min_plus_semiring &x) {\n        return\
    \ os << x.val;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: number/min_plus_semiring.hpp
  requiredBy: []
  timestamp: '2022-01-25 23:19:52+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - linear_algebra_matrix/test/linalg_min_plus_semiring.yuki1780.test.cpp
  - linear_algebra_matrix/test/linalg_semirings.yuki1340.test.cpp
documentation_of: number/min_plus_semiring.hpp
layout: document
title: "Min-plus semiring / tropical semiring\uFF08(min, +) \u534A\u74B0\u30FB\u30C8\
  \u30ED\u30D4\u30AB\u30EB\u534A\u74B0\uFF09"
---

加法を `min`，乗法を `+` で定義した半環．零元は `std::numeric_limits<T>::max() / 2` （オーバーフロー回避），単位元は `0` となっていることに注意．例えば距離行列に載せて行列積をとることで，パス長最小化等に使用できる．

なお，（当たり前ではあるが）零元と任意の値（正負に関わらず）との乗算の結果は零元になることに注意．
## 使用例

```cpp
using R = min_plus_semiring<int>;
matrix<R> mat(N, N);

while (M--) {
    int a, b;
    cin >> a >> b;
    mat[b][a] = 0;
}

std::vector<R> initvec(N, R()); // R() == INF
initvec[0] = R::id(); // R::id() == 0
auto vec = mat.pow_vec(T, initvec);
cout << count(vec.begin(), vec.end(), R(0)) << '\n';
```

## 問題例

- [No.1340 おーじ君をさがせ - yukicoder](https://yukicoder.me/problems/no/1340)
- [No.1780 [Cherry Anniversary] 真冬に咲く26の櫻の木 - yukicoder](https://yukicoder.me/problems/no/1780)
