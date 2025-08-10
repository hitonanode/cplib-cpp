---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other_algorithms/monge_d_edge_shortest_paths_enum.hpp
    title: "Shortest paths of DAG with Monge weights using $d = 1, \\ldots, d_{\\\
      mathrm{max}}$ edges \uFF08Monge \u91CD\u307F DAG \u306E\u4F7F\u7528\u8FBA\u6570\
      \u6BCE\u306E\u6700\u77ED\u8DEF\u9577\u5217\u6319\uFF09"
  - icon: ':heavy_check_mark:'
    path: other_algorithms/smawk.hpp
    title: Totally Monotone Matrix Searching (SMAWK)
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/952
    links:
    - https://yukicoder.me/problems/no/952
  bundledCode: "#line 1 \"other_algorithms/test/monge_d_edge_shortest_paths_enum.yuki952.test.cpp\"\
    \n#define PROBLEM \"https://yukicoder.me/problems/no/952\"\n\n#line 2 \"other_algorithms/smawk.hpp\"\
    \n#include <cassert>\n#include <functional>\n#include <numeric>\n#include <utility>\n\
    #include <vector>\n\n// SMAWK: finding minima of totally monotone function f(i,\
    \ j) (0 <= i < N, 0 <= j < M) for each i\n// Constraints: every submatrix of f(i,\
    \ j) is monotone.\n// Complexity: O(N + M)\n// Reference:\n// https://topcoder-g-hatena-ne-jp.jag-icpc.org/spaghetti_source/20120923/1348327542.html\n\
    // http://web.cs.unlv.edu/larmore/Courses/CSC477/monge.pdf\n// Verify: https://codeforces.com/contest/1423/submission/98368491\n\
    template <class T>\nstd::vector<std::pair<int, T>> SMAWK(int N, int M, const std::function<T(int\
    \ i, int j)> &weight) {\n    std::vector<std::pair<int, T>> minima(N);\n\n   \
    \ auto rec = [&](auto &&self, const std::vector<int> &js, int ib, int ie, int\
    \ id) {\n        if (ib > ie) return;\n        std::vector<int> js2;\n       \
    \ int i = ib;\n        for (int j : js) {\n            while (!js2.empty() and\
    \ weight(i, js2.back()) >= weight(i, j)) js2.pop_back(), i -= id;\n          \
    \  if (int(js2.size()) != (ie - ib) / id) js2.push_back(j), i += id;\n       \
    \ }\n        self(self, js2, ib + id, ie, id * 2);\n\n        for (int i = ib,\
    \ q = 0; i <= ie; i += id * 2) {\n            const int jt = (i + id <= ie ? minima[i\
    \ + id].first : js.back());\n            T fm = 0;\n            bool init = true;\n\
    \            for (; q < int(js.size()); ++q) {\n                const T fq = weight(i,\
    \ js[q]);\n                if (init or fm > fq) fm = fq, minima[i] = std::make_pair(js[q],\
    \ fq);\n                init = false;\n                if (js[q] == jt) break;\n\
    \            }\n        }\n    };\n\n    std::vector<int> js(M);\n    std::iota(js.begin(),\
    \ js.end(), 0);\n    rec(rec, js, 0, N - 1, 1);\n\n    return minima;\n}\n\n//\
    \ Concave max-plus convolution\n// b must be concave\n// Complexity: O(n + m)\n\
    // Verify: https://www.codechef.com/problems/MAXPREFFLIP\ntemplate <class S, S\
    \ INF>\nstd::vector<S> concave_max_plus_convolution(const std::vector<S> &a, const\
    \ std::vector<S> &b) {\n    const int n = a.size(), m = b.size();\n\n    auto\
    \ is_concave = [&](const std::vector<S> &u) -> bool {\n        for (int i = 1;\
    \ i + 1 < int(u.size()); ++i) {\n            if (u[i - 1] + u[i + 1] > u[i] +\
    \ u[i]) return false;\n        }\n        return true;\n    };\n\n    bool a_concave\
    \ = is_concave(a), b_concave = is_concave(b);\n    assert(a_concave or b_concave);\n\
    \    if (!b_concave) return concave_max_plus_convolution<S, INF>(b, a);\n\n  \
    \  auto select = [&](int i, int j) -> S {\n        int aidx = j, bidx = i - j;\n\
    \        if (bidx < 0 or bidx >= m or aidx >= n) return INF;\n        return -(a[aidx]\
    \ + b[bidx]);\n    };\n    const auto minima = SMAWK<S>(n + m - 1, n, select);\n\
    \    std::vector<S> ret;\n    for (auto x : minima) ret.push_back(-x.second);\n\
    \    return ret;\n}\n#line 3 \"other_algorithms/monge_d_edge_shortest_paths_enum.hpp\"\
    \n\n#line 7 \"other_algorithms/monge_d_edge_shortest_paths_enum.hpp\"\n\n// Calculate\
    \ min cost paths of N vertices DAG from 0 to (N - 1), whose weight is Monge\n\
    // returns vector<T> costs, where costs[d - 1] == (min cost from 0 to (N - 1)\
    \ with exactly d edges)\n// Complexity: O(N maxD) (if SMAWK is used)\n// Verify:\
    \ https://yukicoder.me/problems/no/952\n// Verify: https://mofecoder.com/contests/monoxercon_202508/tasks/monoxercon_202508_k\n\
    template <class T>\nstd::vector<T>\nMongeDEdgeShortestPaths(int N, int max_d,\
    \ const std::function<T(int i, int j)> &weight, T inf) {\n    assert(max_d < N);\n\
    \    std::vector<T> ans;\n\n    std::vector<T> dp(N, inf);\n    dp.at(0) = 0;\n\
    \    // std::vector prevs(max_d, std::vector<int>(N, -1)); // if you need to retrieve\
    \ path\n\n    std::vector<T> costs;\n    for (int d = 1; d <= max_d; ++d) {\n\
    \        // MonotoneMinima<T>() is Also OK\n        const auto res = SMAWK<T>(\n\
    \            N, N - 1, [&](int j, int i) -> T { return i < j ? dp[i] + weight(i,\
    \ j) : inf; });\n\n        for (int i = d; i < N; ++i) dp.at(i) = res.at(i).second;\n\
    \        // for (int i = d; i < N; ++i) {\n        //     prevs.at(d - 1).at(i)\
    \ = res.at(i).first;\n        // }\n        costs.push_back(dp.at(N - 1));\n \
    \   }\n\n    return costs;\n}\n#line 4 \"other_algorithms/test/monge_d_edge_shortest_paths_enum.yuki952.test.cpp\"\
    \n\n#include <algorithm>\n#include <iostream>\nusing namespace std;\n\nint main()\
    \ {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\n    int N;\n    cin\
    \ >> N;\n    vector<int> A(N);\n    for (auto &a : A) cin >> a;\n\n    vector<long\
    \ long> cs(N + 1);\n    for (int i = 0; i < N; ++i) cs.at(i + 1) = cs.at(i) +\
    \ A.at(i);\n\n    constexpr long long inf = 1LL << 60;\n\n    auto f = [&](int\
    \ i, int j) -> long long {\n        long long sum = cs.at(j - 1) - cs.at(i);\n\
    \        return sum * sum;\n    };\n\n    auto costs = MongeDEdgeShortestPaths<long\
    \ long>(N + 2, N, f, inf);\n    std::reverse(costs.begin(), costs.end());\n  \
    \  for (auto x : costs) cout << x << '\\n';\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/952\"\n\n#include \"../monge_d_edge_shortest_paths_enum.hpp\"\
    \n\n#include <algorithm>\n#include <iostream>\nusing namespace std;\n\nint main()\
    \ {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\n    int N;\n    cin\
    \ >> N;\n    vector<int> A(N);\n    for (auto &a : A) cin >> a;\n\n    vector<long\
    \ long> cs(N + 1);\n    for (int i = 0; i < N; ++i) cs.at(i + 1) = cs.at(i) +\
    \ A.at(i);\n\n    constexpr long long inf = 1LL << 60;\n\n    auto f = [&](int\
    \ i, int j) -> long long {\n        long long sum = cs.at(j - 1) - cs.at(i);\n\
    \        return sum * sum;\n    };\n\n    auto costs = MongeDEdgeShortestPaths<long\
    \ long>(N + 2, N, f, inf);\n    std::reverse(costs.begin(), costs.end());\n  \
    \  for (auto x : costs) cout << x << '\\n';\n}\n"
  dependsOn:
  - other_algorithms/monge_d_edge_shortest_paths_enum.hpp
  - other_algorithms/smawk.hpp
  isVerificationFile: true
  path: other_algorithms/test/monge_d_edge_shortest_paths_enum.yuki952.test.cpp
  requiredBy: []
  timestamp: '2025-08-10 22:53:14+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: other_algorithms/test/monge_d_edge_shortest_paths_enum.yuki952.test.cpp
layout: document
redirect_from:
- /verify/other_algorithms/test/monge_d_edge_shortest_paths_enum.yuki952.test.cpp
- /verify/other_algorithms/test/monge_d_edge_shortest_paths_enum.yuki952.test.cpp.html
title: other_algorithms/test/monge_d_edge_shortest_paths_enum.yuki952.test.cpp
---
