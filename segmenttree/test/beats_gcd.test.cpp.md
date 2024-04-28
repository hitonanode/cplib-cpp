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
    path: segmenttree/trees/acl_range-update-gcd-range-max-sum.hpp
    title: segmenttree/trees/acl_range-update-gcd-range-max-sum.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/880
    links:
    - https://yukicoder.me/problems/no/880
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.12.3/x64/lib/python3.12/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.12.3/x64/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.12.3/x64/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.12.3/x64/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.12.3/x64/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.12.3/x64/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 355, in update\n    raise BundleErrorAt(path, i + 1, \"found codes out\
    \ of include guard\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ segmenttree/acl_lazysegtree.hpp: line 37: found codes out of include guard\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/880\"\n#include \"../trees/acl_range-update-gcd-range-max-sum.hpp\"\
    \n\n#include <iostream>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n    uint32_t N, Q;\n    cin >> N >> Q;\n    vector<yuki880::S>\
    \ A(N);\n    for (auto &a : A) {\n        uint32_t tmp;\n        cin >> tmp, a\
    \ = {tmp, 1};\n    }\n\n    yuki880::segtree segtree(A);\n    uint32_t q, l, r,\
    \ x;\n    while (Q--) {\n        cin >> q >> l >> r;\n        l--;\n        if\
    \ (q <= 2) {\n            cin >> x;\n            if (q == 1) segtree.apply(l,\
    \ r, yuki880::F::update(x));\n            if (q == 2) segtree.apply(l, r, yuki880::F::gcd(x));\n\
    \        } else {\n            auto v = segtree.prod(l, r);\n            if (q\
    \ == 3) cout << v.max << '\\n';\n            if (q == 4) cout << v.sum << '\\\
    n';\n        }\n    }\n}\n"
  dependsOn:
  - segmenttree/trees/acl_range-update-gcd-range-max-sum.hpp
  - segmenttree/acl_beats.hpp
  - segmenttree/acl_lazysegtree.hpp
  isVerificationFile: true
  path: segmenttree/test/beats_gcd.test.cpp
  requiredBy: []
  timestamp: '2024-04-28 17:37:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: segmenttree/test/beats_gcd.test.cpp
layout: document
redirect_from:
- /verify/segmenttree/test/beats_gcd.test.cpp
- /verify/segmenttree/test/beats_gcd.test.cpp.html
title: segmenttree/test/beats_gcd.test.cpp
---
