---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: convolution/fft_double.hpp
    title: convolution/fft_double.hpp
  - icon: ':heavy_check_mark:'
    path: tree/centroid_decomposition.hpp
    title: "Centroid decomposition \uFF08\u68EE\u306E\u91CD\u5FC3\u5206\u89E3\uFF09"
  - icon: ':heavy_check_mark:'
    path: tree/frequency_table_of_tree_distance.hpp
    title: Frequency table of tree distance
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/frequency_table_of_tree_distance
    links:
    - https://judge.yosupo.jp/problem/frequency_table_of_tree_distance
  bundledCode: "#line 2 \"tree/centroid_decomposition.hpp\"\n#include <cassert>\n\
    #include <utility>\n#include <vector>\n\n// Centroid Decomposition\n// Verification:\
    \ https://yukicoder.me/problems/no/2892\n// find_current_centroids(int r, int\
    \ conn_size): Enumerate centroid(s) of the subtree which `r` belongs to.\nstruct\
    \ CentroidDecomposition {\n    int V;\n    std::vector<std::vector<int>> to;\n\
    \nprivate:\n    std::vector<int> is_alive;\n    std::vector<int> subtree_size;\n\
    \n    template <class F> void decompose(int r, int conn_size, F callback) {\n\n\
    \        const int c = find_current_centroids(r, conn_size).first;\n        is_alive.at(c)\
    \ = 0;\n\n        callback(c);\n\n        for (int nxt : to.at(c)) {\n       \
    \     if (!is_alive.at(nxt)) continue;\n            int next_size = subtree_size.at(nxt);\n\
    \            if (subtree_size.at(nxt) > subtree_size.at(c))\n                next_size\
    \ = subtree_size.at(r) - subtree_size.at(c);\n            decompose(nxt, next_size,\
    \ callback);\n        }\n    }\n\npublic:\n    CentroidDecomposition(int v = 0)\
    \ : V(v), to(v), is_alive(v, 1), subtree_size(v) {}\n\n    CentroidDecomposition(int\
    \ v, const std::vector<std::pair<int, int>> &tree_edges)\n        : CentroidDecomposition(v)\
    \ {\n        for (auto e : tree_edges) add_edge(e.first, e.second);\n    }\n\n\
    \    void add_edge(int v1, int v2) {\n        assert(0 <= v1 and v1 < V and 0\
    \ <= v2 and v2 < V);\n        assert(v1 != v2);\n        to.at(v1).push_back(v2),\
    \ to.at(v2).emplace_back(v1);\n    }\n\n    std::pair<int, int> find_current_centroids(int\
    \ r, int conn_size) {\n        assert(is_alive.at(r));\n\n        const int thres\
    \ = conn_size / 2;\n\n        int c1 = -1, c2 = -1;\n\n        auto rec_search\
    \ = [&](auto &&self, int now, int prv) -> void {\n            bool is_centroid\
    \ = true;\n            subtree_size.at(now) = 1;\n            for (int nxt : to.at(now))\
    \ {\n                if (nxt == prv or !is_alive.at(nxt)) continue;\n        \
    \        self(self, nxt, now);\n                subtree_size.at(now) += subtree_size.at(nxt);\n\
    \                if (subtree_size.at(nxt) > thres) is_centroid = false;\n    \
    \        }\n            if (conn_size - subtree_size.at(now) > thres) is_centroid\
    \ = false;\n\n            if (is_centroid) (c1 < 0 ? c1 : c2) = now;\n       \
    \ };\n        rec_search(rec_search, r, -1);\n\n        return {c1, c2};\n   \
    \ }\n\n    template <class F> void run(int r, F callback) {\n        int conn_size\
    \ = 0;\n\n        auto rec = [&](auto &&self, int now, int prv) -> void {\n  \
    \          ++conn_size;\n            is_alive.at(now) = 1;\n\n            for\
    \ (int nxt : to.at(now)) {\n                if (nxt == prv) continue;\n      \
    \          self(self, nxt, now);\n            }\n        };\n        rec(rec,\
    \ r, -1);\n\n        decompose(r, conn_size, callback);\n    }\n\n    std::vector<int>\
    \ centroid_decomposition(int r) {\n        std::vector<int> res;\n        run(r,\
    \ [&](int v) { res.push_back(v); });\n        return res;\n    }\n};\n#line 2\
    \ \"tree/frequency_table_of_tree_distance.hpp\"\n#include <algorithm>\n#line 5\
    \ \"tree/frequency_table_of_tree_distance.hpp\"\n\nstruct frequency_table_of_tree_distance\
    \ {\n    std::vector<std::vector<int>> tos;\n    std::vector<int> cd;\n    std::vector<std::pair<int,\
    \ int>> tmp;\n    std::vector<int> alive;\n\n    void _dfs(int now, int prv, int\
    \ depth) {\n        // if (int(tmp.size()) <= depth) tmp.resize(depth + 1, 0);\n\
    \        // tmp[depth]++;\n        tmp.emplace_back(now, depth);\n        for\
    \ (auto nxt : tos[now]) {\n            if (alive[nxt] and nxt != prv) _dfs(nxt,\
    \ now, depth + 1);\n        }\n    }\n    std::vector<std::pair<int, int>> cnt_dfs(int\
    \ root) {\n        return tmp.clear(), _dfs(root, -1, 0), tmp;\n    }\n    frequency_table_of_tree_distance(const\
    \ std::vector<std::vector<int>> &to) {\n        tos = to;\n\n        CentroidDecomposition\
    \ c(to.size());\n        for (int i = 0; i < int(to.size()); i++) {\n        \
    \    for (int j : to[i]) {\n                if (i < j) c.add_edge(i, j);\n   \
    \         }\n        }\n\n        cd = c.centroid_decomposition(0);\n    }\n \
    \   template <class S, std::vector<S> (*conv)(const std::vector<S> &, const std::vector<S>\
    \ &)>\n    std::vector<S> solve(const std::vector<S> &weight) {\n        alive.assign(tos.size(),\
    \ 1);\n        std::vector<S> ret(tos.size());\n        std::vector<S> v;\n  \
    \      for (auto root : cd) {\n            std::vector<std::vector<S>> vv;\n \
    \           alive[root] = 0;\n            for (auto nxt : tos[root]) {\n     \
    \           if (!alive[nxt]) continue;\n                v.clear();\n         \
    \       for (auto p : cnt_dfs(nxt)) {\n                    while (int(v.size())\
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
    \ 2 \"convolution/fft_double.hpp\"\n#include <complex>\n#line 5 \"convolution/fft_double.hpp\"\
    \n\n// Convolution by FFT (Fast Fourier Transform)\n// Algorithm based on http://kirika-comp.hatenablog.com/entry/2018/03/12/210446\n\
    // Verified: ATC001C (168 ms) https://atcoder.jp/contests/atc001/submissions/9243440\n\
    using cmplx = std::complex<double>;\nvoid fft(int N, std::vector<cmplx> &a, double\
    \ dir) {\n    int i = 0;\n    for (int j = 1; j < N - 1; j++) {\n        for (int\
    \ k = N >> 1; k > (i ^= k); k >>= 1) {}\n        if (j < i) std::swap(a[i], a[j]);\n\
    \    }\n\n    std::vector<cmplx> zeta_pow(N);\n    for (int i = 0; i < N; i++)\
    \ {\n        double theta = M_PI / N * i * dir;\n        zeta_pow[i] = {cos(theta),\
    \ sin(theta)};\n    }\n\n    for (int m = 1; m < N; m *= 2) {\n        for (int\
    \ y = 0; y < m; y++) {\n            cmplx fac = zeta_pow[N / m * y];\n       \
    \     for (int x = 0; x < N; x += 2 * m) {\n                int u = x + y;\n \
    \               int v = x + y + m;\n                cmplx s = a[u] + fac * a[v];\n\
    \                cmplx t = a[u] - fac * a[v];\n                a[u] = s;\n   \
    \             a[v] = t;\n            }\n        }\n    }\n}\ntemplate <typename\
    \ T>\nstd::vector<cmplx> conv_cmplx(const std::vector<T> &a, const std::vector<T>\
    \ &b) {\n    int N = 1;\n    while (N < (int)a.size() + (int)b.size()) N *= 2;\n\
    \    std::vector<cmplx> a_(N), b_(N);\n    for (int i = 0; i < (int)a.size();\
    \ i++) a_[i] = a[i];\n    for (int i = 0; i < (int)b.size(); i++) b_[i] = b[i];\n\
    \    fft(N, a_, 1);\n    fft(N, b_, 1);\n    for (int i = 0; i < N; i++) a_[i]\
    \ *= b_[i];\n    fft(N, a_, -1);\n    for (int i = 0; i < N; i++) a_[i] /= N;\n\
    \    return a_;\n}\n// retval[i] = \\sum_j a[j]b[i - j]\n// Requirement: length\
    \ * max(a) * max(b) < 10^15\ntemplate <typename T>\nstd::vector<long long int>\
    \ fftconv(const std::vector<T> &a, const std::vector<T> &b) {\n    std::vector<cmplx>\
    \ ans = conv_cmplx(a, b);\n    std::vector<long long int> ret(ans.size());\n \
    \   for (int i = 0; i < (int)ans.size(); i++) ret[i] = floor(ans[i].real() + 0.5);\n\
    \    ret.resize(a.size() + b.size() - 1);\n    return ret;\n}\n#line 4 \"tree/test/frequency_table_of_tree_distance.test.cpp\"\
    \n#include <iostream>\n#line 6 \"tree/test/frequency_table_of_tree_distance.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/frequency_table_of_tree_distance\"\
    \nusing namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    int N;\n    cin >> N;\n    vector<vector<int>> to(N);\n    for (int i =\
    \ 0; i < N - 1; i++) {\n        int s, t;\n        cin >> s >> t;\n        to[s].emplace_back(t),\
    \ to[t].emplace_back(s);\n    }\n\n    auto ret =\n        frequency_table_of_tree_distance(to).solve<long\
    \ long, fftconv>(std::vector<long long>(N, 1));\n    for (int i = 1; i < N; i++)\
    \ cout << ret[i] << ' ';\n    cout << '\\n';\n}\n"
  code: "#include \"../frequency_table_of_tree_distance.hpp\"\n#include \"../../convolution/fft_double.hpp\"\
    \n#include <algorithm>\n#include <iostream>\n#include <vector>\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/frequency_table_of_tree_distance\"\nusing\
    \ namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    int N;\n    cin >> N;\n    vector<vector<int>> to(N);\n    for (int i =\
    \ 0; i < N - 1; i++) {\n        int s, t;\n        cin >> s >> t;\n        to[s].emplace_back(t),\
    \ to[t].emplace_back(s);\n    }\n\n    auto ret =\n        frequency_table_of_tree_distance(to).solve<long\
    \ long, fftconv>(std::vector<long long>(N, 1));\n    for (int i = 1; i < N; i++)\
    \ cout << ret[i] << ' ';\n    cout << '\\n';\n}\n"
  dependsOn:
  - tree/frequency_table_of_tree_distance.hpp
  - tree/centroid_decomposition.hpp
  - convolution/fft_double.hpp
  isVerificationFile: true
  path: tree/test/frequency_table_of_tree_distance.test.cpp
  requiredBy: []
  timestamp: '2024-09-25 00:42:32+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: tree/test/frequency_table_of_tree_distance.test.cpp
layout: document
redirect_from:
- /verify/tree/test/frequency_table_of_tree_distance.test.cpp
- /verify/tree/test/frequency_table_of_tree_distance.test.cpp.html
title: tree/test/frequency_table_of_tree_distance.test.cpp
---
