---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':heavy_check_mark:'
    path: segmenttree/acl_lazysegtree.hpp
    title: Lazy Segtree (based on atcoder::lazy_segtree)
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: segmenttree/test/acl_range-affine-range-sum.test.cpp
    title: segmenttree/test/acl_range-affine-range-sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.12.6/x64/lib/python3.12/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.12.6/x64/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.12.6/x64/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.12.6/x64/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 355, in update\n    raise BundleErrorAt(path, i + 1, \"found codes out\
    \ of include guard\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ segmenttree/acl_lazysegtree.hpp: line 37: found codes out of include guard\n"
  code: "#pragma once\n#include \"../../modint.hpp\"\n#include \"../acl_lazysegtree.hpp\"\
    \n#include <utility>\n\n// CUT begin\nnamespace RangeAffineRangeSum {\nusing T\
    \ = ModInt<998244353>;\nusing S = std::pair<T, size_t>;\nusing F = std::pair<T,\
    \ T>;\nS op(S l, S r) { return std::make_pair(l.first + r.first, l.second + r.second);\
    \ }\nS mapping(F f, S x) { return std::make_pair(f.first * x.first + f.second\
    \ * x.second, x.second); }\nF composition(F later, F conv) {\n    return std::make_pair(conv.first\
    \ * later.first, later.second + later.first * conv.second);\n}\nS e() { return\
    \ std::make_pair(0, 0); }\nF id() { return std::make_pair(1, 0); }\nusing segtree\
    \ = atcoder::lazy_segtree<S, op, e, F, mapping, composition, id>;\n}; // namespace\
    \ RangeAffineRangeSum\n"
  dependsOn:
  - modint.hpp
  - segmenttree/acl_lazysegtree.hpp
  isVerificationFile: false
  path: segmenttree/trees/acl_range-affine-range-sum.hpp
  requiredBy: []
  timestamp: '2023-12-26 21:26:22+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - segmenttree/test/acl_range-affine-range-sum.test.cpp
documentation_of: segmenttree/trees/acl_range-affine-range-sum.hpp
layout: document
redirect_from:
- /library/segmenttree/trees/acl_range-affine-range-sum.hpp
- /library/segmenttree/trees/acl_range-affine-range-sum.hpp.html
title: segmenttree/trees/acl_range-affine-range-sum.hpp
---
