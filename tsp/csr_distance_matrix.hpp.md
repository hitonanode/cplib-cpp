---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.13.7/x64/lib/python3.13/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ~~~~~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.13.7/x64/lib/python3.13/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n    ~~~~~~~~~~~~~~^^^^^^\n  File\
    \ \"/opt/hostedtoolcache/Python/3.13.7/x64/lib/python3.13/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \    ~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.13.7/x64/lib/python3.13/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \    ~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.13.7/x64/lib/python3.13/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 312, in update\n    raise BundleErrorAt(path, i + 1, \"#pragma once found\
    \ in a non-first line\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ tsp/mst_edges.hpp: line 2: #pragma once found in a non-first line\n"
  code: "#pragma once\n\n#include <algorithm>\n#include <utility>\n#include <vector>\n\
    \n#include \"tsp/calc_lkh_alpha.hpp\"\n\ntemplate <class T> class csr_distance_matrix\
    \ {\n\n    int _rows = 0;\n    std::vector<int> begins;\n    std::vector<std::pair<int,\
    \ T>> vals;\n\npublic:\n    csr_distance_matrix() : csr_distance_matrix({}, 0)\
    \ {}\n\n    csr_distance_matrix(const std::vector<std::tuple<int, int, T>> &init,\
    \ int rows)\n        : _rows(rows), begins(rows + 1) {\n        std::vector<int>\
    \ degs(rows);\n        for (const auto &p : init) ++degs.at(std::get<0>(p));\n\
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
    \ dist.n());\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: tsp/csr_distance_matrix.hpp
  requiredBy: []
  timestamp: '2023-08-30 22:52:16+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: tsp/csr_distance_matrix.hpp
layout: document
redirect_from:
- /library/tsp/csr_distance_matrix.hpp
- /library/tsp/csr_distance_matrix.hpp.html
title: tsp/csr_distance_matrix.hpp
---
