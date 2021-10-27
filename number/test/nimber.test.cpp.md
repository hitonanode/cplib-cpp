---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: number/nimber.hpp
    title: "Nimber, Nim product \uFF08\u30CB\u30E0\u6570\uFF0C$\\mathbb{F}\\_{2^{64}}$\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/nim_product_64
    links:
    - https://judge.yosupo.jp/problem/nim_product_64
  bundledCode: "#line 1 \"number/test/nimber.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/nim_product_64\"\
    \n#line 2 \"number/nimber.hpp\"\n#include <array>\n\n// Nimber (64 bit)\n// Reference:\n\
    // - https://en.wikipedia.org/wiki/Nimber\n// - https://kyopro-friends.hatenablog.com/entry/2020/04/07/195850\n\
    // - https://judge.yosupo.jp/submission/4542 (implementation idea)\nstruct Nimber\
    \ {\n    using ull = unsigned long long;\n    ull v;\n    const static std::array<std::array<unsigned,\
    \ 256>, 256> small_table;\n    const static std::array<std::array<std::array<ull,\
    \ 256>, 8>, 8> precalc;\n\n    explicit operator bool() const { return v != 0;\
    \ }\n    Nimber(ull val = 0) : v(val) {}\n    Nimber operator+(const Nimber &x)\
    \ const { return Nimber(v ^ x.v); }\n    Nimber operator-(const Nimber &x) const\
    \ { return Nimber(v ^ x.v); }\n    Nimber operator-() const { return *this; }\n\
    \    Nimber &operator+=(const Nimber &x) { return *this = *this + x; }\n    Nimber\
    \ &operator-=(const Nimber &x) { return *this = *this + x; }\n    template <class\
    \ IStream> friend IStream &operator>>(IStream &is, Nimber &x) {\n        ull v;\n\
    \        return is >> v, x = Nimber(v), is;\n    }\n    template <class OStream>\
    \ friend OStream &operator<<(OStream &os, const Nimber &x) {\n        return os\
    \ << x.v;\n    }\n    bool operator==(const Nimber &x) const { return v == x.v;\
    \ }\n    bool operator!=(const Nimber &x) const { return v != x.v; }\n    bool\
    \ operator<(const Nimber &x) const { return v < x.v; }\n\n    static ull _rec(ull\
    \ x, ull y) {\n        if (x == 0 or y == 0) return 0;\n        if (x < y) x ^=\
    \ y, y ^= x, x ^= y; // Make x >= y\n        if (y == 1) return x;\n        for\
    \ (int shift = 64 / 2;; shift >>= 1) {\n            ull mask = (1ULL << shift)\
    \ - 1;\n            if (y >> shift) {\n                ull v00 = _rec(x & mask,\
    \ y & mask);\n                ull v01 = _rec(x & mask, y >> shift);\n        \
    \        ull v10 = _rec(x >> shift, y & mask);\n                ull v11 = _rec(x\
    \ >> shift, y >> shift);\n                return v00 ^ ((v01 ^ v10 ^ v11) << shift)\
    \ ^ _rec(v11, 1ULL << (shift - 1));\n            } else if (x >> shift) {\n  \
    \              return (_rec(x >> shift, y) << shift) ^ _rec(x & mask, y);\n  \
    \          }\n        }\n    }\n    Nimber operator*(const Nimber &x) const {\n\
    \        ull ret = 0;\n        for (int d = 0; d < 8; ++d) {\n            for\
    \ (int e = 0; e < 8; ++e) {\n                ret ^= precalc[d][e][small_table[(v\
    \ >> (d * 8)) & 255][(x.v >> (e * 8)) & 255]];\n            }\n        }\n   \
    \     return Nimber(ret);\n    }\n    Nimber &operator*=(const Nimber &x) { return\
    \ *this = *this * x; }\n};\n\nconst std::array<std::array<unsigned, 256>, 256>\
    \ Nimber::small_table = []() {\n    std::array<std::array<unsigned, 256>, 256>\
    \ ret;\n    for (int i = 0; i < 256; ++i) {\n        for (int j = 0; j < 256;\
    \ ++j) ret[i][j] = _rec(i, j);\n    }\n    return ret;\n}();\nconst std::array<std::array<std::array<unsigned\
    \ long long, 256>, 8>, 8> Nimber::precalc = []() {\n    std::array<std::array<std::array<unsigned\
    \ long long, 256>, 8>, 8> ret;\n    for (int d = 0; d < 8; ++d) {\n        for\
    \ (int e = 0; e < 8; ++e) {\n            ull p = _rec(1ULL << (8 * d), 1ULL <<\
    \ (8 * e));\n            for (int i = 0; i < 256; ++i) ret[d][e][i] = _rec(p,\
    \ i);\n        }\n    }\n    return ret;\n}();\n#line 3 \"number/test/nimber.test.cpp\"\
    \n#include <iostream>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n    int T;\n    cin >> T;\n    while (T--) {\n\
    \        Nimber A, B;\n        cin >> A >> B;\n        cout << A * B << '\\n';\n\
    \    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/nim_product_64\"\n#include\
    \ \"../nimber.hpp\"\n#include <iostream>\nusing namespace std;\n\nint main() {\n\
    \    cin.tie(nullptr), ios::sync_with_stdio(false);\n    int T;\n    cin >> T;\n\
    \    while (T--) {\n        Nimber A, B;\n        cin >> A >> B;\n        cout\
    \ << A * B << '\\n';\n    }\n}\n"
  dependsOn:
  - number/nimber.hpp
  isVerificationFile: true
  path: number/test/nimber.test.cpp
  requiredBy: []
  timestamp: '2021-10-27 23:41:07+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: number/test/nimber.test.cpp
layout: document
redirect_from:
- /verify/number/test/nimber.test.cpp
- /verify/number/test/nimber.test.cpp.html
title: number/test/nimber.test.cpp
---
