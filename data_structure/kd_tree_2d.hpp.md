---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://atcoder.jp/contests/abc234/submissions/28456735
  bundledCode: "#line 2 \"data_structure/kd_tree_2d.hpp\"\n#include <algorithm>\n\
    #include <tuple>\n#include <utility>\n#include <vector>\n\n// 2\u6B21\u5143\u306E\
    \ kd-tree\n// \u77E9\u5F62\u5185\u306E\u5168\u9802\u70B9\u53D6\u5F97\u304C\u53EF\
    \u80FD\n// Verified: abc234h https://atcoder.jp/contests/abc234/submissions/28456735\n\
    template <class T> struct kd_tree {\n    std::vector<std::pair<T, T>> _ps;\n \
    \   struct Node {\n        T xmin, xmax, ymin, ymax;\n        std::vector<int>\
    \ ids;\n        int lch, rch;\n        template <class OStream> friend OStream\
    \ &operator<<(OStream &os, const Node &n) {\n            os << \"{Node[\" << n.xmin\
    \ << \", \" << n.xmax << \"]x[\" << n.ymin << \", \" << n.ymax\n             \
    \  << \"], ids=(\";\n            for (auto i : n.ids) os << i << ',';\n      \
    \      os << \"), chs=\" << n.lch << ',' << n.rch << '}';\n            return\
    \ os;\n        }\n    };\n    std::vector<Node> _nodes;\n\n    using Tpl = std::tuple<int,\
    \ T, T>;\n    std::vector<Tpl> _tmp;\n\n    int _build(int l, int r, int nsplitx,\
    \ int nsplity) {\n        if (l >= r) return -1;\n        T xmin = std::get<1>(_tmp[l]),\
    \ xmax = xmin, ymin = std::get<2>(_tmp[l]), ymax = ymin;\n        std::vector<int>\
    \ ids(r - l);\n        for (int i = l; i < r; ++i) {\n            T x = std::get<1>(_tmp[i]),\
    \ y = std::get<2>(_tmp[i]);\n            if (x < xmin) xmin = x;\n           \
    \ if (x > xmax) xmax = x;\n            if (y < ymin) ymin = y;\n            if\
    \ (y > ymax) ymax = y;\n            ids[i - l] = std::get<0>(_tmp[i]);\n     \
    \   }\n        const int _node_id = _nodes.size();\n        _nodes.push_back({xmin,\
    \ xmax, ymin, ymax, ids, -1, -1});\n\n        // Decide which direction to split\n\
    \        bool split_x = xmax - xmin > ymax - ymin;\n        if (nsplitx > 3) split_x\
    \ = false; // \u540C\u3058\u65B9\u5411\u306B\u4F55\u5EA6\u3082\u9023\u7D9A\u3067\
    \u5207\u3089\u306A\u3044\n        if (nsplity > 3) split_x = true;\n\n       \
    \ if (r - l > 1) {\n            int c = (l + r) / 2;\n            if (split_x)\
    \ {\n                // split x\n                std::nth_element(\n         \
    \           _tmp.begin() + l, _tmp.begin() + c, _tmp.begin() + r,\n          \
    \          [&](const Tpl &l, const Tpl &r) { return std::get<1>(l) < std::get<1>(r);\
    \ });\n                _nodes[_node_id].lch = _build(l, c, nsplitx + 1, 0);\n\
    \                _nodes[_node_id].rch = _build(c, r, nsplitx + 1, 0);\n      \
    \      } else {\n                // split y\n                std::nth_element(\n\
    \                    _tmp.begin() + l, _tmp.begin() + c, _tmp.begin() + r,\n \
    \                   [&](const Tpl &l, const Tpl &r) { return std::get<2>(l) <\
    \ std : get<2>(r); });\n                _nodes[_node_id].lch = _build(l, c, 0,\
    \ nsplity + 1);:\n                _nodes[_node_id].rch = _build(c, r, 0, nsplity\
    \ + 1);\n            }\n        }\n        return _node_id;\n    }\n\n    void\
    \ _initialize(const std::vector<std::pair<T, T>> &vs) {\n        _ps = vs;\n \
    \       _tmp.resize(_ps.size());\n        for (int i = 0; i < int(vs.size());\
    \ ++i)\n            _tmp[i] = std::make_tuple(i, vs[i].first, vs[i].second);\n\
    \        _build(0, _tmp.size(), 0, 0);\n    }\n    kd_tree(const std::vector<std::pair<T,\
    \ T>> &vs) { _initialize(vs); }\n\n    std::vector<int> get_rect(T xmin, T xmax,\
    \ T ymin, T ymax) const {\n        // [xmin, xmax] * [ymin, ymax] \u306B\u542B\
    \u307E\u308C\u308B\u5168\u70B9\u53D6\u5F97\n        std::vector<int> ret;\n  \
    \      std::vector<int> _stack;\n        if (_nodes.size()) _stack.push_back(0);\n\
    \        while (!_stack.empty()) {\n            const Node &now = _nodes[_stack.back()];\n\
    \            _stack.pop_back();\n            if (xmax < now.xmin or now.xmax <\
    \ xmin or ymax < now.ymin or now.ymax < ymin) {\n                ;\n         \
    \   } else if (xmin <= now.xmin and now.xmax <= xmax and ymin <= now.ymin and\n\
    \                       now.ymax <= ymax) {\n                ret.insert(ret.end(),\
    \ now.ids.begin(), now.ids.end());\n            } else {\n                if (now.lch\
    \ >= 0) _stack.push_back(now.lch);\n                if (now.rch >= 0) _stack.push_back(now.rch);\n\
    \            }\n        }\n        return ret;\n    }\n};\n"
  code: "#pragma once\n#include <algorithm>\n#include <tuple>\n#include <utility>\n\
    #include <vector>\n\n// 2\u6B21\u5143\u306E kd-tree\n// \u77E9\u5F62\u5185\u306E\
    \u5168\u9802\u70B9\u53D6\u5F97\u304C\u53EF\u80FD\n// Verified: abc234h https://atcoder.jp/contests/abc234/submissions/28456735\n\
    template <class T> struct kd_tree {\n    std::vector<std::pair<T, T>> _ps;\n \
    \   struct Node {\n        T xmin, xmax, ymin, ymax;\n        std::vector<int>\
    \ ids;\n        int lch, rch;\n        template <class OStream> friend OStream\
    \ &operator<<(OStream &os, const Node &n) {\n            os << \"{Node[\" << n.xmin\
    \ << \", \" << n.xmax << \"]x[\" << n.ymin << \", \" << n.ymax\n             \
    \  << \"], ids=(\";\n            for (auto i : n.ids) os << i << ',';\n      \
    \      os << \"), chs=\" << n.lch << ',' << n.rch << '}';\n            return\
    \ os;\n        }\n    };\n    std::vector<Node> _nodes;\n\n    using Tpl = std::tuple<int,\
    \ T, T>;\n    std::vector<Tpl> _tmp;\n\n    int _build(int l, int r, int nsplitx,\
    \ int nsplity) {\n        if (l >= r) return -1;\n        T xmin = std::get<1>(_tmp[l]),\
    \ xmax = xmin, ymin = std::get<2>(_tmp[l]), ymax = ymin;\n        std::vector<int>\
    \ ids(r - l);\n        for (int i = l; i < r; ++i) {\n            T x = std::get<1>(_tmp[i]),\
    \ y = std::get<2>(_tmp[i]);\n            if (x < xmin) xmin = x;\n           \
    \ if (x > xmax) xmax = x;\n            if (y < ymin) ymin = y;\n            if\
    \ (y > ymax) ymax = y;\n            ids[i - l] = std::get<0>(_tmp[i]);\n     \
    \   }\n        const int _node_id = _nodes.size();\n        _nodes.push_back({xmin,\
    \ xmax, ymin, ymax, ids, -1, -1});\n\n        // Decide which direction to split\n\
    \        bool split_x = xmax - xmin > ymax - ymin;\n        if (nsplitx > 3) split_x\
    \ = false; // \u540C\u3058\u65B9\u5411\u306B\u4F55\u5EA6\u3082\u9023\u7D9A\u3067\
    \u5207\u3089\u306A\u3044\n        if (nsplity > 3) split_x = true;\n\n       \
    \ if (r - l > 1) {\n            int c = (l + r) / 2;\n            if (split_x)\
    \ {\n                // split x\n                std::nth_element(\n         \
    \           _tmp.begin() + l, _tmp.begin() + c, _tmp.begin() + r,\n          \
    \          [&](const Tpl &l, const Tpl &r) { return std::get<1>(l) < std::get<1>(r);\
    \ });\n                _nodes[_node_id].lch = _build(l, c, nsplitx + 1, 0);\n\
    \                _nodes[_node_id].rch = _build(c, r, nsplitx + 1, 0);\n      \
    \      } else {\n                // split y\n                std::nth_element(\n\
    \                    _tmp.begin() + l, _tmp.begin() + c, _tmp.begin() + r,\n \
    \                   [&](const Tpl &l, const Tpl &r) { return std::get<2>(l) <\
    \ std : get<2>(r); });\n                _nodes[_node_id].lch = _build(l, c, 0,\
    \ nsplity + 1);:\n                _nodes[_node_id].rch = _build(c, r, 0, nsplity\
    \ + 1);\n            }\n        }\n        return _node_id;\n    }\n\n    void\
    \ _initialize(const std::vector<std::pair<T, T>> &vs) {\n        _ps = vs;\n \
    \       _tmp.resize(_ps.size());\n        for (int i = 0; i < int(vs.size());\
    \ ++i)\n            _tmp[i] = std::make_tuple(i, vs[i].first, vs[i].second);\n\
    \        _build(0, _tmp.size(), 0, 0);\n    }\n    kd_tree(const std::vector<std::pair<T,\
    \ T>> &vs) { _initialize(vs); }\n\n    std::vector<int> get_rect(T xmin, T xmax,\
    \ T ymin, T ymax) const {\n        // [xmin, xmax] * [ymin, ymax] \u306B\u542B\
    \u307E\u308C\u308B\u5168\u70B9\u53D6\u5F97\n        std::vector<int> ret;\n  \
    \      std::vector<int> _stack;\n        if (_nodes.size()) _stack.push_back(0);\n\
    \        while (!_stack.empty()) {\n            const Node &now = _nodes[_stack.back()];\n\
    \            _stack.pop_back();\n            if (xmax < now.xmin or now.xmax <\
    \ xmin or ymax < now.ymin or now.ymax < ymin) {\n                ;\n         \
    \   } else if (xmin <= now.xmin and now.xmax <= xmax and ymin <= now.ymin and\n\
    \                       now.ymax <= ymax) {\n                ret.insert(ret.end(),\
    \ now.ids.begin(), now.ids.end());\n            } else {\n                if (now.lch\
    \ >= 0) _stack.push_back(now.lch);\n                if (now.rch >= 0) _stack.push_back(now.rch);\n\
    \            }\n        }\n        return ret;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/kd_tree_2d.hpp
  requiredBy: []
  timestamp: '2022-01-11 01:21:14+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data_structure/kd_tree_2d.hpp
layout: document
title: k-d tree (2D)
---

$k$-d tree の二次元平面の場合の実装．

木の各ノードにおいて平面を切断する方向は原則として $x$, $y$ 方向のうち最大値と最小値の差が大きい方を採用するが，ワーストケースでの計算量悪化を回避するため，同じ方向の切断が連続しすぎないよう簡単な工夫を入れている．

```cpp
vector<pair<long long, long long>> xys;

kd_tree<long long> kdt(xys);

long long xmin, xmax, ymin, ymax;
vector<int> ids = kdt.get_rect(xmin, xmax, ymin, ymax);  // 矩形に含まれる頂点番号取得
```

## 問題例

- [AtCoder Beginner Contest 234 Ex - Enumerate Pairs](https://atcoder.jp/contests/abc234/submissions/28456735)
