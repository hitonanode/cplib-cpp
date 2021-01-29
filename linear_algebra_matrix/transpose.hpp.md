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
  bundledCode: "#line 1 \"linear_algebra_matrix/transpose.hpp\"\n#include <vector>\n\
    \n// CUT begin\ntemplate <typename T> std::vector<std::vector<T>> trans(std::vector<std::vector<T>>\
    \ v) {\n    int H = v.size(), W = v[0].size();\n    std::vector<std::vector<T>>\
    \ ret(W, std::vector<T>(H));\n    for (int i = 0; i < H; i++) {\n        for (int\
    \ j = 0; j < W; j++) ret[j][i] = v[i][j];\n    }\n    return ret;\n}\n"
  code: "#include <vector>\n\n// CUT begin\ntemplate <typename T> std::vector<std::vector<T>>\
    \ trans(std::vector<std::vector<T>> v) {\n    int H = v.size(), W = v[0].size();\n\
    \    std::vector<std::vector<T>> ret(W, std::vector<T>(H));\n    for (int i =\
    \ 0; i < H; i++) {\n        for (int j = 0; j < W; j++) ret[j][i] = v[i][j];\n\
    \    }\n    return ret;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: linear_algebra_matrix/transpose.hpp
  requiredBy: []
  timestamp: '2020-11-18 20:06:08+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: linear_algebra_matrix/transpose.hpp
layout: document
redirect_from:
- /library/linear_algebra_matrix/transpose.hpp
- /library/linear_algebra_matrix/transpose.hpp.html
title: linear_algebra_matrix/transpose.hpp
---
