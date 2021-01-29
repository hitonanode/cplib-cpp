---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://gist.github.com/draftcode/1357281
  bundledCode: "#line 2 \"syntactic_analysis/ll1parser.hpp\"\n#include <cmath>\n#include\
    \ <string>\n\n// CUT begin\n// \u69CB\u6587\u6728\u3092\u4F5C\u3089\u305A\u7C21\
    \u5358\u306A\u6574\u6570\u52A0\u6E1B\u4E57\u7B97\u3092\u3084\u308BLL(1)\u69CB\u6587\
    \u89E3\u6790\n// https://gist.github.com/draftcode/1357281 \u306A\u3069\u304C\u53C2\
    \u8003\u306B\u306A\u308B\ntemplate <typename T> struct Parser {\n    using State\
    \ = std::string::const_iterator;\n\n    Parser() {}\n\n    T expr(State &begin)\
    \ {\n        T ret = term(begin);\n        while (true) {\n            if (*begin\
    \ == '+') {\n                begin++;\n                ret += term(begin);\n \
    \           } else if (*begin == '-') {\n                begin++;\n          \
    \      ret -= term(begin);\n            } else\n                break;\n     \
    \   }\n        return ret;\n    }\n\n    T term(State &begin) {\n        T ret\
    \ = factor(begin);\n        while (true) {\n            if (*begin == '*') {\n\
    \                begin++;\n                ret *= factor(begin);\n           \
    \ } else\n                break;\n        }\n        return ret;\n    }\n\n  \
    \  T value(State &begin) {\n        T ret = 0;\n        while (isdigit(*begin))\
    \ {\n            ret *= 10;\n            ret += *begin - '0';\n            begin++;\n\
    \        }\n        return ret;\n    }\n\n    T factor(State &begin) {\n     \
    \   if (*begin == '(') {\n            begin++;\n            T ret = expr(begin);\n\
    \            begin++;\n            return ret;\n        } else\n            return\
    \ value(begin);\n    }\n};\n/* example usage\nParser<long long> parser();\nstd::string::const_iterator\
    \ iter = S.begin();\nstd::cout << parser.expr(iter) << '\\n';\n*/\n"
  code: "#pragma once\n#include <cmath>\n#include <string>\n\n// CUT begin\n// \u69CB\
    \u6587\u6728\u3092\u4F5C\u3089\u305A\u7C21\u5358\u306A\u6574\u6570\u52A0\u6E1B\
    \u4E57\u7B97\u3092\u3084\u308BLL(1)\u69CB\u6587\u89E3\u6790\n// https://gist.github.com/draftcode/1357281\
    \ \u306A\u3069\u304C\u53C2\u8003\u306B\u306A\u308B\ntemplate <typename T> struct\
    \ Parser {\n    using State = std::string::const_iterator;\n\n    Parser() {}\n\
    \n    T expr(State &begin) {\n        T ret = term(begin);\n        while (true)\
    \ {\n            if (*begin == '+') {\n                begin++;\n            \
    \    ret += term(begin);\n            } else if (*begin == '-') {\n          \
    \      begin++;\n                ret -= term(begin);\n            } else\n   \
    \             break;\n        }\n        return ret;\n    }\n\n    T term(State\
    \ &begin) {\n        T ret = factor(begin);\n        while (true) {\n        \
    \    if (*begin == '*') {\n                begin++;\n                ret *= factor(begin);\n\
    \            } else\n                break;\n        }\n        return ret;\n\
    \    }\n\n    T value(State &begin) {\n        T ret = 0;\n        while (isdigit(*begin))\
    \ {\n            ret *= 10;\n            ret += *begin - '0';\n            begin++;\n\
    \        }\n        return ret;\n    }\n\n    T factor(State &begin) {\n     \
    \   if (*begin == '(') {\n            begin++;\n            T ret = expr(begin);\n\
    \            begin++;\n            return ret;\n        } else\n            return\
    \ value(begin);\n    }\n};\n/* example usage\nParser<long long> parser();\nstd::string::const_iterator\
    \ iter = S.begin();\nstd::cout << parser.expr(iter) << '\\n';\n*/\n"
  dependsOn: []
  isVerificationFile: false
  path: syntactic_analysis/ll1parser.hpp
  requiredBy: []
  timestamp: '2020-11-18 20:25:12+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: syntactic_analysis/ll1parser.hpp
layout: document
redirect_from:
- /library/syntactic_analysis/ll1parser.hpp
- /library/syntactic_analysis/ll1parser.hpp.html
title: syntactic_analysis/ll1parser.hpp
---
