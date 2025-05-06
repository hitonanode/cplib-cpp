---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: random/xorshift.hpp
    title: random/xorshift.hpp
  - icon: ':heavy_check_mark:'
    path: segmenttree/acl_beats.hpp
    title: Segment Tree Beats (based on atcoder::lazy_segtree)
  - icon: ':heavy_check_mark:'
    path: segmenttree/acl_lazysegtree.hpp
    title: Lazy Segtree (based on atcoder::lazy_segtree)
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.13.3/x64/lib/python3.13/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ~~~~~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.13.3/x64/lib/python3.13/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n    ~~~~~~~~~~~~~~^^^^^^\n  File\
    \ \"/opt/hostedtoolcache/Python/3.13.3/x64/lib/python3.13/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \    ~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.13.3/x64/lib/python3.13/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \    ~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.13.3/x64/lib/python3.13/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 355, in update\n    raise BundleErrorAt(path, i + 1, \"found codes out\
    \ of include guard\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ segmenttree/acl_lazysegtree.hpp: line 37: found codes out of include guard\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \ // DUMMY\n\n#include \"../../random/xorshift.hpp\"\n#include \"../acl_beats.hpp\"\
    \n\n#include <algorithm>\n#include <cstdio>\n#include <numeric>\n#include <vector>\n\
    \nusing RangeChMinMaxAddSum::S, RangeChMinMaxAddSum::F;\n\nint main() {\n    for\
    \ (int trial = 0; trial < 1 << 20; ++trial) {\n        const int N = rand_int()\
    \ % 32 + 1;\n\n        const int maxA = rand_int() % 50 + 1;\n        const int\
    \ Q = rand_int() % 10 + 1;\n\n        std::vector<S> A(N);\n        std::vector<int>\
    \ simulate(N);\n        for (int i = 0; i < N; ++i) {\n            simulate.at(i)\
    \ = rand_int() % (maxA + 1);\n            A.at(i) = S(simulate.at(i), 1);\n  \
    \      }\n\n        segtree_beats<S, RangeChMinMaxAddSum::op, RangeChMinMaxAddSum::e,\
    \ F, RangeChMinMaxAddSum::mapping,\n                      RangeChMinMaxAddSum::composition,\
    \ RangeChMinMaxAddSum::id>\n            segtree(A);\n\n        for (int q = 0;\
    \ q < Q; ++q) {\n            int tp = rand_int() % 4;\n            if (q == Q\
    \ - 1) tp = 3;\n\n            int l = 0, r = 0;\n            while (l == r) {\n\
    \                l = rand_int() % (N + 1);\n                r = rand_int() % (N\
    \ + 1);\n                if (l > r) std::swap(l, r);\n            }\n\n      \
    \      if (tp < 3) {\n                int b = rand_int() % (maxA + 1);\n     \
    \           if (tp == 0) {\n                    for (int i = l; i < r; ++i) simulate.at(i)\
    \ = std::min(simulate.at(i), b);\n                    segtree.apply(l, r, RangeChMinMaxAddSum::F::chmin(b));\n\
    \                }\n\n                if (tp == 1) {\n                    for\
    \ (int i = l; i < r; ++i) simulate.at(i) = std::max(simulate.at(i), b);\n    \
    \                segtree.apply(l, r, RangeChMinMaxAddSum::F::chmax(b));\n    \
    \            }\n\n                if (tp == 2) {\n                    for (int\
    \ i = l; i < r; ++i) simulate.at(i) += b;\n                    segtree.apply(l,\
    \ r, RangeChMinMaxAddSum::F::add(b));\n                }\n            }\n\n  \
    \          if (tp == 3) {\n                auto prod = segtree.prod(l, r);\n\n\
    \                std::vector<int> values;\n                for (int i = l; i <\
    \ r; ++i) values.push_back(simulate.at(i));\n                std::sort(values.begin(),\
    \ values.end());\n\n                assert(prod.lo == values.front());\n     \
    \           assert(prod.nlo == std::count(values.begin(), values.end(), prod.lo));\n\
    \n                assert(prod.hi == values.back());\n                assert(prod.nhi\
    \ == std::count(values.begin(), values.end(), prod.hi));\n\n                assert(prod.sum\
    \ == std::accumulate(values.begin(), values.end(), 0LL));\n\n                assert(prod.sz\
    \ == r - l);\n                assert(!prod.fail);\n\n                if (values.front()\
    \ != values.back()) {\n                    int i = 0;\n                    while\
    \ (values.at(i) == values.front()) ++i;\n                    assert(prod.lo2 ==\
    \ values.at(i));\n\n                    i = (int)values.size() - 1;\n        \
    \            while (values.at(i) == values.back()) --i;\n                    assert(prod.hi2\
    \ == values.at(i));\n                }\n            }\n        }\n    }\n\n  \
    \  puts(\"Hello World\");\n}\n"
  dependsOn:
  - random/xorshift.hpp
  - segmenttree/acl_beats.hpp
  - segmenttree/acl_lazysegtree.hpp
  isVerificationFile: true
  path: segmenttree/test/beats_random_test.test.cpp
  requiredBy: []
  timestamp: '2024-04-28 17:28:53+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: segmenttree/test/beats_random_test.test.cpp
layout: document
redirect_from:
- /verify/segmenttree/test/beats_random_test.test.cpp
- /verify/segmenttree/test/beats_random_test.test.cpp.html
title: segmenttree/test/beats_random_test.test.cpp
---
