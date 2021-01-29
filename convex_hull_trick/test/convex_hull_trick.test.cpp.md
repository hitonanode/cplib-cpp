---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: convex_hull_trick/convex_hull_trick.hpp
    title: convex_hull_trick/convex_hull_trick.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/line_add_get_min
    links:
    - https://judge.yosupo.jp/problem/line_add_get_min
  bundledCode: "#line 2 \"convex_hull_trick/convex_hull_trick.hpp\"\n/*\nConvex Hull\
    \ Trick\n- y = ax + b \u304C\u9806\u6B21\u8FFD\u52A0\u3055\u308C\u3064\u3064\uFF0C\
    \u6700\u5927\u5024/\u6700\u5C0F\u5024\u30AF\u30A8\u30EA\u306B\u7B54\u3048\u308B\
    \n- y = c(x - a)^2 + b \u578B\u306E\u95A2\u6570\u3092\u8868\u3059(a, b)\u305F\u3061\
    \u304C\u9806\u6B21\u8FFD\u52A0\u3055\u308C\u3064\u3064\uFF0C\u6700\u5C0F\u5024\
    \u30AF\u30A8\u30EA\u306B\u7B54\u3048\u308B\nVerify:\nCF 1179D <https://codeforces.com/contest/1179/submission/59448330>\n\
    CF 1137E <https://codeforces.com/contest/1137/submission/59448399>\n*/\n#include\
    \ <limits>\n#include <set>\n#include <utility>\n#include <vector>\n// CUT begin\n\
    // Convex Hull Trick\n// Implementation Idea: <https://github.com/satanic0258/Cpp_snippet/blob/master/src/technique/ConvexHullTrick.cpp>\n\
    // #include <boost/multiprecision/cpp_int.hpp>\n// using mpint = boost::multiprecision::cpp_int;\n\
    namespace CHT {\nusing T_CHT = long long;\nstatic const T_CHT T_MIN = std::numeric_limits<T_CHT>::lowest()\
    \ + 1;\nstruct Line {\n    T_CHT a, b;                         // y = ax + b\n\
    \    mutable std::pair<T_CHT, T_CHT> rp; // (numerator, denominator) `x` coordinate\
    \ of the crossing point with next line\n    Line(T_CHT a, T_CHT b) : a(a), b(b),\
    \ rp(T_MIN, T_MIN) {}\n    static std::pair<T_CHT, T_CHT> cross(const Line &ll,\
    \ const Line &lr) {\n        return std::make_pair(ll.b - lr.b, lr.a - ll.a);\
    \ // `ll.a < lr.a` is assumed implicitly\n    }\n    bool operator<(const Line\
    \ &r) const {\n        if (b == T_MIN) {\n            return r.rp.first == T_MIN\
    \ ? true : a * r.rp.second < r.rp.first;\n        } else if (r.b == T_MIN) {\n\
    \            return rp.first == T_MIN ? false : !(r.a * rp.second < rp.first);\n\
    \        } else {\n            return a < r.a;\n        }\n    }\n};\ntemplate\
    \ <typename T_MP> struct Lines : std::multiset<Line> {\n    bool flg_min; // true\
    \ iff for minimization\n    inline bool isNeedless(iterator itr) {\n        if\
    \ (size() == 1) return false;\n        auto nxt = std::next(itr);\n        if\
    \ (itr == begin())\n            return itr->a == nxt->a and itr->b <= nxt->b;\n\
    \        else {\n            auto prv = std::prev(itr);\n            if (nxt ==\
    \ end())\n                return itr->a == prv->a and itr->b <= prv->b;\n    \
    \        else\n                return T_MP(prv->b - itr->b) * (nxt->a - itr->a)\
    \ >= T_MP(itr->b - nxt->b) * (itr->a - prv->a);\n        }\n    }\n    void add_line(T_CHT\
    \ a, T_CHT b) {\n        if (flg_min) a = -a, b = -b;\n        auto itr = insert({a,\
    \ b});\n        if (isNeedless(itr))\n            erase(itr);\n        else {\n\
    \            while (std::next(itr) != end() and isNeedless(std::next(itr))) {\
    \ erase(std::next(itr)); }\n            while (itr != begin() and isNeedless(std::prev(itr)))\
    \ { erase(std::prev(itr)); }\n            if (std::next(itr) != end()) { itr->rp\
    \ = CHT::Line::cross(*itr, *std::next(itr)); }\n            if (itr != begin())\
    \ { std::prev(itr)->rp = CHT::Line::cross(*std::prev(itr), *itr); }\n        }\n\
    \    }\n    Lines(bool is_minimizer) : flg_min(is_minimizer) {}\n    std::pair<T_CHT,\
    \ T_CHT> get(T_CHT x) {\n        auto itr = lower_bound({x, CHT::T_MIN});\n  \
    \      T_CHT retval = CHT::T_MIN, reta = CHT::T_MIN;\n        if (itr != end())\
    \ { retval = itr->a * x + itr->b, reta = itr->a; }\n        if (itr != begin())\
    \ {\n            T_CHT tmp = std::prev(itr)->a * x + std::prev(itr)->b;\n    \
    \        if (tmp >= retval) { retval = tmp, reta = std::max(reta, std::prev(itr)->a);\
    \ }\n        }\n        return std::make_pair(flg_min ? -retval : retval, flg_min\
    \ ? -reta : reta);\n    }\n};\n} // namespace CHT\n\ntemplate <typename T_MP>\
    \ struct ConvexHullTrick {\n    using T_CHT = CHT::T_CHT;\n    CHT::Lines<T_MP>\
    \ lines;\n    ConvexHullTrick(bool is_minimizer) : lines(is_minimizer) {}\n  \
    \  void add_line(T_CHT a, T_CHT b) { lines.add_line(a, b); } // Add y = ax + b\n\
    \    std::pair<T_CHT, T_CHT> get(T_CHT x) { return lines.get(x); }\n    void add_convex_parabola(T_CHT\
    \ c, T_CHT a, T_CHT b) { add_line(c * a * (-2), c * a * a + b); } // Add y = c(x\
    \ - a)^2 + b\n    T_CHT parabola_lower_bound(T_CHT c, T_CHT x) { return lines.get(x).first\
    \ + c * x * x; }\n};\n#line 2 \"convex_hull_trick/test/convex_hull_trick.test.cpp\"\
    \n#include <cassert>\n#include <iostream>\n#define PROBLEM \"https://judge.yosupo.jp/problem/line_add_get_min\"\
    \n\nConvexHullTrick<__int128> cht_min(true), cht_max(false);\n\nvoid add_line()\
    \ {\n    long long int a, b;\n    std::cin >> a >> b;\n    cht_min.add_line(a,\
    \ b);\n    cht_max.add_line(-a, -b);\n}\n\nint main() {\n    std::cin.tie(nullptr),\
    \ std::ios::sync_with_stdio(false);\n\n    int N, Q;\n    std::cin >> N >> Q;\n\
    \    while (N--) add_line();\n    while (Q--) {\n        int q;\n        std::cin\
    \ >> q;\n        if (q) {\n            int p;\n            std::cin >> p;\n  \
    \          auto ret1 = cht_min.get(p);\n            auto ret2 = cht_max.get(p);\n\
    \            assert(ret1.first == -ret2.first);\n            std::cout << ret1.first\
    \ << '\\n';\n        } else {\n            add_line();\n        }\n    }\n}\n"
  code: "#include \"convex_hull_trick/convex_hull_trick.hpp\"\n#include <cassert>\n\
    #include <iostream>\n#define PROBLEM \"https://judge.yosupo.jp/problem/line_add_get_min\"\
    \n\nConvexHullTrick<__int128> cht_min(true), cht_max(false);\n\nvoid add_line()\
    \ {\n    long long int a, b;\n    std::cin >> a >> b;\n    cht_min.add_line(a,\
    \ b);\n    cht_max.add_line(-a, -b);\n}\n\nint main() {\n    std::cin.tie(nullptr),\
    \ std::ios::sync_with_stdio(false);\n\n    int N, Q;\n    std::cin >> N >> Q;\n\
    \    while (N--) add_line();\n    while (Q--) {\n        int q;\n        std::cin\
    \ >> q;\n        if (q) {\n            int p;\n            std::cin >> p;\n  \
    \          auto ret1 = cht_min.get(p);\n            auto ret2 = cht_max.get(p);\n\
    \            assert(ret1.first == -ret2.first);\n            std::cout << ret1.first\
    \ << '\\n';\n        } else {\n            add_line();\n        }\n    }\n}\n"
  dependsOn:
  - convex_hull_trick/convex_hull_trick.hpp
  isVerificationFile: true
  path: convex_hull_trick/test/convex_hull_trick.test.cpp
  requiredBy: []
  timestamp: '2020-11-18 20:33:55+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: convex_hull_trick/test/convex_hull_trick.test.cpp
layout: document
redirect_from:
- /verify/convex_hull_trick/test/convex_hull_trick.test.cpp
- /verify/convex_hull_trick/test/convex_hull_trick.test.cpp.html
title: convex_hull_trick/test/convex_hull_trick.test.cpp
---
