---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: segmenttree/acl_lazysegtree.hpp
    title: segmenttree/acl_lazysegtree.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: segmenttree/test/beats.test.cpp
    title: segmenttree/test/beats.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.1/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.1/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 193, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.1/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.1/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 355, in update\n    raise BundleErrorAt(path, i + 1, \"found codes out\
    \ of include guard\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ segmenttree/acl_lazysegtree.hpp: line 37: found codes out of include guard\n"
  code: "#pragma once\n#include \"acl_lazysegtree.hpp\"\n\ntemplate <class S, S (*op)(S,\
    \ S), S (*e)(), class F, S (*mapping)(F, S), F (*composition)(F, F), F (*id)()>\n\
    class segtree_beats : public atcoder::lazy_segtree<S, op, e, F, mapping, composition,\
    \ id> {\n    using Base = atcoder::lazy_segtree<S, op, e, F, mapping, composition,\
    \ id>;\n    using Base::lazy_segtree;\n    void all_apply(int k, F f) override\
    \ {\n        Base::d[k] = mapping(f, this->d[k]);\n        if (k < Base::size)\
    \ {\n            Base::lz[k] = composition(f, Base::lz[k]);\n            if (Base::d[k].sz\
    \ == unsigned(-1)) Base::push(k), Base::update(k);\n        }\n    }\n};\n\ntemplate\
    \ <typename Num> inline Num second_lowest(Num a, Num a2, Num c, Num c2) noexcept\
    \ { // a < a2, c < c2\n    return a == c ? std::min(a2, c2) : a2 <= c ? a2 : c2\
    \ <= a ? c2 : std::max(a, c);\n}\ntemplate <typename Num> inline Num second_highest(Num\
    \ a, Num a2, Num b, Num b2) noexcept { // a > a2, b > b2\n    return a == b ?\
    \ std::max(a2, b2) : a2 >= b ? a2 : b2 >= a ? b2 : std::min(a, b);\n}\n\nusing\
    \ BNum = long long;\nconstexpr BNum BINF = 1LL << 61;\n\nstruct BNode {\n    BNum\
    \ lo, hi, lo2, hi2, sum;\n    unsigned sz, nlo, nhi;\n    BNode() : lo(BINF),\
    \ hi(-BINF), lo2(BINF), hi2(-BINF), sum(0), sz(0), nlo(0), nhi(0) {}\n    BNode(BNum\
    \ x, unsigned sz_ = 1) : lo(x), hi(x), lo2(BINF), hi2(-BINF), sum(x * sz_), sz(sz_),\
    \ nlo(sz_), nhi(sz_) {}\n    friend std::ostream &operator<<(std::ostream &os,\
    \ const BNode s) {\n        return os << \"[(\" << s.lo << \"x\" << s.nlo << \"\
    , \" << s.lo2 << \", \" << s.hi2 << \", \" << s.hi << \"x\" << s.nhi << \"), sz=\"\
    \ << s.sz << \", sum=\" << s.sum << \"]\";\n    }\n};\n\nBNode be() { return BNode();\
    \ }\nBNode bop(BNode l, BNode r) {\n    if (l.lo > l.hi) return r;\n    if (r.lo\
    \ > r.hi) return l;\n    BNode ret;\n    ret.lo = std::min(l.lo, r.lo), ret.hi\
    \ = std::max(l.hi, r.hi);\n    ret.lo2 = second_lowest(l.lo, l.lo2, r.lo, r.lo2),\
    \ ret.hi2 = second_highest(l.hi, l.hi2, r.hi, r.hi2);\n    ret.sum = l.sum + r.sum,\
    \ ret.sz = l.sz + r.sz;\n    ret.nlo = l.nlo * (l.lo <= r.lo) + r.nlo * (r.lo\
    \ <= l.lo);\n    ret.nhi = l.nhi * (l.hi >= r.hi) + r.nhi * (r.hi >= l.hi);\n\
    \    return ret;\n}\nstruct BF {\n    BNum lb, ub, bias;\n    BF() : lb(-BINF),\
    \ ub(BINF), bias(0) {}\n    BF(BNum chmax_, BNum chmin_, BNum add) : lb(chmax_),\
    \ ub(chmin_), bias(add) {}\n    static BF chmin(BNum x) noexcept { return BF(-BINF,\
    \ x, BNum(0)); }\n    static BF chmax(BNum x) noexcept { return BF(x, BINF, BNum(0));\
    \ }\n    static BF add(BNum x) noexcept { return BF(-BINF, BINF, x); };\n};\n\n\
    BF bcomposition(BF fnew, BF fold) {\n    BF ret;\n    ret.lb = std::max(std::min(fold.lb\
    \ + fold.bias, fnew.ub), fnew.lb) - fold.bias;\n    ret.ub = std::min(std::max(fold.ub\
    \ + fold.bias, fnew.lb), fnew.ub) - fold.bias;\n    ret.bias = fold.bias + fnew.bias;\n\
    \    return ret;\n}\nBF bid() { return BF(); }\nBNode bmapping(BF f, BNode x)\
    \ {\n    if (x.sz == unsigned(-1)) return x;\n    if (x.sz == 0) return be();\n\
    \    if (x.lo == x.hi or f.lb == f.ub or f.lb >= x.hi or f.ub < x.lo)\n      \
    \  return BNode(std::min(std::max(x.lo, f.lb), f.ub) + f.bias, x.sz);\n    if\
    \ (x.lo2 == x.hi) {\n        x.lo = x.hi2 = std::max(x.lo, f.lb) + f.bias, x.hi\
    \ = x.lo2 = std::min(x.hi, f.ub) + f.bias;\n        x.sum = x.lo * x.nlo + x.hi\
    \ * x.nhi;\n        return x;\n    }\n    if (f.lb < x.lo2 and f.ub > x.hi2) {\n\
    \        BNum nxt_lo = std::max(x.lo, f.lb), nxt_hi = std::min(x.hi, f.ub);\n\
    \        x.sum += (nxt_lo - x.lo) * x.nlo - (x.hi - nxt_hi) * x.nhi + f.bias *\
    \ x.sz;\n        x.lo = nxt_lo + f.bias, x.hi = nxt_hi + f.bias, x.lo2 += f.bias,\
    \ x.hi2 += f.bias;\n        return x;\n    }\n    x.sz = -1;\n    return x;\n\
    }\n"
  dependsOn:
  - segmenttree/acl_lazysegtree.hpp
  isVerificationFile: false
  path: segmenttree/acl_beats.hpp
  requiredBy: []
  timestamp: '2021-01-30 19:57:35+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - segmenttree/test/beats.test.cpp
documentation_of: segmenttree/acl_beats.hpp
layout: document
redirect_from:
- /library/segmenttree/acl_beats.hpp
- /library/segmenttree/acl_beats.hpp.html
title: segmenttree/acl_beats.hpp
---
