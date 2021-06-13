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
  bundledCode: "#line 1 \"utilities/transpose.hpp\"\n#include <vector>\n\n// CUT begin\n\
    template <typename T> std::vector<std::vector<T>> trans(std::vector<std::vector<T>>\
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
  path: utilities/transpose.hpp
  requiredBy: []
  timestamp: '2021-06-13 19:08:25+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utilities/transpose.hpp
layout: document
redirect_from:
- /library/utilities/transpose.hpp
- /library/utilities/transpose.hpp.html
title: utilities/transpose.hpp
---
