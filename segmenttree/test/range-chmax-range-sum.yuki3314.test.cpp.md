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
    path: segmenttree/trees/range-chmax-range-sum.hpp
    title: segmenttree/trees/range-chmax-range-sum.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/3314
    links:
    - https://yukicoder.me/problems/no/3314
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.14.2/x64/lib/python3.14/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ~~~~~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.14.2/x64/lib/python3.14/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n    ~~~~~~~~~~~~~~^^^^^^\n  File\
    \ \"/opt/hostedtoolcache/Python/3.14.2/x64/lib/python3.14/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \    ~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.14.2/x64/lib/python3.14/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \    ~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.14.2/x64/lib/python3.14/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \    ~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.14.2/x64/lib/python3.14/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 355, in update\n    raise BundleErrorAt(path, i + 1, \"found codes out\
    \ of include guard\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ segmenttree/acl_lazysegtree.hpp: line 56: found codes out of include guard\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/3314\"\n#include \"../trees/range-chmax-range-sum.hpp\"\
    \n\n#include <iostream>\n#include <tuple>\n#include <vector>\nusing namespace\
    \ std;\n\nusing RCRS = RangeChmaxRangeSum<long long, (1LL << 60)>;\n\nint main()\
    \ {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\n    int N, K, Q;\n\
    \    cin >> N >> K >> Q;\n\n    RCRS::segtree seg(N);\n    for (int i = 0; i <\
    \ N; ++i) {\n        int a;\n        cin >> a;\n        seg.set(i, RCRS::Gen(a));\n\
    \    }\n\n    vector<tuple<int, int, int>> updates(K);\n    for (auto &[l, r,\
    \ x] : updates) cin >> l >> r >> x, --l;\n\n    vector<tuple<int, int, long long>>\
    \ query(Q);\n    for (auto &[l, r, x] : query) cin >> l >> r >> x, --l;\n\n  \
    \  vector<int> ok(Q, K + 1), ng(Q, -1);\n\n    for (int t = 0; t < 15; ++t) {\n\
    \        vector<vector<int>> t2qs(K + 1);\n        for (int q = 0; q < Q; ++q)\
    \ {\n            const int t = (ok.at(q) + ng.at(q)) / 2;\n            t2qs.at(t).push_back(q);\n\
    \        }\n\n        RCRS::segtree tree = seg;\n\n        for (int t = 0; t <\
    \ K + 1; ++t) {\n            if (t) {\n                auto [l, r, x] = updates.at(t\
    \ - 1);\n                tree.apply(l, r, RCRS::Chmax(x));\n            }\n\n\
    \            for (int q : t2qs.at(t)) {\n                auto [l, r, x] = query.at(q);\n\
    \                (tree.prod(l, r).sum >= x ? ok : ng).at(q) = t;\n           \
    \ }\n        }\n    }\n\n    for (auto t : ok) cout << (t == K + 1 ? -1 : t) <<\
    \ '\\n';\n}\n"
  dependsOn:
  - segmenttree/trees/range-chmax-range-sum.hpp
  - segmenttree/acl_beats.hpp
  - segmenttree/acl_lazysegtree.hpp
  isVerificationFile: true
  path: segmenttree/test/range-chmax-range-sum.yuki3314.test.cpp
  requiredBy: []
  timestamp: '2025-10-26 13:49:19+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: segmenttree/test/range-chmax-range-sum.yuki3314.test.cpp
layout: document
redirect_from:
- /verify/segmenttree/test/range-chmax-range-sum.yuki3314.test.cpp
- /verify/segmenttree/test/range-chmax-range-sum.yuki3314.test.cpp.html
title: segmenttree/test/range-chmax-range-sum.yuki3314.test.cpp
---
