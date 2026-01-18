---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: segmenttree/acl_lazysegtree.hpp
    title: Lazy Segtree (based on atcoder::lazy_segtree)
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.14.2/x64/lib/python3.14/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ~~~~~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.14.2/x64/lib/python3.14/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n    ~~~~~~~~~~~~~~^^^^^^\n  File\
    \ \"/opt/hostedtoolcache/Python/3.14.2/x64/lib/python3.14/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \    ~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.14.2/x64/lib/python3.14/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 355, in update\n    raise BundleErrorAt(path, i + 1, \"found codes out\
    \ of include guard\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ segmenttree/acl_lazysegtree.hpp: line 56: found codes out of include guard\n"
  code: "#pragma once\n#include \"../acl_lazysegtree.hpp\"\n#include <algorithm>\n\
    \nnamespace RangeAddChmaxRangeMin {\n\nusing S = long long;\nconstexpr S INF =\
    \ 1LL << 60;\n\nS e() { return INF; }\n\nS op(S l, S r) { return std::min(l, r);\
    \ }\n\nstruct F {\n    // meaning: max(lower_bound, x) + bias\n    S lower_bound,\
    \ bias;\n    F() : lower_bound(-INF), bias(0) {}\n    F(S lower_bound, S bias)\
    \ : lower_bound(lower_bound), bias(bias) {}\n    static F chmax(S x) { return\
    \ F(x, S()); }\n    static F add(S x) { return F(-INF, x); }\n};\n\nF id() { return\
    \ F(); }\n\nS mapping(F f, S x) { return std::max(f.lower_bound, x) + f.bias;\
    \ }\n\nF composition(F fnew, F gold) {\n    return F(std::max(gold.lower_bound\
    \ + gold.bias, fnew.lower_bound) - gold.bias,\n             gold.bias + fnew.bias);\n\
    }\n\nusing segtree = atcoder::lazy_segtree<S, op, e, F, mapping, composition,\
    \ id>;\n}; // namespace RangeAddChmaxRangeMin\n"
  dependsOn:
  - segmenttree/acl_lazysegtree.hpp
  isVerificationFile: false
  path: segmenttree/trees/acl_range-add-chmax-range-min.hpp
  requiredBy: []
  timestamp: '2025-10-07 09:41:07+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: segmenttree/trees/acl_range-add-chmax-range-min.hpp
layout: document
redirect_from:
- /library/segmenttree/trees/acl_range-add-chmax-range-min.hpp
- /library/segmenttree/trees/acl_range-add-chmax-range-min.hpp.html
title: segmenttree/trees/acl_range-add-chmax-range-min.hpp
---
