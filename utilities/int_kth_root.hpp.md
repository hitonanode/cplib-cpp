---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: utilities/test/kth_root_integer.test.cpp
    title: utilities/test/kth_root_integer.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"utilities/int_kth_root.hpp\"\n\n// floor(a^(1/k)) (the largest\
    \ x s.t. x^k doesn't exceed a)\n// Constraints: a >= 0, k > 0\nunsigned long long\
    \ int_kth_root(unsigned long long a, int k) {\n    using Int = __int128;\n   \
    \ if (a == 0) {\n        return 0;\n    } else if (k == 1) {\n        return a;\n\
    \    } else {\n        Int ok = 1, ng = Int(a) + 1;\n        while (ng - ok >\
    \ 1) {\n            Int c = (ok + ng) / 2, p = c;\n            for (int t = 0;\
    \ t < k - 1; t++) {\n                p *= c;\n                if (p > a) break;\n\
    \            }\n            (p > a ? ng : ok) = c;\n        }\n        return\
    \ ok;\n    }\n}\n"
  code: "#pragma once\n\n// floor(a^(1/k)) (the largest x s.t. x^k doesn't exceed\
    \ a)\n// Constraints: a >= 0, k > 0\nunsigned long long int_kth_root(unsigned\
    \ long long a, int k) {\n    using Int = __int128;\n    if (a == 0) {\n      \
    \  return 0;\n    } else if (k == 1) {\n        return a;\n    } else {\n    \
    \    Int ok = 1, ng = Int(a) + 1;\n        while (ng - ok > 1) {\n           \
    \ Int c = (ok + ng) / 2, p = c;\n            for (int t = 0; t < k - 1; t++) {\n\
    \                p *= c;\n                if (p > a) break;\n            }\n \
    \           (p > a ? ng : ok) = c;\n        }\n        return ok;\n    }\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/int_kth_root.hpp
  requiredBy: []
  timestamp: '2020-11-15 01:44:41+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - utilities/test/kth_root_integer.test.cpp
documentation_of: utilities/int_kth_root.hpp
layout: document
redirect_from:
- /library/utilities/int_kth_root.hpp
- /library/utilities/int_kth_root.hpp.html
title: utilities/int_kth_root.hpp
---
