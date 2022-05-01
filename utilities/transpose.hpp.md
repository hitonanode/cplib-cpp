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
  bundledCode: "#line 2 \"utilities/transpose.hpp\"\n#include <string>\n#include <vector>\n\
    \ntemplate <typename T> std::vector<std::vector<T>> transpose(const std::vector<std::vector<T>>\
    \ &v) {\n    const int H = v.size(), W = v[0].size();\n    std::vector<std::vector<T>>\
    \ ret(W, std::vector<T>(H));\n    for (int i = 0; i < H; i++) {\n        for (int\
    \ j = 0; j < W; j++) ret[j][i] = v[i][j];\n    }\n    return ret;\n}\n\nstd::vector<std::string>\
    \ transpose(const std::vector<std::string> &v) {\n    const int H = v.size(),\
    \ W = v[0].size();\n    std::vector<std::string> ret(W, std::string(H, '\\0'));\n\
    \    for (int i = 0; i < H; i++) {\n        for (int j = 0; j < W; j++) ret[j][i]\
    \ = v[i][j];\n    }\n    return ret;\n}\n"
  code: "#pragma once\n#include <string>\n#include <vector>\n\ntemplate <typename\
    \ T> std::vector<std::vector<T>> transpose(const std::vector<std::vector<T>> &v)\
    \ {\n    const int H = v.size(), W = v[0].size();\n    std::vector<std::vector<T>>\
    \ ret(W, std::vector<T>(H));\n    for (int i = 0; i < H; i++) {\n        for (int\
    \ j = 0; j < W; j++) ret[j][i] = v[i][j];\n    }\n    return ret;\n}\n\nstd::vector<std::string>\
    \ transpose(const std::vector<std::string> &v) {\n    const int H = v.size(),\
    \ W = v[0].size();\n    std::vector<std::string> ret(W, std::string(H, '\\0'));\n\
    \    for (int i = 0; i < H; i++) {\n        for (int j = 0; j < W; j++) ret[j][i]\
    \ = v[i][j];\n    }\n    return ret;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/transpose.hpp
  requiredBy: []
  timestamp: '2022-05-01 15:34:14+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utilities/transpose.hpp
layout: document
redirect_from:
- /library/utilities/transpose.hpp
- /library/utilities/transpose.hpp.html
title: utilities/transpose.hpp
---
