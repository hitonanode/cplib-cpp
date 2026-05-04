---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"segmenttree/persistent_segtree.hpp\"\n\n#include <bit>\n\
    #include <cassert>\n#include <functional>\n#include <vector>\n\ntemplate <class\
    \ S, auto op, auto e> struct persistent_segtree {\n    static_assert(std::is_convertible_v<decltype(op),\
    \ std::function<S(S, S)>>,\n                  \"op must work as S(S, S)\");\n\
    \    static_assert(std::is_convertible_v<decltype(e), std::function<S()>>, \"\
    e must work as S()\");\n\n    struct Root {\n        int id;\n    };\n\n    explicit\
    \ persistent_segtree(int n) : persistent_segtree(std::vector<S>(n, e())) {}\n\
    \    explicit persistent_segtree(const std::vector<S> &v) : _n(int(v.size()))\
    \ {\n        size = std::bit_ceil((unsigned int)_n);\n        lg = std::countr_zero((unsigned\
    \ int)size);\n        nodes.assign(2 * size, Node{e(), -1, -1});\n\n        for\
    \ (int i = 0; i < _n; i++) nodes[size + i].val = v[i];\n        for (int i = size\
    \ - 1; i >= 1; i--) {\n            nodes[i].left = 2 * i;\n            nodes[i].right\
    \ = 2 * i + 1;\n            nodes[i].val = op(nodes[2 * i].val, nodes[2 * i +\
    \ 1].val);\n        }\n    }\n\n    Root set(const Root &root, int p, const S\
    \ &x) {\n        assert(0 <= p && p < _n);\n\n        std::vector<int> ids(lg\
    \ + 1);\n\n        ids[lg] = root.id;\n        for (int i = lg - 1; i >= 0; --i)\
    \ {\n            const Node &par = nodes[ids[i + 1]];\n            ids[i] = ((p\
    \ >> i) & 1) ? par.right : par.left;\n        }\n\n        int copy_cur = new_node(x,\
    \ -1, -1);\n\n        for (int i = 1; i <= lg; i++) {\n            const int par\
    \ = ids[i], cur = ids[i - 1];\n            const Node &par_node = nodes[par];\n\
    \            const int left = par_node.left == cur ? copy_cur : par_node.left;\n\
    \            const int right = par_node.right == cur ? copy_cur : par_node.right;\n\
    \            copy_cur = new_node(op(nodes[left].val, nodes[right].val), left,\
    \ right);\n        }\n\n        return Root{copy_cur};\n    }\n\n    S get(const\
    \ Root &root, int p) const {\n        assert(0 <= p && p < _n);\n        int i\
    \ = root.id;\n        for (int bit = lg - 1; bit >= 0; --bit) {\n            i\
    \ = ((p >> bit) & 1) ? nodes[i].right : nodes[i].left;\n        }\n        return\
    \ nodes[i].val;\n    }\n\n    S prod(const Root &root, int l, int r) const {\n\
    \        assert(0 <= l && l <= r && r <= _n);\n        auto rec = [&](auto &&self,\
    \ int i, int lo, int hi) -> S {\n            if (r <= lo || hi <= l) return e();\n\
    \            if (l <= lo && hi <= r) return nodes[i].val;\n            const int\
    \ mid = (lo + hi) >> 1;\n            return op(self(self, nodes[i].left, lo, mid),\
    \ self(self, nodes[i].right, mid, hi));\n        };\n        return rec(rec, root.id,\
    \ 0, size);\n    }\n\n    S all_prod(const Root &root) const { return nodes[root.id].val;\
    \ }\n\n    template <bool (*f)(S)> int max_right(const Root &root, int l) const\
    \ {\n        return max_right(root, l, [](S x) { return f(x); });\n    }\n   \
    \ template <class F> int max_right(const Root &root, int l, F f) const {\n   \
    \     assert(0 <= l && l <= _n);\n        assert(f(e()));\n        if (l == _n)\
    \ return _n;\n        S sm = e();\n        auto rec = [&](auto &&self, int i,\
    \ int lo, int hi) -> int {\n            if (hi <= l) return hi;\n            if\
    \ (l <= lo) {\n                const S nxt = op(sm, nodes[i].val);\n         \
    \       if (f(nxt)) {\n                    sm = nxt;\n                    return\
    \ hi;\n                }\n                if (hi - lo == 1) return lo;\n     \
    \       }\n            const int mid = (lo + hi) >> 1;\n            if (l < mid)\
    \ {\n                const int left_res = self(self, nodes[i].left, lo, mid);\n\
    \                if (left_res < mid) return left_res;\n            }\n       \
    \     return self(self, nodes[i].right, mid, hi);\n        };\n        return\
    \ std::min(rec(rec, root.id, 0, size), _n);\n    }\n\n    template <bool (*f)(S)>\
    \ int min_left(const Root &root, int r) const {\n        return min_left(root,\
    \ r, [](S x) { return f(x); });\n    }\n    template <class F> int min_left(const\
    \ Root &root, int r, F f) const {\n        assert(0 <= r && r <= _n);\n      \
    \  assert(f(e()));\n        if (r == 0) return 0;\n        S sm = e();\n     \
    \   auto rec = [&](auto &&self, int i, int lo, int hi) -> int {\n            if\
    \ (r <= lo) return lo;\n            if (hi <= r) {\n                const S nxt\
    \ = op(nodes[i].val, sm);\n                if (f(nxt)) {\n                   \
    \ sm = nxt;\n                    return lo;\n                }\n             \
    \   if (hi - lo == 1) return hi;\n            }\n            const int mid = (lo\
    \ + hi) >> 1;\n            if (mid < r) {\n                const int right_res\
    \ = self(self, nodes[i].right, mid, hi);\n                if (mid < right_res)\
    \ return right_res;\n            }\n            return self(self, nodes[i].left,\
    \ lo, mid);\n        };\n        return rec(rec, root.id, 0, size);\n    }\n\n\
    \    Root get_root() const { return {1}; }\n\n    struct Node {\n        S val;\n\
    \        int left, right;\n    };\n\n    int _n, size, lg;\n    std::vector<Node>\
    \ nodes;\n\n    int new_node(const S &val, int left, int right) {\n        nodes.push_back(Node{val,\
    \ left, right});\n        return int(nodes.size()) - 1;\n    }\n};\n"
  code: "#pragma once\n\n#include <bit>\n#include <cassert>\n#include <functional>\n\
    #include <vector>\n\ntemplate <class S, auto op, auto e> struct persistent_segtree\
    \ {\n    static_assert(std::is_convertible_v<decltype(op), std::function<S(S,\
    \ S)>>,\n                  \"op must work as S(S, S)\");\n    static_assert(std::is_convertible_v<decltype(e),\
    \ std::function<S()>>, \"e must work as S()\");\n\n    struct Root {\n       \
    \ int id;\n    };\n\n    explicit persistent_segtree(int n) : persistent_segtree(std::vector<S>(n,\
    \ e())) {}\n    explicit persistent_segtree(const std::vector<S> &v) : _n(int(v.size()))\
    \ {\n        size = std::bit_ceil((unsigned int)_n);\n        lg = std::countr_zero((unsigned\
    \ int)size);\n        nodes.assign(2 * size, Node{e(), -1, -1});\n\n        for\
    \ (int i = 0; i < _n; i++) nodes[size + i].val = v[i];\n        for (int i = size\
    \ - 1; i >= 1; i--) {\n            nodes[i].left = 2 * i;\n            nodes[i].right\
    \ = 2 * i + 1;\n            nodes[i].val = op(nodes[2 * i].val, nodes[2 * i +\
    \ 1].val);\n        }\n    }\n\n    Root set(const Root &root, int p, const S\
    \ &x) {\n        assert(0 <= p && p < _n);\n\n        std::vector<int> ids(lg\
    \ + 1);\n\n        ids[lg] = root.id;\n        for (int i = lg - 1; i >= 0; --i)\
    \ {\n            const Node &par = nodes[ids[i + 1]];\n            ids[i] = ((p\
    \ >> i) & 1) ? par.right : par.left;\n        }\n\n        int copy_cur = new_node(x,\
    \ -1, -1);\n\n        for (int i = 1; i <= lg; i++) {\n            const int par\
    \ = ids[i], cur = ids[i - 1];\n            const Node &par_node = nodes[par];\n\
    \            const int left = par_node.left == cur ? copy_cur : par_node.left;\n\
    \            const int right = par_node.right == cur ? copy_cur : par_node.right;\n\
    \            copy_cur = new_node(op(nodes[left].val, nodes[right].val), left,\
    \ right);\n        }\n\n        return Root{copy_cur};\n    }\n\n    S get(const\
    \ Root &root, int p) const {\n        assert(0 <= p && p < _n);\n        int i\
    \ = root.id;\n        for (int bit = lg - 1; bit >= 0; --bit) {\n            i\
    \ = ((p >> bit) & 1) ? nodes[i].right : nodes[i].left;\n        }\n        return\
    \ nodes[i].val;\n    }\n\n    S prod(const Root &root, int l, int r) const {\n\
    \        assert(0 <= l && l <= r && r <= _n);\n        auto rec = [&](auto &&self,\
    \ int i, int lo, int hi) -> S {\n            if (r <= lo || hi <= l) return e();\n\
    \            if (l <= lo && hi <= r) return nodes[i].val;\n            const int\
    \ mid = (lo + hi) >> 1;\n            return op(self(self, nodes[i].left, lo, mid),\
    \ self(self, nodes[i].right, mid, hi));\n        };\n        return rec(rec, root.id,\
    \ 0, size);\n    }\n\n    S all_prod(const Root &root) const { return nodes[root.id].val;\
    \ }\n\n    template <bool (*f)(S)> int max_right(const Root &root, int l) const\
    \ {\n        return max_right(root, l, [](S x) { return f(x); });\n    }\n   \
    \ template <class F> int max_right(const Root &root, int l, F f) const {\n   \
    \     assert(0 <= l && l <= _n);\n        assert(f(e()));\n        if (l == _n)\
    \ return _n;\n        S sm = e();\n        auto rec = [&](auto &&self, int i,\
    \ int lo, int hi) -> int {\n            if (hi <= l) return hi;\n            if\
    \ (l <= lo) {\n                const S nxt = op(sm, nodes[i].val);\n         \
    \       if (f(nxt)) {\n                    sm = nxt;\n                    return\
    \ hi;\n                }\n                if (hi - lo == 1) return lo;\n     \
    \       }\n            const int mid = (lo + hi) >> 1;\n            if (l < mid)\
    \ {\n                const int left_res = self(self, nodes[i].left, lo, mid);\n\
    \                if (left_res < mid) return left_res;\n            }\n       \
    \     return self(self, nodes[i].right, mid, hi);\n        };\n        return\
    \ std::min(rec(rec, root.id, 0, size), _n);\n    }\n\n    template <bool (*f)(S)>\
    \ int min_left(const Root &root, int r) const {\n        return min_left(root,\
    \ r, [](S x) { return f(x); });\n    }\n    template <class F> int min_left(const\
    \ Root &root, int r, F f) const {\n        assert(0 <= r && r <= _n);\n      \
    \  assert(f(e()));\n        if (r == 0) return 0;\n        S sm = e();\n     \
    \   auto rec = [&](auto &&self, int i, int lo, int hi) -> int {\n            if\
    \ (r <= lo) return lo;\n            if (hi <= r) {\n                const S nxt\
    \ = op(nodes[i].val, sm);\n                if (f(nxt)) {\n                   \
    \ sm = nxt;\n                    return lo;\n                }\n             \
    \   if (hi - lo == 1) return hi;\n            }\n            const int mid = (lo\
    \ + hi) >> 1;\n            if (mid < r) {\n                const int right_res\
    \ = self(self, nodes[i].right, mid, hi);\n                if (mid < right_res)\
    \ return right_res;\n            }\n            return self(self, nodes[i].left,\
    \ lo, mid);\n        };\n        return rec(rec, root.id, 0, size);\n    }\n\n\
    \    Root get_root() const { return {1}; }\n\n    struct Node {\n        S val;\n\
    \        int left, right;\n    };\n\n    int _n, size, lg;\n    std::vector<Node>\
    \ nodes;\n\n    int new_node(const S &val, int left, int right) {\n        nodes.push_back(Node{val,\
    \ left, right});\n        return int(nodes.size()) - 1;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: segmenttree/persistent_segtree.hpp
  requiredBy: []
  timestamp: '2026-05-04 14:45:25+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: segmenttree/persistent_segtree.hpp
layout: document
title: "Persistent segtree \uFF08\u5B8C\u5168\u6C38\u7D9A\u30BB\u30B0\u30E1\u30F3\u30C8\
  \u6728\uFF09"
---

完全永続版のセグメント木．各点更新のたびに新しい版の根を返し，過去の任意の版に対して 1 点更新や区間積クエリを行える．インターフェースは `atcoder::segtree` に近く，第一引数に更新のもととなる版の根を与える点が異なる．

## 使用方法

```cpp
struct S {
    unsigned long long sum;
    int len;
};
S op(S l, S r) { return {l.sum + r.sum, l.len + r.len}; }
S e() { return {0, 0}; }

vector<S> A(N, {0, 1});
persistent_segtree<S, op, e> seg(A);

auto root0 = seg.get_root();              // 初期版
auto root1 = seg.set(root0, idx, {x, 1});   // idx 番目を更新した新しい版

S x = seg.get(root0, idx);                  // root0 版の idx 番目の値
S y = seg.prod(root1, l, r);              // root1 版の [l, r) の積
S z = seg.all_prod(root1);                // root1 版の列全体の積

int i = seg.max_right(root1, l, [](S x) { return x.sum <= lim; });
int j = seg.min_left(root1, r, [](S x) { return x.sum <= lim; });
```

`max_right`, `min_left` の意味は `atcoder::segtree` と同じ．すなわち，`f(e()) = true` を満たす単調な述語 `f` に対して，

- `max_right(root, l, f)` は `prod(root, l, r)` が `f` を満たすような最大の `r` を返す．
- `min_left(root, r, f)` は `prod(root, l, r)` が `f` を満たすような最小の `l` を返す．

計算量は以下の通り．

- 構築 $O(N)$
- `set` $O(\log N)$ 時間，更新 1 回あたり追加ノード数 $O(\log N)$
- `get`, `prod`, `max_right`, `min_left` $O(\log N)$
- `all_prod` $O(1)$

## 問題例

- [The 1st Universal Cup. Stage 15: Hangzhou G. Game: Celeste - Problem - QOJ.ac](https://qoj.ac/contest/1221/problem/6400)
- [AtCoder Beginner Contest 453 G - Copy Query](https://atcoder.jp/contests/abc453/tasks/abc453_g)

## Link

- [永続セグメント木 - AtCoderInfo](https://info.atcoder.jp/entry/algorithm_lectures/persistent_segment_tree)
