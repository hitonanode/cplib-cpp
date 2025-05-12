---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other_algorithms/bisect.hpp
    title: "Binary search \uFF08\u4E8C\u5206\u63A2\u7D22\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    ERROR: 1e-5
    PROBLEM: https://yukicoder.me/problems/no/2352
    links:
    - https://yukicoder.me/problems/no/2352
  bundledCode: "#line 1 \"other_algorithms/test/bisect_yuki2352.test.cpp\"\n#define\
    \ PROBLEM \"https://yukicoder.me/problems/no/2352\"\n#define ERROR 1e-5\n#line\
    \ 2 \"other_algorithms/bisect.hpp\"\n#include <bit>\n#include <functional>\n#include\
    \ <numeric>\n\n// Calculate next point to check in floating point \"binary\" search\n\
    double bisect_mid_fp(double a, double b) {\n    auto encode = [&](double x) ->\
    \ unsigned long long {\n        auto tmp = std::bit_cast<unsigned long long>(x);\n\
    \        return x >= 0 ? (tmp ^ (1ULL << 63)) : ~tmp;\n    };\n\n    auto decode\
    \ = [&](unsigned long long x) -> double {\n        auto tmp = (x >> 63) ? (x ^\
    \ (1ULL << 63)) : ~x;\n        return std::bit_cast<double>(tmp);\n    };\n\n\
    \    unsigned long long tmp = std::midpoint(encode(a), encode(b));\n\n    return\
    \ decode(tmp);\n}\n\n// Binary search\n// Maintain f(ok) = true and f(ng) = false\
    \ and return (ok, ng)\n// Final (ok, ng) satisfies |ok - ng| <= abs_tol\ntemplate\
    \ <class T> auto bisect(T ok, T ng, const std::function<bool(T)> &f, T abs_tol\
    \ = T()) {\n    struct Result {\n        T ok, ng;\n    };\n\n    while (true)\
    \ {\n        T mid = std::is_floating_point<T>::value ? bisect_mid_fp(ok, ng)\
    \ : std::midpoint(ok, ng);\n        if (mid == ok or mid == ng) break;\n     \
    \   (f(mid) ? ok : ng) = mid;\n        if (ok - ng <= abs_tol and ng - ok <= abs_tol)\
    \ break;\n    }\n\n    return Result{ok, ng};\n}\n#line 4 \"other_algorithms/test/bisect_yuki2352.test.cpp\"\
    \n\n#include <cmath>\n#include <iomanip>\n#include <iostream>\nusing namespace\
    \ std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false), cout\
    \ << fixed << setprecision(10);\n    int R, K;\n    cin >> R >> K;\n    const\
    \ double pi = acos(-1);\n\n    for (int i = 1; i < K + 1; ++i) {\n        double\
    \ tgt = pi / (K + 1) * i;\n\n        auto res = bisect<double>(0, pi, [&](double\
    \ c) { return c - sin(c * 2) / 2 < tgt; });\n        cout << -cos(res.ng) * R\
    \ << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/2352\"\n#define ERROR\
    \ 1e-5\n#include \"../bisect.hpp\"\n\n#include <cmath>\n#include <iomanip>\n#include\
    \ <iostream>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false),\
    \ cout << fixed << setprecision(10);\n    int R, K;\n    cin >> R >> K;\n    const\
    \ double pi = acos(-1);\n\n    for (int i = 1; i < K + 1; ++i) {\n        double\
    \ tgt = pi / (K + 1) * i;\n\n        auto res = bisect<double>(0, pi, [&](double\
    \ c) { return c - sin(c * 2) / 2 < tgt; });\n        cout << -cos(res.ng) * R\
    \ << '\\n';\n    }\n}\n"
  dependsOn:
  - other_algorithms/bisect.hpp
  isVerificationFile: true
  path: other_algorithms/test/bisect_yuki2352.test.cpp
  requiredBy: []
  timestamp: '2025-05-06 20:50:55+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: other_algorithms/test/bisect_yuki2352.test.cpp
layout: document
redirect_from:
- /verify/other_algorithms/test/bisect_yuki2352.test.cpp
- /verify/other_algorithms/test/bisect_yuki2352.test.cpp.html
title: other_algorithms/test/bisect_yuki2352.test.cpp
---
