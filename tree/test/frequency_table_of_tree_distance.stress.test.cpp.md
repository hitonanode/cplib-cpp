---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: convolution/ntt.hpp
    title: convolution/ntt.hpp
  - icon: ':question:'
    path: graph/shortest_path.hpp
    title: "Shortest Path \uFF08\u5358\u4E00\u59CB\u70B9\u6700\u77ED\u8DEF\uFF09"
  - icon: ':question:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':question:'
    path: random/xorshift.hpp
    title: random/xorshift.hpp
  - icon: ':x:'
    path: tree/centroid_decomposition.hpp
    title: tree/centroid_decomposition.hpp
  - icon: ':x:'
    path: tree/frequency_table_of_tree_distance.hpp
    title: Frequency table of tree distance
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
  bundledCode: "#line 1 \"tree/test/frequency_table_of_tree_distance.stress.test.cpp\"\
    \n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \ // DUMMY\n#line 2 \"tree/centroid_decomposition.hpp\"\n#include <tuple>\n#include\
    \ <utility>\n#include <vector>\n\n// CUT begin\n/*\n(Recursive) Centroid Decomposition\n\
    Verification: Codeforces #190 Div.1 C https://codeforces.com/contest/321/submission/59093583\n\
    \nfix_root(int r): Build information of the tree which `r` belongs to.\ndetect_centroid(int\
    \ r): Enumerate centroid(s) of the tree which `r` belongs to.\n*/\nstruct CentroidDecomposition\
    \ {\n    int NO_PARENT = -1;\n    int V;\n    int E;\n    std::vector<std::vector<std::pair<int,\
    \ int>>> to; // (node_id, edge_id)\n    std::vector<int> par;                \
    \             // parent node_id par[root] = -1\n    std::vector<std::vector<int>>\
    \ chi;                // children id's\n    std::vector<int> subtree_size;   \
    \                 // size of each subtree\n    std::vector<int> available_edge;\
    \                  // If 0, ignore the corresponding edge.\n\n    CentroidDecomposition(int\
    \ v = 0)\n        : V(v), E(0), to(v), par(v, NO_PARENT), chi(v), subtree_size(v)\
    \ {}\n    CentroidDecomposition(const std::vector<std::vector<int>> &to_)\n  \
    \      : CentroidDecomposition(to_.size()) {\n        for (int i = 0; i < V; i++)\
    \ {\n            for (auto j : to_[i]) {\n                if (i < j) { add_edge(i,\
    \ j); }\n            }\n        }\n    }\n\n    void add_edge(int v1, int v2)\
    \ {\n        to[v1].emplace_back(v2, E), to[v2].emplace_back(v1, E), E++;\n  \
    \      available_edge.emplace_back(1);\n    }\n\n    int _dfs_fixroot(int now,\
    \ int prv) {\n        chi[now].clear(), subtree_size[now] = 1;\n        for (auto\
    \ nxt : to[now]) {\n            if (nxt.first != prv and available_edge[nxt.second])\
    \ {\n                par[nxt.first] = now, chi[now].push_back(nxt.first);\n  \
    \              subtree_size[now] += _dfs_fixroot(nxt.first, now);\n          \
    \  }\n        }\n        return subtree_size[now];\n    }\n\n    void fix_root(int\
    \ root) {\n        par[root] = NO_PARENT;\n        _dfs_fixroot(root, -1);\n \
    \   }\n\n    //// Centroid Decpmposition ////\n    std::vector<int> centroid_cand_tmp;\n\
    \    void _dfs_detect_centroids(int now, int prv, int n) {\n        bool is_centroid\
    \ = true;\n        for (auto nxt : to[now]) {\n            if (nxt.first != prv\
    \ and available_edge[nxt.second]) {\n                _dfs_detect_centroids(nxt.first,\
    \ now, n);\n                if (subtree_size[nxt.first] > n / 2) is_centroid =\
    \ false;\n            }\n        }\n        if (n - subtree_size[now] > n / 2)\
    \ is_centroid = false;\n        if (is_centroid) centroid_cand_tmp.push_back(now);\n\
    \    }\n    std::pair<int, int> detect_centroids(int r) { // ([centroid_node_id1],\
    \ ([centroid_node_id2]|-1))\n        centroid_cand_tmp.clear();\n        while\
    \ (par[r] != NO_PARENT) r = par[r];\n        int n = subtree_size[r];\n      \
    \  _dfs_detect_centroids(r, -1, n);\n        if (centroid_cand_tmp.size() == 1)\n\
    \            return std::make_pair(centroid_cand_tmp[0], -1);\n        else\n\
    \            return std::make_pair(centroid_cand_tmp[0], centroid_cand_tmp[1]);\n\
    \    }\n\n    std::vector<int> _cd_vertices;\n    void _centroid_decomposition(int\
    \ now) {\n        fix_root(now);\n        now = detect_centroids(now).first;\n\
    \        _cd_vertices.emplace_back(now);\n        /*\n        do something\n \
    \       */\n        for (auto p : to[now]) {\n            int nxt, eid;\n    \
    \        std::tie(nxt, eid) = p;\n            if (available_edge[eid] == 0) continue;\n\
    \            available_edge[eid] = 0;\n            _centroid_decomposition(nxt);\n\
    \        }\n    }\n    std::vector<int> centroid_decomposition(int x) {\n    \
    \    _cd_vertices.clear();\n        _centroid_decomposition(x);\n        return\
    \ _cd_vertices;\n    }\n};\n#line 2 \"tree/frequency_table_of_tree_distance.hpp\"\
    \n#include <algorithm>\n#line 5 \"tree/frequency_table_of_tree_distance.hpp\"\n\
    \nstruct frequency_table_of_tree_distance {\n    std::vector<std::vector<int>>\
    \ tos;\n    std::vector<int> cd;\n    std::vector<std::pair<int, int>> tmp;\n\
    \    std::vector<int> alive;\n\n    void _dfs(int now, int prv, int depth) {\n\
    \        // if (int(tmp.size()) <= depth) tmp.resize(depth + 1, 0);\n        //\
    \ tmp[depth]++;\n        tmp.emplace_back(now, depth);\n        for (auto nxt\
    \ : tos[now]) {\n            if (alive[nxt] and nxt != prv) _dfs(nxt, now, depth\
    \ + 1);\n        }\n    }\n    std::vector<std::pair<int, int>> cnt_dfs(int root)\
    \ {\n        return tmp.clear(), _dfs(root, -1, 0), tmp;\n    }\n    frequency_table_of_tree_distance(const\
    \ std::vector<std::vector<int>> &to) {\n        tos = to;\n        cd = CentroidDecomposition(to).centroid_decomposition(0);\n\
    \    }\n    template <class S, std::vector<S> (*conv)(const std::vector<S> &,\
    \ const std::vector<S> &)>\n    std::vector<S> solve(const std::vector<S> &weight)\
    \ {\n        alive.assign(tos.size(), 1);\n        std::vector<S> ret(tos.size());\n\
    \        std::vector<S> v;\n        for (auto root : cd) {\n            std::vector<std::vector<S>>\
    \ vv;\n            alive[root] = 0;\n            for (auto nxt : tos[root]) {\n\
    \                if (!alive[nxt]) continue;\n                v.clear();\n    \
    \            for (auto p : cnt_dfs(nxt)) {\n                    while (int(v.size())\
    \ <= p.second) v.push_back(S(0));\n                    v[p.second] += weight[p.first];\n\
    \                }\n                for (int i = 0; i < int(v.size()); i++) ret[i\
    \ + 1] += v[i] * weight[root];\n                vv.emplace_back(v);\n        \
    \    }\n            std::sort(vv.begin(), vv.end(), [&](const std::vector<S> &l,\
    \ const std::vector<S> &r) {\n                return l.size() < r.size();\n  \
    \          });\n            for (size_t j = 1; j < vv.size(); j++) {\n       \
    \         const std::vector<S> c = conv(vv[j - 1], vv[j]);\n                for\
    \ (size_t i = 0; i < c.size(); i++) ret[i + 2] += c[i];\n                for (size_t\
    \ i = 0; i < vv[j - 1].size(); i++) vv[j][i] += vv[j - 1][i];\n            }\n\
    \            tos[root].clear();\n        }\n        return ret;\n    }\n};\n#line\
    \ 2 \"modint.hpp\"\n#include <iostream>\n#include <set>\n#line 5 \"modint.hpp\"\
    \n\n// CUT begin\ntemplate <int md> struct ModInt {\n#if __cplusplus >= 201402L\n\
    #define MDCONST constexpr\n#else\n#define MDCONST\n#endif\n    using lint = long\
    \ long;\n    MDCONST static int mod() { return md; }\n    static int get_primitive_root()\
    \ {\n        static int primitive_root = 0;\n        if (!primitive_root) {\n\
    \            primitive_root = [&]() {\n                std::set<int> fac;\n  \
    \              int v = md - 1;\n                for (lint i = 2; i * i <= v; i++)\n\
    \                    while (v % i == 0) fac.insert(i), v /= i;\n             \
    \   if (v > 1) fac.insert(v);\n                for (int g = 1; g < md; g++) {\n\
    \                    bool ok = true;\n                    for (auto i : fac)\n\
    \                        if (ModInt(g).pow((md - 1) / i) == 1) {\n           \
    \                 ok = false;\n                            break;\n          \
    \              }\n                    if (ok) return g;\n                }\n \
    \               return -1;\n            }();\n        }\n        return primitive_root;\n\
    \    }\n    int val;\n    MDCONST ModInt() : val(0) {}\n    MDCONST ModInt &_setval(lint\
    \ v) { return val = (v >= md ? v - md : v), *this; }\n    MDCONST ModInt(lint\
    \ v) { _setval(v % md + md); }\n    MDCONST explicit operator bool() const { return\
    \ val != 0; }\n    MDCONST ModInt operator+(const ModInt &x) const { return ModInt()._setval((lint)val\
    \ + x.val); }\n    MDCONST ModInt operator-(const ModInt &x) const {\n       \
    \ return ModInt()._setval((lint)val - x.val + md);\n    }\n    MDCONST ModInt\
    \ operator*(const ModInt &x) const {\n        return ModInt()._setval((lint)val\
    \ * x.val % md);\n    }\n    MDCONST ModInt operator/(const ModInt &x) const {\n\
    \        return ModInt()._setval((lint)val * x.inv() % md);\n    }\n    MDCONST\
    \ ModInt operator-() const { return ModInt()._setval(md - val); }\n    MDCONST\
    \ ModInt &operator+=(const ModInt &x) { return *this = *this + x; }\n    MDCONST\
    \ ModInt &operator-=(const ModInt &x) { return *this = *this - x; }\n    MDCONST\
    \ ModInt &operator*=(const ModInt &x) { return *this = *this * x; }\n    MDCONST\
    \ ModInt &operator/=(const ModInt &x) { return *this = *this / x; }\n    friend\
    \ MDCONST ModInt operator+(lint a, const ModInt &x) {\n        return ModInt()._setval(a\
    \ % md + x.val);\n    }\n    friend MDCONST ModInt operator-(lint a, const ModInt\
    \ &x) {\n        return ModInt()._setval(a % md - x.val + md);\n    }\n    friend\
    \ MDCONST ModInt operator*(lint a, const ModInt &x) {\n        return ModInt()._setval(a\
    \ % md * x.val % md);\n    }\n    friend MDCONST ModInt operator/(lint a, const\
    \ ModInt &x) {\n        return ModInt()._setval(a % md * x.inv() % md);\n    }\n\
    \    MDCONST bool operator==(const ModInt &x) const { return val == x.val; }\n\
    \    MDCONST bool operator!=(const ModInt &x) const { return val != x.val; }\n\
    \    MDCONST bool operator<(const ModInt &x) const {\n        return val < x.val;\n\
    \    } // To use std::map<ModInt, T>\n    friend std::istream &operator>>(std::istream\
    \ &is, ModInt &x) {\n        lint t;\n        return is >> t, x = ModInt(t), is;\n\
    \    }\n    MDCONST friend std::ostream &operator<<(std::ostream &os, const ModInt\
    \ &x) {\n        return os << x.val;\n    }\n    MDCONST ModInt pow(lint n) const\
    \ {\n        ModInt ans = 1, tmp = *this;\n        while (n) {\n            if\
    \ (n & 1) ans *= tmp;\n            tmp *= tmp, n >>= 1;\n        }\n        return\
    \ ans;\n    }\n\n    static std::vector<ModInt> facs, facinvs, invs;\n    MDCONST\
    \ static void _precalculation(int N) {\n        int l0 = facs.size();\n      \
    \  if (N > md) N = md;\n        if (N <= l0) return;\n        facs.resize(N),\
    \ facinvs.resize(N), invs.resize(N);\n        for (int i = l0; i < N; i++) facs[i]\
    \ = facs[i - 1] * i;\n        facinvs[N - 1] = facs.back().pow(md - 2);\n    \
    \    for (int i = N - 2; i >= l0; i--) facinvs[i] = facinvs[i + 1] * (i + 1);\n\
    \        for (int i = N - 1; i >= l0; i--) invs[i] = facinvs[i] * facs[i - 1];\n\
    \    }\n    MDCONST lint inv() const {\n        if (this->val < std::min(md >>\
    \ 1, 1 << 21)) {\n            while (this->val >= int(facs.size())) _precalculation(facs.size()\
    \ * 2);\n            return invs[this->val].val;\n        } else {\n         \
    \   return this->pow(md - 2).val;\n        }\n    }\n    MDCONST ModInt fac()\
    \ const {\n        while (this->val >= int(facs.size())) _precalculation(facs.size()\
    \ * 2);\n        return facs[this->val];\n    }\n    MDCONST ModInt facinv() const\
    \ {\n        while (this->val >= int(facs.size())) _precalculation(facs.size()\
    \ * 2);\n        return facinvs[this->val];\n    }\n    MDCONST ModInt doublefac()\
    \ const {\n        lint k = (this->val + 1) / 2;\n        return (this->val &\
    \ 1) ? ModInt(k * 2).fac() / (ModInt(2).pow(k) * ModInt(k).fac())\n          \
    \                     : ModInt(k).fac() * ModInt(2).pow(k);\n    }\n    MDCONST\
    \ ModInt nCr(const ModInt &r) const {\n        return (this->val < r.val) ? 0\
    \ : this->fac() * (*this - r).facinv() * r.facinv();\n    }\n    MDCONST ModInt\
    \ nPr(const ModInt &r) const {\n        return (this->val < r.val) ? 0 : this->fac()\
    \ * (*this - r).facinv();\n    }\n\n    ModInt sqrt() const {\n        if (val\
    \ == 0) return 0;\n        if (md == 2) return val;\n        if (pow((md - 1)\
    \ / 2) != 1) return 0;\n        ModInt b = 1;\n        while (b.pow((md - 1) /\
    \ 2) == 1) b += 1;\n        int e = 0, m = md - 1;\n        while (m % 2 == 0)\
    \ m >>= 1, e++;\n        ModInt x = pow((m - 1) / 2), y = (*this) * x * x;\n \
    \       x *= (*this);\n        ModInt z = b.pow(m);\n        while (y != 1) {\n\
    \            int j = 0;\n            ModInt t = y;\n            while (t != 1)\
    \ j++, t *= t;\n            z = z.pow(1LL << (e - j - 1));\n            x *= z,\
    \ z *= z, y *= z;\n            e = j;\n        }\n        return ModInt(std::min(x.val,\
    \ md - x.val));\n    }\n};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facs\
    \ = {1};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facinvs = {1};\n\
    template <int md> std::vector<ModInt<md>> ModInt<md>::invs = {0};\n// using mint\
    \ = ModInt<998244353>;\n// using mint = ModInt<1000000007>;\n#line 3 \"convolution/ntt.hpp\"\
    \n\n#line 5 \"convolution/ntt.hpp\"\n#include <array>\n#include <cassert>\n#line\
    \ 9 \"convolution/ntt.hpp\"\n\n// CUT begin\n// Integer convolution for arbitrary\
    \ mod\n// with NTT (and Garner's algorithm) for ModInt / ModIntRuntime class.\n\
    // We skip Garner's algorithm if `skip_garner` is true or mod is in `nttprimes`.\n\
    // input: a (size: n), b (size: m)\n// return: vector (size: n + m - 1)\ntemplate\
    \ <typename MODINT>\nstd::vector<MODINT> nttconv(std::vector<MODINT> a, std::vector<MODINT>\
    \ b, bool skip_garner);\n\nconstexpr int nttprimes[3] = {998244353, 167772161,\
    \ 469762049};\n\n// Integer FFT (Fast Fourier Transform) for ModInt class\n//\
    \ (Also known as Number Theoretic Transform, NTT)\n// is_inverse: inverse transform\n\
    // ** Input size must be 2^n **\ntemplate <typename MODINT> void ntt(std::vector<MODINT>\
    \ &a, bool is_inverse = false) {\n    int n = a.size();\n    if (n == 1) return;\n\
    \    static const int mod = MODINT::mod();\n    static const MODINT root = MODINT::get_primitive_root();\n\
    \    assert(__builtin_popcount(n) == 1 and (mod - 1) % n == 0);\n\n    static\
    \ std::vector<MODINT> w{1}, iw{1};\n    for (int m = w.size(); m < n / 2; m *=\
    \ 2) {\n        MODINT dw = root.pow((mod - 1) / (4 * m)), dwinv = 1 / dw;\n \
    \       w.resize(m * 2), iw.resize(m * 2);\n        for (int i = 0; i < m; i++)\
    \ w[m + i] = w[i] * dw, iw[m + i] = iw[i] * dwinv;\n    }\n\n    if (!is_inverse)\
    \ {\n        for (int m = n; m >>= 1;) {\n            for (int s = 0, k = 0; s\
    \ < n; s += 2 * m, k++) {\n                for (int i = s; i < s + m; i++) {\n\
    \                    MODINT x = a[i], y = a[i + m] * w[k];\n                 \
    \   a[i] = x + y, a[i + m] = x - y;\n                }\n            }\n      \
    \  }\n    } else {\n        for (int m = 1; m < n; m *= 2) {\n            for\
    \ (int s = 0, k = 0; s < n; s += 2 * m, k++) {\n                for (int i = s;\
    \ i < s + m; i++) {\n                    MODINT x = a[i], y = a[i + m];\n    \
    \                a[i] = x + y, a[i + m] = (x - y) * iw[k];\n                }\n\
    \            }\n        }\n        int n_inv = MODINT(n).inv();\n        for (auto\
    \ &v : a) v *= n_inv;\n    }\n}\ntemplate <int MOD>\nstd::vector<ModInt<MOD>>\
    \ nttconv_(const std::vector<int> &a, const std::vector<int> &b) {\n    int sz\
    \ = a.size();\n    assert(a.size() == b.size() and __builtin_popcount(sz) == 1);\n\
    \    std::vector<ModInt<MOD>> ap(sz), bp(sz);\n    for (int i = 0; i < sz; i++)\
    \ ap[i] = a[i], bp[i] = b[i];\n    ntt(ap, false);\n    if (a == b)\n        bp\
    \ = ap;\n    else\n        ntt(bp, false);\n    for (int i = 0; i < sz; i++) ap[i]\
    \ *= bp[i];\n    ntt(ap, true);\n    return ap;\n}\nlong long garner_ntt_(int\
    \ r0, int r1, int r2, int mod) {\n    using mint2 = ModInt<nttprimes[2]>;\n  \
    \  static const long long m01 = 1LL * nttprimes[0] * nttprimes[1];\n    static\
    \ const long long m0_inv_m1 = ModInt<nttprimes[1]>(nttprimes[0]).inv();\n    static\
    \ const long long m01_inv_m2 = mint2(m01).inv();\n\n    int v1 = (m0_inv_m1 *\
    \ (r1 + nttprimes[1] - r0)) % nttprimes[1];\n    auto v2 = (mint2(r2) - r0 - mint2(nttprimes[0])\
    \ * v1) * m01_inv_m2;\n    return (r0 + 1LL * nttprimes[0] * v1 + m01 % mod *\
    \ v2.val) % mod;\n}\ntemplate <typename MODINT>\nstd::vector<MODINT> nttconv(std::vector<MODINT>\
    \ a, std::vector<MODINT> b, bool skip_garner) {\n    if (a.empty() or b.empty())\
    \ return {};\n    int sz = 1, n = a.size(), m = b.size();\n    while (sz < n +\
    \ m) sz <<= 1;\n    if (sz <= 16) {\n        std::vector<MODINT> ret(n + m - 1);\n\
    \        for (int i = 0; i < n; i++) {\n            for (int j = 0; j < m; j++)\
    \ ret[i + j] += a[i] * b[j];\n        }\n        return ret;\n    }\n    int mod\
    \ = MODINT::mod();\n    if (skip_garner or\n        std::find(std::begin(nttprimes),\
    \ std::end(nttprimes), mod) != std::end(nttprimes)) {\n        a.resize(sz), b.resize(sz);\n\
    \        if (a == b) {\n            ntt(a, false);\n            b = a;\n     \
    \   } else {\n            ntt(a, false), ntt(b, false);\n        }\n        for\
    \ (int i = 0; i < sz; i++) a[i] *= b[i];\n        ntt(a, true);\n        a.resize(n\
    \ + m - 1);\n    } else {\n        std::vector<int> ai(sz), bi(sz);\n        for\
    \ (int i = 0; i < n; i++) ai[i] = a[i].val;\n        for (int i = 0; i < m; i++)\
    \ bi[i] = b[i].val;\n        auto ntt0 = nttconv_<nttprimes[0]>(ai, bi);\n   \
    \     auto ntt1 = nttconv_<nttprimes[1]>(ai, bi);\n        auto ntt2 = nttconv_<nttprimes[2]>(ai,\
    \ bi);\n        a.resize(n + m - 1);\n        for (int i = 0; i < n + m - 1; i++)\n\
    \            a[i] = garner_ntt_(ntt0[i].val, ntt1[i].val, ntt2[i].val, mod);\n\
    \    }\n    return a;\n}\n\ntemplate <typename MODINT>\nstd::vector<MODINT> nttconv(const\
    \ std::vector<MODINT> &a, const std::vector<MODINT> &b) {\n    return nttconv<MODINT>(a,\
    \ b, false);\n}\n#line 4 \"graph/shortest_path.hpp\"\n#include <deque>\n#include\
    \ <fstream>\n#include <functional>\n#include <limits>\n#include <queue>\n#include\
    \ <string>\n#line 12 \"graph/shortest_path.hpp\"\n\n// CUT begin\ntemplate <typename\
    \ T, T INF = std::numeric_limits<T>::max() / 2, int INVALID = -1>\nstruct ShortestPath\
    \ {\n    int V, E;\n    bool single_positive_weight;\n    T wmin, wmax;\n    std::vector<std::vector<std::pair<int,\
    \ T>>> to;\n\n    ShortestPath(int V = 0) : V(V), E(0), single_positive_weight(true),\
    \ wmin(0), wmax(0), to(V) {}\n    void add_edge(int s, int t, T w) {\n       \
    \ assert(0 <= s and s < V);\n        assert(0 <= t and t < V);\n        to[s].emplace_back(t,\
    \ w);\n        E++;\n        if (w > 0 and wmax > 0 and wmax != w) single_positive_weight\
    \ = false;\n        wmin = std::min(wmin, w);\n        wmax = std::max(wmax, w);\n\
    \    }\n\n    std::vector<T> dist;\n    std::vector<int> prev;\n\n    // Dijkstra\
    \ algorithm\n    // Complexity: O(E log E)\n    using Pque = std::priority_queue<std::pair<T,\
    \ int>, std::vector<std::pair<T, int>>,\n                                    \
    \ std::greater<std::pair<T, int>>>;\n    template <class Heap = Pque> void Dijkstra(int\
    \ s) {\n        assert(0 <= s and s < V);\n        dist.assign(V, INF);\n    \
    \    dist[s] = 0;\n        prev.assign(V, INVALID);\n        Heap pq;\n      \
    \  pq.emplace(0, s);\n        while (!pq.empty()) {\n            T d;\n      \
    \      int v;\n            std::tie(d, v) = pq.top();\n            pq.pop();\n\
    \            if (dist[v] < d) continue;\n            for (auto nx : to[v]) {\n\
    \                T dnx = d + nx.second;\n                if (dist[nx.first] >\
    \ dnx) {\n                    dist[nx.first] = dnx, prev[nx.first] = v;\n    \
    \                pq.emplace(dnx, nx.first);\n                }\n            }\n\
    \        }\n    }\n\n    // Dijkstra algorithm, O(V^2 + E)\n    void DijkstraVquad(int\
    \ s) {\n        assert(0 <= s and s < V);\n        dist.assign(V, INF);\n    \
    \    dist[s] = 0;\n        prev.assign(V, INVALID);\n        std::vector<char>\
    \ fixed(V, false);\n        while (true) {\n            int r = INVALID;\n   \
    \         T dr = INF;\n            for (int i = 0; i < V; i++) {\n           \
    \     if (!fixed[i] and dist[i] < dr) r = i, dr = dist[i];\n            }\n  \
    \          if (r == INVALID) break;\n            fixed[r] = true;\n          \
    \  int nxt;\n            T dx;\n            for (auto p : to[r]) {\n         \
    \       std::tie(nxt, dx) = p;\n                if (dist[nxt] > dist[r] + dx)\
    \ dist[nxt] = dist[r] + dx, prev[nxt] = r;\n            }\n        }\n    }\n\n\
    \    // Bellman-Ford algorithm\n    // Complexity: O(VE)\n    bool BellmanFord(int\
    \ s, int nb_loop) {\n        assert(0 <= s and s < V);\n        dist.assign(V,\
    \ INF), prev.assign(V, INVALID);\n        dist[s] = 0;\n        for (int l = 0;\
    \ l < nb_loop; l++) {\n            bool upd = false;\n            for (int v =\
    \ 0; v < V; v++) {\n                if (dist[v] == INF) continue;\n          \
    \      for (auto nx : to[v]) {\n                    T dnx = dist[v] + nx.second;\n\
    \                    if (dist[nx.first] > dnx) dist[nx.first] = dnx, prev[nx.first]\
    \ = v, upd = true;\n                }\n            }\n            if (!upd) return\
    \ true;\n        }\n        return false;\n    }\n\n    // Bellman-ford algorithm\
    \ using queue (deque)\n    // Complexity: O(VE)\n    // Requirement: no negative\
    \ loop\n    void SPFA(int s) {\n        assert(0 <= s and s < V);\n        dist.assign(V,\
    \ INF);\n        prev.assign(V, INVALID);\n        std::deque<int> q;\n      \
    \  std::vector<char> in_queue(V);\n        dist[s] = 0;\n        q.push_back(s),\
    \ in_queue[s] = 1;\n        while (!q.empty()) {\n            int now = q.front();\n\
    \            q.pop_front(), in_queue[now] = 0;\n            for (auto nx : to[now])\
    \ {\n                T dnx = dist[now] + nx.second;\n                int nxt =\
    \ nx.first;\n                if (dist[nxt] > dnx) {\n                    dist[nxt]\
    \ = dnx;\n                    if (!in_queue[nxt]) {\n                        if\
    \ (q.size() and dnx < dist[q.front()]) { // Small label first optimization\n \
    \                           q.push_front(nxt);\n                        } else\
    \ {\n                            q.push_back(nxt);\n                        }\n\
    \                        prev[nxt] = now, in_queue[nxt] = 1;\n               \
    \     }\n                }\n            }\n        }\n    }\n\n    void ZeroOneBFS(int\
    \ s) {\n        assert(0 <= s and s < V);\n        dist.assign(V, INF), prev.assign(V,\
    \ INVALID);\n        dist[s] = 0;\n        std::deque<int> que;\n        que.push_back(s);\n\
    \        while (!que.empty()) {\n            int v = que.front();\n          \
    \  que.pop_front();\n            for (auto nx : to[v]) {\n                T dnx\
    \ = dist[v] + nx.second;\n                if (dist[nx.first] > dnx) {\n      \
    \              dist[nx.first] = dnx, prev[nx.first] = v;\n                   \
    \ if (nx.second) {\n                        que.push_back(nx.first);\n       \
    \             } else {\n                        que.push_front(nx.first);\n  \
    \                  }\n                }\n            }\n        }\n    }\n\n \
    \   bool dag_solver(int s) {\n        assert(0 <= s and s < V);\n        std::vector<int>\
    \ indeg(V, 0);\n        std::queue<int> que;\n        que.push(s);\n        while\
    \ (que.size()) {\n            int now = que.front();\n            que.pop();\n\
    \            for (auto nx : to[now]) {\n                indeg[nx.first]++;\n \
    \               if (indeg[nx.first] == 1) que.push(nx.first);\n            }\n\
    \        }\n        dist.assign(V, INF), prev.assign(V, INVALID);\n        dist[s]\
    \ = 0;\n        que.push(s);\n        while (que.size()) {\n            int now\
    \ = que.front();\n            que.pop();\n            for (auto nx : to[now])\
    \ {\n                indeg[nx.first]--;\n                if (dist[nx.first] >\
    \ dist[now] + nx.second)\n                    dist[nx.first] = dist[now] + nx.second,\
    \ prev[nx.first] = now;\n                if (indeg[nx.first] == 0) que.push(nx.first);\n\
    \            }\n        }\n        return *max_element(indeg.begin(), indeg.end())\
    \ == 0;\n    }\n\n    // Retrieve a sequence of vertex ids that represents shortest\
    \ path [s, ..., goal]\n    // If not reachable to goal, return {}\n    std::vector<int>\
    \ retrieve_path(int goal) const {\n        assert(int(prev.size()) == V);\n  \
    \      assert(0 <= goal and goal < V);\n        if (dist[goal] == INF) return\
    \ {};\n        std::vector<int> ret{goal};\n        while (prev[goal] != INVALID)\
    \ {\n            goal = prev[goal];\n            ret.push_back(goal);\n      \
    \  }\n        std::reverse(ret.begin(), ret.end());\n        return ret;\n   \
    \ }\n\n    void solve(int s) {\n        if (wmin >= 0) {\n            if (single_positive_weight)\
    \ {\n                ZeroOneBFS(s);\n            } else {\n                if\
    \ ((long long)V * V < (E << 4)) {\n                    DijkstraVquad(s);\n   \
    \             } else {\n                    Dijkstra(s);\n                }\n\
    \            }\n        } else {\n            BellmanFord(s, V);\n        }\n\
    \    }\n\n    // Warshall-Floyd algorithm\n    // Complexity: O(E + V^3)\n   \
    \ std::vector<std::vector<T>> dist2d;\n    void WarshallFloyd() {\n        dist2d.assign(V,\
    \ std::vector<T>(V, INF));\n        for (int i = 0; i < V; i++) {\n          \
    \  dist2d[i][i] = 0;\n            for (auto p : to[i]) dist2d[i][p.first] = std::min(dist2d[i][p.first],\
    \ p.second);\n        }\n        for (int k = 0; k < V; k++) {\n            for\
    \ (int i = 0; i < V; i++) {\n                if (dist2d[i][k] == INF) continue;\n\
    \                for (int j = 0; j < V; j++) {\n                    if (dist2d[k][j]\
    \ == INF) continue;\n                    dist2d[i][j] = std::min(dist2d[i][j],\
    \ dist2d[i][k] + dist2d[k][j]);\n                }\n            }\n        }\n\
    \    }\n\n    void dump_graphviz(std::string filename = \"shortest_path\") const\
    \ {\n        std::ofstream ss(filename + \".DOT\");\n        ss << \"digraph{\\\
    n\";\n        for (int i = 0; i < V; i++) {\n            for (const auto &e :\
    \ to[i])\n                ss << i << \"->\" << e.first << \"[label=\" << e.second\
    \ << \"];\\n\";\n        }\n        ss << \"}\\n\";\n        ss.close();\n   \
    \     return;\n    }\n};\n#line 2 \"random/xorshift.hpp\"\n#include <cstdint>\n\
    \n// CUT begin\nuint32_t rand_int() // XorShift random integer generator\n{\n\
    \    static uint32_t x = 123456789, y = 362436069, z = 521288629, w = 88675123;\n\
    \    uint32_t t = x ^ (x << 11);\n    x = y;\n    y = z;\n    z = w;\n    return\
    \ w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));\n}\ndouble rand_double() { return (double)rand_int()\
    \ / UINT32_MAX; }\n#line 10 \"tree/test/frequency_table_of_tree_distance.stress.test.cpp\"\
    \nusing namespace std;\n\nusing mint = ModInt<998244353>;\n\nint main() {\n  \
    \  for (int t = 0; t < 10000; t++) {\n        int n = rand_int() % 100 + 1;\n\
    \        int w = rand_int() % n + 1;\n        vector<vector<int>> to(n);\n   \
    \     ShortestPath<int> graph(n);\n        for (int i = 1; i < n; i++) {\n   \
    \         int j = max<int>(0, i - 1 - rand_int() % w);\n            to[i].push_back(j);\n\
    \            to[j].push_back(i);\n            graph.add_edge(i, j, 1);\n     \
    \       graph.add_edge(j, i, 1);\n        }\n        vector<mint> weight(n);\n\
    \        for (auto &x : weight) x = rand_int() % mint::mod();\n\n        auto\
    \ ret1 = frequency_table_of_tree_distance(to).solve<mint, nttconv<mint>>(weight);\n\
    \        vector<mint> ret2(n);\n        for (int i = 0; i < n; i++) {\n      \
    \      graph.solve(i);\n            for (int j = i + 1; j < n; j++) ret2[graph.dist[j]]\
    \ += weight[i] * weight[j];\n        }\n        assert(ret1 == ret2);\n    }\n\
    \    cout << \"Hello World\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \ // DUMMY\n#include \"../frequency_table_of_tree_distance.hpp\"\n#include \"\
    ../../convolution/ntt.hpp\"\n#include \"../../graph/shortest_path.hpp\"\n#include\
    \ \"../../modint.hpp\"\n#include \"../../random/xorshift.hpp\"\n#include <cassert>\n\
    #include <iostream>\n#include <vector>\nusing namespace std;\n\nusing mint = ModInt<998244353>;\n\
    \nint main() {\n    for (int t = 0; t < 10000; t++) {\n        int n = rand_int()\
    \ % 100 + 1;\n        int w = rand_int() % n + 1;\n        vector<vector<int>>\
    \ to(n);\n        ShortestPath<int> graph(n);\n        for (int i = 1; i < n;\
    \ i++) {\n            int j = max<int>(0, i - 1 - rand_int() % w);\n         \
    \   to[i].push_back(j);\n            to[j].push_back(i);\n            graph.add_edge(i,\
    \ j, 1);\n            graph.add_edge(j, i, 1);\n        }\n        vector<mint>\
    \ weight(n);\n        for (auto &x : weight) x = rand_int() % mint::mod();\n\n\
    \        auto ret1 = frequency_table_of_tree_distance(to).solve<mint, nttconv<mint>>(weight);\n\
    \        vector<mint> ret2(n);\n        for (int i = 0; i < n; i++) {\n      \
    \      graph.solve(i);\n            for (int j = i + 1; j < n; j++) ret2[graph.dist[j]]\
    \ += weight[i] * weight[j];\n        }\n        assert(ret1 == ret2);\n    }\n\
    \    cout << \"Hello World\\n\";\n}\n"
  dependsOn:
  - tree/frequency_table_of_tree_distance.hpp
  - tree/centroid_decomposition.hpp
  - convolution/ntt.hpp
  - modint.hpp
  - graph/shortest_path.hpp
  - random/xorshift.hpp
  isVerificationFile: true
  path: tree/test/frequency_table_of_tree_distance.stress.test.cpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: tree/test/frequency_table_of_tree_distance.stress.test.cpp
layout: document
redirect_from:
- /verify/tree/test/frequency_table_of_tree_distance.stress.test.cpp
- /verify/tree/test/frequency_table_of_tree_distance.stress.test.cpp.html
title: tree/test/frequency_table_of_tree_distance.stress.test.cpp
---
