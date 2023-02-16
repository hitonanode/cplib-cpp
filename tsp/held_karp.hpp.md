---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: tsp/csr_distance_matrix.hpp
    title: tsp/csr_distance_matrix.hpp
  - icon: ':warning:'
    path: tsp/minimum_one_tree.hpp
    title: tsp/minimum_one_tree.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - http://webhotel4.ruc.dk/~keld/research/LKH/LKH-2.0/DOC/LKH_REPORT.pdf
  bundledCode: "#line 2 \"tsp/held_karp.hpp\"\n\n#line 2 \"tsp/csr_distance_matrix.hpp\"\
    \n\n#include <algorithm>\n#include <utility>\n#include <vector>\n\ntemplate <class\
    \ T> class csr_distance_matrix {\n\n    int _rows = 0;\n    std::vector<int> begins;\n\
    \    std::vector<std::pair<int, T>> vals;\n\npublic:\n    csr_distance_matrix()\
    \ : csr_distance_matrix({}, 0) {}\n\n    csr_distance_matrix(const std::vector<std::tuple<int,\
    \ int, T>> &init, int rows)\n        : _rows(rows), begins(rows + 1) {\n     \
    \   std::vector<int> degs(rows);\n        for (const auto &p : init) ++degs.at(std::get<0>(p));\n\
    \n        for (int i = 0; i < rows; ++i) begins.at(i + 1) = begins.at(i) + degs.at(i);\n\
    \n        vals.resize(init.size(), std::make_pair(-1, T()));\n        for (auto\
    \ [i, j, w] : init) vals.at(begins.at(i + 1) - (degs.at(i)--)) = {j, w};\n   \
    \ }\n\n    void apply_pi(const std::vector<T> &pi) {\n        for (int i = 0;\
    \ i < n(); ++i) {\n            for (auto &[j, d] : adjacents(i)) d += pi.at(i)\
    \ + pi.at(j);\n        }\n    }\n\n    int n() const noexcept { return _rows;\
    \ }\n\n    struct adjacents_sequence {\n        csr_distance_matrix *ptr;\n  \
    \      int from;\n\n        using iterator = typename std::vector<std::pair<int,\
    \ T>>::iterator;\n        iterator begin() { return std::next(ptr->vals.begin(),\
    \ ptr->begins.at(from)); }\n        iterator end() { return std::next(ptr->vals.begin(),\
    \ ptr->begins.at(from + 1)); }\n    };\n\n    struct const_adjacents_sequence\
    \ {\n        const csr_distance_matrix *ptr;\n        const int from;\n\n    \
    \    using const_iterator = typename std::vector<std::pair<int, T>>::const_iterator;\n\
    \        const_iterator begin() const {\n            return std::next(ptr->vals.cbegin(),\
    \ ptr->begins.at(from));\n        }\n        const_iterator end() const {\n  \
    \          return std::next(ptr->vals.cbegin(), ptr->begins.at(from + 1));\n \
    \       }\n    };\n\n    adjacents_sequence adjacents(int from) { return {this,\
    \ from}; }\n\n    const_adjacents_sequence adjacents(int from) const { return\
    \ {this, from}; }\n    const_adjacents_sequence operator()(int from) const { return\
    \ {this, from}; }\n};\n\ntemplate <class DistanceMatrix> auto build_adjacent_info(const\
    \ DistanceMatrix &dist, int sz) {\n    using T = decltype((*dist.adjacents(0).begin()).second);\n\
    \n    const std::vector<std::vector<T>> alpha = calc_lkh_alpha(dist);\n\n    std::vector<std::tuple<int,\
    \ int, T>> adjacent_edges;\n\n    std::vector<std::tuple<T, T, int>> candidates;\n\
    \    for (int i = 0; i < dist.n(); ++i) {\n        candidates.clear();\n     \
    \   for (auto [j, d] : dist.adjacents(i)) {\n            if (i != j) candidates.emplace_back(alpha.at(i).at(j),\
    \ d, j);\n        }\n\n        const int final_sz = std::min<int>(sz, candidates.size());\n\
    \        std::nth_element(candidates.begin(), candidates.begin() + final_sz, candidates.end());\n\
    \n        candidates.resize(final_sz);\n        std::sort(candidates.begin(),\
    \ candidates.end(),\n                  [&](const auto &l, const auto &r) { return\
    \ std::get<1>(l) < std::get<1>(r); });\n        for (auto [alpha, dij, j] : candidates)\
    \ adjacent_edges.emplace_back(i, j, dij);\n    }\n    return csr_distance_matrix(adjacent_edges,\
    \ dist.n());\n}\n#line 2 \"tsp/minimum_one_tree.hpp\"\n\n#include <numeric>\n\
    #line 6 \"tsp/minimum_one_tree.hpp\"\n\ntemplate <class T, class DistanceMatrix>\n\
    std::pair<T, std::vector<int>>\nminimum_one_tree(const DistanceMatrix &dist, const\
    \ std::vector<T> &pi) {\n\n    assert(dist.n() > 2);\n    std::vector<T> dp(dist.n(),\
    \ std::numeric_limits<T>::max());\n    std::vector<int> prv(dist.n(), -1);\n \
    \   std::vector<int> used(dist.n());\n\n    auto fix_v = [&](int x) -> void {\n\
    \        dp.at(x) = std::numeric_limits<T>::max();\n        used.at(x) = 1;\n\
    \        for (auto [y, d] : dist.adjacents(x)) {\n            if (used.at(y))\
    \ continue;\n            if (T len = pi.at(x) + pi.at(y) + d; len < dp.at(y))\
    \ dp.at(y) = len, prv.at(y) = x;\n        }\n    };\n\n    T W = T();\n    std::vector<int>\
    \ V(dist.n(), -2);\n\n    fix_v(0);\n    for (int t = 0; t < dist.n() - 1; ++t)\
    \ {\n        int i = std::min_element(dp.cbegin(), dp.cend()) - dp.cbegin();\n\
    \        W += dp.at(i);\n        ++V.at(i);\n        ++V.at(prv.at(i));\n    \
    \    fix_v(i);\n    }\n\n    // p.26, http://webhotel4.ruc.dk/~keld/research/LKH/LKH-2.0/DOC/LKH_REPORT.pdf\n\
    \    T wlo = T();\n    int ilo = -1, jlo = -1;\n    for (int i = 0; i < dist.n();\
    \ ++i) {\n        if (V.at(i) != -1) continue;\n        T tmp = T();\n       \
    \ int jtmp = -1;\n        for (auto [j, d] : dist.adjacents(i)) {\n          \
    \  if (prv.at(i) == j or prv.at(j) == i or i == j) continue;\n            if (T\
    \ len = pi.at(i) + pi.at(j) + d; jtmp == -1 or tmp > len) tmp = len, jtmp = j;\n\
    \        }\n        if (jtmp != -1 and (ilo == -1 or wlo < tmp)) wlo = tmp, ilo\
    \ = i, jlo = jtmp;\n    }\n    ++V.at(ilo);\n    ++V.at(jlo);\n\n    W += wlo\
    \ - std::accumulate(pi.cbegin(), pi.cend(), T()) * 2;\n\n    return {W, V};\n\
    }\n#line 5 \"tsp/held_karp.hpp\"\n\n#line 9 \"tsp/held_karp.hpp\"\n\n// Held\u2013\
    Karp lower bound\n// http://webhotel4.ruc.dk/~keld/research/LKH/LKH-2.0/DOC/LKH_REPORT.pdf\n\
    // p.26, p.33\ntemplate <class DistanceMatrix> auto held_karp_lower_bound(const\
    \ DistanceMatrix &dist) {\n    using T = decltype((*dist.adjacents(0).begin()).second);\n\
    \n    std::vector<T> best_pi(dist.n()), pi(dist.n());\n    std::vector<int> V;\n\
    \    T W;\n    std::tie(W, V) = minimum_one_tree(dist, pi);\n    if (std::count(V.cbegin(),\
    \ V.cend(), 0) == dist.n()) return std::make_pair(W, pi);\n\n    std::vector<int>\
    \ lastV = V;\n\n    T BestW = W;\n    const int initial_period = (dist.n() + 1)\
    \ / 2;\n    bool is_initial_phase = true;\n    int period = initial_period;\n\n\
    \    const auto sparse_subgraph = build_adjacent_info(dist, 50); // p.47\n\n \
    \   for (long long t0 = 1; t0 > 0; period /= 2, t0 /= 2) {\n        for (int p\
    \ = 1; t0 > 0 and p <= period; ++p) {\n            for (int i = 0; i < dist.n();\
    \ ++i) {\n                if (V.at(i) != 0) pi.at(i) += t0 * (7 * V.at(i) + 3\
    \ * lastV.at(i)) / 10;\n            }\n            std::swap(lastV, V);\n    \
    \        std::tie(W, V) = minimum_one_tree(sparse_subgraph, pi);\n           \
    \ if (std::count(begin(V), begin(V) + dist.n(), 0) == dist.n())\n            \
    \    return std::make_pair(W, pi);\n            if (W > BestW) {\n           \
    \     BestW = W;\n                best_pi = pi;\n                if (is_initial_phase)\
    \ t0 *= 2;\n                if (p == period) period = std::min(period * 2, initial_period);\n\
    \n            } else if (is_initial_phase and p > period / 2) {\n            \
    \    is_initial_phase = false;\n                p = 0;\n                t0 = 3\
    \ * t0 / 4;\n            }\n        }\n    }\n    BestW = minimum_one_tree(dist,\
    \ best_pi).first;\n    return std::make_pair(BestW, best_pi);\n}\n"
  code: "#pragma once\n\n#include \"csr_distance_matrix.hpp\"\n#include \"minimum_one_tree.hpp\"\
    \n\n#include <algorithm>\n#include <utility>\n#include <vector>\n\n// Held\u2013\
    Karp lower bound\n// http://webhotel4.ruc.dk/~keld/research/LKH/LKH-2.0/DOC/LKH_REPORT.pdf\n\
    // p.26, p.33\ntemplate <class DistanceMatrix> auto held_karp_lower_bound(const\
    \ DistanceMatrix &dist) {\n    using T = decltype((*dist.adjacents(0).begin()).second);\n\
    \n    std::vector<T> best_pi(dist.n()), pi(dist.n());\n    std::vector<int> V;\n\
    \    T W;\n    std::tie(W, V) = minimum_one_tree(dist, pi);\n    if (std::count(V.cbegin(),\
    \ V.cend(), 0) == dist.n()) return std::make_pair(W, pi);\n\n    std::vector<int>\
    \ lastV = V;\n\n    T BestW = W;\n    const int initial_period = (dist.n() + 1)\
    \ / 2;\n    bool is_initial_phase = true;\n    int period = initial_period;\n\n\
    \    const auto sparse_subgraph = build_adjacent_info(dist, 50); // p.47\n\n \
    \   for (long long t0 = 1; t0 > 0; period /= 2, t0 /= 2) {\n        for (int p\
    \ = 1; t0 > 0 and p <= period; ++p) {\n            for (int i = 0; i < dist.n();\
    \ ++i) {\n                if (V.at(i) != 0) pi.at(i) += t0 * (7 * V.at(i) + 3\
    \ * lastV.at(i)) / 10;\n            }\n            std::swap(lastV, V);\n    \
    \        std::tie(W, V) = minimum_one_tree(sparse_subgraph, pi);\n           \
    \ if (std::count(begin(V), begin(V) + dist.n(), 0) == dist.n())\n            \
    \    return std::make_pair(W, pi);\n            if (W > BestW) {\n           \
    \     BestW = W;\n                best_pi = pi;\n                if (is_initial_phase)\
    \ t0 *= 2;\n                if (p == period) period = std::min(period * 2, initial_period);\n\
    \n            } else if (is_initial_phase and p > period / 2) {\n            \
    \    is_initial_phase = false;\n                p = 0;\n                t0 = 3\
    \ * t0 / 4;\n            }\n        }\n    }\n    BestW = minimum_one_tree(dist,\
    \ best_pi).first;\n    return std::make_pair(BestW, best_pi);\n}\n"
  dependsOn:
  - tsp/csr_distance_matrix.hpp
  - tsp/minimum_one_tree.hpp
  isVerificationFile: false
  path: tsp/held_karp.hpp
  requiredBy: []
  timestamp: '2023-02-16 23:07:28+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: tsp/held_karp.hpp
layout: document
redirect_from:
- /library/tsp/held_karp.hpp
- /library/tsp/held_karp.hpp.html
title: tsp/held_karp.hpp
---
