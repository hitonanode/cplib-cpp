---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: convex_hull_trick/li_chao_tree.hpp
    title: Li-Chao tree
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/segment_add_get_min
    links:
    - https://judge.yosupo.jp/problem/segment_add_get_min
  bundledCode: "#line 1 \"convex_hull_trick/test/li_chao_tree.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/segment_add_get_min\"\n#line 2 \"\
    convex_hull_trick/li_chao_tree.hpp\"\n#include <algorithm>\n#include <cassert>\n\
    #include <tuple>\n#include <vector>\n\n// Li-Chao tree\n// init() : set x's where\
    \ we will execute get(x) queries\n// add_segment(l, r, a, b): update by ax + b\
    \ in [l, r)\n// get(x): get min\ntemplate <class T, class T_MP> struct li_chao_tree\
    \ {\n    int _n, _head;\n    std::vector<T> xs;\n    li_chao_tree() : _n(0), _head(0)\
    \ {}\n\n    struct _Line {\n        T a, b;\n        int line_idx;\n        bool\
    \ is_valid;\n        T_MP eval(T x) const noexcept { return T_MP(a) * x + b; }\n\
    \    };\n\n    std::vector<_Line> lines;\n    struct LCR {\n        T l, c, r;\n\
    \    };\n    std::vector<LCR> lcr;\n\n    void init(const std::vector<T> &xs_)\
    \ {\n        xs = xs_;\n        std::sort(xs.begin(), xs.end());\n        xs.erase(std::unique(xs.begin(),\
    \ xs.end()), xs.end());\n        _n = xs.size();\n        _head = 1;\n       \
    \ while (_head < _n) _head <<= 1;\n        lines.assign(_head * 2, {0, 0, -1,\
    \ false});\n        lcr.resize(_head * 2);\n        for (int i = 0; i < _n; ++i)\
    \ lcr[_head + i] = {xs[i], xs[i], xs[i]};\n        for (int i = _head - 1; i;\
    \ --i) {\n            int l = i * 2, r = i * 2 + 1;\n            lcr[i] = {lcr[l].l,\
    \ lcr[r].l, lcr[r].r};\n        }\n    }\n\n    int il, ir;\n    void _rec(int\
    \ now, int nowl, int nowr, _Line line_add) {\n        const int nowc = (nowl +\
    \ nowr) / 2;\n\n        if (nowl >= ir or nowr <= il) {\n            return;\n\
    \        } else if (il <= nowl and nowr <= ir) {\n            if (!lines[now].is_valid)\
    \ {\n                lines[now] = line_add;\n                return;\n       \
    \     }\n            bool upd_l = lines[now].eval(lcr[now].l) > line_add.eval(lcr[now].l);\n\
    \            bool upd_c = lines[now].eval(lcr[now].c) > line_add.eval(lcr[now].c);\n\
    \            bool upd_r = lines[now].eval(lcr[now].r) > line_add.eval(lcr[now].r);\n\
    \            if (upd_l and upd_c and upd_r) {\n                lines[now] = line_add;\n\
    \                return;\n            } else if (upd_c and upd_r) {\n        \
    \        std::swap(lines[now], line_add);\n                _rec(now * 2, nowl,\
    \ nowc, line_add);\n            } else if (upd_l and upd_c) {\n              \
    \  std::swap(lines[now], line_add);\n                _rec(now * 2 + 1, nowc, nowr,\
    \ line_add);\n            } else if (upd_l) {\n                _rec(now * 2, nowl,\
    \ nowc, line_add);\n            } else if (upd_r) {\n                _rec(now\
    \ * 2 + 1, nowc, nowr, line_add);\n            } else {\n                return;\n\
    \            }\n        } else {\n            if (il < nowc) _rec(now * 2, nowl,\
    \ nowc, line_add);\n            if (ir > nowc) _rec(now * 2 + 1, nowc, nowr, line_add);\n\
    \        }\n    }\n\n    void add_line(T a, T b, int idx = -1) {\n        il =\
    \ 0, ir = _n;\n        if (il >= ir) return;\n        _rec(1, 0, _head, _Line{a,\
    \ b, idx, true});\n    }\n    void add_segment(T xl, T xr, T a, T b, int idx =\
    \ -1) {\n        il = std::lower_bound(xs.begin(), xs.end(), xl) - xs.begin();\n\
    \        ir = std::lower_bound(xs.begin(), xs.end(), xr) - xs.begin();\n     \
    \   if (il >= ir) return;\n        _rec(1, 0, _head, _Line{a, b, idx, true});\n\
    \    }\n    struct Ret {\n        T line_a, line_b;\n        int line_idx;\n \
    \       bool is_valid;\n        T_MP minval;\n    };\n    Ret _get_i(int i, T\
    \ x) {\n        i += _head;\n        _Line ret = lines[i];\n        T_MP val =\
    \ ret.is_valid ? ret.eval(x) : 0;\n        for (i /= 2; i; i /= 2) {\n       \
    \     if (!lines[i].is_valid) continue;\n            T_MP tmp = lines[i].eval(x);\n\
    \            if (!ret.is_valid or tmp < val) ret = lines[i], val = tmp;\n    \
    \    }\n        return {ret.a, ret.b, ret.line_idx, ret.is_valid, val};\n    }\n\
    \n    Ret get(T x) {\n        int i = std::lower_bound(xs.begin(), xs.end(), x)\
    \ - xs.begin();\n        assert(i < _n and xs[i] == x);\n        return _get_i(i,\
    \ x);\n    }\n};\n#line 3 \"convex_hull_trick/test/li_chao_tree.test.cpp\"\n#include\
    \ <iostream>\n#line 5 \"convex_hull_trick/test/li_chao_tree.test.cpp\"\n#include\
    \ <utility>\n#line 7 \"convex_hull_trick/test/li_chao_tree.test.cpp\"\nusing namespace\
    \ std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n \
    \   int N, Q;\n    cin >> N >> Q;\n    std::vector<std::tuple<bool, int, int,\
    \ int, long long>> qs;\n    std::vector<long long> xs;\n\n    int tp, l, r, a,\
    \ p;\n    long long b;\n\n    while (N--) {\n        cin >> l >> r >> a >> b;\n\
    \        qs.emplace_back(false, l, r, a, b);\n    }\n    while (Q--) {\n     \
    \   cin >> tp;\n        if (tp == 0) {\n            cin >> l >> r >> a >> b;\n\
    \            qs.emplace_back(false, l, r, a, b);\n        } else {\n         \
    \   cin >> p;\n            qs.emplace_back(true, p, 0, 0, 0);\n            xs.push_back(p);\n\
    \        }\n    }\n    li_chao_tree<long long, long long> tree;\n    tree.init(xs);\n\
    \n    for (auto q : qs) {\n        tie(tp, l, r, a, b) = q;\n        if (tp ==\
    \ 0) tree.add_segment(l, r, a, b, 0);\n        if (tp == 1) {\n            auto\
    \ ret = tree.get(l);\n            if (ret.is_valid) {\n                cout <<\
    \ ret.minval << '\\n';\n            } else {\n                cout << \"INFINITY\\\
    n\";\n            }\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/segment_add_get_min\"\n\
    #include \"../li_chao_tree.hpp\"\n#include <iostream>\n#include <tuple>\n#include\
    \ <utility>\n#include <vector>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n    int N, Q;\n    cin >> N >> Q;\n    std::vector<std::tuple<bool,\
    \ int, int, int, long long>> qs;\n    std::vector<long long> xs;\n\n    int tp,\
    \ l, r, a, p;\n    long long b;\n\n    while (N--) {\n        cin >> l >> r >>\
    \ a >> b;\n        qs.emplace_back(false, l, r, a, b);\n    }\n    while (Q--)\
    \ {\n        cin >> tp;\n        if (tp == 0) {\n            cin >> l >> r >>\
    \ a >> b;\n            qs.emplace_back(false, l, r, a, b);\n        } else {\n\
    \            cin >> p;\n            qs.emplace_back(true, p, 0, 0, 0);\n     \
    \       xs.push_back(p);\n        }\n    }\n    li_chao_tree<long long, long long>\
    \ tree;\n    tree.init(xs);\n\n    for (auto q : qs) {\n        tie(tp, l, r,\
    \ a, b) = q;\n        if (tp == 0) tree.add_segment(l, r, a, b, 0);\n        if\
    \ (tp == 1) {\n            auto ret = tree.get(l);\n            if (ret.is_valid)\
    \ {\n                cout << ret.minval << '\\n';\n            } else {\n    \
    \            cout << \"INFINITY\\n\";\n            }\n        }\n    }\n}\n"
  dependsOn:
  - convex_hull_trick/li_chao_tree.hpp
  isVerificationFile: true
  path: convex_hull_trick/test/li_chao_tree.test.cpp
  requiredBy: []
  timestamp: '2021-09-16 00:36:41+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: convex_hull_trick/test/li_chao_tree.test.cpp
layout: document
redirect_from:
- /verify/convex_hull_trick/test/li_chao_tree.test.cpp
- /verify/convex_hull_trick/test/li_chao_tree.test.cpp.html
title: convex_hull_trick/test/li_chao_tree.test.cpp
---
