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
    PROBLEM: https://yukicoder.me/problems/no/1625
    links:
    - https://yukicoder.me/problems/no/1625
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
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/1625\"\n#include \"../rangetree.hpp\"\
    \n#include <algorithm>\n#include <iostream>\n#include <tuple>\n#include <utility>\n\
    #include <vector>\nusing namespace std;\nlong long op(long long l, long long r)\
    \ { return l > r ? l : r; }\nlong long e() { return -1; }\n\npair<int, int> read_pint()\
    \ {\n    int a, b;\n    cin >> a >> b;\n    return {a, b};\n};\n\nusing Tri =\
    \ pair<pair<int, int>, long long>;\nTri read_tri() {\n\n    auto A = read_pint(),\
    \ B = read_pint(), C = read_pint();\n    long long dx1 = B.first - A.first, dy1\
    \ = B.second - A.second, dx2 = C.first - A.first,\n              dy2 = C.second\
    \ - A.second;\n\n    const auto S = abs(dx1 * dy2 - dy1 * dx2);\n    const int\
    \ lo = min({A.first, B.first, C.first}), hi = max({A.first, B.first, C.first});\n\
    \    return {{lo, hi}, S};\n}\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \    int N, Q;\n    cin >> N >> Q;\n\n    vector<Tri> tris(N);\n    for (auto\
    \ &x : tris) x = read_tri();\n\n    vector<int> TP(Q);\n    vector<Tri> tris_add(Q);\n\
    \    vector<pair<int, int>> qs(Q);\n    for (int q = 0; q < Q; q++) {\n      \
    \  cin >> TP[q];\n        if (TP[q] == 1) {\n            tris_add[q] = read_tri();\n\
    \        } else {\n            qs[q] = read_pint();\n        }\n    }\n\n    rangetree<long\
    \ long, op, e, int> tree;\n    for (const auto trivec : {tris, tris_add}) {\n\
    \        for (const auto lh_S : trivec) {\n            auto lh = lh_S.first;\n\
    \            if (lh.first > 0) tree.add_point(lh.first, lh.second);\n        }\n\
    \    }\n    tree.build();\n\n    auto add_tri = [&](Tri tri) {\n        auto lr\
    \ = tri.first;\n        auto S = tri.second;\n        tree.add(lr.first, lr.second,\
    \ S);\n    };\n\n    for (auto tri : tris) add_tri(tri);\n\n    for (int q = 0;\
    \ q < Q; q++) {\n        if (TP[q] == 1) {\n            add_tri(tris_add[q]);\n\
    \        } else {\n            int l, r;\n            tie(l, r) = qs[q];\n   \
    \         cout << tree.prod(l, r + 1, l, r + 1) << '\\n';\n        }\n    }\n\
    }\n"
  dependsOn:
  - segmenttree/rangetree.hpp
  - segmenttree/acl_segtree.hpp
  isVerificationFile: true
  path: segmenttree/test/rangetree.yuki1625.test.cpp
  requiredBy: []
  timestamp: '2025-08-24 23:32:38+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: segmenttree/test/rangetree.yuki1625.test.cpp
layout: document
redirect_from:
- /verify/segmenttree/test/rangetree.yuki1625.test.cpp
- /verify/segmenttree/test/rangetree.yuki1625.test.cpp.html
title: segmenttree/test/rangetree.yuki1625.test.cpp
---
