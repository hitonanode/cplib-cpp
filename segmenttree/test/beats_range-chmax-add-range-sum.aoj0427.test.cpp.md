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
    path: segmenttree/trees/range-chmax-add-range-sum.hpp
    title: segmenttree/trees/range-chmax-add-range-sum.hpp
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
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \    ~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.14.0/x64/lib/python3.14/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \    ~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.14.0/x64/lib/python3.14/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 355, in update\n    raise BundleErrorAt(path, i + 1, \"found codes out\
    \ of include guard\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ segmenttree/acl_lazysegtree.hpp: line 56: found codes out of include guard\n"
  code: "#include \"../trees/range-chmax-add-range-sum.hpp\"\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0427\"\
    \n#include <iostream>\nusing namespace std;\n\nusing RCARS = RangeChmaxAddRangeSum<long\
    \ long, (1LL << 60)>;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    int N, tmp;\n    cin >> N;\n    vector<RCARS::S> A(N);\n    for (auto &a\
    \ : A) cin >> tmp, a = RCARS::Gen(tmp);\n\n    RCARS::segtree segtree(A);\n\n\
    \    int Q, q, l, r, d;\n    cin >> Q;\n\n    while (Q--) {\n        cin >> q\
    \ >> l >> r >> d;\n        l--;\n        if (q == 1) {\n            segtree.apply(l,\
    \ r, RCARS::Add(d));\n        } else {\n            auto before = segtree.prod(l,\
    \ r).sum;\n            auto f1 = RCARS::Add(-d);\n            auto f2 = RCARS::Chmax(0);\n\
    \            segtree.apply(l, r, RCARS::composition(f2, f1));\n            auto\
    \ after = segtree.prod(l, r).sum;\n            cout << before - after << '\\n';\n\
    \        }\n    }\n}\n"
  dependsOn:
  - segmenttree/trees/range-chmax-add-range-sum.hpp
  - segmenttree/acl_beats.hpp
  - segmenttree/acl_lazysegtree.hpp
  isVerificationFile: true
  path: segmenttree/test/beats_range-chmax-add-range-sum.aoj0427.test.cpp
  requiredBy: []
  timestamp: '2025-10-26 14:03:13+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: segmenttree/test/beats_range-chmax-add-range-sum.aoj0427.test.cpp
layout: document
redirect_from:
- /verify/segmenttree/test/beats_range-chmax-add-range-sum.aoj0427.test.cpp
- /verify/segmenttree/test/beats_range-chmax-add-range-sum.aoj0427.test.cpp.html
title: segmenttree/test/beats_range-chmax-add-range-sum.aoj0427.test.cpp
---
