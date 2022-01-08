---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/link_cut_tree.hpp
    title: Link-Cut tree
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_path_sum
    links:
    - https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_path_sum
  bundledCode: "#line 1 \"data_structure/test/link_cut_tree.sum.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_path_sum\"\
    \n#line 2 \"data_structure/link_cut_tree.hpp\"\n\n// CUT begin\n// Link-Cut Tree\n\
    // Reference:\n// - https://www.slideshare.net/iwiwi/2-12188845\n// - https://ei1333.github.io/library/structure/lct/link-cut-tree-lazy-path.cpp\n\
    template <class S, class F, S (*op)(S, S), S (*reversal)(S), S (*mapping)(F, S),\n\
    \          F (*composition)(F, F), F (*id)()>\nclass lazy_linkcuttree {\npublic:\n\
    \    struct Node {\n        Node *l, *r, *p;\n        S d, sum;\n        F lz;\n\
    \        bool is_reversed;\n        int sz;\n        Node(S val)\n           \
    \ : l(nullptr), r(nullptr), p(nullptr), d(val), sum(val), lz(id()), is_reversed(false),\n\
    \              sz(1) {}\n        bool is_root() const { return !p || (p->l !=\
    \ this and p->r != this); }\n        template <class OStream> friend OStream &operator<<(OStream\
    \ &os, const Node &n) {\n            os << '[';\n            if (n.l) os << *(n.l)\
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
    \ max(l.sum + r.lhi, l.lhi), max(l.rhi + r.sum, r.rhi),\nmax<int>({l.inhi, r.inhi,\
    \ l.rhi + r.lhi}));\n}\nS reversal(S x) { return S(x.sz, x.sum, x.rhi, x.lhi,\
    \ x.inhi); }\nS mapping(F f, S x) {\n    if (f.first) {\n        auto v = f.second;\n\
    \        auto sum = x.sz * v;\n        return S{x.sz, sum, max(v, sum), max(v,\
    \ sum), max(v, sum)};\n    } else {\n        return x;\n    }\n}\nF composition(F\
    \ fnew, F gold) { return fnew.first ? fnew : gold; }\nF id() { return {false,\
    \ 0}; }\nusing LCT = lazy_linkcuttree<S, F, op, reversal, mapping, composition,\
    \ id>;\nvector<LCT::Node*> vs;\n*/\n#line 3 \"data_structure/test/link_cut_tree.sum.test.cpp\"\
    \n#include <iostream>\n#include <tuple>\n#include <utility>\n#include <vector>\n\
    using namespace std;\n\nusing S = unsigned long long;\nusing F = tuple<>;\n\n\
    F id() noexcept { return {}; }\nS op(S l, S r) noexcept { return l + r; }\nS mapping(F\
    \ f, S x) noexcept { return x; }\nS reversal(S x) noexcept { return x; }\nF composition(F\
    \ f, F g) noexcept { return {}; }\nusing LCT = lazy_linkcuttree<S, F, op, reversal,\
    \ mapping, composition, id>;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \    int N, Q;\n    cin >> N >> Q;\n    LCT lct;\n    vector<LCT::Node *> vs;\n\
    \    vector<unsigned long long> A(N);\n    for (auto &a : A) {\n        cin >>\
    \ a;\n        vs.push_back(lct.make_node(a));\n    }\n    for (int e = 0; e <\
    \ N - 1; e++) {\n        int u, v;\n        cin >> u >> v;\n        lct.link(vs[u],\
    \ vs[v]);\n    }\n    while (Q--) {\n        int tp;\n        cin >> tp;\n   \
    \     if (tp == 0) {\n            int u, v, w, x;\n            cin >> u >> v >>\
    \ w >> x;\n            lct.cut(vs[u], vs[v]);\n            lct.link(vs[w], vs[x]);\n\
    \        }\n        if (tp == 1) {\n            int p, x;\n            cin >>\
    \ p >> x;\n            A[p] += x;\n            lct.set(vs[p], A[p]);\n       \
    \ }\n        if (tp == 2) {\n            int u, v;\n            cin >> u >> v;\n\
    \            cout << lct.prod(vs[u], vs[v]) << '\\n';\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_path_sum\"\
    \n#include \"../link_cut_tree.hpp\"\n#include <iostream>\n#include <tuple>\n#include\
    \ <utility>\n#include <vector>\nusing namespace std;\n\nusing S = unsigned long\
    \ long;\nusing F = tuple<>;\n\nF id() noexcept { return {}; }\nS op(S l, S r)\
    \ noexcept { return l + r; }\nS mapping(F f, S x) noexcept { return x; }\nS reversal(S\
    \ x) noexcept { return x; }\nF composition(F f, F g) noexcept { return {}; }\n\
    using LCT = lazy_linkcuttree<S, F, op, reversal, mapping, composition, id>;\n\n\
    int main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n    int N, Q;\n\
    \    cin >> N >> Q;\n    LCT lct;\n    vector<LCT::Node *> vs;\n    vector<unsigned\
    \ long long> A(N);\n    for (auto &a : A) {\n        cin >> a;\n        vs.push_back(lct.make_node(a));\n\
    \    }\n    for (int e = 0; e < N - 1; e++) {\n        int u, v;\n        cin\
    \ >> u >> v;\n        lct.link(vs[u], vs[v]);\n    }\n    while (Q--) {\n    \
    \    int tp;\n        cin >> tp;\n        if (tp == 0) {\n            int u, v,\
    \ w, x;\n            cin >> u >> v >> w >> x;\n            lct.cut(vs[u], vs[v]);\n\
    \            lct.link(vs[w], vs[x]);\n        }\n        if (tp == 1) {\n    \
    \        int p, x;\n            cin >> p >> x;\n            A[p] += x;\n     \
    \       lct.set(vs[p], A[p]);\n        }\n        if (tp == 2) {\n           \
    \ int u, v;\n            cin >> u >> v;\n            cout << lct.prod(vs[u], vs[v])\
    \ << '\\n';\n        }\n    }\n}\n"
  dependsOn:
  - data_structure/link_cut_tree.hpp
  isVerificationFile: true
  path: data_structure/test/link_cut_tree.sum.test.cpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: data_structure/test/link_cut_tree.sum.test.cpp
layout: document
redirect_from:
- /verify/data_structure/test/link_cut_tree.sum.test.cpp
- /verify/data_structure/test/link_cut_tree.sum.test.cpp.html
title: data_structure/test/link_cut_tree.sum.test.cpp
---
