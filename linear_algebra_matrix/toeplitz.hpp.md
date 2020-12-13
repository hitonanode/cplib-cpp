---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://en.wikipedia.org/wiki/Levinson_recursion>
  bundledCode: "#line 2 \"linear_algebra_matrix/toeplitz.hpp\"\n#include <cassert>\n\
    #include <vector>\n\n// CUT begin\n// solve Mx = y based on Levinson recursion\n\
    //\n// M = [\n// [ t_(N-1) t_(N-2) ... t_1 t_0     ]\n// [ t_N     t_(N-1) ...\
    \ t_2 t_1     ]\n// [ ...                             ]\n// [ t_(N*2-2)      \
    \ ...     t_(N-1) ]]\n//\n// Complexity: O(N^2)\n// Reference: <https://en.wikipedia.org/wiki/Levinson_recursion>\n\
    // return: - x = N-dim vector (if all principal minors of M are nonsingular)\n\
    //         - empty vector     (otherwise)\ntemplate <typename T> std::vector<T>\
    \ levinson_recursion(const std::vector<T> &toeplitz, const std::vector<T> &y)\
    \ {\n    const int N = y.size();\n    assert(int(toeplitz.size()) == N * 2 - 1);\n\
    \    std::vector<T> x(N);\n    std::vector<T> fn(1), en(1);\n    if (toeplitz[N\
    \ - 1] == 0) { return {}; }\n    fn[0] = en[0] = toeplitz[N - 1].inv();\n    x[0]\
    \ = fn[0] * y[0];\n    for (int n = 1; n < N; n++) {\n        T ef = 0, eb = 0;\n\
    \        for (int i = 0; i < n; i++) {\n            ef += fn[i] * toeplitz[N -\
    \ 1 + n - i];\n            eb += en[i] * toeplitz[N - 2 - i];\n        }\n   \
    \     if (ef * eb == 1) { return {}; }\n        auto nxtfn = fn, nxten = en;\n\
    \        nxtfn.emplace_back(0), nxten.insert(nxten.begin(), 0);\n        for (int\
    \ i = 0; i < n; i++) {\n            nxtfn[i + 1] -= ef * en[i];\n            nxten[i]\
    \ -= eb * fn[i];\n        }\n        T c = (1 - ef * eb).inv();\n        for (int\
    \ i = 0; i < n + 1; i++) { nxtfn[i] *= c, nxten[i] *= c; }\n        fn = nxtfn,\
    \ en = nxten;\n\n        T z = y[n];\n        for (int i = 0; i < n; i++) z -=\
    \ x[i] * toeplitz[N - 1 + n - i];\n        for (int i = 0; i < n + 1; i++) x[i]\
    \ += en[i] * z;\n    }\n    return x;\n}\n"
  code: "#pragma once\n#include <cassert>\n#include <vector>\n\n// CUT begin\n// solve\
    \ Mx = y based on Levinson recursion\n//\n// M = [\n// [ t_(N-1) t_(N-2) ... t_1\
    \ t_0     ]\n// [ t_N     t_(N-1) ... t_2 t_1     ]\n// [ ...                \
    \             ]\n// [ t_(N*2-2)       ...     t_(N-1) ]]\n//\n// Complexity: O(N^2)\n\
    // Reference: <https://en.wikipedia.org/wiki/Levinson_recursion>\n// return: -\
    \ x = N-dim vector (if all principal minors of M are nonsingular)\n//        \
    \ - empty vector     (otherwise)\ntemplate <typename T> std::vector<T> levinson_recursion(const\
    \ std::vector<T> &toeplitz, const std::vector<T> &y) {\n    const int N = y.size();\n\
    \    assert(int(toeplitz.size()) == N * 2 - 1);\n    std::vector<T> x(N);\n  \
    \  std::vector<T> fn(1), en(1);\n    if (toeplitz[N - 1] == 0) { return {}; }\n\
    \    fn[0] = en[0] = toeplitz[N - 1].inv();\n    x[0] = fn[0] * y[0];\n    for\
    \ (int n = 1; n < N; n++) {\n        T ef = 0, eb = 0;\n        for (int i = 0;\
    \ i < n; i++) {\n            ef += fn[i] * toeplitz[N - 1 + n - i];\n        \
    \    eb += en[i] * toeplitz[N - 2 - i];\n        }\n        if (ef * eb == 1)\
    \ { return {}; }\n        auto nxtfn = fn, nxten = en;\n        nxtfn.emplace_back(0),\
    \ nxten.insert(nxten.begin(), 0);\n        for (int i = 0; i < n; i++) {\n   \
    \         nxtfn[i + 1] -= ef * en[i];\n            nxten[i] -= eb * fn[i];\n \
    \       }\n        T c = (1 - ef * eb).inv();\n        for (int i = 0; i < n +\
    \ 1; i++) { nxtfn[i] *= c, nxten[i] *= c; }\n        fn = nxtfn, en = nxten;\n\
    \n        T z = y[n];\n        for (int i = 0; i < n; i++) z -= x[i] * toeplitz[N\
    \ - 1 + n - i];\n        for (int i = 0; i < n + 1; i++) x[i] += en[i] * z;\n\
    \    }\n    return x;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: linear_algebra_matrix/toeplitz.hpp
  requiredBy: []
  timestamp: '2020-12-14 02:23:38+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: linear_algebra_matrix/toeplitz.hpp
layout: document
redirect_from:
- /library/linear_algebra_matrix/toeplitz.hpp
- /library/linear_algebra_matrix/toeplitz.hpp.html
title: linear_algebra_matrix/toeplitz.hpp
---
