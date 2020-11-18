---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"utilities/rotate90.hpp\"\n#include <vector>\n\n// CUT begin\n\
    template <typename T> std::vector<std::vector<T>> rotate90(const std::vector<std::vector<T>>&\
    \ in) {\n    const size_t H = in.size(), W = in[0].size();\n    std::vector<std::vector<T>>\
    \ ret(W, std::vector<T>(H));\n    for (size_t i = 0; i < H; i++) {\n        for\
    \ (size_t j = 0; j < W; j++) ret[j][i] = in[i][W - 1 - j];\n    }\n    return\
    \ ret;\n}\n"
  code: "#pragma once\n#include <vector>\n\n// CUT begin\ntemplate <typename T> std::vector<std::vector<T>>\
    \ rotate90(const std::vector<std::vector<T>>& in) {\n    const size_t H = in.size(),\
    \ W = in[0].size();\n    std::vector<std::vector<T>> ret(W, std::vector<T>(H));\n\
    \    for (size_t i = 0; i < H; i++) {\n        for (size_t j = 0; j < W; j++)\
    \ ret[j][i] = in[i][W - 1 - j];\n    }\n    return ret;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/rotate90.hpp
  requiredBy: []
  timestamp: '2020-11-18 20:25:12+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utilities/rotate90.hpp
layout: document
redirect_from:
- /library/utilities/rotate90.hpp
- /library/utilities/rotate90.hpp.html
title: utilities/rotate90.hpp
---
