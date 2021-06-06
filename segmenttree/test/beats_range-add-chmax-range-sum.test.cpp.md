---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: segmenttree/acl_beats.hpp
    title: Segment Tree Beats (based on atcoder::lazy_segtree)
  - icon: ':heavy_check_mark:'
    path: segmenttree/acl_lazysegtree.hpp
    title: Lazy Segtree (based on atcoder::lazy_segtree)
  - icon: ':heavy_check_mark:'
    path: segmenttree/trees/acl_range-add-chmax-range-sum.hpp
    title: segmenttree/trees/acl_range-add-chmax-range-sum.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0427
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0427
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 355, in update\n    raise BundleErrorAt(path, i + 1, \"found codes out\
    \ of include guard\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ segmenttree/acl_lazysegtree.hpp: line 37: found codes out of include guard\n"
  code: "#include \"../trees/acl_range-add-chmax-range-sum.hpp\"\n#define PROBLEM\
    \ \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0427\"\n#include\
    \ <iostream>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    int N, tmp;\n    cin >> N;\n    vector<RangeAddChmaxRangeSum::S> A(N);\n\
    \    for (auto &a : A) cin >> tmp, a = tmp;\n\n    RangeAddChmaxRangeSum::segtree\
    \ segtree(A);\n\n    int Q, q, l, r, d;\n    cin >> Q;\n\n    while (Q--) {\n\
    \        cin >> q >> l >> r >> d;\n        l--;\n        if (q == 1) {\n     \
    \       segtree.apply(l, r, RangeAddChmaxRangeSum::F::add(d));\n        } else\
    \ {\n            auto before = segtree.prod(l, r).sum;\n            auto f1 =\
    \ RangeAddChmaxRangeSum::F::add(-d);\n            auto f2 = RangeAddChmaxRangeSum::F::chmax(0);\n\
    \            segtree.apply(l, r, RangeAddChmaxRangeSum::composition(f2, f1));\n\
    \            auto after = segtree.prod(l, r).sum;\n            cout << before\
    \ - after << '\\n';\n        }\n    }\n}\n"
  dependsOn:
  - segmenttree/trees/acl_range-add-chmax-range-sum.hpp
  - segmenttree/acl_beats.hpp
  - segmenttree/acl_lazysegtree.hpp
  isVerificationFile: true
  path: segmenttree/test/beats_range-add-chmax-range-sum.test.cpp
  requiredBy: []
  timestamp: '2021-02-15 23:59:04+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: segmenttree/test/beats_range-add-chmax-range-sum.test.cpp
layout: document
redirect_from:
- /verify/segmenttree/test/beats_range-add-chmax-range-sum.test.cpp
- /verify/segmenttree/test/beats_range-add-chmax-range-sum.test.cpp.html
title: segmenttree/test/beats_range-add-chmax-range-sum.test.cpp
---
