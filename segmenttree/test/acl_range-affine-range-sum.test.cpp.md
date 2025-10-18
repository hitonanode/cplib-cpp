---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':heavy_check_mark:'
    path: segmenttree/acl_lazysegtree.hpp
    title: Lazy Segtree (based on atcoder::lazy_segtree)
  - icon: ':heavy_check_mark:'
    path: segmenttree/trees/acl_range-affine-range-sum.hpp
    title: segmenttree/trees/acl_range-affine-range-sum.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/range_affine_range_sum
    links:
    - https://judge.yosupo.jp/problem/range_affine_range_sum
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.13.8/x64/lib/python3.13/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ~~~~~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.13.8/x64/lib/python3.13/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n    ~~~~~~~~~~~~~~^^^^^^\n  File\
    \ \"/opt/hostedtoolcache/Python/3.13.8/x64/lib/python3.13/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \    ~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.13.8/x64/lib/python3.13/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \    ~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.13.8/x64/lib/python3.13/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 355, in update\n    raise BundleErrorAt(path, i + 1, \"found codes out\
    \ of include guard\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ segmenttree/acl_lazysegtree.hpp: line 56: found codes out of include guard\n"
  code: "#include \"../../modint.hpp\"\n#include \"../trees/acl_range-affine-range-sum.hpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/range_affine_range_sum\"\n\
    using namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    int N, Q;\n    cin >> N >> Q;\n\n    vector<RangeAffineRangeSum::S> A(N);\n\
    \    for (auto &a : A) cin >> a.first, a.second = 1;\n    RangeAffineRangeSum::segtree\
    \ segtree(A);\n    while (Q--) {\n        int q, l, r;\n        cin >> q >> l\
    \ >> r;\n        if (q) {\n            cout << segtree.prod(l, r).first << '\\\
    n';\n        } else {\n            RangeAffineRangeSum::F f;\n            cin\
    \ >> f.first >> f.second;\n            segtree.apply(l, r, f);\n        }\n  \
    \  }\n}\n"
  dependsOn:
  - modint.hpp
  - segmenttree/trees/acl_range-affine-range-sum.hpp
  - segmenttree/acl_lazysegtree.hpp
  isVerificationFile: true
  path: segmenttree/test/acl_range-affine-range-sum.test.cpp
  requiredBy: []
  timestamp: '2025-10-07 09:41:07+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: segmenttree/test/acl_range-affine-range-sum.test.cpp
layout: document
redirect_from:
- /verify/segmenttree/test/acl_range-affine-range-sum.test.cpp
- /verify/segmenttree/test/acl_range-affine-range-sum.test.cpp.html
title: segmenttree/test/acl_range-affine-range-sum.test.cpp
---
