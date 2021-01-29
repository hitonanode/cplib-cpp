---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: segmenttree/acl_lazysegtree.hpp
    title: segmenttree/acl_lazysegtree.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://codeforces.com/contest/1439/submission/98816580>
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.1/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.1/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 193, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.1/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.1/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 355, in update\n    raise BundleErrorAt(path, i + 1, \"found codes out\
    \ of include guard\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ segmenttree/acl_lazysegtree.hpp: line 37: found codes out of include guard\n"
  code: "#pragma once\n#include <algorithm>\n\n// CUT begin\n#include \"acl_lazysegtree.hpp\"\
    \nnamespace rangeupdaterangesummin {\nusing Int = long long;\nconst Int INF =\
    \ 101010101010LL;\nstruct S {\n    Int sum;\n    int sz;\n    Int minval;\n};\n\
    using F = std::pair<bool, Int>;\nS op(S a, S b) { return S{a.sum + b.sum, a.sz\
    \ + b.sz, std::min(a.minval, b.minval)}; }\nS mapping(F f, S x) { return f.first\
    \ ? S{x.sz * f.second, x.sz, f.second} : x; }\nF composition(F later, F conventional)\
    \ { return later.first ? later : conventional; }\nS e() { return S{0, 0, INF};\
    \ }\nF id() { return std::make_pair(false, INF); }\nusing RangeUpdateRangeSumMin\
    \ = atcoder::lazy_segtree<S, op, e, F, mapping, composition, id>;\n}; // namespace\
    \ rangeupdaterangesummin\nusing rangeupdaterangesummin::RangeUpdateRangeSumMin;\n\
    using rangeupdaterangesummin::S;\n// Example of usage <https://codeforces.com/contest/1439/submission/98816580>\n"
  dependsOn:
  - segmenttree/acl_lazysegtree.hpp
  isVerificationFile: false
  path: segmenttree/acl_range-update-range-sum-min.hpp
  requiredBy: []
  timestamp: '2020-12-30 23:06:06+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: segmenttree/acl_range-update-range-sum-min.hpp
layout: document
redirect_from:
- /library/segmenttree/acl_range-update-range-sum-min.hpp
- /library/segmenttree/acl_range-update-range-sum-min.hpp.html
title: segmenttree/acl_range-update-range-sum-min.hpp
---
