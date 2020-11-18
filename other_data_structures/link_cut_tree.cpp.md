---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"other_data_structures/link_cut_tree.cpp\"\n#include <bits/stdc++.h>\n\
    using namespace std;\n#define FOR(i, begin, end) for (int i = (begin), i##_end_\
    \ = (end); i < i##_end_; i++)\n#define REP(i, n) FOR(i, 0, n)\n\n// using VAL\
    \ = pair<lint, lint>;\nusing VAL = long long;\nusing LAZY = long long;\nconstexpr\
    \ LAZY lazy_0 = 0;\nstruct LinkCutTree {\n    struct Node {\n        Node *l,\
    \ *r, *p;\n        VAL key;\n        LAZY lazy;\n        bool is_reversed;\n \
    \       uint32_t sz;\n        Node(VAL val) : l(nullptr), r(nullptr), p(nullptr),\
    \ key(val), lazy(lazy_0), is_reversed(false), sz(1) {}\n        bool is_root()\
    \ const { return !p || (p->l != this and p->r != this); }\n        friend ostream\
    \ &operator<<(ostream &os, const Node &n) {\n            os << \"[\";\n      \
    \      if (n.l) os << *(n.l) << \",\";\n            os << n.key << \",\";\n  \
    \          if (n.r) os << *(n.r);\n            os << \"]\";\n            return\
    \ os;\n        }\n    };\n    inline Node *_revise_val(Node *t) {\n        if\
    \ (t) {\n            t->sz = 1;\n            // t->key.second = t->key.first;\n\
    \            if (t->l) {\n                t->sz += t->l->sz;\n               \
    \ // t->key.second += t->l->key.second;\n            }\n            if (t->r)\
    \ {\n                t->sz += t->r->sz;\n                // t->key.second += t->r->key.second;\n\
    \            }\n        }\n        return t;\n    }\n    inline void _propagate_lazy(LAZY\
    \ &a, LAZY b) // \u9045\u5EF6\u8A55\u4FA1\u4F1D\u64AD\n    {\n        a += b;\n\
    \    }\n    inline void _reflect_lazy(Node *a, LAZY b) // \u9045\u5EF6\u8A55\u4FA1\
    \u53CD\u6620\n    {\n        // a->key.first += b;\n        // a->key.second +=\
    \ a->sz * b;\n        a->key += b;\n    }\n    inline void _toggle(Node *t) {\n\
    \        swap(t->l, t->r);\n        /* key/lazy modification here */\n       \
    \ t->is_reversed ^= true;\n    }\n\n    inline void _resolve_lazy(Node *&t) //\
    \ \u5BFE\u8C61\u306E\u9045\u5EF6\u8A55\u4FA1\u3092\u89E3\u6C7A\n    {\n      \
    \  if (t and t->lazy != lazy_0) {\n            if (t->l) _propagate_lazy(t->l->lazy,\
    \ t->lazy);\n            if (t->r) _propagate_lazy(t->r->lazy, t->lazy);\n   \
    \         _reflect_lazy(t, t->lazy);\n            t->lazy = lazy_0;\n        }\n\
    \        if (t->is_reversed) {\n            if (t->l) _toggle(t->l);\n       \
    \     if (t->r) _toggle(t->r);\n            t->is_reversed = false;\n        }\n\
    \    }\n\n    void _rot_r(Node *t) {\n        Node *x = t->p, *y = x->p;\n   \
    \     if ((x->l = t->r)) t->r->p = x;\n        t->r = x, x->p = t;\n        _revise_val(x),\
    \ _revise_val(t);\n        if ((t->p = y)) {\n            if (y->l == x) y->l\
    \ = t;\n            if (y->r == x) y->r = t;\n            _revise_val(y);\n  \
    \      }\n    }\n    void _rot_l(Node *t) {\n        Node *x = t->p, *y = x->p;\n\
    \        if ((x->r = t->l)) t->l->p = x;\n        t->l = x, x->p = t;\n      \
    \  _revise_val(x), _revise_val(t);\n        if ((t->p = y)) {\n            if\
    \ (y->l == x) y->l = t;\n            if (y->r == x) y->r = t;\n            _revise_val(y);\n\
    \        }\n    }\n\n    void _splay(Node *t) {\n        _resolve_lazy(t);\n \
    \       while (!t->is_root()) {\n            Node *q = t->p;\n            if (q->is_root())\
    \ {\n                _resolve_lazy(q), _resolve_lazy(t);\n                if (q->l\
    \ == t)\n                    _rot_r(t);\n                else\n              \
    \      _rot_l(t);\n            } else {\n                Node *r = q->p;\n   \
    \             _resolve_lazy(r), _resolve_lazy(q), _resolve_lazy(t);\n        \
    \        if (r->l == q) {\n                    if (q->l == t)\n              \
    \          _rot_r(q), _rot_r(t);\n                    else\n                 \
    \       _rot_l(t), _rot_r(t);\n                } else {\n                    if\
    \ (q->r == t)\n                        _rot_l(q), _rot_l(t);\n               \
    \     else\n                        _rot_r(t), _rot_l(t);\n                }\n\
    \            }\n        }\n    }\n\n    Node *make_node(VAL val) { return new\
    \ Node(val); }\n\n    Node *expose(Node *t) {\n        Node *rp = nullptr;\n \
    \       for (Node *cur = t; cur; cur = cur->p) {\n            _splay(cur);\n \
    \           cur->r = rp;\n            _revise_val(cur);\n            rp = cur;\n\
    \        }\n        _splay(t);\n        return rp;\n    }\n    void link(Node\
    \ *chi, Node *par) {\n        expose(chi);\n        expose(par);\n        chi->p\
    \ = par;\n        par->r = chi;\n        _revise_val(par);\n    }\n    void cut(Node\
    \ *chi) {\n        expose(chi);\n        Node *par = chi->l;\n        chi->l =\
    \ nullptr;\n        _revise_val(chi);\n        par->p = nullptr;\n    }\n    void\
    \ evert(Node *t) {\n        expose(t);\n        _toggle(t);\n        _resolve_lazy(t);\n\
    \    }\n    Node *lca(Node *u, Node *v) {\n        expose(u);\n        return\
    \ expose(v);\n    }\n    void add_lazy(Node *t, const LAZY &x) {\n        expose(t);\n\
    \        _propagate_lazy(t->lazy, x);\n        _resolve_lazy(t);\n    }\n};\n\n\
    int main() {\n    std::cin.tie(nullptr), std::ios::sync_with_stdio(false);\n \
    \   int N;\n    cin >> N;\n    LinkCutTree lct;\n    vector<LinkCutTree::Node\
    \ *> vec(N);\n    REP(i, N) vec[i] = lct.make_node(i);\n    REP(i, N) {\n    \
    \    int K;\n        cin >> K;\n        REP(_, K) {\n            int T;\n    \
    \        cin >> T;\n            lct.link(vec[i], vec[T]);\n        }\n    }\n\
    \    int Q;\n    cin >> Q;\n    REP(_, Q) {\n        int U, V;\n        cin >>\
    \ U >> V;\n        cout << lct.lca(vec[V], vec[U])->key << endl;\n    }\n}\n"
  code: "#include <bits/stdc++.h>\nusing namespace std;\n#define FOR(i, begin, end)\
    \ for (int i = (begin), i##_end_ = (end); i < i##_end_; i++)\n#define REP(i, n)\
    \ FOR(i, 0, n)\n\n// using VAL = pair<lint, lint>;\nusing VAL = long long;\nusing\
    \ LAZY = long long;\nconstexpr LAZY lazy_0 = 0;\nstruct LinkCutTree {\n    struct\
    \ Node {\n        Node *l, *r, *p;\n        VAL key;\n        LAZY lazy;\n   \
    \     bool is_reversed;\n        uint32_t sz;\n        Node(VAL val) : l(nullptr),\
    \ r(nullptr), p(nullptr), key(val), lazy(lazy_0), is_reversed(false), sz(1) {}\n\
    \        bool is_root() const { return !p || (p->l != this and p->r != this);\
    \ }\n        friend ostream &operator<<(ostream &os, const Node &n) {\n      \
    \      os << \"[\";\n            if (n.l) os << *(n.l) << \",\";\n           \
    \ os << n.key << \",\";\n            if (n.r) os << *(n.r);\n            os <<\
    \ \"]\";\n            return os;\n        }\n    };\n    inline Node *_revise_val(Node\
    \ *t) {\n        if (t) {\n            t->sz = 1;\n            // t->key.second\
    \ = t->key.first;\n            if (t->l) {\n                t->sz += t->l->sz;\n\
    \                // t->key.second += t->l->key.second;\n            }\n      \
    \      if (t->r) {\n                t->sz += t->r->sz;\n                // t->key.second\
    \ += t->r->key.second;\n            }\n        }\n        return t;\n    }\n \
    \   inline void _propagate_lazy(LAZY &a, LAZY b) // \u9045\u5EF6\u8A55\u4FA1\u4F1D\
    \u64AD\n    {\n        a += b;\n    }\n    inline void _reflect_lazy(Node *a,\
    \ LAZY b) // \u9045\u5EF6\u8A55\u4FA1\u53CD\u6620\n    {\n        // a->key.first\
    \ += b;\n        // a->key.second += a->sz * b;\n        a->key += b;\n    }\n\
    \    inline void _toggle(Node *t) {\n        swap(t->l, t->r);\n        /* key/lazy\
    \ modification here */\n        t->is_reversed ^= true;\n    }\n\n    inline void\
    \ _resolve_lazy(Node *&t) // \u5BFE\u8C61\u306E\u9045\u5EF6\u8A55\u4FA1\u3092\u89E3\
    \u6C7A\n    {\n        if (t and t->lazy != lazy_0) {\n            if (t->l) _propagate_lazy(t->l->lazy,\
    \ t->lazy);\n            if (t->r) _propagate_lazy(t->r->lazy, t->lazy);\n   \
    \         _reflect_lazy(t, t->lazy);\n            t->lazy = lazy_0;\n        }\n\
    \        if (t->is_reversed) {\n            if (t->l) _toggle(t->l);\n       \
    \     if (t->r) _toggle(t->r);\n            t->is_reversed = false;\n        }\n\
    \    }\n\n    void _rot_r(Node *t) {\n        Node *x = t->p, *y = x->p;\n   \
    \     if ((x->l = t->r)) t->r->p = x;\n        t->r = x, x->p = t;\n        _revise_val(x),\
    \ _revise_val(t);\n        if ((t->p = y)) {\n            if (y->l == x) y->l\
    \ = t;\n            if (y->r == x) y->r = t;\n            _revise_val(y);\n  \
    \      }\n    }\n    void _rot_l(Node *t) {\n        Node *x = t->p, *y = x->p;\n\
    \        if ((x->r = t->l)) t->l->p = x;\n        t->l = x, x->p = t;\n      \
    \  _revise_val(x), _revise_val(t);\n        if ((t->p = y)) {\n            if\
    \ (y->l == x) y->l = t;\n            if (y->r == x) y->r = t;\n            _revise_val(y);\n\
    \        }\n    }\n\n    void _splay(Node *t) {\n        _resolve_lazy(t);\n \
    \       while (!t->is_root()) {\n            Node *q = t->p;\n            if (q->is_root())\
    \ {\n                _resolve_lazy(q), _resolve_lazy(t);\n                if (q->l\
    \ == t)\n                    _rot_r(t);\n                else\n              \
    \      _rot_l(t);\n            } else {\n                Node *r = q->p;\n   \
    \             _resolve_lazy(r), _resolve_lazy(q), _resolve_lazy(t);\n        \
    \        if (r->l == q) {\n                    if (q->l == t)\n              \
    \          _rot_r(q), _rot_r(t);\n                    else\n                 \
    \       _rot_l(t), _rot_r(t);\n                } else {\n                    if\
    \ (q->r == t)\n                        _rot_l(q), _rot_l(t);\n               \
    \     else\n                        _rot_r(t), _rot_l(t);\n                }\n\
    \            }\n        }\n    }\n\n    Node *make_node(VAL val) { return new\
    \ Node(val); }\n\n    Node *expose(Node *t) {\n        Node *rp = nullptr;\n \
    \       for (Node *cur = t; cur; cur = cur->p) {\n            _splay(cur);\n \
    \           cur->r = rp;\n            _revise_val(cur);\n            rp = cur;\n\
    \        }\n        _splay(t);\n        return rp;\n    }\n    void link(Node\
    \ *chi, Node *par) {\n        expose(chi);\n        expose(par);\n        chi->p\
    \ = par;\n        par->r = chi;\n        _revise_val(par);\n    }\n    void cut(Node\
    \ *chi) {\n        expose(chi);\n        Node *par = chi->l;\n        chi->l =\
    \ nullptr;\n        _revise_val(chi);\n        par->p = nullptr;\n    }\n    void\
    \ evert(Node *t) {\n        expose(t);\n        _toggle(t);\n        _resolve_lazy(t);\n\
    \    }\n    Node *lca(Node *u, Node *v) {\n        expose(u);\n        return\
    \ expose(v);\n    }\n    void add_lazy(Node *t, const LAZY &x) {\n        expose(t);\n\
    \        _propagate_lazy(t->lazy, x);\n        _resolve_lazy(t);\n    }\n};\n\n\
    int main() {\n    std::cin.tie(nullptr), std::ios::sync_with_stdio(false);\n \
    \   int N;\n    cin >> N;\n    LinkCutTree lct;\n    vector<LinkCutTree::Node\
    \ *> vec(N);\n    REP(i, N) vec[i] = lct.make_node(i);\n    REP(i, N) {\n    \
    \    int K;\n        cin >> K;\n        REP(_, K) {\n            int T;\n    \
    \        cin >> T;\n            lct.link(vec[i], vec[T]);\n        }\n    }\n\
    \    int Q;\n    cin >> Q;\n    REP(_, Q) {\n        int U, V;\n        cin >>\
    \ U >> V;\n        cout << lct.lca(vec[V], vec[U])->key << endl;\n    }\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: other_data_structures/link_cut_tree.cpp
  requiredBy: []
  timestamp: '2020-11-18 20:33:55+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: other_data_structures/link_cut_tree.cpp
layout: document
redirect_from:
- /library/other_data_structures/link_cut_tree.cpp
- /library/other_data_structures/link_cut_tree.cpp.html
title: other_data_structures/link_cut_tree.cpp
---
