---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: string/test/rolling_hash_2d.aoj.test.cpp
    title: string/test/rolling_hash_2d.aoj.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"string/rolling_hash_2d.hpp\"\n#include <string>\n#include\
    \ <vector>\n\n\n// Rolling Hash (Rabin-Karp), 2dim\ntemplate <typename V> struct\
    \ rolling_hash_2d {\n    const V Bx, By;\n    std::vector<V> powx, powy;  // powx[i]\
    \ = Bx^i\n    std::vector<std::vector<V>> hash;\n\n    void gen_pow(int h, int\
    \ w) {\n        powx.assign(h + 1, V(1));\n        for (int i = 1; i <= h; ++i)\
    \ powx.at(i) = powx.at(i - 1) * Bx;\n        powy.assign(w + 1, V(1));\n     \
    \   for (int i = 1; i <= w; ++i) powy.at(i) = powy.at(i - 1) * By;\n    }\n\n\
    \    inline V _at(int x, int y) const noexcept {\n        if (x < 0 or x >= int(hash.size()))\
    \ return V();\n        if (y < 0 or y >= int(hash[x].size())) return V();\n  \
    \      return hash[x][y];\n    }\n\n    template <typename Int>\n    void build(const\
    \ std::vector<std::vector<Int>> &s) {\n        const int H = s.size(), W = H ?\
    \ s.at(0).size() : 0;\n        gen_pow(H, W);\n\n        hash.assign(H, std::vector<V>(W,\
    \ V()));\n        for (int i = 0; i < H; ++i) {\n            for (int j = 0; j\
    \ < W; ++j) hash[i][j] = _at(i, j - 1) * By + s[i][j];\n        }\n\n        for\
    \ (int i = 0; i < H; ++i) {\n            for (int j = 0; j < W; ++j) hash[i][j]\
    \ = hash[i][j] + _at(i - 1, j) * Bx;\n        }\n    }\n\n    template <typename\
    \ Int>\n    rolling_hash_2d(const std::vector<std::vector<Int>> &s, V bx, V by)\
    \ : Bx(bx), By(by) {\n        build(s);\n    }\n\n    rolling_hash_2d(const std::vector<std::string>\
    \ &m, V bx, V by) : Bx(bx), By(by) {\n        std::vector<std::vector<int>> v_;\n\
    \        for (const auto &s : m) {\n            v_.push_back({});\n          \
    \  for (char c : s) v_.back().push_back(int(c));\n        }\n        build(v_);\n\
    \    }\n\n    V get(int xl, int xr, int yl, int yr) const {\n        return _at(xr\
    \ - 1, yr - 1) - _at(xl - 1, yr - 1) * powx[xr - xl] -\n               _at(xr\
    \ - 1, yl - 1) * powy[yr - yl] +\n               _at(xl - 1, yl - 1) * powx[xr\
    \ - xl] * powy[yr - yl];\n    }\n};\n"
  code: "#pragma once\n#include <string>\n#include <vector>\n\n\n// Rolling Hash (Rabin-Karp),\
    \ 2dim\ntemplate <typename V> struct rolling_hash_2d {\n    const V Bx, By;\n\
    \    std::vector<V> powx, powy;  // powx[i] = Bx^i\n    std::vector<std::vector<V>>\
    \ hash;\n\n    void gen_pow(int h, int w) {\n        powx.assign(h + 1, V(1));\n\
    \        for (int i = 1; i <= h; ++i) powx.at(i) = powx.at(i - 1) * Bx;\n    \
    \    powy.assign(w + 1, V(1));\n        for (int i = 1; i <= w; ++i) powy.at(i)\
    \ = powy.at(i - 1) * By;\n    }\n\n    inline V _at(int x, int y) const noexcept\
    \ {\n        if (x < 0 or x >= int(hash.size())) return V();\n        if (y <\
    \ 0 or y >= int(hash[x].size())) return V();\n        return hash[x][y];\n   \
    \ }\n\n    template <typename Int>\n    void build(const std::vector<std::vector<Int>>\
    \ &s) {\n        const int H = s.size(), W = H ? s.at(0).size() : 0;\n       \
    \ gen_pow(H, W);\n\n        hash.assign(H, std::vector<V>(W, V()));\n        for\
    \ (int i = 0; i < H; ++i) {\n            for (int j = 0; j < W; ++j) hash[i][j]\
    \ = _at(i, j - 1) * By + s[i][j];\n        }\n\n        for (int i = 0; i < H;\
    \ ++i) {\n            for (int j = 0; j < W; ++j) hash[i][j] = hash[i][j] + _at(i\
    \ - 1, j) * Bx;\n        }\n    }\n\n    template <typename Int>\n    rolling_hash_2d(const\
    \ std::vector<std::vector<Int>> &s, V bx, V by) : Bx(bx), By(by) {\n        build(s);\n\
    \    }\n\n    rolling_hash_2d(const std::vector<std::string> &m, V bx, V by) :\
    \ Bx(bx), By(by) {\n        std::vector<std::vector<int>> v_;\n        for (const\
    \ auto &s : m) {\n            v_.push_back({});\n            for (char c : s)\
    \ v_.back().push_back(int(c));\n        }\n        build(v_);\n    }\n\n    V\
    \ get(int xl, int xr, int yl, int yr) const {\n        return _at(xr - 1, yr -\
    \ 1) - _at(xl - 1, yr - 1) * powx[xr - xl] -\n               _at(xr - 1, yl -\
    \ 1) * powy[yr - yl] +\n               _at(xl - 1, yl - 1) * powx[xr - xl] * powy[yr\
    \ - yl];\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: string/rolling_hash_2d.hpp
  requiredBy: []
  timestamp: '2022-10-09 14:11:30+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - string/test/rolling_hash_2d.aoj.test.cpp
documentation_of: string/rolling_hash_2d.hpp
layout: document
title: "Rolling hash (two dimensional) \uFF08\u4E8C\u6B21\u5143\u30ED\u30FC\u30EA\u30F3\
  \u30B0\u30CF\u30C3\u30B7\u30E5\uFF09"
---

行列に対する典型的なローリングハッシュ．構築・矩形取得が線形時間で可能．

## 使用方法

```cpp
using Hash = ModIntMersenne61;

vector<string> mat;
rolling_hash_2d<Hash> rh(mat)

int xl, xr, yl, yr;
Hash h = rh.get(xl, xr, yl, yr);  // [xl, xr) * [yl, yr) のハッシュ値を取得する
```

ハッシュの型 `PairHash` や `TupleHash3` は任意に入れ子にすることも可能で，例えば

```cpp
using Hash = ModIntMersenne61;
using Hash = TupleHash3<ModInt998244353, ModInt998244353, ModInt998244353>;
using PH = PairHash<ModInt998244353, ModInt998244353>;
using Hash = TupleHash3<PH, ModInt998244353, PH>;
using Hash = PairHash<PH, PairHash<ModInt998244353, ModInt998244353>>;
```

は全て動作する．
