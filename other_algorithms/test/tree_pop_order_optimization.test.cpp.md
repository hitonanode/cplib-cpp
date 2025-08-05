---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other_algorithms/tree_pop_order_optimization.hpp
    title: "Tree pop order optimization / \"01 on Tree\" \uFF08\u6728\u306E\u6839\u304B\
      \u3089 2 \u6B21\u5143\u30D9\u30AF\u30C8\u30EB\u3084 01 \u6587\u5B57\u5217\u306A\
      \u3069\u3092 pop \u3059\u308B\u9806\u5217\u306B\u95A2\u3059\u308B\u6700\u5C0F\
      \u5316\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/rooted_tree_topological_order_with_minimum_inversions
    links:
    - https://judge.yosupo.jp/problem/rooted_tree_topological_order_with_minimum_inversions
  bundledCode: "#line 1 \"other_algorithms/test/tree_pop_order_optimization.test.cpp\"\
    \n#define PROBLEM                                                            \
    \                       \\\n    \"https://judge.yosupo.jp/problem/rooted_tree_topological_order_with_minimum_inversions\"\
    \n#line 2 \"other_algorithms/tree_pop_order_optimization.hpp\"\n#include <algorithm>\n\
    #include <cassert>\n#include <queue>\n#include <utility>\n#include <vector>\n\n\
    // \"01 on Tree\"\n// https://judge.yosupo.jp/problem/rooted_tree_topological_order_with_minimum_inversions\n\
    // https://yukicoder.me/problems/no/3148\ntemplate <class S> struct TreePopOrderOptimization\
    \ {\n    std::vector<std::vector<int>> to;\n    std::vector<S> labels;\n    int\
    \ root = -1;\n    std::vector<S> first_slope;\n    std::vector<int> par;\n\n \
    \   TreePopOrderOptimization(const std::vector<std::vector<int>> &to, const std::vector<S>\
    \ &labels,\n                             int root)\n        : to(to), labels(labels),\
    \ root(root), first_slope(to.size()), par(to.size(), -1) {\n\n        using Pque\
    \ = std::priority_queue<S, std::vector<S>, std::greater<S>>;\n        auto rec\
    \ = [&](auto &&self, int now, int prv) -> Pque {\n            std::vector<Pque>\
    \ chs;\n\n            for (int nxt : to[now]) {\n                if (nxt == prv)\
    \ continue;\n                assert(par[nxt] == -1);\n                par[nxt]\
    \ = now;\n                chs.emplace_back(self(self, nxt, now));\n          \
    \  }\n\n            const S &v = labels.at(now);\n            if (chs.empty())\
    \ {\n                first_slope[now] = v;\n                Pque pq;\n       \
    \         pq.emplace(v);\n                return pq;\n            } else {\n \
    \               S first = v;\n\n                const int idx = std::max_element(chs.begin(),\
    \ chs.end(),\n                                                 [](const auto &a,\
    \ const auto &b) {\n                                                     return\
    \ a.size() < b.size();\n                                                 }) -\n\
    \                                chs.begin();\n                std::swap(chs[idx],\
    \ chs.front());\n\n                for (int i = 1; i < (int)chs.size(); ++i) {\n\
    \                    while (!chs[i].empty()) {\n                        chs.front().emplace(chs[i].top());\n\
    \                        chs[i].pop();\n                    }\n              \
    \  }\n\n                while (!chs.front().empty() and chs.front().top() < first)\
    \ {\n                    first += chs.front().top();\n                    chs.front().pop();\n\
    \                }\n                chs.front().emplace(first_slope[now] = first);\n\
    \                return std::move(chs.front());\n            }\n        };\n\n\
    \        rec(rec, root, -1);\n    }\n\n    std::pair<std::vector<int>, S> Solve()\
    \ const { return SolveSubtree(root); }\n\n    // Generate optimal pop order of\
    \ the subproblem rooted at `r`.\n    std::pair<std::vector<int>, S> SolveSubtree(int\
    \ r) const {\n        using P = std::pair<S, int>;\n        std::priority_queue<P,\
    \ std::vector<P>, std::greater<P>> pq;\n        pq.emplace(first_slope.at(r),\
    \ r);\n\n        std::vector<int> order;\n        S ret = labels.at(r);\n    \
    \    while (!pq.empty()) {\n            const int idx = pq.top().second;\n   \
    \         order.emplace_back(idx);\n            pq.pop();\n            if (idx\
    \ != r) ret += labels.at(idx);\n\n            for (int nxt : to.at(idx)) {\n \
    \               if (nxt == par.at(idx)) continue;\n                pq.emplace(first_slope.at(nxt),\
    \ nxt);\n            }\n        }\n\n        return {order, ret};\n    }\n};\n\
    \ntemplate <class T> struct Vector01onTree {\n    T x, y;\n    T res;\n    Vector01onTree(T\
    \ x, T y) : x(x), y(y), res(0) {}\n    Vector01onTree() : x(0), y(0), res(0) {}\n\
    \    bool operator<(const Vector01onTree &r) const {\n        if (x == 0 and y\
    \ == 0) return false;\n        if (r.x == 0 and r.y == 0) return true;\n     \
    \   if (x == 0 and r.x == 0) return y < r.y;\n        if (x == 0) return false;\n\
    \        if (r.x == 0) return true;\n        return y * r.x < x * r.y; // be careful\
    \ of overflow\n    }\n    bool operator>(const Vector01onTree &r) const { return\
    \ r < *this; }\n\n    void operator+=(const Vector01onTree &r) {\n        res\
    \ += r.res + y * r.x;\n        x += r.x;\n        y += r.y;\n    }\n};\n\ntemplate\
    \ <class T>\nstd::pair<std::vector<int>, T>\nSolve01OnTree(const std::vector<std::vector<int>>\
    \ &to, const std::vector<T> &xs,\n              const std::vector<T> &ys, int\
    \ root) {\n\n    const int n = to.size();\n    std::vector<Vector01onTree<T>>\
    \ labels;\n    for (int i = 0; i < n; ++i) labels.emplace_back(xs.at(i), ys.at(i));\n\
    \n    const TreePopOrderOptimization<Vector01onTree<T>> tpo(to, labels, root);\n\
    \    auto [order, all_prod] = tpo.Solve();\n    return {order, all_prod.res};\n\
    }\n#line 4 \"other_algorithms/test/tree_pop_order_optimization.test.cpp\"\n#include\
    \ <iostream>\n#line 6 \"other_algorithms/test/tree_pop_order_optimization.test.cpp\"\
    \nusing namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    int N;\n    cin >> N;\n    vector<vector<int>> to(N);\n\n    for (int i\
    \ = 1; i < N; ++i) {\n        int p;\n        cin >> p;\n        to.at(p).push_back(i);\n\
    \        to.at(i).push_back(p);\n    }\n\n    vector<long long> c(N), d(N);\n\
    \    for (auto &e : c) cin >> e;\n    for (auto &e : d) cin >> e;\n\n    const\
    \ auto [order, ret] = Solve01OnTree(to, c, d, 0);\n    cout << ret << '\\n';\n\
    \    for (auto e : order) cout << e << ' ';\n    cout << '\\n';\n}\n"
  code: "#define PROBLEM                                                         \
    \                          \\\n    \"https://judge.yosupo.jp/problem/rooted_tree_topological_order_with_minimum_inversions\"\
    \n#include \"../tree_pop_order_optimization.hpp\"\n#include <iostream>\n#include\
    \ <vector>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    int N;\n    cin >> N;\n    vector<vector<int>> to(N);\n\n    for (int i\
    \ = 1; i < N; ++i) {\n        int p;\n        cin >> p;\n        to.at(p).push_back(i);\n\
    \        to.at(i).push_back(p);\n    }\n\n    vector<long long> c(N), d(N);\n\
    \    for (auto &e : c) cin >> e;\n    for (auto &e : d) cin >> e;\n\n    const\
    \ auto [order, ret] = Solve01OnTree(to, c, d, 0);\n    cout << ret << '\\n';\n\
    \    for (auto e : order) cout << e << ' ';\n    cout << '\\n';\n}\n"
  dependsOn:
  - other_algorithms/tree_pop_order_optimization.hpp
  isVerificationFile: true
  path: other_algorithms/test/tree_pop_order_optimization.test.cpp
  requiredBy: []
  timestamp: '2025-08-05 23:34:24+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: other_algorithms/test/tree_pop_order_optimization.test.cpp
layout: document
redirect_from:
- /verify/other_algorithms/test/tree_pop_order_optimization.test.cpp
- /verify/other_algorithms/test/tree_pop_order_optimization.test.cpp.html
title: other_algorithms/test/tree_pop_order_optimization.test.cpp
---
