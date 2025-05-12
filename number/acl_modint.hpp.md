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
  bundledCode: "#line 2 \"number/acl_modint.hpp\"\n#include <atcoder/modint>\n#include\
    \ <cassert>\n#include <iostream>\n#include <vector>\n\n// Utility functions for\
    \ atcoder::static_modint<md>\ntemplate <int md> std::istream &operator>>(std::istream\
    \ &is, atcoder::static_modint<md> &x) {\n    long long t;\n    return is >> t,\
    \ x = t, is;\n}\ntemplate <int md> std::ostream &operator<<(std::ostream &os,\
    \ const atcoder::static_modint<md> &x) {\n    return os << x.val();\n}\n// atcoder::static_modint<P>,\
    \ P: prime number\ntemplate <typename modint> struct acl_fac {\n    std::vector<modint>\
    \ facs, facinvs;\n    acl_fac(int N) {\n        assert(-1 <= N and N < modint::mod());\n\
    \        facs.resize(N + 1, 1);\n        for (int i = 1; i <= N; i++) facs[i]\
    \ = facs[i - 1] * i;\n        facinvs.assign(N + 1, facs.back().inv());\n    \
    \    for (int i = N; i > 0; i--) facinvs[i - 1] = facinvs[i] * i;\n    }\n   \
    \ modint ncr(int n, int r) const {\n        if (n < 0 or r < 0 or n < r) return\
    \ 0;\n        return facs[n] * facinvs[r] * facinvs[n - r];\n    }\n    modint\
    \ operator[](int i) const { return facs[i]; }\n    modint finv(int i) const {\
    \ return facinvs[i]; }\n    modint inv(int i) const { return i > 0 ? facinvs[i]\
    \ * facs[i - 1] : 1; }\n};\n// acl_fac<mint> fac(1000000);\n"
  code: "#pragma once\n#include <atcoder/modint>\n#include <cassert>\n#include <iostream>\n\
    #include <vector>\n\n// Utility functions for atcoder::static_modint<md>\ntemplate\
    \ <int md> std::istream &operator>>(std::istream &is, atcoder::static_modint<md>\
    \ &x) {\n    long long t;\n    return is >> t, x = t, is;\n}\ntemplate <int md>\
    \ std::ostream &operator<<(std::ostream &os, const atcoder::static_modint<md>\
    \ &x) {\n    return os << x.val();\n}\n// atcoder::static_modint<P>, P: prime\
    \ number\ntemplate <typename modint> struct acl_fac {\n    std::vector<modint>\
    \ facs, facinvs;\n    acl_fac(int N) {\n        assert(-1 <= N and N < modint::mod());\n\
    \        facs.resize(N + 1, 1);\n        for (int i = 1; i <= N; i++) facs[i]\
    \ = facs[i - 1] * i;\n        facinvs.assign(N + 1, facs.back().inv());\n    \
    \    for (int i = N; i > 0; i--) facinvs[i - 1] = facinvs[i] * i;\n    }\n   \
    \ modint ncr(int n, int r) const {\n        if (n < 0 or r < 0 or n < r) return\
    \ 0;\n        return facs[n] * facinvs[r] * facinvs[n - r];\n    }\n    modint\
    \ operator[](int i) const { return facs[i]; }\n    modint finv(int i) const {\
    \ return facinvs[i]; }\n    modint inv(int i) const { return i > 0 ? facinvs[i]\
    \ * facs[i - 1] : 1; }\n};\n// acl_fac<mint> fac(1000000);\n"
  dependsOn: []
  isVerificationFile: false
  path: number/acl_modint.hpp
  requiredBy: []
  timestamp: '2025-05-12 23:00:20+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: number/acl_modint.hpp
layout: document
redirect_from:
- /library/number/acl_modint.hpp
- /library/number/acl_modint.hpp.html
title: number/acl_modint.hpp
---
