---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':x:'
    path: tree/tree_isomorphism.hpp
    title: "Tree isomrphism \uFF08\u6728\u306E\u540C\u578B\u5224\u5B9A\uFF09"
  - icon: ':x:'
    path: unionfind/grid_unionfind.hpp
    title: unionfind/grid_unionfind.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1613
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1613
  bundledCode: "#line 1 \"tree/test/tree_isomorphism.aoj1613.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1613\"\n#line 2\
    \ \"tree/tree_isomorphism.hpp\"\n#include <chrono>\n#include <utility>\n#include\
    \ <vector>\n\n// Tree isomorphism with hashing \uFF08\u30CF\u30C3\u30B7\u30E5\u306B\
    \u3088\u308B\u6728\u306E\u540C\u578B\u5224\u5B9A\uFF09\n// Dependence: ModInt\
    \ or ModIntRuntime\n// Reference: https://snuke.hatenablog.com/entry/2017/02/03/054210\n\
    // Verified: https://atcoder.jp/contests/nikkei2019-2-final/submissions/9044698\
    \ (ModInt)\n//           https://atcoder.jp/contests/nikkei2019-2-final/submissions/9044745\
    \ (ModIntRuntime)\ntemplate <typename ModInt> struct tree_isomorphism {\n    using\
    \ DoubleHash = std::pair<ModInt, ModInt>;\n    using Edges = std::vector<std::vector<int>>;\
    \ // vector<set<int>>;\n    int V;\n    Edges e;\n    tree_isomorphism(int v)\
    \ : V(v), e(v) {}\n    void add_edge(int u, int v) {\n        e[u].emplace_back(v);\n\
    \        e[v].emplace_back(u);\n    }\n\n    static uint64_t splitmix64(uint64_t\
    \ x) {\n        // https://codeforces.com/blog/entry/62393 http://xorshift.di.unimi.it/splitmix64.c\n\
    \        x += 0x9e3779b97f4a7c15;\n        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;\n\
    \        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;\n        return x ^ (x >> 31);\n\
    \    }\n    DoubleHash get_hash(DoubleHash x) const {\n        static const uint64_t\
    \ FIXED_RANDOM =\n            std::chrono::steady_clock::now().time_since_epoch().count();\n\
    \        return {splitmix64(x.first.val() + FIXED_RANDOM), splitmix64(x.second.val()\
    \ + FIXED_RANDOM)};\n    }\n\n    static void add_hash(DoubleHash &l, const DoubleHash\
    \ &r) {\n        l.first += r.first, l.second += r.second;\n    }\n    static\
    \ DoubleHash subtract_hash(const DoubleHash &l, const DoubleHash &r) {\n     \
    \   return {l.first - r.first, l.second - r.second};\n    }\n\n    std::vector<DoubleHash>\
    \ hash;         // hash of the tree, each node regarded as root\n    std::vector<DoubleHash>\
    \ hash_subtree; // hash of the subtree\n    std::vector<DoubleHash> hash_par;\
    \ // hash of the subtree whose root is parent[i], not containing i\n    DoubleHash\
    \ hash_p;                // \\in [1, hmod), should be set randomly\n    DoubleHash\
    \ hash_dfs1_(int now, int prv) {\n        hash_subtree[now] = hash_p;\n      \
    \  for (auto nxt : e[now]) {\n            if (nxt != prv) add_hash(hash_subtree[now],\
    \ hash_dfs1_(nxt, now));\n        }\n        return get_hash(hash_subtree[now]);\n\
    \    }\n    void hash_dfs2_(int now, int prv) {\n        add_hash(hash[now], hash_subtree[now]);\n\
    \        if (prv >= 0) hash_par[now] = subtract_hash(hash[prv], get_hash(hash_subtree[now]));\n\
    \        for (auto nxt : e[now])\n            if (nxt != prv) {\n            \
    \    DoubleHash tmp = subtract_hash(hash[now], get_hash(hash_subtree[nxt]));\n\
    \                add_hash(hash[nxt], get_hash(tmp));\n                hash_dfs2_(nxt,\
    \ now);\n            }\n    }\n    void build_hash(int root, int p1, int p2) {\n\
    \        hash_p = std::make_pair(p1, p2);\n        hash.resize(V), hash_subtree.resize(V),\
    \ hash_par.resize(V);\n        hash_dfs1_(root, -1);\n        hash_dfs2_(root,\
    \ -1);\n    }\n};\n#line 2 \"modint.hpp\"\n#include <iostream>\n#include <set>\n\
    #line 5 \"modint.hpp\"\n\ntemplate <int md> struct ModInt {\n#if __cplusplus >=\
    \ 201402L\n#define MDCONST constexpr\n#else\n#define MDCONST\n#endif\n    using\
    \ lint = long long;\n    MDCONST static int mod() { return md; }\n    static int\
    \ get_primitive_root() {\n        static int primitive_root = 0;\n        if (!primitive_root)\
    \ {\n            primitive_root = [&]() {\n                std::set<int> fac;\n\
    \                int v = md - 1;\n                for (lint i = 2; i * i <= v;\
    \ i++)\n                    while (v % i == 0) fac.insert(i), v /= i;\n      \
    \          if (v > 1) fac.insert(v);\n                for (int g = 1; g < md;\
    \ g++) {\n                    bool ok = true;\n                    for (auto i\
    \ : fac)\n                        if (ModInt(g).pow((md - 1) / i) == 1) {\n  \
    \                          ok = false;\n                            break;\n \
    \                       }\n                    if (ok) return g;\n           \
    \     }\n                return -1;\n            }();\n        }\n        return\
    \ primitive_root;\n    }\n    int val_;\n    int val() const noexcept { return\
    \ val_; }\n    MDCONST ModInt() : val_(0) {}\n    MDCONST ModInt &_setval(lint\
    \ v) { return val_ = (v >= md ? v - md : v), *this; }\n    MDCONST ModInt(lint\
    \ v) { _setval(v % md + md); }\n    MDCONST explicit operator bool() const { return\
    \ val_ != 0; }\n    MDCONST ModInt operator+(const ModInt &x) const {\n      \
    \  return ModInt()._setval((lint)val_ + x.val_);\n    }\n    MDCONST ModInt operator-(const\
    \ ModInt &x) const {\n        return ModInt()._setval((lint)val_ - x.val_ + md);\n\
    \    }\n    MDCONST ModInt operator*(const ModInt &x) const {\n        return\
    \ ModInt()._setval((lint)val_ * x.val_ % md);\n    }\n    MDCONST ModInt operator/(const\
    \ ModInt &x) const {\n        return ModInt()._setval((lint)val_ * x.inv().val()\
    \ % md);\n    }\n    MDCONST ModInt operator-() const { return ModInt()._setval(md\
    \ - val_); }\n    MDCONST ModInt &operator+=(const ModInt &x) { return *this =\
    \ *this + x; }\n    MDCONST ModInt &operator-=(const ModInt &x) { return *this\
    \ = *this - x; }\n    MDCONST ModInt &operator*=(const ModInt &x) { return *this\
    \ = *this * x; }\n    MDCONST ModInt &operator/=(const ModInt &x) { return *this\
    \ = *this / x; }\n    friend MDCONST ModInt operator+(lint a, const ModInt &x)\
    \ {\n        return ModInt()._setval(a % md + x.val_);\n    }\n    friend MDCONST\
    \ ModInt operator-(lint a, const ModInt &x) {\n        return ModInt()._setval(a\
    \ % md - x.val_ + md);\n    }\n    friend MDCONST ModInt operator*(lint a, const\
    \ ModInt &x) {\n        return ModInt()._setval(a % md * x.val_ % md);\n    }\n\
    \    friend MDCONST ModInt operator/(lint a, const ModInt &x) {\n        return\
    \ ModInt()._setval(a % md * x.inv().val() % md);\n    }\n    MDCONST bool operator==(const\
    \ ModInt &x) const { return val_ == x.val_; }\n    MDCONST bool operator!=(const\
    \ ModInt &x) const { return val_ != x.val_; }\n    MDCONST bool operator<(const\
    \ ModInt &x) const {\n        return val_ < x.val_;\n    } // To use std::map<ModInt,\
    \ T>\n    friend std::istream &operator>>(std::istream &is, ModInt &x) {\n   \
    \     lint t;\n        return is >> t, x = ModInt(t), is;\n    }\n    MDCONST\
    \ friend std::ostream &operator<<(std::ostream &os, const ModInt &x) {\n     \
    \   return os << x.val_;\n    }\n    MDCONST ModInt pow(lint n) const {\n    \
    \    ModInt ans = 1, tmp = *this;\n        while (n) {\n            if (n & 1)\
    \ ans *= tmp;\n            tmp *= tmp, n >>= 1;\n        }\n        return ans;\n\
    \    }\n\n    static std::vector<ModInt> facs, facinvs, invs;\n    MDCONST static\
    \ void _precalculation(int N) {\n        int l0 = facs.size();\n        if (N\
    \ > md) N = md;\n        if (N <= l0) return;\n        facs.resize(N), facinvs.resize(N),\
    \ invs.resize(N);\n        for (int i = l0; i < N; i++) facs[i] = facs[i - 1]\
    \ * i;\n        facinvs[N - 1] = facs.back().pow(md - 2);\n        for (int i\
    \ = N - 2; i >= l0; i--) facinvs[i] = facinvs[i + 1] * (i + 1);\n        for (int\
    \ i = N - 1; i >= l0; i--) invs[i] = facinvs[i] * facs[i - 1];\n    }\n    MDCONST\
    \ ModInt inv() const {\n        if (this->val_ < std::min(md >> 1, 1 << 21)) {\n\
    \            while (this->val_ >= int(facs.size())) _precalculation(facs.size()\
    \ * 2);\n            return invs[this->val_];\n        } else {\n            return\
    \ this->pow(md - 2);\n        }\n    }\n    MDCONST ModInt fac() const {\n   \
    \     while (this->val_ >= int(facs.size())) _precalculation(facs.size() * 2);\n\
    \        return facs[this->val_];\n    }\n    MDCONST ModInt facinv() const {\n\
    \        while (this->val_ >= int(facs.size())) _precalculation(facs.size() *\
    \ 2);\n        return facinvs[this->val_];\n    }\n    MDCONST ModInt doublefac()\
    \ const {\n        lint k = (this->val_ + 1) / 2;\n        return (this->val_\
    \ & 1) ? ModInt(k * 2).fac() / (ModInt(2).pow(k) * ModInt(k).fac())\n        \
    \                        : ModInt(k).fac() * ModInt(2).pow(k);\n    }\n    MDCONST\
    \ ModInt nCr(const ModInt &r) const {\n        return (this->val_ < r.val_) ?\
    \ 0 : this->fac() * (*this - r).facinv() * r.facinv();\n    }\n    MDCONST ModInt\
    \ nPr(const ModInt &r) const {\n        return (this->val_ < r.val_) ? 0 : this->fac()\
    \ * (*this - r).facinv();\n    }\n\n    ModInt sqrt() const {\n        if (val_\
    \ == 0) return 0;\n        if (md == 2) return val_;\n        if (pow((md - 1)\
    \ / 2) != 1) return 0;\n        ModInt b = 1;\n        while (b.pow((md - 1) /\
    \ 2) == 1) b += 1;\n        int e = 0, m = md - 1;\n        while (m % 2 == 0)\
    \ m >>= 1, e++;\n        ModInt x = pow((m - 1) / 2), y = (*this) * x * x;\n \
    \       x *= (*this);\n        ModInt z = b.pow(m);\n        while (y != 1) {\n\
    \            int j = 0;\n            ModInt t = y;\n            while (t != 1)\
    \ j++, t *= t;\n            z = z.pow(1LL << (e - j - 1));\n            x *= z,\
    \ z *= z, y *= z;\n            e = j;\n        }\n        return ModInt(std::min(x.val_,\
    \ md - x.val_));\n    }\n};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facs\
    \ = {1};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facinvs = {1};\n\
    template <int md> std::vector<ModInt<md>> ModInt<md>::invs = {0};\n// using mint\
    \ = ModInt<998244353>;\n// using mint = ModInt<1000000007>;\n#line 2 \"unionfind/grid_unionfind.hpp\"\
    \n#include <cassert>\n#include <iomanip>\n#include <numeric>\n#line 7 \"unionfind/grid_unionfind.hpp\"\
    \n\n// CUT begin\nstruct GridUnionFind {\n    int H, W;\n    std::vector<int>\
    \ par, cou;\n    using P = std::pair<int, int>;\n    GridUnionFind(int H_, int\
    \ W_) : H(H_), W(W_), par(H * W), cou(H * W, 1) {\n        std::iota(par.begin(),\
    \ par.end(), 0);\n    }\n    inline int id_(int h, int w) { return h * W + w;\
    \ }\n    inline bool coordinate_valid(int h, int w) { return h >= 0 and h < H\
    \ and w >= 0 and w < W; }\n    int _find(int x) { return (par[x] == x) ? x : (par[x]\
    \ = _find(par[x])); }\n    bool _unite(int x, int y) {\n        x = _find(x),\
    \ y = _find(y);\n        if (x == y) return false;\n        if (cou[x] < cou[y])\
    \ std::swap(x, y);\n        par[y] = x, cou[x] += cou[y];\n        return true;\n\
    \    }\n    int find(int h, int w) {\n        assert(coordinate_valid(h, w));\n\
    \        return _find(id_(h, w));\n    }\n    bool unite(int h, int w, int h2,\
    \ int w2) {\n        assert(coordinate_valid(h, w) and coordinate_valid(h2, w2));\n\
    \        return _unite(id_(h, w), id_(h2, w2));\n    }\n    int count(int h, int\
    \ w) { return cou[find(h, w)]; }\n    bool same(int h, int w, int h2, int w2)\
    \ { return find(h, w) == find(h2, w2); }\n\n    int find(P p) { return find(p.first,\
    \ p.second); }\n    bool unite(P p, P p2) { return unite(p.first, p.second, p2.first,\
    \ p2.second); }\n    int count(P p) { return count(p.first, p.second); }\n   \
    \ bool same(P p, P p2) { return same(p.first, p.second, p2.first, p2.second);\
    \ }\n\n    void merge_outer() {\n        for (int h = 0; h < H - 1; h++) unite(h,\
    \ 0, h + 1, 0), unite(h, W - 1, h + 1, W - 1);\n        for (int w = 0; w < W\
    \ - 1; w++) unite(0, w, 0, w + 1), unite(H - 1, w, H - 1, w + 1);\n    }\n   \
    \ template <typename OStream> friend OStream &operator<<(OStream &os, GridUnionFind\
    \ &g) {\n        constexpr int WW = 3;\n        os << \"[(\" << g.H << \" * \"\
    \ << g.W << \" grid)\\n\";\n        for (int i = 0; i < g.H; i++) {\n        \
    \    for (int j = 0; j < g.W - 1; j++) {\n                os << std::setw(WW)\
    \ << g.find(i, j) << (g.same(i, j, i, j + 1) ? '-' : ' ');\n            }\n  \
    \          os << std::setw(WW) << g.find(i, g.W - 1) << '\\n';\n            if\
    \ (i < g.H - 1) {\n                for (int j = 0; j < g.W; j++)\n           \
    \         os << std::setw(WW + 1) << (g.same(i, j, i + 1, j) ? \"| \" : \"  \"\
    );\n                os << \"\\n\";\n            }\n        }\n        os << \"\
    ]\\n\";\n        return os;\n    }\n};\n#line 5 \"tree/test/tree_isomorphism.aoj1613.test.cpp\"\
    \n#include <algorithm>\n#include <array>\n#line 8 \"tree/test/tree_isomorphism.aoj1613.test.cpp\"\
    \n#include <string>\n#line 11 \"tree/test/tree_isomorphism.aoj1613.test.cpp\"\n\
    using namespace std;\n\nusing mint = ModInt<998244353>;\n\npair<mint, mint> tree_hash(vector<string>\
    \ S) {\n    for (auto &s : S) s = \".\" + s + \".\";\n    const int W = S[0].size();\n\
    \    S.insert(S.begin(), string(W, '.'));\n    S.push_back(string(W, '.'));\n\
    \    const int H = S.size();\n    GridUnionFind uf(H, W);\n    vector<pair<int,\
    \ int>> dx4{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};\n    vector<pair<int, int>> dx8{\n\
    \        {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};\n\
    \    auto is_inner = [&](int i, int j) { return i >= 0 and i < H and j >= 0 and\
    \ j < W; };\n    for (int i = 0; i < H; i++) {\n        for (int j = 0; j < W;\
    \ j++) {\n            vector<pair<int, int>> *ptr = S[i][j] == '#' ? &dx8 : &dx4;\n\
    \            for (auto p : *ptr) {\n                int nx = i + p.first, ny =\
    \ j + p.second;\n                if (is_inner(nx, ny) and S[i][j] == S[nx][ny])\
    \ uf.unite(i, j, nx, ny);\n            }\n        }\n    }\n    std::vector<int>\
    \ roots;\n    for (int i = 0; i < H; i++) {\n        for (int j = 0; j < W; j++)\
    \ roots.push_back(uf.find(i, j));\n    }\n    sort(roots.begin(), roots.end());\n\
    \    roots.erase(unique(roots.begin(), roots.end()), roots.end());\n    tree_isomorphism<mint>\
    \ iso(roots.size());\n    vector<int> seen(H * W);\n    seen[uf.find(0, 0)] =\
    \ 1;\n    for (int i = 0; i < H; i++) {\n        for (int j = 0; j < W; j++) {\n\
    \            int r = uf.find(i, j);\n            if (seen[r]) continue;\n    \
    \        seen[r] = 1;\n            int outer = -1;\n            int cur = i;\n\
    \            while (cur >= 0) {\n                if (uf.find(cur, j) == r) {\n\
    \                    outer = -1;\n                } else if (outer < 0) {\n  \
    \                  outer = uf.find(cur, j);\n                }\n             \
    \   cur--;\n            }\n            int u = lower_bound(roots.begin(), roots.end(),\
    \ r) - roots.begin();\n            int v = lower_bound(roots.begin(), roots.end(),\
    \ outer) - roots.begin();\n            iso.add_edge(u, v);\n        }\n    }\n\
    \    int rid = lower_bound(roots.begin(), roots.end(), uf.find(0, 0)) - roots.begin();\n\
    \    iso.build_hash(0, 141598, 181263479);\n    return iso.hash[rid];\n}\n\nint\
    \ main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n    int H, W;\n\
    \    while (true) {\n        cin >> H >> W;\n        if (!H) break;\n        vector<string>\
    \ S(H);\n        for (auto &s : S) cin >> s;\n        int H2, W2;\n        cin\
    \ >> H2 >> W2;\n        vector<string> T(H2);\n        for (auto &s : T) cin >>\
    \ s;\n        cout << (tree_hash(S) == tree_hash(T) ? \"yes\" : \"no\") << '\\\
    n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1613\"\
    \n#include \"../tree_isomorphism.hpp\"\n#include \"../../modint.hpp\"\n#include\
    \ \"../../unionfind/grid_unionfind.hpp\"\n#include <algorithm>\n#include <array>\n\
    #include <iostream>\n#include <string>\n#include <utility>\n#include <vector>\n\
    using namespace std;\n\nusing mint = ModInt<998244353>;\n\npair<mint, mint> tree_hash(vector<string>\
    \ S) {\n    for (auto &s : S) s = \".\" + s + \".\";\n    const int W = S[0].size();\n\
    \    S.insert(S.begin(), string(W, '.'));\n    S.push_back(string(W, '.'));\n\
    \    const int H = S.size();\n    GridUnionFind uf(H, W);\n    vector<pair<int,\
    \ int>> dx4{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};\n    vector<pair<int, int>> dx8{\n\
    \        {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};\n\
    \    auto is_inner = [&](int i, int j) { return i >= 0 and i < H and j >= 0 and\
    \ j < W; };\n    for (int i = 0; i < H; i++) {\n        for (int j = 0; j < W;\
    \ j++) {\n            vector<pair<int, int>> *ptr = S[i][j] == '#' ? &dx8 : &dx4;\n\
    \            for (auto p : *ptr) {\n                int nx = i + p.first, ny =\
    \ j + p.second;\n                if (is_inner(nx, ny) and S[i][j] == S[nx][ny])\
    \ uf.unite(i, j, nx, ny);\n            }\n        }\n    }\n    std::vector<int>\
    \ roots;\n    for (int i = 0; i < H; i++) {\n        for (int j = 0; j < W; j++)\
    \ roots.push_back(uf.find(i, j));\n    }\n    sort(roots.begin(), roots.end());\n\
    \    roots.erase(unique(roots.begin(), roots.end()), roots.end());\n    tree_isomorphism<mint>\
    \ iso(roots.size());\n    vector<int> seen(H * W);\n    seen[uf.find(0, 0)] =\
    \ 1;\n    for (int i = 0; i < H; i++) {\n        for (int j = 0; j < W; j++) {\n\
    \            int r = uf.find(i, j);\n            if (seen[r]) continue;\n    \
    \        seen[r] = 1;\n            int outer = -1;\n            int cur = i;\n\
    \            while (cur >= 0) {\n                if (uf.find(cur, j) == r) {\n\
    \                    outer = -1;\n                } else if (outer < 0) {\n  \
    \                  outer = uf.find(cur, j);\n                }\n             \
    \   cur--;\n            }\n            int u = lower_bound(roots.begin(), roots.end(),\
    \ r) - roots.begin();\n            int v = lower_bound(roots.begin(), roots.end(),\
    \ outer) - roots.begin();\n            iso.add_edge(u, v);\n        }\n    }\n\
    \    int rid = lower_bound(roots.begin(), roots.end(), uf.find(0, 0)) - roots.begin();\n\
    \    iso.build_hash(0, 141598, 181263479);\n    return iso.hash[rid];\n}\n\nint\
    \ main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n    int H, W;\n\
    \    while (true) {\n        cin >> H >> W;\n        if (!H) break;\n        vector<string>\
    \ S(H);\n        for (auto &s : S) cin >> s;\n        int H2, W2;\n        cin\
    \ >> H2 >> W2;\n        vector<string> T(H2);\n        for (auto &s : T) cin >>\
    \ s;\n        cout << (tree_hash(S) == tree_hash(T) ? \"yes\" : \"no\") << '\\\
    n';\n    }\n}\n"
  dependsOn:
  - tree/tree_isomorphism.hpp
  - modint.hpp
  - unionfind/grid_unionfind.hpp
  isVerificationFile: true
  path: tree/test/tree_isomorphism.aoj1613.test.cpp
  requiredBy: []
  timestamp: '2022-05-01 16:11:38+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: tree/test/tree_isomorphism.aoj1613.test.cpp
layout: document
redirect_from:
- /verify/tree/test/tree_isomorphism.aoj1613.test.cpp
- /verify/tree/test/tree_isomorphism.aoj1613.test.cpp.html
title: tree/test/tree_isomorphism.aoj1613.test.cpp
---
