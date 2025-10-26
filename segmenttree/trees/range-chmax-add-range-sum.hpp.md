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
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: segmenttree/test/beats_range-chmax-add-range-sum.aoj0427.test.cpp
    title: segmenttree/test/beats_range-chmax-add-range-sum.aoj0427.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0427
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.13.7/x64/lib/python3.13/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ~~~~~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.13.7/x64/lib/python3.13/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n    ~~~~~~~~~~~~~~^^^^^^\n  File\
    \ \"/opt/hostedtoolcache/Python/3.13.7/x64/lib/python3.13/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \    ~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.13.7/x64/lib/python3.13/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \    ~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.13.7/x64/lib/python3.13/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 355, in update\n    raise BundleErrorAt(path, i + 1, \"found codes out\
    \ of include guard\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ segmenttree/acl_lazysegtree.hpp: line 56: found codes out of include guard\n"
  code: "#pragma once\n#include \"../acl_beats.hpp\"\n#include <algorithm>\n#include\
    \ <type_traits>\n\n// Verified: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0427\n\
    template <typename Num, Num INF> struct RangeChmaxAddRangeSum {\n    static_assert(std::is_signed<Num>::value,\
    \ \"Num must be signed\");\n\n    static Num second_lowest(Num a, Num a2, Num\
    \ c, Num c2) noexcept { // a < a2, c < c2\n        return a == c ? std::min(a2,\
    \ c2) : a2 <= c ? a2 : c2 <= a ? c2 : std::max(a, c);\n    }\n\n    struct S {\n\
    \        Num lo, lo2, sum;\n        unsigned sz, nlo;\n        bool fail;\n  \
    \      S() : lo(INF), lo2(INF), sum(0), sz(0), nlo(0), fail(false) {}\n      \
    \  S(Num x, unsigned sz_ = 1)\n            : lo(x), lo2(INF), sum(Num(x) * sz_),\
    \ sz(sz_), nlo(sz_), fail(false) {}\n    };\n\nprivate:\n    static S e() { return\
    \ S(); }\n\n    static S op(S l, S r) {\n        S ret;\n        ret.lo = std::min(l.lo,\
    \ r.lo);\n        ret.lo2 = second_lowest(l.lo, l.lo2, r.lo, r.lo2);\n       \
    \ ret.sum = l.sum + r.sum, ret.sz = l.sz + r.sz;\n        ret.nlo = l.nlo * (l.lo\
    \ <= r.lo) + r.nlo * (r.lo <= l.lo);\n        return ret;\n    }\n\n    struct\
    \ F {\n        Num lb, bias;\n        F() : lb(-INF), bias(0) {}\n        F(Num\
    \ chmax_, Num add) : lb(chmax_), bias(add) {}\n    };\n\n    static F id() { return\
    \ F(); }\n\n    static S mapping(F f, S x) {\n        if (x.sz == 0) return e();\n\
    \        if (f.lb < x.lo2) {\n            Num nxt_lo = std::max(x.lo, f.lb);\n\
    \            x.sum += (nxt_lo - x.lo) * x.nlo + f.bias * x.sz;\n            x.lo\
    \ = nxt_lo + f.bias, x.lo2 += f.bias;\n            return x;\n        }\n    \
    \    x.fail = 1;\n        return x;\n    }\n\npublic:\n    static F composition(F\
    \ fnew, F fold) {\n        F ret;\n        ret.lb = std::max(fold.lb + fold.bias,\
    \ fnew.lb) - fold.bias;\n        ret.bias = fold.bias + fnew.bias;\n        return\
    \ ret;\n    }\n\n    static F Chmax(Num x) noexcept { return F(x, Num(0)); }\n\
    \    static F Add(Num x) noexcept { return F(-INF, x); };\n\n    static S Gen(Num\
    \ x, unsigned sz = 1) { return S{x, sz}; }\n\n    using segtree = segtree_beats<S,\
    \ op, e, F, mapping, composition, id>;\n};\n/* Usage:\nusing RCARS = RangeChmaxAddRangeSum<long\
    \ long, (1LL << 60)>;\nvector<RCARS::S> init;\nfor (auto a : A) init.push_back(RCARS::Gen(a,\
    \ 1));\nRCARS::segtree tree(init);\n\ntree.apply(l, r, RCARS::Chmax(x));\ntree.apply(l,\
    \ r, RCARS::Add(x));\nauto p = tree.prod(l, r);\n*/\n"
  dependsOn:
  - segmenttree/acl_beats.hpp
  - segmenttree/acl_lazysegtree.hpp
  isVerificationFile: false
  path: segmenttree/trees/range-chmax-add-range-sum.hpp
  requiredBy: []
  timestamp: '2025-10-26 14:03:13+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - segmenttree/test/beats_range-chmax-add-range-sum.aoj0427.test.cpp
documentation_of: segmenttree/trees/range-chmax-add-range-sum.hpp
layout: document
redirect_from:
- /library/segmenttree/trees/range-chmax-add-range-sum.hpp
- /library/segmenttree/trees/range-chmax-add-range-sum.hpp.html
title: segmenttree/trees/range-chmax-add-range-sum.hpp
---
