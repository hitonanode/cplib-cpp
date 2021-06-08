---
data:
  _extendedDependsOn:
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
  bundledCode: "#line 1 \"segmenttree/test/rangetree.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/point_add_rectangle_sum\"\n#line 2 \"segmenttree/rangetree.hpp\"\
    \n#include <algorithm>\n#include <cassert>\n#include <utility>\n#include <vector>\n\
    \n// CUT begin\n// \u9818\u57DF\u6728\ntemplate <class S, void (*opadd)(S &, S),\
    \ void (*opsub)(S &, S), S (*e)(), class Coordinate> class rangetree {\n    int\
    \ n;\n    std::vector<std::pair<Coordinate, Coordinate>> _pts;\n    struct BIT\
    \ {\n        std::vector<S> data;\n        BIT(int len) : data(len, e()) {}\n\
    \        void add(int pos, S v) {\n            for (pos++; pos and pos <= int(data.size());\
    \ pos += pos & -pos) opadd(data[pos - 1], v);\n        }\n        S sum(int r)\
    \ const {\n            S ret = e();\n            while (r) opadd(ret, data[r -\
    \ 1]), r -= r & -r;\n            return ret;\n        }\n    };\n\n    std::vector<std::vector<Coordinate>>\
    \ _range2ys;\n    std::vector<BIT> bits;\n    void _add_singlenode(int v, Coordinate\
    \ y, S val) {\n        auto i = std::distance(_range2ys[v].begin(), std::lower_bound(_range2ys[v].begin(),\
    \ _range2ys[v].end(), y));\n        bits[v].add(i, val);\n    }\n    S _get_singlenode(int\
    \ v, Coordinate y) const {\n        auto i = std::distance(_range2ys[v].begin(),\
    \ std::lower_bound(_range2ys[v].begin(), _range2ys[v].end(), y));\n        return\
    \ bits[v].sum(i);\n    }\n    S _sum(Coordinate xl, Coordinate xr, Coordinate\
    \ yr) const { // [xl, xr) * (-INF, yr)\n        auto compx = [](std::pair<Coordinate,\
    \ Coordinate> l, std::pair<Coordinate, Coordinate> r) {\n            return l.first\
    \ < r.first;\n        };\n        int l = n + std::distance(_pts.begin(), std::lower_bound(_pts.begin(),\
    \ _pts.end(), std::make_pair(xl, yr), compx));\n        int r = n + std::distance(_pts.begin(),\
    \ std::lower_bound(_pts.begin(), _pts.end(), std::make_pair(xr, yr), compx));\n\
    \        S ret = e();\n        while (l < r) {\n            if (l & 1) opadd(ret,\
    \ _get_singlenode(l++, yr));\n            if (r & 1) opadd(ret, _get_singlenode(--r,\
    \ yr));\n            l >>= 1, r >>= 1;\n        }\n        return ret;\n    }\n\
    \npublic:\n    rangetree() = default;\n    void add_point(Coordinate x, Coordinate\
    \ y) noexcept { _pts.emplace_back(x, y); }\n    void build() {\n        std::sort(_pts.begin(),\
    \ _pts.end());\n        _pts.erase(std::unique(_pts.begin(), _pts.end()), _pts.end());\n\
    \        n = _pts.size();\n\n        _range2ys.resize(n * 2);\n        for (int\
    \ i = 0; i < n; i++) _range2ys[n + i] = {_pts[i].second};\n        for (int i\
    \ = n - 1; i > 0; i--) {\n            auto &lch = _range2ys[i * 2];\n        \
    \    auto &rch = _range2ys[i * 2 + 1];\n            std::merge(lch.begin(), lch.end(),\
    \ rch.begin(), rch.end(), std::back_inserter(_range2ys[i]));\n            _range2ys[i].erase(std::unique(_range2ys[i].begin(),\
    \ _range2ys[i].end()), _range2ys[i].end());\n        }\n        for (const auto\
    \ &v : _range2ys) bits.push_back(BIT(v.size()));\n    }\n    void add(Coordinate\
    \ x, Coordinate y, S val) {\n        int i = std::distance(_pts.begin(), std::lower_bound(_pts.begin(),\
    \ _pts.end(), std::make_pair(x, y)));\n        assert(i < n and _pts[i] == std::make_pair(x,\
    \ y));\n        for (i += n; i; i >>= 1) _add_singlenode(i, y, val);\n    }\n\
    \    S sum(Coordinate xl, Coordinate xr, Coordinate yl, Coordinate yr) const {\n\
    \        auto ret_r = _sum(xl, xr, yr);\n        auto ret_l = _sum(xl, xr, yl);\n\
    \        opsub(ret_r, ret_l);\n        return ret_r;\n    }\n};\n#line 3 \"segmenttree/test/rangetree.test.cpp\"\
    \n#include <iostream>\n#include <tuple>\n#line 6 \"segmenttree/test/rangetree.test.cpp\"\
    \nusing namespace std;\n\nusing S = unsigned long long;\nS e() noexcept { return\
    \ 0; }\nvoid opadd(S &l, S r) noexcept { l += r; }\nvoid opsub(S &l, S r) noexcept\
    \ { l -= r; }\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \    int N, Q;\n    cin >> N >> Q;\n    std::vector<int> x(N), y(N), w(N);\n \
    \   rangetree<S, opadd, opsub, e, int> tree;\n\n    for (int i = 0; i < N; i++)\
    \ {\n        cin >> x[i] >> y[i] >> w[i];\n        tree.add_point(x[i], y[i]);\n\
    \    }\n    std::vector<std::tuple<int, int, int, int, int>> qs;\n    for (int\
    \ i = 0; i < Q; i++) {\n        int t;\n        cin >> t;\n        if (t == 0)\
    \ {\n            int x, y, w;\n            cin >> x >> y >> w;\n            qs.emplace_back(t,\
    \ x, y, w, 0);\n            tree.add_point(x, y);\n        } else {\n        \
    \    int l, d, r, u;\n            cin >> l >> d >> r >> u;\n            qs.emplace_back(t,\
    \ l, r, d, u);\n        }\n    }\n    tree.build();\n    for (int i = 0; i < N;\
    \ i++) tree.add(x[i], y[i], w[i]);\n    for (auto q : qs) {\n        if (std::get<0>(q)\
    \ == 0) {\n            int t, x, y, w, z;\n            tie(t, x, y, w, z) = q;\n\
    \            tree.add(x, y, w);\n        } else {\n            int t, l, r, d,\
    \ u;\n            tie(t, l, r, d, u) = q;\n            cout << tree.sum(l, r,\
    \ d, u) << '\\n';\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_rectangle_sum\"\
    \n#include \"../rangetree.hpp\"\n#include <iostream>\n#include <tuple>\n#include\
    \ <vector>\nusing namespace std;\n\nusing S = unsigned long long;\nS e() noexcept\
    \ { return 0; }\nvoid opadd(S &l, S r) noexcept { l += r; }\nvoid opsub(S &l,\
    \ S r) noexcept { l -= r; }\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \    int N, Q;\n    cin >> N >> Q;\n    std::vector<int> x(N), y(N), w(N);\n \
    \   rangetree<S, opadd, opsub, e, int> tree;\n\n    for (int i = 0; i < N; i++)\
    \ {\n        cin >> x[i] >> y[i] >> w[i];\n        tree.add_point(x[i], y[i]);\n\
    \    }\n    std::vector<std::tuple<int, int, int, int, int>> qs;\n    for (int\
    \ i = 0; i < Q; i++) {\n        int t;\n        cin >> t;\n        if (t == 0)\
    \ {\n            int x, y, w;\n            cin >> x >> y >> w;\n            qs.emplace_back(t,\
    \ x, y, w, 0);\n            tree.add_point(x, y);\n        } else {\n        \
    \    int l, d, r, u;\n            cin >> l >> d >> r >> u;\n            qs.emplace_back(t,\
    \ l, r, d, u);\n        }\n    }\n    tree.build();\n    for (int i = 0; i < N;\
    \ i++) tree.add(x[i], y[i], w[i]);\n    for (auto q : qs) {\n        if (std::get<0>(q)\
    \ == 0) {\n            int t, x, y, w, z;\n            tie(t, x, y, w, z) = q;\n\
    \            tree.add(x, y, w);\n        } else {\n            int t, l, r, d,\
    \ u;\n            tie(t, l, r, d, u) = q;\n            cout << tree.sum(l, r,\
    \ d, u) << '\\n';\n        }\n    }\n}"
  dependsOn:
  - segmenttree/rangetree.hpp
  isVerificationFile: true
  path: segmenttree/test/rangetree.test.cpp
  requiredBy: []
  timestamp: '2021-06-08 20:31:49+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: segmenttree/test/rangetree.test.cpp
layout: document
redirect_from:
- /verify/segmenttree/test/rangetree.test.cpp
- /verify/segmenttree/test/rangetree.test.cpp.html
title: segmenttree/test/rangetree.test.cpp
---
