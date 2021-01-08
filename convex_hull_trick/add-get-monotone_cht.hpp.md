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
    #include <list>\n#include <utility>\n\n// CUT begin\n// Convex Hull Trick for\
    \ monotone increasing queries, monotone decreasing slopes\n// Each operation is\
    \ amortized O(1)\n// - is_minimizer: if true, calculates min. Otherwise, calculates\
    \ max.\n// - add_line(a, b): Add `y = ax + b`, a must be monotone decreasing (if\
    \ is_minimizer == true) / increasing (otherwise)\n// - add_convex_parabola(c,\
    \ a, b): Add `y = c(x - a)^2 + b`, c is constant, a is monotone increasing (if\
    \ is_minimizer == true) / decreasing (otherwise)\n// - get(x): Calculate min/max.\
    \ value of `y = ax + b`'s at point x, x must be monotone increasing FOR BOTH CASES.\n\
    // - parabola_get(c, x): Caclculate min/max. value of `y = c(x - a)^2 + b`'s,\
    \ x must be monotone increasing FOR BOTH CASES.\n// - If you need random access,\
    \ change `std::list` to `std::deque`\n// Verified: <https://yukicoder.me/submissions/409156>\n\
    template <bool is_minimizer, typename T_CHT = long long, typename T_MP = __int128,\
    \ T_CHT INF = 1LL << 61>\nstruct MonotoneConvexHullTrick : std::list<std::pair<T_CHT,\
    \ T_CHT>> // (a, b) means `y = ax + b`\n{\n    MonotoneConvexHullTrick() = default;\n\
    \    void add_line(T_CHT a, T_CHT b) { // Add y = ax + b\n        if (!is_minimizer)\
    \ a = -a, b = -b;\n        assert(this->empty() or this->back().first >= a);\n\
    \        while (this->size() > 1u) {\n            if (this->back().first == a)\
    \ {\n                if (this->back().second <= b) {\n                    return;\n\
    \                } else {\n                    this->pop_back();\n           \
    \         continue;\n                }\n            }\n            auto ill =\
    \ std::prev(this->end(), 2);\n            auto l = (T_MP)(this->back().second\
    \ - ill->second) * (this->back().first - a); // Overflow might occur here.\n \
    \           auto r = (T_MP)(b - this->back().second) * (ill->first - this->back().first);\n\
    \            if (l < r) break;\n            this->pop_back();\n        }\n   \
    \     this->emplace_back(a, b);\n    }\n    T_CHT get(T_CHT x) {\n        while\
    \ (this->size() > 1u and\n               this->begin()->first * x + this->begin()->second\
    \ >= (++this->begin())->first * x + (++this->begin())->second)\n            this->pop_front();\n\
    \        return (this->empty() ? INF : this->begin()->first * x + this->begin()->second)\
    \ * (is_minimizer ? 1 : -1);\n    }\n    void add_convex_parabola(T_CHT c, T_CHT\
    \ a, T_CHT b) { add_line(c * a * (-2), c * a * a + b); }\n    T_CHT parabola_get(T_CHT\
    \ c, T_CHT x) { return get(x) + c * x * x; }\n\n    static MonotoneConvexHullTrick\
    \ merge(const MonotoneConvexHullTrick &cht1, const MonotoneConvexHullTrick &cht2)\
    \ {\n        MonotoneConvexHullTrick ret;\n        auto i1 = cht1.begin(), i2\
    \ = cht2.begin();\n        static const T_CHT sgn = is_minimizer ? 1 : -1;\n \
    \       T_CHT a = 0, b = 0;\n        while (i1 != cht1.end() and i2 != cht2.end())\
    \ {\n            if (i1->first == i2->first) {\n                a = i1->first,\
    \ b = std::min(i1->second, i2->second);\n                i1++, i2++;\n       \
    \     } else if (i1->first > i2->first) {\n                a = i1->first, b =\
    \ i1->second, i1++;\n            } else {\n                a = i2->first, b =\
    \ i2->second, i2++;\n            }\n            ret.add_line(a * sgn, b * sgn);\n\
    \        }\n        while (i1 != cht1.end()) ret.add_line(i1->first * sgn, i1->second\
    \ * sgn), i1++;\n        while (i2 != cht2.end()) ret.add_line(i2->first * sgn,\
    \ i2->second * sgn), i2++;\n        return ret;\n    }\n};\n"
  code: "#pragma once\n#include <cassert>\n#include <list>\n#include <utility>\n\n\
    // CUT begin\n// Convex Hull Trick for monotone increasing queries, monotone decreasing\
    \ slopes\n// Each operation is amortized O(1)\n// - is_minimizer: if true, calculates\
    \ min. Otherwise, calculates max.\n// - add_line(a, b): Add `y = ax + b`, a must\
    \ be monotone decreasing (if is_minimizer == true) / increasing (otherwise)\n\
    // - add_convex_parabola(c, a, b): Add `y = c(x - a)^2 + b`, c is constant, a\
    \ is monotone increasing (if is_minimizer == true) / decreasing (otherwise)\n\
    // - get(x): Calculate min/max. value of `y = ax + b`'s at point x, x must be\
    \ monotone increasing FOR BOTH CASES.\n// - parabola_get(c, x): Caclculate min/max.\
    \ value of `y = c(x - a)^2 + b`'s, x must be monotone increasing FOR BOTH CASES.\n\
    // - If you need random access, change `std::list` to `std::deque`\n// Verified:\
    \ <https://yukicoder.me/submissions/409156>\ntemplate <bool is_minimizer, typename\
    \ T_CHT = long long, typename T_MP = __int128, T_CHT INF = 1LL << 61>\nstruct\
    \ MonotoneConvexHullTrick : std::list<std::pair<T_CHT, T_CHT>> // (a, b) means\
    \ `y = ax + b`\n{\n    MonotoneConvexHullTrick() = default;\n    void add_line(T_CHT\
    \ a, T_CHT b) { // Add y = ax + b\n        if (!is_minimizer) a = -a, b = -b;\n\
    \        assert(this->empty() or this->back().first >= a);\n        while (this->size()\
    \ > 1u) {\n            if (this->back().first == a) {\n                if (this->back().second\
    \ <= b) {\n                    return;\n                } else {\n           \
    \         this->pop_back();\n                    continue;\n                }\n\
    \            }\n            auto ill = std::prev(this->end(), 2);\n          \
    \  auto l = (T_MP)(this->back().second - ill->second) * (this->back().first -\
    \ a); // Overflow might occur here.\n            auto r = (T_MP)(b - this->back().second)\
    \ * (ill->first - this->back().first);\n            if (l < r) break;\n      \
    \      this->pop_back();\n        }\n        this->emplace_back(a, b);\n    }\n\
    \    T_CHT get(T_CHT x) {\n        while (this->size() > 1u and\n            \
    \   this->begin()->first * x + this->begin()->second >= (++this->begin())->first\
    \ * x + (++this->begin())->second)\n            this->pop_front();\n        return\
    \ (this->empty() ? INF : this->begin()->first * x + this->begin()->second) * (is_minimizer\
    \ ? 1 : -1);\n    }\n    void add_convex_parabola(T_CHT c, T_CHT a, T_CHT b) {\
    \ add_line(c * a * (-2), c * a * a + b); }\n    T_CHT parabola_get(T_CHT c, T_CHT\
    \ x) { return get(x) + c * x * x; }\n\n    static MonotoneConvexHullTrick merge(const\
    \ MonotoneConvexHullTrick &cht1, const MonotoneConvexHullTrick &cht2) {\n    \
    \    MonotoneConvexHullTrick ret;\n        auto i1 = cht1.begin(), i2 = cht2.begin();\n\
    \        static const T_CHT sgn = is_minimizer ? 1 : -1;\n        T_CHT a = 0,\
    \ b = 0;\n        while (i1 != cht1.end() and i2 != cht2.end()) {\n          \
    \  if (i1->first == i2->first) {\n                a = i1->first, b = std::min(i1->second,\
    \ i2->second);\n                i1++, i2++;\n            } else if (i1->first\
    \ > i2->first) {\n                a = i1->first, b = i1->second, i1++;\n     \
    \       } else {\n                a = i2->first, b = i2->second, i2++;\n     \
    \       }\n            ret.add_line(a * sgn, b * sgn);\n        }\n        while\
    \ (i1 != cht1.end()) ret.add_line(i1->first * sgn, i1->second * sgn), i1++;\n\
    \        while (i2 != cht2.end()) ret.add_line(i2->first * sgn, i2->second * sgn),\
    \ i2++;\n        return ret;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: convex_hull_trick/add-get-monotone_cht.hpp
  requiredBy: []
  timestamp: '2021-01-08 19:10:55+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: convex_hull_trick/add-get-monotone_cht.hpp
layout: document
redirect_from:
- /library/convex_hull_trick/add-get-monotone_cht.hpp
- /library/convex_hull_trick/add-get-monotone_cht.hpp.html
title: convex_hull_trick/add-get-monotone_cht.hpp
---
