---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: utilities/test/multidim_index.zeta.test.cpp
    title: utilities/test/multidim_index.zeta.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"utilities/multidim_index.hpp\"\n#include <cassert>\n#include\
    \ <vector>\n\n// n-dimentional index <-> 1-dimentional index converter\n// [a_0,\
    \ ..., a_{dim - 1}] <-> a_0 + a_1 * size_0 + ... + a_{dim - 1} * (size_0 * ...\
    \ * size_{dim - 2})\ntemplate <class T = int> struct multidim_index {\n    int\
    \ dim = 0;\n    T _size = 1;\n    std::vector<T> sizes;\n    std::vector<T> weights;\n\
    \n    multidim_index() = default;\n\n    explicit multidim_index(const std::vector<T>\
    \ &sizes)\n        : dim(sizes.size()), sizes(sizes), weights(dim, T(1)) {\n \
    \       for (int d = 0; d < (int)sizes.size(); ++d) {\n            assert(sizes.at(d)\
    \ > 0);\n            _size *= sizes.at(d);\n            if (d >= 1) weights.at(d)\
    \ = weights.at(d - 1) * sizes.at(d - 1);\n        }\n    }\n\n    T size() const\
    \ { return _size; }\n\n    T flat_index(const std::vector<T> &encoded_vec) const\
    \ {\n        assert((int)encoded_vec.size() == (int)sizes.size());\n        T\
    \ ret = 0;\n        for (int d = 0; d < (int)sizes.size(); ++d) {\n          \
    \  assert(0 <= encoded_vec.at(d) and encoded_vec.at(d) < sizes.at(d));\n     \
    \       ret += encoded_vec.at(d) * weights.at(d);\n        }\n        return ret;\n\
    \    }\n\n    std::vector<T> encode(T flat_index) const {\n        assert(0 <=\
    \ flat_index and flat_index < size());\n        std::vector<T> ret(sizes.size());\n\
    \        for (int d = (int)sizes.size() - 1; d >= 0; --d) {\n            ret.at(d)\
    \ = flat_index / weights.at(d);\n            flat_index %= weights.at(d);\n  \
    \      }\n        return ret;\n    }\n\n    template <class F> void lo_to_hi(F\
    \ f) {\n        for (int d = 0; d < (int)sizes.size(); ++d) {\n            if\
    \ (sizes.at(d) == 1) continue;\n\n            T i = 0;\n            std::vector<T>\
    \ ivec(sizes.size());\n\n            int cur = sizes.size();\n\n            while\
    \ (true) {\n                f(i, i + weights.at(d));\n                --cur;\n\
    \n                while (cur >= 0 and ivec.at(cur) + 1 == sizes.at(cur) - (cur\
    \ == d)) {\n                    i -= ivec.at(cur) * weights.at(cur);\n       \
    \             ivec.at(cur--) = 0;\n                }\n\n                if (cur\
    \ < 0) break;\n\n                ++ivec.at(cur);\n                i += weights.at(cur);\n\
    \                cur = sizes.size();\n            }\n        }\n    }\n\n    //\
    \ Subset sum (fast zeta transform)\n    template <class U> void subset_sum(std::vector<U>\
    \ &vec) {\n        assert((T)vec.size() == size());\n        lo_to_hi([&](T lo,\
    \ T hi) { vec.at(hi) += vec.at(lo); });\n    }\n\n    // Inverse of subset sum\
    \ (fast moebius transform)\n    template <class U> void subset_sum_inv(std::vector<U>\
    \ &vec) {\n        assert((T)vec.size() == size());\n        const T s = size()\
    \ - 1;\n        lo_to_hi([&](T dummylo, T dummyhi) { vec.at(s - dummylo) -= vec.at(s\
    \ - dummyhi); });\n    }\n\n    // Superset sum (fast zeta transform)\n    template\
    \ <class U> void superset_sum(std::vector<U> &vec) {\n        assert((T)vec.size()\
    \ == size());\n        const T s = size() - 1;\n        lo_to_hi([&](T dummylo,\
    \ T dummyhi) { vec.at(s - dummyhi) += vec.at(s - dummylo); });\n    }\n\n    //\
    \ Inverse of superset sum (fast moebius transform)\n    template <class U> void\
    \ superset_sum_inv(std::vector<U> &vec) {\n        assert((T)vec.size() == size());\n\
    \        lo_to_hi([&](T lo, T hi) { vec.at(lo) -= vec.at(hi); });\n    }\n};\n"
  code: "#include <cassert>\n#include <vector>\n\n// n-dimentional index <-> 1-dimentional\
    \ index converter\n// [a_0, ..., a_{dim - 1}] <-> a_0 + a_1 * size_0 + ... + a_{dim\
    \ - 1} * (size_0 * ... * size_{dim - 2})\ntemplate <class T = int> struct multidim_index\
    \ {\n    int dim = 0;\n    T _size = 1;\n    std::vector<T> sizes;\n    std::vector<T>\
    \ weights;\n\n    multidim_index() = default;\n\n    explicit multidim_index(const\
    \ std::vector<T> &sizes)\n        : dim(sizes.size()), sizes(sizes), weights(dim,\
    \ T(1)) {\n        for (int d = 0; d < (int)sizes.size(); ++d) {\n           \
    \ assert(sizes.at(d) > 0);\n            _size *= sizes.at(d);\n            if\
    \ (d >= 1) weights.at(d) = weights.at(d - 1) * sizes.at(d - 1);\n        }\n \
    \   }\n\n    T size() const { return _size; }\n\n    T flat_index(const std::vector<T>\
    \ &encoded_vec) const {\n        assert((int)encoded_vec.size() == (int)sizes.size());\n\
    \        T ret = 0;\n        for (int d = 0; d < (int)sizes.size(); ++d) {\n \
    \           assert(0 <= encoded_vec.at(d) and encoded_vec.at(d) < sizes.at(d));\n\
    \            ret += encoded_vec.at(d) * weights.at(d);\n        }\n        return\
    \ ret;\n    }\n\n    std::vector<T> encode(T flat_index) const {\n        assert(0\
    \ <= flat_index and flat_index < size());\n        std::vector<T> ret(sizes.size());\n\
    \        for (int d = (int)sizes.size() - 1; d >= 0; --d) {\n            ret.at(d)\
    \ = flat_index / weights.at(d);\n            flat_index %= weights.at(d);\n  \
    \      }\n        return ret;\n    }\n\n    template <class F> void lo_to_hi(F\
    \ f) {\n        for (int d = 0; d < (int)sizes.size(); ++d) {\n            if\
    \ (sizes.at(d) == 1) continue;\n\n            T i = 0;\n            std::vector<T>\
    \ ivec(sizes.size());\n\n            int cur = sizes.size();\n\n            while\
    \ (true) {\n                f(i, i + weights.at(d));\n                --cur;\n\
    \n                while (cur >= 0 and ivec.at(cur) + 1 == sizes.at(cur) - (cur\
    \ == d)) {\n                    i -= ivec.at(cur) * weights.at(cur);\n       \
    \             ivec.at(cur--) = 0;\n                }\n\n                if (cur\
    \ < 0) break;\n\n                ++ivec.at(cur);\n                i += weights.at(cur);\n\
    \                cur = sizes.size();\n            }\n        }\n    }\n\n    //\
    \ Subset sum (fast zeta transform)\n    template <class U> void subset_sum(std::vector<U>\
    \ &vec) {\n        assert((T)vec.size() == size());\n        lo_to_hi([&](T lo,\
    \ T hi) { vec.at(hi) += vec.at(lo); });\n    }\n\n    // Inverse of subset sum\
    \ (fast moebius transform)\n    template <class U> void subset_sum_inv(std::vector<U>\
    \ &vec) {\n        assert((T)vec.size() == size());\n        const T s = size()\
    \ - 1;\n        lo_to_hi([&](T dummylo, T dummyhi) { vec.at(s - dummylo) -= vec.at(s\
    \ - dummyhi); });\n    }\n\n    // Superset sum (fast zeta transform)\n    template\
    \ <class U> void superset_sum(std::vector<U> &vec) {\n        assert((T)vec.size()\
    \ == size());\n        const T s = size() - 1;\n        lo_to_hi([&](T dummylo,\
    \ T dummyhi) { vec.at(s - dummyhi) += vec.at(s - dummylo); });\n    }\n\n    //\
    \ Inverse of superset sum (fast moebius transform)\n    template <class U> void\
    \ superset_sum_inv(std::vector<U> &vec) {\n        assert((T)vec.size() == size());\n\
    \        lo_to_hi([&](T lo, T hi) { vec.at(lo) -= vec.at(hi); });\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/multidim_index.hpp
  requiredBy: []
  timestamp: '2024-01-13 20:41:28+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - utilities/test/multidim_index.zeta.test.cpp
documentation_of: utilities/multidim_index.hpp
layout: document
title: Multidimensional index
---

多次元の添え字を 1 次元に潰す処理とその逆変換の実装．

## 使用方法

### 添字変換

以下のような C++ コードを実行すると，以下のような結果を得る．

```cpp
multidim_index mi({2, 3, 4});

for (int i = 0; i < mi.size(); ++i) {
    const auto vec = mi.encode(i);
    assert(mi.flat_index(vec) == i);

    cout << i << ": (";
    for (int x : vec) cout << x << ",";
    cout << ")\n";
}
```

```txt
0: (0,0,0,)
1: (1,0,0,)
2: (0,1,0,)
3: (1,1,0,)
4: (0,2,0,)
5: (1,2,0,)
6: (0,0,1,)
...
23: (1,2,3,)
```

### 累積和やその逆変換

通常の `+=` 演算子による累積和処理に関しては， `subset_sum()` / `subset_sum_inv()` （下側累積和およびその逆変換）・ `superset_sum()` / `superset_sum_inv()` （上側累積和およびその逆変換）が提供されている．

より一般の演算を行いたい場合は，ラムダ式　`f` を用意した上で `lo_to_hi(F f)` 関数を使えばよい．

## 問題例

- [AtCoder Beginner Contest 335（Sponsored by Mynavi） G - Discrete Logarithm Problems](https://atcoder.jp/contests/abc335/tasks/abc335_g)
  - $P - 1$ の正の約数全てをキーとする DP テーブルで，整序関係をもとに累積和を取る． [参考提出](https://atcoder.jp/contests/abc335/submissions/49118789)
