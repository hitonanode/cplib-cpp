---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: convolution/fft_double.hpp
    title: convolution/fft_double.hpp
  - icon: ':heavy_check_mark:'
    path: tree/centroid_decomposition.hpp
    title: tree/centroid_decomposition.hpp
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
  bundledCode: "#line 2 \"tree/centroid_decomposition.hpp\"\n#include <tuple>\n#include\
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
    \ 2 \"convolution/fft_double.hpp\"\n#include <complex>\n#line 5 \"convolution/fft_double.hpp\"\
    \n\n// CUT begin\n// Convolution by FFT (Fast Fourier Transform)\n// Algorithm\
    \ based on http://kirika-comp.hatenablog.com/entry/2018/03/12/210446\n// Verified:\
    \ ATC001C (168 ms) https://atcoder.jp/contests/atc001/submissions/9243440\nusing\
    \ cmplx = std::complex<double>;\nvoid fft(int N, std::vector<cmplx> &a, double\
    \ dir) {\n    int i = 0;\n    for (int j = 1; j < N - 1; j++) {\n        for (int\
    \ k = N >> 1; k > (i ^= k); k >>= 1)\n            ;\n        if (j < i) std::swap(a[i],\
    \ a[j]);\n    }\n\n    std::vector<cmplx> zeta_pow(N);\n    for (int i = 0; i\
    \ < N; i++) {\n        double theta = M_PI / N * i * dir;\n        zeta_pow[i]\
    \ = {cos(theta), sin(theta)};\n    }\n\n    for (int m = 1; m < N; m *= 2) {\n\
    \        for (int y = 0; y < m; y++) {\n            cmplx fac = zeta_pow[N / m\
    \ * y];\n            for (int x = 0; x < N; x += 2 * m) {\n                int\
    \ u = x + y;\n                int v = x + y + m;\n                cmplx s = a[u]\
    \ + fac * a[v];\n                cmplx t = a[u] - fac * a[v];\n              \
    \  a[u] = s;\n                a[v] = t;\n            }\n        }\n    }\n}\n\
    template <typename T>\nstd::vector<cmplx> conv_cmplx(const std::vector<T> &a,\
    \ const std::vector<T> &b) {\n    int N = 1;\n    while (N < (int)a.size() + (int)b.size())\
    \ N *= 2;\n    std::vector<cmplx> a_(N), b_(N);\n    for (int i = 0; i < (int)a.size();\
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
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: tree/test/frequency_table_of_tree_distance.test.cpp
layout: document
redirect_from:
- /verify/tree/test/frequency_table_of_tree_distance.test.cpp
- /verify/tree/test/frequency_table_of_tree_distance.test.cpp.html
title: tree/test/frequency_table_of_tree_distance.test.cpp
---
