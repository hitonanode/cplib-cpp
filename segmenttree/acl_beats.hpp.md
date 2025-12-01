---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: segmenttree/acl_lazysegtree.hpp
    title: Lazy Segtree (based on atcoder::lazy_segtree)
  _extendedRequiredBy:
  - icon: ':warning:'
    path: segmenttree/trees/acl_range-bitwiseandor-range-max.hpp
    title: segmenttree/trees/acl_range-bitwiseandor-range-max.hpp
  - icon: ':heavy_check_mark:'
    path: segmenttree/trees/acl_range-update-gcd-range-max-sum.hpp
    title: segmenttree/trees/acl_range-update-gcd-range-max-sum.hpp
  - icon: ':heavy_check_mark:'
    path: segmenttree/trees/range-chmax-add-range-sum.hpp
    title: segmenttree/trees/range-chmax-add-range-sum.hpp
  - icon: ':heavy_check_mark:'
    path: segmenttree/trees/range-chmax-range-sum.hpp
    title: segmenttree/trees/range-chmax-range-sum.hpp
  - icon: ':heavy_check_mark:'
    path: segmenttree/trees/range-chmin-chmax-add-range-sum.hpp
    title: segmenttree/trees/range-chmin-chmax-add-range-sum.hpp
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
    path: segmenttree/test/beats_range-chmax-add-range-sum.aoj0427.test.cpp
    title: segmenttree/test/beats_range-chmax-add-range-sum.aoj0427.test.cpp
  - icon: ':heavy_check_mark:'
    path: segmenttree/test/range-chmax-range-sum.yuki3314.test.cpp
    title: segmenttree/test/range-chmax-range-sum.yuki3314.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.14.0/x64/lib/python3.14/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ~~~~~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.14.0/x64/lib/python3.14/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n    ~~~~~~~~~~~~~~^^^^^^\n  File\
    \ \"/opt/hostedtoolcache/Python/3.14.0/x64/lib/python3.14/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \    ~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.14.0/x64/lib/python3.14/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 355, in update\n    raise BundleErrorAt(path, i + 1, \"found codes out\
    \ of include guard\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ segmenttree/acl_lazysegtree.hpp: line 56: found codes out of include guard\n"
  code: "#pragma once\n#include \"acl_lazysegtree.hpp\"\n\ntemplate <class S, auto\
    \ op, auto e, class F, auto mapping, auto composition, auto id>\nclass segtree_beats\
    \ : public atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> {\n  \
    \  using Base = atcoder::lazy_segtree<S, op, e, F, mapping, composition, id>;\n\
    \    using Base::lazy_segtree;\n    void all_apply(int k, F f) override {\n  \
    \      Base::d[k] = mapping(f, Base::d[k]);\n        if (k < Base::size) {\n \
    \           Base::lz[k] = composition(f, Base::lz[k]);\n            if (Base::d[k].fail)\
    \ Base::push(k), Base::update(k);\n        }\n    }\n};\n"
  dependsOn:
  - segmenttree/acl_lazysegtree.hpp
  isVerificationFile: false
  path: segmenttree/acl_beats.hpp
  requiredBy:
  - segmenttree/trees/range-chmax-add-range-sum.hpp
  - segmenttree/trees/acl_range-update-gcd-range-max-sum.hpp
  - segmenttree/trees/acl_range-bitwiseandor-range-max.hpp
  - segmenttree/trees/range-chmax-range-sum.hpp
  - segmenttree/trees/range-chmin-chmax-add-range-sum.hpp
  timestamp: '2025-10-26 13:49:19+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - segmenttree/test/beats_gcd.test.cpp
  - segmenttree/test/beats_range-chmax-add-range-sum.aoj0427.test.cpp
  - segmenttree/test/beats_random_test.test.cpp
  - segmenttree/test/beats.test.cpp
  - segmenttree/test/range-chmax-range-sum.yuki3314.test.cpp
documentation_of: segmenttree/acl_beats.hpp
layout: document
title: Segment Tree Beats (based on atcoder::lazy_segtree)
---

ACL-based [segment tree beats](https://codeforces.com/blog/entry/57319)

## Link

- [ACL reference](https://atcoder.github.io/ac-library/production/document_ja/lazysegtree.html)
- [My blog](https://rsm9.hatenablog.com/entry/2021/02/01/220408)
