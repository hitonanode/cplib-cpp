---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: segmenttree/acl_segtree.hpp
    title: Segtree (based on atcoder::segtree)
  - icon: ':heavy_check_mark:'
    path: segmenttree/rangetree.hpp
    title: "Range Tree \uFF08\u9818\u57DF\u6728\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/point_add_rectangle_sum
    links:
    - https://judge.yosupo.jp/problem/point_add_rectangle_sum
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
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \    ~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.13.7/x64/lib/python3.13/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 355, in update\n    raise BundleErrorAt(path, i + 1, \"found codes out\
    \ of include guard\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ segmenttree/acl_segtree.hpp: line 48: found codes out of include guard\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_rectangle_sum\"\
    \n#include \"../rangetree.hpp\"\n#include <iostream>\n#include <tuple>\n#include\
    \ <vector>\nusing namespace std;\n\nusing S = unsigned long long;\nS op(S l, S\
    \ r) noexcept { return l + r; }\nS e() noexcept { return 0; }\n\nint main() {\n\
    \    cin.tie(nullptr), ios::sync_with_stdio(false);\n    int N, Q;\n    cin >>\
    \ N >> Q;\n    std::vector<int> x(N), y(N), w(N);\n    rangetree<S, op, e, int>\
    \ tree;\n\n    for (int i = 0; i < N; i++) {\n        cin >> x[i] >> y[i] >> w[i];\n\
    \        tree.add_point(x[i], y[i]);\n    }\n    std::vector<std::tuple<int, int,\
    \ int, int, int>> qs;\n    for (int i = 0; i < Q; i++) {\n        int t;\n   \
    \     cin >> t;\n        if (t == 0) {\n            int x, y, w;\n           \
    \ cin >> x >> y >> w;\n            qs.emplace_back(t, x, y, w, 0);\n         \
    \   tree.add_point(x, y);\n        } else {\n            int l, d, r, u;\n   \
    \         cin >> l >> d >> r >> u;\n            qs.emplace_back(t, l, r, d, u);\n\
    \        }\n    }\n    tree.build();\n    for (int i = 0; i < N; i++) tree.add(x[i],\
    \ y[i], w[i]);\n    for (auto q : qs) {\n        if (std::get<0>(q) == 0) {\n\
    \            int t, x, y, w, z;\n            tie(t, x, y, w, z) = q;\n       \
    \     tree.add(x, y, w);\n        } else {\n            int t, l, r, d, u;\n \
    \           tie(t, l, r, d, u) = q;\n            cout << tree.prod(l, r, d, u)\
    \ << '\\n';\n        }\n    }\n}"
  dependsOn:
  - segmenttree/rangetree.hpp
  - segmenttree/acl_segtree.hpp
  isVerificationFile: true
  path: segmenttree/test/rangetree.test.cpp
  requiredBy: []
  timestamp: '2025-08-24 23:32:38+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: segmenttree/test/rangetree.test.cpp
layout: document
redirect_from:
- /verify/segmenttree/test/rangetree.test.cpp
- /verify/segmenttree/test/rangetree.test.cpp.html
title: segmenttree/test/rangetree.test.cpp
---
