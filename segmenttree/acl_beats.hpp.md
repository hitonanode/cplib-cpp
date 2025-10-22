---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: segmenttree/acl_lazysegtree.hpp
    title: Lazy Segtree (based on atcoder::lazy_segtree)
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: segmenttree/trees/acl_range-add-chmax-range-sum.hpp
    title: segmenttree/trees/acl_range-add-chmax-range-sum.hpp
  - icon: ':warning:'
    path: segmenttree/trees/acl_range-bitwiseandor-range-max.hpp
    title: segmenttree/trees/acl_range-bitwiseandor-range-max.hpp
  - icon: ':heavy_check_mark:'
    path: segmenttree/trees/acl_range-update-gcd-range-max-sum.hpp
    title: segmenttree/trees/acl_range-update-gcd-range-max-sum.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: segmenttree/test/beats.test.cpp
    title: segmenttree/test/beats.test.cpp
  - icon: ':heavy_check_mark:'
    path: segmenttree/test/beats_gcd.test.cpp
    title: segmenttree/test/beats_gcd.test.cpp
  - icon: ':heavy_check_mark:'
    path: segmenttree/test/beats_random_test.test.cpp
    title: segmenttree/test/beats_random_test.test.cpp
  - icon: ':heavy_check_mark:'
    path: segmenttree/test/beats_range-add-chmax-range-sum.test.cpp
    title: segmenttree/test/beats_range-add-chmax-range-sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
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
    , line 355, in update\n    raise BundleErrorAt(path, i + 1, \"found codes out\
    \ of include guard\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ segmenttree/acl_lazysegtree.hpp: line 56: found codes out of include guard\n"
  code: "#pragma once\n#include \"acl_lazysegtree.hpp\"\n\n#include <algorithm>\n\
    #include <iostream>\n\ntemplate <class S, auto op, auto e, class F, auto mapping,\
    \ auto composition, auto id>\nclass segtree_beats : public atcoder::lazy_segtree<S,\
    \ op, e, F, mapping, composition, id> {\n    using Base = atcoder::lazy_segtree<S,\
    \ op, e, F, mapping, composition, id>;\n    using Base::lazy_segtree;\n    void\
    \ all_apply(int k, F f) override {\n        Base::d[k] = mapping(f, Base::d[k]);\n\
    \        if (k < Base::size) {\n            Base::lz[k] = composition(f, Base::lz[k]);\n\
    \            if (Base::d[k].fail) Base::push(k), Base::update(k);\n        }\n\
    \    }\n};\n\nnamespace RangeChMinMaxAddSum {\ntemplate <typename Num> inline\
    \ Num second_lowest(Num a, Num a2, Num c, Num c2) noexcept {\n    assert(a <=\
    \ a2); // a < a2 or a == a2 == INF\n    assert(c <= c2); // c < c2 or c == c2\
    \ == -INF\n    return a == c ? std::min(a2, c2) : a2 <= c ? a2 : c2 <= a ? c2\
    \ : std::max(a, c);\n}\ntemplate <typename Num> inline Num second_highest(Num\
    \ a, Num a2, Num b, Num b2) noexcept {\n    assert(a >= a2); // a > a2 or a ==\
    \ a2 == -INF\n    assert(b >= b2); // b > b2 or b == b2 == INF\n    return a ==\
    \ b ? std::max(a2, b2) : a2 >= b ? a2 : b2 >= a ? b2 : std::min(a, b);\n}\n\n\
    using BNum = long long;\nconstexpr BNum BINF = 1LL << 61;\n\nstruct S {\n    BNum\
    \ lo, hi, lo2, hi2, sum;\n    unsigned sz, nlo, nhi;\n    bool fail;\n    S()\
    \ : lo(BINF), hi(-BINF), lo2(BINF), hi2(-BINF), sum(0), sz(0), nlo(0), nhi(0),\
    \ fail(0) {}\n    S(BNum x, unsigned sz_)\n        : lo(x), hi(x), lo2(BINF),\
    \ hi2(-BINF), sum(x * sz_), sz(sz_), nlo(sz_), nhi(sz_), fail(0) {}\n    friend\
    \ std::ostream &operator<<(std::ostream &os, const S s) {\n        return os <<\
    \ \"[(\" << s.lo << \"x\" << s.nlo << \", \" << s.lo2 << \", \" << s.hi2 << \"\
    , \" << s.hi\n                  << \"x\" << s.nhi << \"), sz=\" << s.sz << \"\
    , sum=\" << s.sum << \"]\";\n    }\n};\n\nS e() { return S(); }\nS op(S l, S r)\
    \ {\n    if (l.lo > l.hi) return r;\n    if (r.lo > r.hi) return l;\n    S ret;\n\
    \    ret.lo = std::min(l.lo, r.lo);\n    ret.hi = std::max(l.hi, r.hi);\n    ret.lo2\
    \ = second_lowest(l.lo, l.lo2, r.lo, r.lo2),\n    ret.hi2 = second_highest(l.hi,\
    \ l.hi2, r.hi, r.hi2);\n    ret.sum = l.sum + r.sum;\n    ret.sz = l.sz + r.sz;\n\
    \    ret.nlo = l.nlo * (l.lo <= r.lo) + r.nlo * (r.lo <= l.lo);\n    ret.nhi =\
    \ l.nhi * (l.hi >= r.hi) + r.nhi * (r.hi >= l.hi);\n    return ret;\n}\nstruct\
    \ F {\n    BNum lb, ub, bias;\n    F() : lb(-BINF), ub(BINF), bias(0) {}\n   \
    \ F(BNum chmax_, BNum chmin_, BNum add) : lb(chmax_), ub(chmin_), bias(add) {}\n\
    \    static F chmin(BNum x) noexcept { return F(-BINF, x, BNum(0)); }\n    static\
    \ F chmax(BNum x) noexcept { return F(x, BINF, BNum(0)); }\n    static F add(BNum\
    \ x) noexcept { return F(-BINF, BINF, x); };\n};\n\nF composition(F fnew, F fold)\
    \ {\n    F ret;\n    ret.lb = std::max(std::min(fold.lb + fold.bias, fnew.ub),\
    \ fnew.lb) - fold.bias;\n    ret.ub = std::min(std::max(fold.ub + fold.bias, fnew.lb),\
    \ fnew.ub) - fold.bias;\n    ret.bias = fold.bias + fnew.bias;\n    return ret;\n\
    }\nF id() { return F(); }\nS mapping(F f, S x) {\n    if (x.sz == 0) return e();\n\
    \n    // f \u306E\u4F5C\u7528\u5F8C x \u306E\u8981\u7D20\u304C 1 \u7A2E\u985E\u3060\
    \u3051\u306B\u306A\u308B\u30B1\u30FC\u30B9\n    if (x.lo == x.hi or f.lb == f.ub\
    \ or f.lb >= x.hi or f.ub <= x.lo) {\n        return S(std::min(std::max(x.lo,\
    \ f.lb), f.ub) + f.bias, x.sz);\n    }\n\n    // 2 \u7A2E\u985E -> 1 \u7A2E\u985E\
    \n    if (x.lo2 == x.hi) {\n        x.lo = x.hi2 = std::max(x.lo, f.lb) + f.bias;\n\
    \        x.hi = x.lo2 = std::min(x.hi, f.ub) + f.bias;\n        x.sum = x.lo *\
    \ x.nlo + x.hi * x.nhi;\n        return x;\n    }\n\n    // lo \u3068 lo2, hi\
    \ \u3068 hi2 \u304C\u6F70\u308C\u306A\u3044\u30B1\u30FC\u30B9\n    if (f.lb <\
    \ x.lo2 and f.ub > x.hi2) {\n        BNum nxt_lo = std::max(x.lo, f.lb), nxt_hi\
    \ = std::min(x.hi, f.ub);\n        x.sum += (nxt_lo - x.lo) * x.nlo - (x.hi -\
    \ nxt_hi) * x.nhi + f.bias * x.sz;\n        x.lo = nxt_lo + f.bias, x.hi = nxt_hi\
    \ + f.bias, x.lo2 += f.bias, x.hi2 += f.bias;\n        return x;\n    }\n\n  \
    \  x.fail = 1;\n    return x;\n}\n\nusing segtree = segtree_beats<S, op, e, F,\
    \ mapping, composition, id>;\n\n} // namespace RangeChMinMaxAddSum\n"
  dependsOn:
  - segmenttree/acl_lazysegtree.hpp
  isVerificationFile: false
  path: segmenttree/acl_beats.hpp
  requiredBy:
  - segmenttree/trees/acl_range-update-gcd-range-max-sum.hpp
  - segmenttree/trees/acl_range-bitwiseandor-range-max.hpp
  - segmenttree/trees/acl_range-add-chmax-range-sum.hpp
  timestamp: '2025-10-07 09:41:07+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - segmenttree/test/beats_gcd.test.cpp
  - segmenttree/test/beats_range-add-chmax-range-sum.test.cpp
  - segmenttree/test/beats_random_test.test.cpp
  - segmenttree/test/beats.test.cpp
documentation_of: segmenttree/acl_beats.hpp
layout: document
title: Segment Tree Beats (based on atcoder::lazy_segtree)
---

ACL-based [segment tree beats](https://codeforces.com/blog/entry/57319)

## Link

- [ACL reference](https://atcoder.github.io/ac-library/production/document_ja/lazysegtree.html)
- [My blog](https://rsm9.hatenablog.com/entry/2021/02/01/220408)
