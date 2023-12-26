---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Bounded knapsack problem (Pisinger's algorithm)
    links:
    - https://qiita.com/lowking/items/a9393f6afb9a4e662c38
    - https://stackoverflow.com/a/9997386/20904249
    - https://www.sciencedirect.com/science/article/abs/pii/S0196677499910349
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.12.1/x64/lib/python3.12/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.12.1/x64/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.12.1/x64/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 312, in update\n    raise BundleErrorAt(path, i + 1, \"#pragma once found\
    \ in a non-first line\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ other_algorithms/bounded_knapsack.hpp: line 8: #pragma once found in a non-first\
    \ line\n"
  code: "/**\n * @file bounded_knapsack.hpp\n * @brief Bounded knapsack problem (Pisinger's\
    \ algorithm)\n * @author hitonanode\n * @date 2023/01/01\n */\n\n#pragma once\n\
    #include <algorithm>\n#include <cassert>\n#include <numeric>\n#include <utility>\n\
    #include <vector>\n\n/**\n * @fn bounded_knapsack_nonnegative(const std::vector<int>\
    \ &, int)\n * Solve bounded knapsack problem: maximize weights(S) s.t. weights(S)\
    \ <= capacity\n * Complexity: O(sum(weights) max(weights)) (Pisinger's linear\
    \ time algorithm)\n * @param weights nonnegative integers describing weights.\n\
    \ * @param capacity knapsack capacity limit.\n * @return std::pair<int, std::vector<bool>>\
    \ {maximal value of weights(S), S that maximizes weights(S)}\n * @sa https://www.sciencedirect.com/science/article/abs/pii/S0196677499910349\n\
    \ * @sa https://stackoverflow.com/a/9997386/20904249\n * @sa https://qiita.com/lowking/items/a9393f6afb9a4e662c38\n\
    \ */\nstd::pair<int, std::vector<bool>>\nbounded_knapsack_nonnegative(const std::vector<int>\
    \ &weights, int capacity) {\n\n    for (int w : weights) assert(w >= 0);\n   \
    \ assert(capacity >= 0);\n\n    auto chmax = [](int &x, int y) { x = std::max(x,\
    \ y); };\n\n    int b = 0, w_bar = 0;\n    const int n = weights.size();\n   \
    \ for (b = 0; b < n and w_bar + weights.at(b) <= capacity; ++b) w_bar += weights.at(b);\n\
    \n    if (b == n) return std::make_pair(w_bar, std::vector<bool>(n, true));\n\n\
    \    int r = 0;\n    for (int w : weights) r = std::max(r, w);\n\n    const int\
    \ O = r - 1; // DP table range: [capacity - r + 1, capacity + r]\n    std::vector\
    \ dp(n - b + 1, std::vector<int>(2 * r));\n    for (int i = 0; i <= O; ++i) dp.front().at(i)\
    \ = -1;\n    dp.front().at(O + w_bar - capacity) = b;\n\n    for (int t = b; t\
    \ < n; ++t) {\n        const std::vector<int> &dpprv = dp.at(t - b);\n       \
    \ std::vector<int> &dpnxt = dp.at(t - b + 1);\n        dpnxt = dpprv;\n\n    \
    \    for (int i = 0; i <= O; ++i) chmax(dpnxt.at(i + weights.at(t)), dpprv.at(i));\n\
    \n        for (int i = O + weights.at(t); i >= O + 1; --i) {\n            for\
    \ (int j = dpnxt.at(i) - 1; j >= dpprv.at(i); --j) {\n                chmax(dpnxt.at(i\
    \ - weights.at(j)), j);\n            }\n        }\n    }\n\n    for (int z = O;\
    \ z >= 0; --z) {\n        if (dp.back().at(z) >= 0) {\n            const int sol\
    \ = capacity - O + z;\n            std::vector<bool> ret(b, true);\n         \
    \   ret.resize(n, false);\n\n            for (int t = n - 1; t >= b; --t) {\n\
    \                const std::vector<int> &dpprv = dp.at(t - b), &dpnxt = dp.at(t\
    \ - b + 1);\n                while (dpnxt.at(z) < b) {\n                    int\
    \ znxt = z + weights.at(dpnxt.at(z));\n                    if (znxt >= int(dpnxt.size())\
    \ or dpnxt.at(z) >= dpnxt.at(znxt)) break;\n                    ret.at(dpnxt.at(z))\
    \ = false;\n                    z = znxt;\n                }\n               \
    \ if (z >= weights.at(t) and dpprv.at(z - weights.at(t)) >= dpnxt.at(z)) {\n \
    \                   z -= weights.at(t);\n                    ret.at(t) = true;\n\
    \                }\n            }\n\n            return {sol, ret};\n        }\n\
    \    }\n    exit(1); // Not occur\n}\n\n/**\n * @fn bounded_knapsack(const std::vector<int>\
    \ &, int)\n * Solve bounded knapsack problem: maximize weights(S) s.t. weights(S)\
    \ <= capacity\n * Complexity: O(sum(abs(weights)) max(abs(weights)))\n * @param\
    \ weights Integers describing weights. Negative values are allowed.\n * @param\
    \ capacity Knapsack capacity limit.\n * @return std::pair<int, std::vector<bool>>\
    \ {maximal value of weights(S), S that maximizes weights(S)}\n */\nstd::pair<int,\
    \ std::vector<bool>> bounded_knapsack(const std::vector<int> &weights, int capacity)\
    \ {\n    assert(capacity >= 0);\n    std::vector<int> tmp = weights;\n    for\
    \ (int &w : tmp) {\n        if (w < 0) w = -w, capacity += w;\n    }\n    auto\
    \ sol = bounded_knapsack_nonnegative(tmp, capacity);\n    for (int i = 0; i <\
    \ int(weights.size()); ++i) {\n        if (weights.at(i) < 0) {\n            capacity\
    \ += weights.at(i);\n            sol.second.at(i).flip();\n        }\n    }\n\
    \    return sol;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: other_algorithms/bounded_knapsack.hpp
  requiredBy: []
  timestamp: '2023-01-01 23:15:53+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: other_algorithms/bounded_knapsack.hpp
layout: document
redirect_from:
- /library/other_algorithms/bounded_knapsack.hpp
- /library/other_algorithms/bounded_knapsack.hpp.html
title: Bounded knapsack problem (Pisinger's algorithm)
---
