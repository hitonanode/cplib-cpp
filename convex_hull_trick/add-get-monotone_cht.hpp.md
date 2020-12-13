---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://yukicoder.me/submissions/409156>
  bundledCode: "#line 2 \"convex_hull_trick/add-get-monotone_cht.hpp\"\n#include <cassert>\n\
    #include <deque>\n#include <utility>\n\n// CUT begin\n// Convex Hull Trick for\
    \ monotone increasing queries, monotone decreasing slopes\n// Each operation is\
    \ amortized O(1)\n// - add_line(a, b): Add `y = ax + b`, a must be monotone decreasing\
    \ (if is_minimizer == true) / increasing (otherwise)\n// - add_convex_parabola(c,\
    \ a, b): Add `y = c(x - a)^2 + b`, c is constant, a is monotone increasing (if\
    \ is_minimizer == true) / decreasing (otherwise)\n// - get(x): Calculate min/max.\
    \ value of `y = ax + b`'s at point x, x must be monotone increasing FOR BOTH CASES.\n\
    // - parabola_get(c, x): Caclculate min/max. value of `y = c(x - a)^2 + b`'s,\
    \ x must be monotone increasing FOR BOTH CASES.\n// Verified: <https://yukicoder.me/submissions/409156>\n\
    // template<typename T_CHT>\nusing T_CHT = long long int;\nstruct MonotoneConvexHullTrick\
    \ : std::deque<std::pair<T_CHT, T_CHT>> // (a, b) means `y = ax + b`\n{\n    using\
    \ T_MP = __int128_t;\n    bool is_minimizer; // If true, this instance calculates\
    \ min. Otherwise, calculates max.\n    MonotoneConvexHullTrick(bool is_minimizer)\
    \ : is_minimizer(is_minimizer) {}\n    void add_line(T_CHT a, T_CHT b) { // Add\
    \ y = ax + b\n        if (!is_minimizer) a = -a, b = -b;\n        assert(this->empty()\
    \ or this->back().first >= a);\n        while (this->size() > 1u) {\n        \
    \    if (this->back().first == a) {\n                if (this->back().second <=\
    \ b) {\n                    return;\n                } else {\n              \
    \      this->pop_back();\n                    continue;\n                }\n \
    \           }\n            int sz = this->size();\n            T_MP l = (T_MP)(this->back().second\
    \ - (*this)[sz - 2].second) * (this->back().first - a); // Overflow might occur\
    \ here.\n            T_MP r = (T_MP)(b - this->back().second) * ((*this)[sz -\
    \ 2].first - this->back().first);\n            if (l < r) break;\n           \
    \ this->pop_back();\n        }\n        this->emplace_back(a, b);\n    }\n   \
    \ T_CHT get(T_CHT x) {\n        while (this->size() > 1u and (*this)[0].first\
    \ * x + (*this)[0].second >= (*this)[1].first * x + (*this)[1].second) { this->pop_front();\
    \ }\n        return ((*this)[0].first * x + (*this)[0].second) * (is_minimizer\
    \ ? 1 : -1);\n    }\n    void add_convex_parabola(T_CHT c, T_CHT a, T_CHT b) {\
    \ add_line(c * a * (-2), c * a * a + b); } // Add y = c(x - a)^2 + b\n    T_CHT\
    \ parabola_get(T_CHT c, T_CHT x) { return get(x) + c * x * x; }\n};\n"
  code: "#pragma once\n#include <cassert>\n#include <deque>\n#include <utility>\n\n\
    // CUT begin\n// Convex Hull Trick for monotone increasing queries, monotone decreasing\
    \ slopes\n// Each operation is amortized O(1)\n// - add_line(a, b): Add `y = ax\
    \ + b`, a must be monotone decreasing (if is_minimizer == true) / increasing (otherwise)\n\
    // - add_convex_parabola(c, a, b): Add `y = c(x - a)^2 + b`, c is constant, a\
    \ is monotone increasing (if is_minimizer == true) / decreasing (otherwise)\n\
    // - get(x): Calculate min/max. value of `y = ax + b`'s at point x, x must be\
    \ monotone increasing FOR BOTH CASES.\n// - parabola_get(c, x): Caclculate min/max.\
    \ value of `y = c(x - a)^2 + b`'s, x must be monotone increasing FOR BOTH CASES.\n\
    // Verified: <https://yukicoder.me/submissions/409156>\n// template<typename T_CHT>\n\
    using T_CHT = long long int;\nstruct MonotoneConvexHullTrick : std::deque<std::pair<T_CHT,\
    \ T_CHT>> // (a, b) means `y = ax + b`\n{\n    using T_MP = __int128_t;\n    bool\
    \ is_minimizer; // If true, this instance calculates min. Otherwise, calculates\
    \ max.\n    MonotoneConvexHullTrick(bool is_minimizer) : is_minimizer(is_minimizer)\
    \ {}\n    void add_line(T_CHT a, T_CHT b) { // Add y = ax + b\n        if (!is_minimizer)\
    \ a = -a, b = -b;\n        assert(this->empty() or this->back().first >= a);\n\
    \        while (this->size() > 1u) {\n            if (this->back().first == a)\
    \ {\n                if (this->back().second <= b) {\n                    return;\n\
    \                } else {\n                    this->pop_back();\n           \
    \         continue;\n                }\n            }\n            int sz = this->size();\n\
    \            T_MP l = (T_MP)(this->back().second - (*this)[sz - 2].second) * (this->back().first\
    \ - a); // Overflow might occur here.\n            T_MP r = (T_MP)(b - this->back().second)\
    \ * ((*this)[sz - 2].first - this->back().first);\n            if (l < r) break;\n\
    \            this->pop_back();\n        }\n        this->emplace_back(a, b);\n\
    \    }\n    T_CHT get(T_CHT x) {\n        while (this->size() > 1u and (*this)[0].first\
    \ * x + (*this)[0].second >= (*this)[1].first * x + (*this)[1].second) { this->pop_front();\
    \ }\n        return ((*this)[0].first * x + (*this)[0].second) * (is_minimizer\
    \ ? 1 : -1);\n    }\n    void add_convex_parabola(T_CHT c, T_CHT a, T_CHT b) {\
    \ add_line(c * a * (-2), c * a * a + b); } // Add y = c(x - a)^2 + b\n    T_CHT\
    \ parabola_get(T_CHT c, T_CHT x) { return get(x) + c * x * x; }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: convex_hull_trick/add-get-monotone_cht.hpp
  requiredBy: []
  timestamp: '2020-12-13 22:27:40+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: convex_hull_trick/add-get-monotone_cht.hpp
layout: document
redirect_from:
- /library/convex_hull_trick/add-get-monotone_cht.hpp
- /library/convex_hull_trick/add-get-monotone_cht.hpp.html
title: convex_hull_trick/add-get-monotone_cht.hpp
---
