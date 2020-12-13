---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 193, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: matroid/matroid.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n#include \"matroid/matroid.hpp\"\n#include <bitset>\n#include\
    \ <cassert>\n#include <unordered_map>\n#include <utility>\n#include <vector>\n\
    using namespace std;\n\n// CUT begin\n// Vector matroid on F2 : linearly independent\
    \ vectors\n// VDIM: max. dimension of vector space\n// Verified: SRM526.5 1000\
    \ (Used only for linear independence check)\ntemplate <int VDIM> struct F2VectorMatroid\
    \ {\n    int M; // # of vectors\n    vector<bitset<VDIM>> mat;\n    mutable vector<unordered_map<State,\
    \ vector<Element>>> cache;\n    F2VectorMatroid() = default;\n    F2VectorMatroid(const\
    \ vector<bitset<VDIM>> &bitmat) : M(bitmat.size()), mat(bitmat), cache(bitmat.size())\
    \ {}\n\n    // If I is independent and I + {e} is not, return elements of the\
    \ circuit.\n    // If e \\in I, or I + {e} is independent, return empty vector.\n\
    \    // If I is NOT independent, undefined.\n    vector<Element> circuit(const\
    \ State &I, const Element &e) const {\n        assert(int(I.size()) == M and e\
    \ < M);\n        if (I[e]) return {};\n        if (cache[e].count(I)) return cache[e][I];\n\
    \        vector<bitset<VDIM + 1>> A(VDIM);\n        vector<int> eid;\n       \
    \ for (int i = 0; i < M; i++) {\n            if (!I[i]) continue;\n          \
    \  for (int j = 0; j < VDIM; j++) A[j][eid.size()] = mat[i][j];\n            eid.push_back(i);\n\
    \            if (eid.size() > VDIM) return {};\n        }\n        int n = eid.size();\n\
    \        for (int j = 0; j < VDIM; j++) A[j][n] = mat[e][j];\n        for (int\
    \ c = 0; c < n; c++) {\n            int piv = -1;\n            for (int r = c;\
    \ r < VDIM; r++) {\n                if (A[r][c]) {\n                    piv =\
    \ r;\n                    break;\n                }\n            }\n         \
    \   if (piv == -1) return cache[e][I] = {};\n            swap(A[piv], A[c]);\n\
    \            for (int r = 0; r < VDIM; r++) {\n                if (r != c and\
    \ A[r][c]) A[r] ^= A[c];\n            }\n        }\n        for (int r = n; r\
    \ < VDIM; r++)\n            if (A[r][n]) return cache[e][I] = {};\n        vector<Element>\
    \ ret;\n        for (size_t i = 0; i < eid.size(); i++) {\n            if (A[i][n])\
    \ ret.push_back(eid[i]);\n        }\n        return cache[e][I] = ret;\n    }\n\
    };\n"
  dependsOn: []
  isVerificationFile: false
  path: combinatorial_opt/vector_matroid.hpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: combinatorial_opt/vector_matroid.hpp
layout: document
redirect_from:
- /library/combinatorial_opt/vector_matroid.hpp
- /library/combinatorial_opt/vector_matroid.hpp.html
title: combinatorial_opt/vector_matroid.hpp
---
