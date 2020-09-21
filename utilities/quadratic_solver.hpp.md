---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: geometry/problem_of_apollonius.hpp
    title: geometry/problem_of_apollonius.hpp
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links:
    - https://atcoder.jp/contests/tricky/tasks/tricky_2>
    - https://yukicoder.me/problems/no/955>
  bundledCode: "#line 2 \"utilities/quadratic_solver.hpp\"\n#include <cmath>\n#include\
    \ <utility>\n#include <vector>\n\n// CUT begin\n// Solve ax^2 + bx + c = 0.\n\
    // retval: (# of solutions (-1 == inf.), solutions(ascending order))\n// Verify:\
    \ <https://yukicoder.me/problems/no/955> <https://atcoder.jp/contests/tricky/tasks/tricky_2>\n\
    template <typename Float>\nstd::pair<int, std::vector<Float>> quadratic_solver(Float\
    \ A, Float B, Float C)\n{\n    if (B < 0) A = -A, B = -B, C = -C;\n    if (A ==\
    \ 0) {\n        if (B == 0) {\n            if (C == 0) return std::make_pair(-1,\
    \ std::vector<Float>{});  // all real numbers\n            else return std::make_pair(0,\
    \ std::vector<Float>{});  // no solution\n        }\n        else return std::make_pair(1,\
    \ std::vector<Float>{-C / B});\n    }\n    Float D = B * B - 4 * A * C;\n    if\
    \ (D < 0) return std::make_pair(0, std::vector<Float>{});\n    if (D == 0) return\
    \ std::make_pair(1, std::vector<Float>{-B / (2 * A)});\n    Float ret1 = (-B -\
    \ sqrt(D)) / (2 * A), ret2 = C / A / ret1;\n    if (ret1 > ret2) swap(ret1, ret2);\n\
    \    return std::make_pair(2, std::vector<Float>{ret1, ret2});\n}\n"
  code: "#pragma once\n#include <cmath>\n#include <utility>\n#include <vector>\n\n\
    // CUT begin\n// Solve ax^2 + bx + c = 0.\n// retval: (# of solutions (-1 == inf.),\
    \ solutions(ascending order))\n// Verify: <https://yukicoder.me/problems/no/955>\
    \ <https://atcoder.jp/contests/tricky/tasks/tricky_2>\ntemplate <typename Float>\n\
    std::pair<int, std::vector<Float>> quadratic_solver(Float A, Float B, Float C)\n\
    {\n    if (B < 0) A = -A, B = -B, C = -C;\n    if (A == 0) {\n        if (B ==\
    \ 0) {\n            if (C == 0) return std::make_pair(-1, std::vector<Float>{});\
    \  // all real numbers\n            else return std::make_pair(0, std::vector<Float>{});\
    \  // no solution\n        }\n        else return std::make_pair(1, std::vector<Float>{-C\
    \ / B});\n    }\n    Float D = B * B - 4 * A * C;\n    if (D < 0) return std::make_pair(0,\
    \ std::vector<Float>{});\n    if (D == 0) return std::make_pair(1, std::vector<Float>{-B\
    \ / (2 * A)});\n    Float ret1 = (-B - sqrt(D)) / (2 * A), ret2 = C / A / ret1;\n\
    \    if (ret1 > ret2) swap(ret1, ret2);\n    return std::make_pair(2, std::vector<Float>{ret1,\
    \ ret2});\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/quadratic_solver.hpp
  requiredBy:
  - geometry/problem_of_apollonius.hpp
  timestamp: '2020-09-21 19:07:56+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utilities/quadratic_solver.hpp
layout: document
redirect_from:
- /library/utilities/quadratic_solver.hpp
- /library/utilities/quadratic_solver.hpp.html
title: utilities/quadratic_solver.hpp
---
