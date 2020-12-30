---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':heavy_check_mark:'
    path: segmenttree/acl_lazysegtree.hpp
    title: segmenttree/acl_lazysegtree.hpp
  - icon: ':heavy_check_mark:'
    path: segmenttree/acl_range-affine-range-sum.hpp
    title: segmenttree/acl_range-affine-range-sum.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/range_affine_range_sum
    links:
    - https://judge.yosupo.jp/problem/range_affine_range_sum
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
  code: "#include \"../acl_range-affine-range-sum.hpp\"\n#include \"modint.hpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/range_affine_range_sum\"\nusing\
    \ namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    int N, Q;\n    cin >> N >> Q;\n\n    vector<S> A(N);\n    for (auto &a :\
    \ A) cin >> a.first, a.second = 1;\n    RangeAffineRangeSum segtree(A);\n    while\
    \ (Q--) {\n        int q, l, r;\n        cin >> q >> l >> r;\n        if (q) {\n\
    \            cout << segtree.prod(l, r).first << '\\n';\n        } else {\n  \
    \          F f;\n            cin >> f.first >> f.second;\n            segtree.apply(l,\
    \ r, f);\n        }\n    }\n}\n"
  dependsOn:
  - segmenttree/acl_range-affine-range-sum.hpp
  - modint.hpp
  - segmenttree/acl_lazysegtree.hpp
  isVerificationFile: true
  path: segmenttree/test/acl_range-affine-range-sum.test.cpp
  requiredBy: []
  timestamp: '2020-12-30 23:06:06+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: segmenttree/test/acl_range-affine-range-sum.test.cpp
layout: document
redirect_from:
- /verify/segmenttree/test/acl_range-affine-range-sum.test.cpp
- /verify/segmenttree/test/acl_range-affine-range-sum.test.cpp.html
title: segmenttree/test/acl_range-affine-range-sum.test.cpp
---
