---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://codeforces.com/gym/101806/problem/R>
  bundledCode: "#line 2 \"convex_hull_trick/add-monotone_cht.hpp\"\n#include <deque>\n\
    #include <utility>\n\n// CUT begin\n// Convex Hull Trick for monotone insertions\n\
    // - is_minimizer: if true, calculates min. Otherwise, calculates max.\n// - add_line(a,\
    \ b): Add `y = ax + b`, O(1) if `a` must be largest or smallest, or do nothing\
    \ otherwise.\n// - add_convex_parabola(c, a, b): Add `y = c(x - a)^2 + b`, c is\
    \ constant\n// - get(x): Calculate min/max. value of `y = ax + b`'s at point x,\
    \ O(logN)\n// - parabola_get(c, x): Caclculate min/max. value of `y = c(x - a)^2\
    \ + b`'s\n// Verifyed: <https://codeforces.com/gym/101806/problem/R>\ntemplate\
    \ <bool is_minimizer, typename T_CHT = long long, typename T_MP = __int128, T_CHT\
    \ INF = 1LL << 61>\nstruct AddMonotoneConvexHullTrick // (a, b) means `y = ax\
    \ + b`\n{\n    std::deque<std::pair<T_CHT, T_CHT>> q;\n    AddMonotoneConvexHullTrick()\
    \ {}\n    void add_line(T_CHT a, T_CHT b) { // Add y = ax + b\n        if (!is_minimizer)\
    \ a = -a, b = -b;\n        if (q.empty())\n            q.emplace_back(a, b);\n\
    \        else if (q.back().first >= a) {\n            while (q.size() > 1u) {\n\
    \                if (q.back().first == a and q.back().second <= b) return;\n \
    \               int sz = q.size();\n                T_MP l = (T_MP)(q.back().second\
    \ - q[sz - 2].second) * (q.back().first - a); // Overflow might occur here.\n\
    \                T_MP r = (T_MP)(b - q.back().second) * (q[sz - 2].first - q.back().first);\n\
    \                if (l < r) break;\n                q.pop_back();\n          \
    \  }\n            q.emplace_back(a, b);\n        } else if (q[0].first <= a) {\n\
    \            while (q.size() > 1u) {\n                if (q[0].first == a and\
    \ q[0].second <= b) return;\n                T_MP l = (T_MP)(q[0].second - q[1].second)\
    \ * (q[0].first - a);\n                T_MP r = (T_MP)(b - q[0].second) * (q[1].first\
    \ - q[0].first);\n                if (l > r) break;\n                q.pop_front();\n\
    \            }\n            q.emplace_front(a, b);\n        }\n    }\n\n    T_CHT\
    \ _get_idx(int i, T_CHT x) const { return q[i].first * x + q[i].second; }\n\n\
    \    T_CHT get(T_CHT x) const {\n        if (q.empty()) return INF * (is_minimizer\
    \ ? 1 : -1);\n        int l = 0, r = q.size();\n        while (l + 1 < r) {\n\
    \            int c = (l + r) / 2, clo = c - 1;\n            (_get_idx(clo, x)\
    \ >= _get_idx(c, x) ? l : r) = c;\n        }\n        return _get_idx(l, x) *\
    \ (is_minimizer ? 1 : -1);\n    }\n    void add_convex_parabola(T_CHT c, T_CHT\
    \ a, T_CHT b) { add_line(c * a * (-2), c * a * a + b); } // Add y = c(x - a)^2\
    \ + b\n    T_CHT parabola_get(T_CHT c, T_CHT x) const { return get(x) + c * x\
    \ * x; }\n};\n"
  code: "#pragma once\n#include <deque>\n#include <utility>\n\n// CUT begin\n// Convex\
    \ Hull Trick for monotone insertions\n// - is_minimizer: if true, calculates min.\
    \ Otherwise, calculates max.\n// - add_line(a, b): Add `y = ax + b`, O(1) if `a`\
    \ must be largest or smallest, or do nothing otherwise.\n// - add_convex_parabola(c,\
    \ a, b): Add `y = c(x - a)^2 + b`, c is constant\n// - get(x): Calculate min/max.\
    \ value of `y = ax + b`'s at point x, O(logN)\n// - parabola_get(c, x): Caclculate\
    \ min/max. value of `y = c(x - a)^2 + b`'s\n// Verifyed: <https://codeforces.com/gym/101806/problem/R>\n\
    template <bool is_minimizer, typename T_CHT = long long, typename T_MP = __int128,\
    \ T_CHT INF = 1LL << 61>\nstruct AddMonotoneConvexHullTrick // (a, b) means `y\
    \ = ax + b`\n{\n    std::deque<std::pair<T_CHT, T_CHT>> q;\n    AddMonotoneConvexHullTrick()\
    \ {}\n    void add_line(T_CHT a, T_CHT b) { // Add y = ax + b\n        if (!is_minimizer)\
    \ a = -a, b = -b;\n        if (q.empty())\n            q.emplace_back(a, b);\n\
    \        else if (q.back().first >= a) {\n            while (q.size() > 1u) {\n\
    \                if (q.back().first == a and q.back().second <= b) return;\n \
    \               int sz = q.size();\n                T_MP l = (T_MP)(q.back().second\
    \ - q[sz - 2].second) * (q.back().first - a); // Overflow might occur here.\n\
    \                T_MP r = (T_MP)(b - q.back().second) * (q[sz - 2].first - q.back().first);\n\
    \                if (l < r) break;\n                q.pop_back();\n          \
    \  }\n            q.emplace_back(a, b);\n        } else if (q[0].first <= a) {\n\
    \            while (q.size() > 1u) {\n                if (q[0].first == a and\
    \ q[0].second <= b) return;\n                T_MP l = (T_MP)(q[0].second - q[1].second)\
    \ * (q[0].first - a);\n                T_MP r = (T_MP)(b - q[0].second) * (q[1].first\
    \ - q[0].first);\n                if (l > r) break;\n                q.pop_front();\n\
    \            }\n            q.emplace_front(a, b);\n        }\n    }\n\n    T_CHT\
    \ _get_idx(int i, T_CHT x) const { return q[i].first * x + q[i].second; }\n\n\
    \    T_CHT get(T_CHT x) const {\n        if (q.empty()) return INF * (is_minimizer\
    \ ? 1 : -1);\n        int l = 0, r = q.size();\n        while (l + 1 < r) {\n\
    \            int c = (l + r) / 2, clo = c - 1;\n            (_get_idx(clo, x)\
    \ >= _get_idx(c, x) ? l : r) = c;\n        }\n        return _get_idx(l, x) *\
    \ (is_minimizer ? 1 : -1);\n    }\n    void add_convex_parabola(T_CHT c, T_CHT\
    \ a, T_CHT b) { add_line(c * a * (-2), c * a * a + b); } // Add y = c(x - a)^2\
    \ + b\n    T_CHT parabola_get(T_CHT c, T_CHT x) const { return get(x) + c * x\
    \ * x; }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: convex_hull_trick/add-monotone_cht.hpp
  requiredBy: []
  timestamp: '2020-11-23 16:24:10+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: convex_hull_trick/add-monotone_cht.hpp
layout: document
redirect_from:
- /library/convex_hull_trick/add-monotone_cht.hpp
- /library/convex_hull_trick/add-monotone_cht.hpp.html
title: convex_hull_trick/add-monotone_cht.hpp
---
