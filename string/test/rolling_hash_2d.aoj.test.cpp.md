---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: number/modint_mersenne61.hpp
    title: "$\\mathbb{F}_{2^{61} - 1}$ \uFF08\u30CF\u30C3\u30B7\u30E5\u7528\u30E1\u30EB\
      \u30BB\u30F3\u30CC\u7D20\u6570 modint\uFF09"
  - icon: ':heavy_check_mark:'
    path: string/rolling_hash_2d.hpp
    title: "Rolling hash (two dimensional) \uFF08\u4E8C\u6B21\u5143\u30ED\u30FC\u30EA\
      \u30F3\u30B0\u30CF\u30C3\u30B7\u30E5\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_C
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_C
  bundledCode: "#line 1 \"string/test/rolling_hash_2d.aoj.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_C\"\n#line\
    \ 2 \"number/modint_mersenne61.hpp\"\n#include <cassert>\n#include <chrono>\n\
    #include <random>\n\n// F_p, p = 2^61 - 1\n// https://qiita.com/keymoon/items/11fac5627672a6d6a9f6\n\
    class ModIntMersenne61 {\n    static const long long md = (1LL << 61) - 1;\n \
    \   long long _v;\n\n    inline unsigned hi() const noexcept { return _v >> 31;\
    \ }\n    inline unsigned lo() const noexcept { return _v & ((1LL << 31) - 1);\
    \ }\n\npublic:\n    static long long mod() { return md; }\n\n    ModIntMersenne61()\
    \ : _v(0) {}\n    // 0 <= x < md * 2\n    explicit ModIntMersenne61(long long\
    \ x) : _v(x >= md ? x - md : x) {}\n\n    long long val() const noexcept { return\
    \ _v; }\n\n    ModIntMersenne61 operator+(const ModIntMersenne61 &x) const {\n\
    \        return ModIntMersenne61(_v + x._v);\n    }\n\n    ModIntMersenne61 operator-(const\
    \ ModIntMersenne61 &x) const {\n        return ModIntMersenne61(_v + md - x._v);\n\
    \    }\n\n    ModIntMersenne61 operator*(const ModIntMersenne61 &x) const {\n\
    \        using ull = unsigned long long;\n\n        ull uu = (ull)hi() * x.hi()\
    \ * 2;\n        ull ll = (ull)lo() * x.lo();\n        ull lu = (ull)hi() * x.lo()\
    \ + (ull)lo() * x.hi();\n\n        ull sum = uu + ll + ((lu & ((1ULL << 30) -\
    \ 1)) << 31) + (lu >> 30);\n        ull reduced = (sum >> 61) + (sum & ull(md));\n\
    \        return ModIntMersenne61(reduced);\n    }\n\n    ModIntMersenne61 pow(long\
    \ long n) const {\n        assert(n >= 0);\n        ModIntMersenne61 ans(1), tmp\
    \ = *this;\n        while (n) {\n            if (n & 1) ans *= tmp;\n        \
    \    tmp *= tmp, n >>= 1;\n        }\n        return ans;\n    }\n\n    ModIntMersenne61\
    \ inv() const { return pow(md - 2); }\n\n    ModIntMersenne61 operator/(const\
    \ ModIntMersenne61 &x) const {\n        return *this * x.inv();\n    }\n\n   \
    \ ModIntMersenne61 operator-() const { return ModIntMersenne61(md - _v); }\n \
    \   ModIntMersenne61 &operator+=(const ModIntMersenne61 &x) { return *this = *this\
    \ + x; }\n    ModIntMersenne61 &operator-=(const ModIntMersenne61 &x) { return\
    \ *this = *this - x; }\n    ModIntMersenne61 &operator*=(const ModIntMersenne61\
    \ &x) { return *this = *this * x; }\n    ModIntMersenne61 &operator/=(const ModIntMersenne61\
    \ &x) { return *this = *this / x; }\n\n    ModIntMersenne61 operator+(unsigned\
    \ x) const {\n        return ModIntMersenne61(this->_v + x);\n    }\n\n    bool\
    \ operator==(const ModIntMersenne61 &x) const { return _v == x._v; }\n    bool\
    \ operator!=(const ModIntMersenne61 &x) const { return _v != x._v; }\n    bool\
    \ operator<(const ModIntMersenne61 &x) const {\n        return _v < x._v;\n  \
    \  } // To use std::map\n\n    template <class OStream> friend OStream &operator<<(OStream\
    \ &os, const ModIntMersenne61 &x) {\n        return os << x._v;\n    }\n\n   \
    \ static ModIntMersenne61 randgen(bool force_update = false) {\n        static\
    \ ModIntMersenne61 b(0);\n        if (b == ModIntMersenne61(0) or force_update)\
    \ {\n            std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());\n\
    \            std::uniform_int_distribution<long long> d(1, ModIntMersenne61::mod());\n\
    \            b = ModIntMersenne61(d(mt));\n        }\n        return b;\n    }\n\
    };\n#line 2 \"string/rolling_hash_2d.hpp\"\n#include <string>\n#include <vector>\n\
    \n\n// Rolling Hash (Rabin-Karp), 2dim\ntemplate <typename V> struct rolling_hash_2d\
    \ {\n    const V Bx, By;\n    std::vector<V> powx, powy;  // powx[i] = Bx^i\n\
    \    std::vector<std::vector<V>> hash;\n\n    void gen_pow(int h, int w) {\n \
    \       powx.assign(h + 1, V(1));\n        for (int i = 1; i <= h; ++i) powx.at(i)\
    \ = powx.at(i - 1) * Bx;\n        powy.assign(w + 1, V(1));\n        for (int\
    \ i = 1; i <= w; ++i) powy.at(i) = powy.at(i - 1) * By;\n    }\n\n    inline V\
    \ _at(int x, int y) const noexcept {\n        if (x < 0 or x >= int(hash.size()))\
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
    \ - xl] * powy[yr - yl];\n    }\n};\n#line 4 \"string/test/rolling_hash_2d.aoj.test.cpp\"\
    \n\n#include <iostream>\n#line 8 \"string/test/rolling_hash_2d.aoj.test.cpp\"\n\
    using namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    int H, W;\n    cin >> H >> W;\n    vector<string> S(H);\n    for (auto &s\
    \ : S) cin >> s;\n\n    int X, Y;\n    cin >> X >> Y;\n    vector<string> T(X);\n\
    \    for (auto &t : T) cin >> t;\n\n    const ModIntMersenne61 b1(418672), b2(956731);\n\
    \n    rolling_hash_2d<ModIntMersenne61> rhs(S, b1, b2);\n\n    const auto tgt\
    \ = rolling_hash_2d<ModIntMersenne61>(T, b1, b2).get(0, X, 0, Y);\n\n    for (int\
    \ i = 0; i + X <= H; ++i) {\n        for (int j = 0; j + Y <= W; ++j) {\n    \
    \        if (rhs.get(i, i + X, j, j + Y) == tgt) cout << i << ' ' << j << '\\\
    n';\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_C\"\
    \n#include \"../../number/modint_mersenne61.hpp\"\n#include \"../rolling_hash_2d.hpp\"\
    \n\n#include <iostream>\n#include <string>\n#include <vector>\nusing namespace\
    \ std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\n\
    \    int H, W;\n    cin >> H >> W;\n    vector<string> S(H);\n    for (auto &s\
    \ : S) cin >> s;\n\n    int X, Y;\n    cin >> X >> Y;\n    vector<string> T(X);\n\
    \    for (auto &t : T) cin >> t;\n\n    const ModIntMersenne61 b1(418672), b2(956731);\n\
    \n    rolling_hash_2d<ModIntMersenne61> rhs(S, b1, b2);\n\n    const auto tgt\
    \ = rolling_hash_2d<ModIntMersenne61>(T, b1, b2).get(0, X, 0, Y);\n\n    for (int\
    \ i = 0; i + X <= H; ++i) {\n        for (int j = 0; j + Y <= W; ++j) {\n    \
    \        if (rhs.get(i, i + X, j, j + Y) == tgt) cout << i << ' ' << j << '\\\
    n';\n        }\n    }\n}\n"
  dependsOn:
  - number/modint_mersenne61.hpp
  - string/rolling_hash_2d.hpp
  isVerificationFile: true
  path: string/test/rolling_hash_2d.aoj.test.cpp
  requiredBy: []
  timestamp: '2022-10-09 14:11:30+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: string/test/rolling_hash_2d.aoj.test.cpp
layout: document
redirect_from:
- /verify/string/test/rolling_hash_2d.aoj.test.cpp
- /verify/string/test/rolling_hash_2d.aoj.test.cpp.html
title: string/test/rolling_hash_2d.aoj.test.cpp
---
