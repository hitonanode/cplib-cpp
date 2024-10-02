---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: number/nimber.hpp
    title: "Nimber, Nim product \uFF08\u30CB\u30E0\u6570\uFF0C$\\mathbb{F}_{2^{64}}$\uFF09"
  - icon: ':heavy_check_mark:'
    path: unionfind/potentialized_unionfind.hpp
    title: "Potentialized UnionFind \uFF08\u91CD\u307F\u4ED8\u304D UnionFind\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    ERROR: '1'
    PROBLEM: https://yukicoder.me/problems/no/1420
    links:
    - https://yukicoder.me/problems/no/1420
  bundledCode: "#line 1 \"unionfind/test/potentialized_unionfind_F2.yuki1420.test.cpp\"\
    \n#define PROBLEM \"https://yukicoder.me/problems/no/1420\"\n#define ERROR 1 //\
    \ Check only whether the answer is -1 or not\n#line 2 \"number/nimber.hpp\"\n\
    #include <array>\n\n// Nimber (64 bit)\n// Reference:\n// - https://judge.yosupo.jp/submission/4542\
    \ (Original implementation idea)\n// - https://en.wikipedia.org/wiki/Nimber\n\
    // - https://kyopro-friends.hatenablog.com/entry/2020/04/07/195850\nstruct Nimber\
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
    \ i);\n        }\n    }\n    return ret;\n}();\n#line 2 \"unionfind/potentialized_unionfind.hpp\"\
    \n#include <numeric>\n#include <utility>\n#include <vector>\n\n// Potentialized\
    \ UnionFind (Weighted UnionFind)\ntemplate <class S> struct PotentializedUnionFind\
    \ {\n    std::vector<int> par, sz;\n    std::vector<S> pot;\n    PotentializedUnionFind(int\
    \ N = 0) : par(N), sz(N, 1), pot(N) {\n        std::iota(par.begin(), par.end(),\
    \ 0);\n    }\n    int find(int x) {\n        if (par[x] != x) {\n            int\
    \ r = find(par[x]);\n            pot[x] = pot[x] + pot[par[x]], par[x] = r;\n\
    \        }\n        return par[x];\n    }\n    bool unite(int s, int t, S rel_diff)\
    \ {\n        // Relate s and t by f[t] = f[s] + rel_diff\n        // Return false\
    \ iff contradiction happens.\n        rel_diff = rel_diff + weight(s) + (-weight(t));\n\
    \        if ((s = find(s)) == (t = find(t))) return rel_diff == 0;\n        if\
    \ (sz[s] < sz[t]) std::swap(s, t), rel_diff = -rel_diff;\n        par[t] = s,\
    \ sz[s] += sz[t], pot[t] = rel_diff;\n        return true;\n    }\n    S weight(int\
    \ x) { return find(x), pot[x]; }\n    S diff(int s, int t) { return weight(t)\
    \ + (-weight(s)); } // return f[t] - f[s]\n    int count(int x) { return sz[find(x)];\
    \ }\n    bool same(int s, int t) { return find(s) == find(t); }\n};\n#line 5 \"\
    unionfind/test/potentialized_unionfind_F2.yuki1420.test.cpp\"\n#include <iostream>\n\
    using namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \    int N, M;\n    cin >> N >> M;\n\n    PotentializedUnionFind<Nimber> uf(N);\n\
    \    while (M--) {\n        int a, b, y;\n        cin >> a >> b >> y;\n      \
    \  a--, b--;\n        if (!uf.unite(a, b, y)) {\n            cout << \"-1\\n\"\
    ;\n            return 0;\n        }\n    }\n    for (int i = 0; i < N; i++) cout\
    \ << uf.weight(i) << '\\n';\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/1420\"\n#define ERROR\
    \ 1 // Check only whether the answer is -1 or not\n#include \"../../number/nimber.hpp\"\
    \n#include \"../potentialized_unionfind.hpp\"\n#include <iostream>\nusing namespace\
    \ std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n \
    \   int N, M;\n    cin >> N >> M;\n\n    PotentializedUnionFind<Nimber> uf(N);\n\
    \    while (M--) {\n        int a, b, y;\n        cin >> a >> b >> y;\n      \
    \  a--, b--;\n        if (!uf.unite(a, b, y)) {\n            cout << \"-1\\n\"\
    ;\n            return 0;\n        }\n    }\n    for (int i = 0; i < N; i++) cout\
    \ << uf.weight(i) << '\\n';\n}\n"
  dependsOn:
  - number/nimber.hpp
  - unionfind/potentialized_unionfind.hpp
  isVerificationFile: true
  path: unionfind/test/potentialized_unionfind_F2.yuki1420.test.cpp
  requiredBy: []
  timestamp: '2024-10-02 23:55:49+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: unionfind/test/potentialized_unionfind_F2.yuki1420.test.cpp
layout: document
redirect_from:
- /verify/unionfind/test/potentialized_unionfind_F2.yuki1420.test.cpp
- /verify/unionfind/test/potentialized_unionfind_F2.yuki1420.test.cpp.html
title: unionfind/test/potentialized_unionfind_F2.yuki1420.test.cpp
---
