---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: segmenttree/acl_beats.hpp
    title: Segment Tree Beats (based on atcoder::lazy_segtree)
  - icon: ':heavy_check_mark:'
    path: segmenttree/acl_lazysegtree.hpp
    title: Lazy Segtree (based on atcoder::lazy_segtree)
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://csacademy.com/contest/round-70/task/and-or-max
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.4/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.4/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.4/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.4/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.4/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 355, in update\n    raise BundleErrorAt(path, i + 1, \"found codes out\
    \ of include guard\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ segmenttree/acl_lazysegtree.hpp: line 37: found codes out of include guard\n"
  code: "#pragma once\n#include \"../acl_beats.hpp\"\n\n// CUT begin\n// Verified:\
    \ https://csacademy.com/contest/round-70/task/and-or-max\nnamespace RangeBitwiseAndOrRangeMax\
    \ {\nusing UINT = uint32_t;\nconstexpr UINT digit = 20;\nconstexpr int mask =\
    \ (1 << digit) - 1;\n\nstruct S {\n    UINT max;\n    UINT upper;\n    UINT lower;\n\
    \    bool fail;\n    S(UINT x = 0) : max(x), upper(x), lower(x), fail(false) {}\n\
    };\n\nS e() { return S(); }\n\nS op(S l, S r) {\n    l.max = std::max(l.max, r.max);\n\
    \    l.upper |= r.upper;\n    l.lower &= r.lower;\n    return l;\n}\n\nstruct\
    \ F {\n    UINT bit_and;\n    UINT bit_or;\n    F() : bit_and(mask), bit_or(0)\
    \ {}\n    F(UINT a, UINT o) : bit_and(a), bit_or(o) {}\n    static F b_and(UINT\
    \ a) noexcept { return {a, 0}; }\n    static F b_or(UINT a) noexcept { return\
    \ {mask, a}; }\n};\n\nF composition(F fnew, F fold) { return F{fnew.bit_and &\
    \ fold.bit_and, fnew.bit_or | (fnew.bit_and & fold.bit_or)}; }\n\nF id() { return\
    \ F(); }\n\nS mapping(F f, S x) {\n    if ((x.upper - x.lower) & (~f.bit_and |\
    \ f.bit_or)) {\n        x.fail = true;\n        return x;\n    }\n    x.upper\
    \ = (x.upper & f.bit_and) | f.bit_or;\n    x.lower = (x.lower & f.bit_and) | f.bit_or;\n\
    \    x.max = (x.max & f.bit_and) | f.bit_or;\n    return x;\n}\nusing segtree\
    \ = segtree_beats<S, op, e, F, mapping, composition, id>;\n} // namespace RangeBitwiseAndOrRangeMax\n"
  dependsOn:
  - segmenttree/acl_beats.hpp
  - segmenttree/acl_lazysegtree.hpp
  isVerificationFile: false
  path: segmenttree/trees/acl_range-bitwiseandor-range-max.hpp
  requiredBy: []
  timestamp: '2021-02-15 23:59:04+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: segmenttree/trees/acl_range-bitwiseandor-range-max.hpp
layout: document
redirect_from:
- /library/segmenttree/trees/acl_range-bitwiseandor-range-max.hpp
- /library/segmenttree/trees/acl_range-bitwiseandor-range-max.hpp.html
title: segmenttree/trees/acl_range-bitwiseandor-range-max.hpp
---
