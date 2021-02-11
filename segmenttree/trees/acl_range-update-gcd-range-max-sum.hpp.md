---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: segmenttree/acl_beats.hpp
    title: Segment Tree Beats (based on atcoder::lazy_segtree)
  - icon: ':heavy_check_mark:'
    path: segmenttree/acl_lazysegtree.hpp
    title: segmenttree/acl_lazysegtree.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: segmenttree/test/beats_gcd.test.cpp
    title: segmenttree/test/beats_gcd.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://yukicoder.me/submissions/611774
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.1/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.1/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 193, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.1/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.1/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.1/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 355, in update\n    raise BundleErrorAt(path, i + 1, \"found codes out\
    \ of include guard\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ segmenttree/acl_lazysegtree.hpp: line 37: found codes out of include guard\n"
  code: "#pragma once\n#include \"../acl_beats.hpp\"\n\n// CUT begin\n// Verified:\
    \ https://yukicoder.me/submissions/611774\nnamespace yuki880 {\nconstexpr uint32_t\
    \ BINF = 1 << 30;\n\nstruct S {\n    uint32_t max;\n    uint32_t lcm;\n    uint32_t\
    \ sz;\n    uint64_t sum;\n    bool fail;\n    bool all_same;\n    S() : max(0),\
    \ lcm(1), sz(1), sum(0), fail(0), all_same(0) {}\n    S(uint32_t x, uint32_t sz_\
    \ = 1) : max(x), lcm(x), sz(sz_), sum((uint64_t)x * sz_), fail(0), all_same(1)\
    \ {}\n};\n\nS e() { return S(); }\n\nS op(S l, S r) {\n    if (r.sz == 0) return\
    \ l;\n    if (l.sz == 0) return r;\n    S ret;\n    ret.max = std::max(l.max,\
    \ r.max);\n    ret.sum = l.sum + r.sum;\n    ret.lcm = (l.lcm >= BINF or r.lcm\
    \ >= BINF) ? BINF : std::min<uint64_t>(BINF, (uint64_t)l.lcm * r.lcm / std::__gcd(l.lcm,\
    \ r.lcm));\n    ret.sz = l.sz + r.sz;\n    if (l.all_same and r.all_same and l.max\
    \ == r.max) ret.all_same = true;\n    return ret;\n}\n\nstruct F {\n    uint32_t\
    \ dogcd, reset;\n    F() : dogcd(0), reset(0) {}\n    F(uint32_t g, uint32_t upd)\
    \ : dogcd(g), reset(upd) {}\n    static F gcd(uint32_t g) noexcept { return F(g,\
    \ 0); }\n    static F update(uint32_t a) noexcept { return F(0, a); }\n};\n\n\
    F composition(F fnew, F fold) { return fnew.reset ? fnew : F(std::__gcd(fnew.dogcd,\
    \ fold.dogcd), fold.reset); }\n\nF id() { return F(); }\n\nS mapping(F f, S x)\
    \ {\n    if (x.fail) return x;\n    if (f.reset) x = S(f.reset, x.sz);\n    if\
    \ (f.dogcd) {\n        if (x.all_same)\n            x = S(std::__gcd(f.dogcd,\
    \ x.max), x.sz);\n        else if (f.dogcd and (x.lcm == BINF or f.dogcd % x.lcm))\n\
    \            x.fail = true;\n    }\n    return x;\n}\nusing segtree = segtree_beats<S,\
    \ op, e, F, mapping, composition, id>;\n} // namespace yuki880\n"
  dependsOn:
  - segmenttree/acl_beats.hpp
  - segmenttree/acl_lazysegtree.hpp
  isVerificationFile: false
  path: segmenttree/trees/acl_range-update-gcd-range-max-sum.hpp
  requiredBy: []
  timestamp: '2021-01-31 16:39:51+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - segmenttree/test/beats_gcd.test.cpp
documentation_of: segmenttree/trees/acl_range-update-gcd-range-max-sum.hpp
layout: document
redirect_from:
- /library/segmenttree/trees/acl_range-update-gcd-range-max-sum.hpp
- /library/segmenttree/trees/acl_range-update-gcd-range-max-sum.hpp.html
title: segmenttree/trees/acl_range-update-gcd-range-max-sum.hpp
---
