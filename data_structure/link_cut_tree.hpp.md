---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: data_structure/test/link_cut_tree.aoj2450.test.cpp
    title: data_structure/test/link_cut_tree.aoj2450.test.cpp
  - icon: ':heavy_check_mark:'
    path: data_structure/test/link_cut_tree.composition.test.cpp
    title: data_structure/test/link_cut_tree.composition.test.cpp
  - icon: ':heavy_check_mark:'
    path: data_structure/test/link_cut_tree.noncommutative.stress.test.cpp
    title: data_structure/test/link_cut_tree.noncommutative.stress.test.cpp
  - icon: ':heavy_check_mark:'
    path: data_structure/test/link_cut_tree.noncommutative2.stress.test.cpp
    title: data_structure/test/link_cut_tree.noncommutative2.stress.test.cpp
  - icon: ':heavy_check_mark:'
    path: data_structure/test/link_cut_tree.pathadd.stress.test.cpp
    title: data_structure/test/link_cut_tree.pathadd.stress.test.cpp
  - icon: ':heavy_check_mark:'
    path: data_structure/test/link_cut_tree.sum.test.cpp
    title: data_structure/test/link_cut_tree.sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://ei1333.github.io/library/structure/lct/link-cut-tree-lazy-path.cpp
    - https://www.slideshare.net/iwiwi/2-12188845
  bundledCode: "#line 2 \"data_structure/link_cut_tree.hpp\"\n\n// CUT begin\n// Link-Cut\
    \ Tree\n// Reference:\n// - https://www.slideshare.net/iwiwi/2-12188845\n// -\
    \ https://ei1333.github.io/library/structure/lct/link-cut-tree-lazy-path.cpp\n\
    template <class S, class F, S (*op)(S, S), S (*reversal)(S), S (*mapping)(F, S),\
    \ F (*composition)(F, F), F (*id)()>\nclass lazy_linkcuttree {\npublic:\n    struct\
    \ Node {\n        Node *l, *r, *p;\n        S d, sum;\n        F lz;\n       \
    \ bool is_reversed;\n        int sz;\n        Node(S val)\n            : l(nullptr),\
    \ r(nullptr), p(nullptr), d(val), sum(val), lz(id()), is_reversed(false), sz(1)\
    \ {}\n        bool is_root() const { return !p || (p->l != this and p->r != this);\
    \ }\n        template <class OStream> friend OStream &operator<<(OStream &os,\
    \ const Node &n) {\n            os << '[';\n            if (n.l) os << *(n.l)\
    \ << ',';\n            os << n.d << ',';\n            if (n.r) os << *(n.r);\n\
    \            return os << ']';\n        }\n    };\n\nprotected:\n    void update(Node\
    \ *t) {\n        if (t == nullptr) return;\n        t->sz = 1;\n        t->sum\
    \ = t->d;\n        if (t->l) {\n            t->sz += t->l->sz;\n            t->sum\
    \ = op(t->l->sum, t->sum);\n        }\n        if (t->r) {\n            t->sz\
    \ += t->r->sz;\n            t->sum = op(t->sum, t->r->sum);\n        }\n    }\n\
    \    void all_apply(Node *a, F b) {\n        a->d = mapping(b, a->d);\n      \
    \  a->sum = mapping(b, a->sum);\n        a->lz = composition(b, a->lz);\n    }\n\
    \    void _toggle(Node *t) {\n        auto tmp = t->l;\n        t->l = t->r, t->r\
    \ = tmp;\n        t->sum = reversal(t->sum);\n        t->is_reversed ^= true;\n\
    \    }\n\n    void push(Node *&t) {\n        if (t->lz != id()) {\n          \
    \  if (t->l) all_apply(t->l, t->lz);\n            if (t->r) all_apply(t->r, t->lz);\n\
    \            t->lz = id();\n        }\n        if (t->is_reversed) {\n       \
    \     if (t->l) _toggle(t->l);\n            if (t->r) _toggle(t->r);\n       \
    \     t->is_reversed = false;\n        }\n    }\n\n    void _rot_r(Node *t) {\n\
    \        Node *x = t->p, *y = x->p;\n        if ((x->l = t->r)) t->r->p = x;\n\
    \        t->r = x, x->p = t;\n        update(x), update(t);\n        if ((t->p\
    \ = y)) {\n            if (y->l == x) y->l = t;\n            if (y->r == x) y->r\
    \ = t;\n            update(y);\n        }\n    }\n    void _rot_l(Node *t) {\n\
    \        Node *x = t->p, *y = x->p;\n        if ((x->r = t->l)) t->l->p = x;\n\
    \        t->l = x, x->p = t;\n        update(x), update(t);\n        if ((t->p\
    \ = y)) {\n            if (y->l == x) y->l = t;\n            if (y->r == x) y->r\
    \ = t;\n            update(y);\n        }\n    }\n\n    void _splay(Node *t) {\n\
    \        push(t);\n        while (!t->is_root()) {\n            Node *q = t->p;\n\
    \            if (q->is_root()) {\n                push(q), push(t);\n        \
    \        if (q->l == t)\n                    _rot_r(t);\n                else\n\
    \                    _rot_l(t);\n            } else {\n                Node *r\
    \ = q->p;\n                push(r), push(q), push(t);\n                if (r->l\
    \ == q) {\n                    if (q->l == t)\n                        _rot_r(q),\
    \ _rot_r(t);\n                    else\n                        _rot_l(t), _rot_r(t);\n\
    \                } else {\n                    if (q->r == t)\n              \
    \          _rot_l(q), _rot_l(t);\n                    else\n                 \
    \       _rot_r(t), _rot_l(t);\n                }\n            }\n        }\n \
    \   }\n\npublic:\n    [[nodiscard]] Node *make_node(S val) { return new Node(val);\
    \ }\n\n    void evert(Node *t) { expose(t), _toggle(t), push(t); }\n\n    Node\
    \ *expose(Node *t) {\n        Node *rp = nullptr;\n        for (Node *cur = t;\
    \ cur; cur = cur->p) {\n            _splay(cur);\n            cur->r = rp;\n \
    \           update(cur);\n            rp = cur;\n        }\n        _splay(t);\n\
    \        return rp;\n    }\n\n    void link(Node *chi, Node *par) {\n        evert(chi);\n\
    \        expose(par);\n        chi->p = par;\n        par->r = chi;\n        update(par);\n\
    \    }\n\n    void cut(Node *chi) {\n        expose(chi);\n        Node *par =\
    \ chi->l;\n        chi->l = nullptr;\n        update(chi);\n        par->p = nullptr;\n\
    \    }\n\n    void cut(Node *u, Node *v) { evert(u), cut(v); }\n\n    Node *lca(Node\
    \ *u, Node *v) { return expose(u), expose(v); }\n\n    void set(Node *t, S x)\
    \ { expose(t), t->d = x, update(t); }\n\n    S get(Node *t) { return expose(t),\
    \ t->d; }\n\n    void apply(Node *u, Node *v, const F &x) {\n        evert(u);\n\
    \        expose(v);\n        all_apply(v, x);\n        push(v);\n    }\n\n   \
    \ S prod(Node *u, Node *v) {\n        evert(u);\n        expose(v);\n        return\
    \ v->sum;\n    }\n\n    Node *kth_parent(Node *t, int k) {\n        expose(t);\n\
    \        while (t) {\n            push(t);\n            if (t->r and t->r->sz\
    \ > k) {\n                t = t->r;\n            } else {\n                if\
    \ (t->r) k -= t->r->sz;\n                if (k == 0) return t;\n             \
    \   k--;\n                t = t->l;\n            }\n        }\n        return\
    \ nullptr;\n    }\n\n    bool is_connected(Node *u, Node *v) {\n        expose(u),\
    \ expose(v);\n        return u == v or u->p;\n    }\n};\n/* example usage:\nstruct\
    \ S {\n    int sz, sum, lhi, rhi, inhi;\n    S(int x) : sz(1), sum(x), lhi(x),\
    \ rhi(x), inhi(x) {}\n    S(int sz_, int sum_, int lhi_, int rhi_, int inhi_)\n\
    \        : sz(sz_), sum(sum_), lhi(lhi_), rhi(rhi_), inhi(inhi_) {}\n};\nusing\
    \ F = pair<bool, int>;\nS op(S l, S r) {\n    return S(l.sz + r.sz, l.sum + r.sum,\
    \ max(l.sum + r.lhi, l.lhi), max(l.rhi + r.sum, r.rhi), max<int>({l.inhi, r.inhi,\
    \ l.rhi + r.lhi}));\n}\nS reversal(S x) { return S(x.sz, x.sum, x.rhi, x.lhi,\
    \ x.inhi); }\nS mapping(F f, S x) {\n    if (f.first) {\n        auto v = f.second;\n\
    \        auto sum = x.sz * v;\n        return S{x.sz, sum, max(v, sum), max(v,\
    \ sum), max(v, sum)};\n    } else {\n        return x;\n    }\n}\nF composition(F\
    \ fnew, F gold) { return fnew.first ? fnew : gold; }\nF id() { return {false,\
    \ 0}; }\nusing LCT = lazy_linkcuttree<S, F, op, reversal, mapping, composition,\
    \ id>;\nvector<LCT::Node*> vs;\n*/\n"
  code: "#pragma once\n\n// CUT begin\n// Link-Cut Tree\n// Reference:\n// - https://www.slideshare.net/iwiwi/2-12188845\n\
    // - https://ei1333.github.io/library/structure/lct/link-cut-tree-lazy-path.cpp\n\
    template <class S, class F, S (*op)(S, S), S (*reversal)(S), S (*mapping)(F, S),\
    \ F (*composition)(F, F), F (*id)()>\nclass lazy_linkcuttree {\npublic:\n    struct\
    \ Node {\n        Node *l, *r, *p;\n        S d, sum;\n        F lz;\n       \
    \ bool is_reversed;\n        int sz;\n        Node(S val)\n            : l(nullptr),\
    \ r(nullptr), p(nullptr), d(val), sum(val), lz(id()), is_reversed(false), sz(1)\
    \ {}\n        bool is_root() const { return !p || (p->l != this and p->r != this);\
    \ }\n        template <class OStream> friend OStream &operator<<(OStream &os,\
    \ const Node &n) {\n            os << '[';\n            if (n.l) os << *(n.l)\
    \ << ',';\n            os << n.d << ',';\n            if (n.r) os << *(n.r);\n\
    \            return os << ']';\n        }\n    };\n\nprotected:\n    void update(Node\
    \ *t) {\n        if (t == nullptr) return;\n        t->sz = 1;\n        t->sum\
    \ = t->d;\n        if (t->l) {\n            t->sz += t->l->sz;\n            t->sum\
    \ = op(t->l->sum, t->sum);\n        }\n        if (t->r) {\n            t->sz\
    \ += t->r->sz;\n            t->sum = op(t->sum, t->r->sum);\n        }\n    }\n\
    \    void all_apply(Node *a, F b) {\n        a->d = mapping(b, a->d);\n      \
    \  a->sum = mapping(b, a->sum);\n        a->lz = composition(b, a->lz);\n    }\n\
    \    void _toggle(Node *t) {\n        auto tmp = t->l;\n        t->l = t->r, t->r\
    \ = tmp;\n        t->sum = reversal(t->sum);\n        t->is_reversed ^= true;\n\
    \    }\n\n    void push(Node *&t) {\n        if (t->lz != id()) {\n          \
    \  if (t->l) all_apply(t->l, t->lz);\n            if (t->r) all_apply(t->r, t->lz);\n\
    \            t->lz = id();\n        }\n        if (t->is_reversed) {\n       \
    \     if (t->l) _toggle(t->l);\n            if (t->r) _toggle(t->r);\n       \
    \     t->is_reversed = false;\n        }\n    }\n\n    void _rot_r(Node *t) {\n\
    \        Node *x = t->p, *y = x->p;\n        if ((x->l = t->r)) t->r->p = x;\n\
    \        t->r = x, x->p = t;\n        update(x), update(t);\n        if ((t->p\
    \ = y)) {\n            if (y->l == x) y->l = t;\n            if (y->r == x) y->r\
    \ = t;\n            update(y);\n        }\n    }\n    void _rot_l(Node *t) {\n\
    \        Node *x = t->p, *y = x->p;\n        if ((x->r = t->l)) t->l->p = x;\n\
    \        t->l = x, x->p = t;\n        update(x), update(t);\n        if ((t->p\
    \ = y)) {\n            if (y->l == x) y->l = t;\n            if (y->r == x) y->r\
    \ = t;\n            update(y);\n        }\n    }\n\n    void _splay(Node *t) {\n\
    \        push(t);\n        while (!t->is_root()) {\n            Node *q = t->p;\n\
    \            if (q->is_root()) {\n                push(q), push(t);\n        \
    \        if (q->l == t)\n                    _rot_r(t);\n                else\n\
    \                    _rot_l(t);\n            } else {\n                Node *r\
    \ = q->p;\n                push(r), push(q), push(t);\n                if (r->l\
    \ == q) {\n                    if (q->l == t)\n                        _rot_r(q),\
    \ _rot_r(t);\n                    else\n                        _rot_l(t), _rot_r(t);\n\
    \                } else {\n                    if (q->r == t)\n              \
    \          _rot_l(q), _rot_l(t);\n                    else\n                 \
    \       _rot_r(t), _rot_l(t);\n                }\n            }\n        }\n \
    \   }\n\npublic:\n    [[nodiscard]] Node *make_node(S val) { return new Node(val);\
    \ }\n\n    void evert(Node *t) { expose(t), _toggle(t), push(t); }\n\n    Node\
    \ *expose(Node *t) {\n        Node *rp = nullptr;\n        for (Node *cur = t;\
    \ cur; cur = cur->p) {\n            _splay(cur);\n            cur->r = rp;\n \
    \           update(cur);\n            rp = cur;\n        }\n        _splay(t);\n\
    \        return rp;\n    }\n\n    void link(Node *chi, Node *par) {\n        evert(chi);\n\
    \        expose(par);\n        chi->p = par;\n        par->r = chi;\n        update(par);\n\
    \    }\n\n    void cut(Node *chi) {\n        expose(chi);\n        Node *par =\
    \ chi->l;\n        chi->l = nullptr;\n        update(chi);\n        par->p = nullptr;\n\
    \    }\n\n    void cut(Node *u, Node *v) { evert(u), cut(v); }\n\n    Node *lca(Node\
    \ *u, Node *v) { return expose(u), expose(v); }\n\n    void set(Node *t, S x)\
    \ { expose(t), t->d = x, update(t); }\n\n    S get(Node *t) { return expose(t),\
    \ t->d; }\n\n    void apply(Node *u, Node *v, const F &x) {\n        evert(u);\n\
    \        expose(v);\n        all_apply(v, x);\n        push(v);\n    }\n\n   \
    \ S prod(Node *u, Node *v) {\n        evert(u);\n        expose(v);\n        return\
    \ v->sum;\n    }\n\n    Node *kth_parent(Node *t, int k) {\n        expose(t);\n\
    \        while (t) {\n            push(t);\n            if (t->r and t->r->sz\
    \ > k) {\n                t = t->r;\n            } else {\n                if\
    \ (t->r) k -= t->r->sz;\n                if (k == 0) return t;\n             \
    \   k--;\n                t = t->l;\n            }\n        }\n        return\
    \ nullptr;\n    }\n\n    bool is_connected(Node *u, Node *v) {\n        expose(u),\
    \ expose(v);\n        return u == v or u->p;\n    }\n};\n/* example usage:\nstruct\
    \ S {\n    int sz, sum, lhi, rhi, inhi;\n    S(int x) : sz(1), sum(x), lhi(x),\
    \ rhi(x), inhi(x) {}\n    S(int sz_, int sum_, int lhi_, int rhi_, int inhi_)\n\
    \        : sz(sz_), sum(sum_), lhi(lhi_), rhi(rhi_), inhi(inhi_) {}\n};\nusing\
    \ F = pair<bool, int>;\nS op(S l, S r) {\n    return S(l.sz + r.sz, l.sum + r.sum,\
    \ max(l.sum + r.lhi, l.lhi), max(l.rhi + r.sum, r.rhi), max<int>({l.inhi, r.inhi,\
    \ l.rhi + r.lhi}));\n}\nS reversal(S x) { return S(x.sz, x.sum, x.rhi, x.lhi,\
    \ x.inhi); }\nS mapping(F f, S x) {\n    if (f.first) {\n        auto v = f.second;\n\
    \        auto sum = x.sz * v;\n        return S{x.sz, sum, max(v, sum), max(v,\
    \ sum), max(v, sum)};\n    } else {\n        return x;\n    }\n}\nF composition(F\
    \ fnew, F gold) { return fnew.first ? fnew : gold; }\nF id() { return {false,\
    \ 0}; }\nusing LCT = lazy_linkcuttree<S, F, op, reversal, mapping, composition,\
    \ id>;\nvector<LCT::Node*> vs;\n*/\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/link_cut_tree.hpp
  requiredBy: []
  timestamp: '2021-07-23 17:14:41+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - data_structure/test/link_cut_tree.composition.test.cpp
  - data_structure/test/link_cut_tree.noncommutative2.stress.test.cpp
  - data_structure/test/link_cut_tree.noncommutative.stress.test.cpp
  - data_structure/test/link_cut_tree.sum.test.cpp
  - data_structure/test/link_cut_tree.aoj2450.test.cpp
  - data_structure/test/link_cut_tree.pathadd.stress.test.cpp
documentation_of: data_structure/link_cut_tree.hpp
layout: document
title: Link-Cut tree
---

パス上の頂点更新・パス上の頂点積取得が可能な Link-Cut tree．インターフェースを `atcoder::lazy_segtree` に寄せている．

## 使用方法

内部で `evert()` を使用する関数は根を変更してしまうので注意．

```cpp
using S = unsigned long long;
using F = tuple<>;

F id() noexcept { return {}; } // 恒等作用素
S op(S l, S r) noexcept { return l + r; } // （非可換）半群 S に入る演算
S mapping(F f, S x) noexcept { return x; } // 半群 S への F の作用
S reversal(S x) noexcept { return x; } // S の列 [x_1, ..., x_N] の積から反転させた列の積を求める
F composition(F f, F g) noexcept { return {}; } // 作用の合成
using LCT = lazy_linkcuttree<S, F, op, reversal, mapping, composition, id>;

LCT tree;
vector<LCT::Node *> vs;
vs.push_back(tree.make_node(a)); // 頂点作成
tree.link(vs[u], vs[v]); // 存在していない辺 uv を新たに張る
tree.cut(vs[u], vs[v]); // 既存の辺 uv を消す
tree.set(vs[p], a); // 頂点 p に乗る半群の元を a にする
tree.apply(vs[u], vs[v], f) // u から v までの最短パス上の各元に f を作用させる
S ret = tree.prod(vs[u], vs[v]) // u から v までの最短パス上の半群の元の積を得る
tree.evert(vs[p]); // 頂点 p を含む部分木の根を p に取る（なお上記の操作は根を勝手に変える）．
auto l = tree.lca(vs[u], vs[v]); // u, v の LCA を求める．
```

## 問題例

- [AOJ 2450: Do use segment tree](https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2450)
  - 
- [13539번: 트리와 쿼리 11](https://www.acmicpc.net/problem/13539) - `lca()`
- [16912번: 트리와 쿼리 12](https://www.acmicpc.net/problem/16912) - `is_connected()`
- [3 - 宇宙船 (Spaceships)](https://atcoder.jp/contests/joisc2013-day4/tasks/joisc2013_spaceships) `is_connected()`, `lca()`
  - [提出 #24456559 - 2013年 日本情報オリンピック春合宿 4日目](https://atcoder.jp/contests/joisc2013-day4/submissions/24456559)
- [A - かえってきたどうぶつたち と しんりんのさいせい (Return of Animals and Regeneration of Forests)](https://atcoder.jp/contests/ijpc2012-3/tasks/ijpc_animals2) `is_connected()`
  - [提出 #24457489 - IOIer Japan Programming Contest #3](https://atcoder.jp/contests/ijpc2012-3/submissions/24457489)
  - 辺に情報を持たせる代わりに，2 頂点間を内分する補助頂点を導入した．

## 参考文献・リンク・参考にした実装

- [1] D. D. Slator and R. E. Tarjan, "A data structure for dynamic trees,"
  Journal of computer and system sciences, 26(3), 362-391, 1983.
- [プログラミングコンテストでのデータ構造 2　～動的木編～](https://www.slideshare.net/iwiwi/2-12188845)
- [Link-Cut-Tree-Lazy-Path \| Luzhiled’s Library](https://ei1333.github.io/library/structure/lct/link-cut-tree-lazy-path.cpp)
