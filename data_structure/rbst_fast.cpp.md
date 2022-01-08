---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"data_structure/rbst_fast.cpp\"\n// Persistent Randomized\
    \ Binary Search Tree\n// Verified : ARC033C\u30FBARC030D\n\n#include <bits/stdc++.h>\n\
    using namespace std;\n#define FOR(i, begin, end) for (int i = (begin); i < (end);\
    \ i++)\n#define REP(i, n) FOR(i, 0, n)\n\nusing lint = long long;\nstruct node\
    \ {\n    lint val, sum;\n    node() : val(0), sum(0) {}\n    node(lint v) : val(v),\
    \ sum(v) {}\n};\n\nusing VAL = node;\nusing DVAL = lint;\ntemplate <uint32_t len>\
    \ struct RandomizedBinarySearchTree {\n    // Do your RuBeSTy! \u2312\xB0( \u30FB\
    \u03C9\u30FB)\xB0\u2312\n    /*\n    struct rand_int_ // non-deterministic\n \
    \   {\n        mt19937 mt;\n        rand_int_() : mt(chrono::steady_clock::now().time_since_epoch().count())\
    \ {}\n        lint operator()(lint x) { return this->operator()(0, x); } // [0,\
    \ x)\n        lint operator()(lint l, lint r) {\n            uniform_int_distribution<lint>\
    \ d(l, r - 1);\n            return d(mt);\n        }\n        lint operator()()\
    \ { return this->operator()(1e8); }\n    } _rand;\n    /*/\n    inline uint32_t\
    \ _rand() // XorShift\n    {\n        static uint32_t x = 123456789, y = 362436069,\
    \ z = 521288629, w = 88675123;\n        uint32_t t = x ^ (x << 11);\n        x\
    \ = y;\n        y = z;\n        z = w;\n        return w = (w ^ (w >> 19)) ^ (t\
    \ ^ (t >> 8));\n    }\n    // */\n\n    // \u5404\u30CE\u30FC\u30C9\u306B\u6301\
    \u305F\u305B\u308B\u30C7\u30FC\u30BF\u578B\u3068\u4EE3\u6570\u69CB\u9020\n   \
    \ DVAL Idval;\n    struct Node {\n        Node *l, *r;\n        uint32_t sz; //\
    \ \u81EA\u8EAB\u3092\u9802\u70B9\u3068\u3059\u308B\u90E8\u5206\u6728\u306E\u30B5\
    \u30A4\u30BA\n        VAL val; // \u81EA\u8EAB\u304Croot\u306E\u90E8\u5206\u6728\
    \u3092\u8A18\u8FF0, dval==Idval\u306E\u3068\u304D\u306E\u307F\u5358\u72EC\u3067\
    \u610F\u5473\u3092\u6301\u3064\n        DVAL dval; // \u81EA\u8EAB\u3068\u305D\
    \u306E\u90E8\u5206\u6728\u306B\u5BFE\u3059\u308B\u9045\u5EF6\u8A55\u4FA1\n   \
    \     Node(const VAL &v, const DVAL &dv) : l(nullptr), r(nullptr), sz(1), val(v),\
    \ dval(dv) {}\n        Node() {}\n    };\n    inline Node *_revise_val(Node *t)\
    \ // \uFF08t\u306E\u5B50\u306B\u95A2\u3059\u308B\u5916\u7684\u64CD\u4F5C\u5F8C\
    \u306B\u547C\u3093\u3067\uFF09sz\u3068val\u3092\u9069\u5207\u306B\u76F4\u3059\n\
    \                                      // t\u306E\u5B50\u306E\u9045\u5EF6\u8A55\
    \u4FA1\u304C\u6E08\u3093\u3067\u3044\u308B\u3068\u306F\u9650\u3089\u306A\u3044\
    \n    {\n        if (t) {\n            t->sz = size(t->l) + size(t->r) + 1;\n\
    \            t->val.sum = t->val.val + (t->l ? t->l->val.sum + t->l->sz * t->l->dval\
    \ : 0) +\n                         (t->r ? t->r->val.sum + t->r->sz * t->r->dval\
    \ : 0);\n        };\n        return t;\n    }\n    inline void _propagate_dval(DVAL\
    \ &a, DVAL b) // \u9045\u5EF6\u8A55\u4FA1\u4F1D\u64AD\n    {\n        a += b;\n\
    \    }\n    inline void _reflect_dval(Node *a, DVAL b) // \u9045\u5EF6\u8A55\u4FA1\
    \u53CD\u6620\n    {\n        a->val.val += b;\n        a->val.sum += a->sz * b;\n\
    \    }\n    vector<Node> data;\n    uint32_t d_ptr;\n\n    RandomizedBinarySearchTree(DVAL\
    \ idval) : Idval(idval), d_ptr(0) { data.resize(len); }\n\n    Node *new_tree()\
    \ { return nullptr; } // \u65B0\u305F\u306A\u6728\u3092\u4F5C\u6210\n    static\
    \ inline uint32_t size(const Node *t) { return t ? t->sz : 0; }\n    inline int\
    \ mem_used() { return (int)d_ptr; }\n    inline bool empty(Node *t) { return !t;\
    \ }\n    inline Node *_make_node(const VAL &val) {\n        if (d_ptr >= len)\
    \ exit(1);\n        return &(data[d_ptr++] = Node(val, Idval));\n    }\n    virtual\
    \ void _duplicate_node(Node *&) {}\n\n    inline void _resolve_dval(Node *&t)\
    \ // \u5BFE\u8C61\u306E\u9045\u5EF6\u8A55\u4FA1\u3092\u89E3\u6C7A\n    {\n   \
    \     if (!t) return;\n        _duplicate_node(t);\n        if (t->dval != Idval)\
    \ {\n            if (t->l) {\n                _duplicate_node(t->l);\n       \
    \         _propagate_dval(t->l->dval, t->dval);\n            }\n            if\
    \ (t->r) {\n                _duplicate_node(t->r);\n                _propagate_dval(t->r->dval,\
    \ t->dval);\n            }\n            _reflect_dval(t, t->dval);\n         \
    \   t->dval = Idval;\n        }\n    }\n\n    // l\u3068r\u3092root\u3068\u3059\
    \u308B\u6728\u540C\u58EB\u3092\u7D50\u5408\u3057\u3066\uFF0C\u65B0\u305F\u306A\
    root\u3092\u8FD4\u3059\n    Node *merge(Node *l, Node *r) {\n        if (l ==\
    \ nullptr || r == nullptr) return l ? l : r;\n        if (_rand() % (l->sz + r->sz)\
    \ < l->sz) {\n            _resolve_dval(l);\n            l->r = merge(l->r, r);\n\
    \            return _revise_val(l);\n        } else {\n            _resolve_dval(r);\n\
    \            r->l = merge(l, r->l);\n            return _revise_val(r);\n    \
    \    }\n    }\n\n    // [0, k)\u306E\u6728\u3068[k, root->size())\u306E\u6728\u306B\
    \u5206\u3051\u3066\u5404root\n    // \uFF08\u90E8\u5206\u6728\u306E\u8981\u7D20\
    \u6570\u304C0\u306A\u3089nullptr\uFF09\u3092\u8FD4\u3059\n    pair<Node *, Node\
    \ *> split(Node *&root, int k) // root\u306E\u5B50\u5B6B\u304B\u3089\u3042\u3068\
    k\u500B\u6B32\u3057\u3044\n    {\n        if (root == nullptr) return make_pair(nullptr,\
    \ nullptr);\n        _resolve_dval(root);\n        if (k <= (int)size(root->l))\
    \ // left\u304B\u3089k\u500B\u62FE\u3048\u308B\n        {\n            auto p\
    \ = split(root->l, k);\n            root->l = p.second;\n            return make_pair(p.first,\
    \ _revise_val(root));\n        } else {\n            auto p = split(root->r, k\
    \ - size(root->l) - 1);\n            root->r = p.first;\n            return make_pair(_revise_val(root),\
    \ p.second);\n        }\n    }\n\n    // 0-indexed\u3067array[pos]\u306E\u624B\
    \u524D\u306B\u65B0\u305F\u306A\u8981\u7D20newval\u3092\u633F\u5165\u3059\u308B\
    \n    void insert(Node *&root, int pos, const VAL &newval) {\n        auto p =\
    \ split(root, pos);\n        root = merge(p.first, merge(_make_node(newval), p.second));\n\
    \    }\n\n    // 0-indexed\u3067array[pos]\u3092\u524A\u9664\u3059\u308B\uFF08\
    \u5148\u982D\u304B\u3089pos+1\u500B\u76EE\u306E\u8981\u7D20\uFF09\n    void erase(Node\
    \ *&root, int pos) {\n        auto p = split(root, pos);\n        auto p2 = split(p.second,\
    \ 1);\n        root = merge(p.first, p2.second);\n    }\n\n    // 1\u70B9\u66F4\
    \u65B0 array[pos].val\u306Bupdval\u3092\u5165\u308C\u308B\n    void set(Node *&root,\
    \ int pos, const VAL &updval) {\n        auto p = split(root, pos);\n        auto\
    \ p2 = split(p.second, 1);\n        root = merge(p.first, merge(_make_node(updval),\
    \ p2.second));\n    }\n\n    // \u9045\u5EF6\u8A55\u4FA1\u3092\u5229\u7528\u3057\
    \u305F\u7BC4\u56F2\u66F4\u65B0 [l, r)\n    void range_set(Node *&root, int l,\
    \ int r, const DVAL &adddval) {\n        auto p = split(root, l);\n        auto\
    \ p2 = split(p.second, r - l);\n        _propagate_dval(p2.first->dval, adddval);\n\
    \        root = merge(p.first, merge(p2.first, p2.second));\n    }\n\n    // array[pos].val\u3092\
    \u53D6\u5F97\u3059\u308B\n    Node range_get(Node *&root, int l, int r) {\n  \
    \      auto p = split(root, l);\n        auto p2 = split(p.second, r - l);\n \
    \       _resolve_dval(p2.first);\n        Node res = *p2.first;\n        root\
    \ = merge(p.first, merge(p2.first, p2.second));\n        return res;\n    }\n\
    \    Node get(Node *&root, int pos) { return range_get(root, pos, pos + 1); }\n\
    \n    // \u666E\u901A\u306Elower_bound\n    int lower_bound(Node *root, const\
    \ VAL &v) {\n        if (root == nullptr) return 0;\n        return (v <= root->val)\
    \ ? lower_bound(root->l, v)\n                                : lower_bound(root->r,\
    \ v) + size(root->l) + 1;\n    }\n\n    // \u30C7\u30FC\u30BF\u3092\u58CA\u3057\
    \u3066\u65B0\u898F\u306Binit\u306E\u5185\u5BB9\u3092\u8A70\u3081\u308B\n    void\
    \ assign(Node *&root, const vector<VAL> &init) {\n        d_ptr = 0;\n       \
    \ int N = init.size();\n        root = N ? _assign_range(0, N, init) : new_tree();\n\
    \    }\n    Node *_assign_range(int l, int r, const vector<VAL> &init) {\n   \
    \     if (r - l == 1) {\n            auto t = _make_node(init[l]);\n         \
    \   return _revise_val(t);\n        }\n        return merge(_assign_range(l, (l\
    \ + r) / 2, init), _assign_range((l + r) / 2, r, init));\n    }\n\n    // \u30C7\
    \u30FC\u30BF\u3092vec\u3078\u66F8\u304D\u51FA\u3057\n    void dump(Node *t, vector<VAL>\
    \ &vec) {\n        if (t == nullptr) return;\n        _resolve_dval(t);\n    \
    \    dump(t->l, vec);\n        vec.push_back(t->val);\n        dump(t->r, vec);\n\
    \    }\n\n    // gc\n    void re_alloc(Node *&root) {\n        vector<VAL> mem;\n\
    \        dump(root, mem);\n        assign(root, mem);\n    }\n};\n\n// \u6C38\u7D9A\
    \u5316\ntemplate <uint32_t len> struct PersistentRBST : RandomizedBinarySearchTree<len>\
    \ {\n    using RBST = RandomizedBinarySearchTree<len>;\n    using Node = typename\
    \ RBST::Node;\n    PersistentRBST(DVAL idval) : RBST(idval) {}\n\n    void _duplicate_node(Node\
    \ *&t) override {\n        if (t == nullptr) return;\n        if (RBST::d_ptr\
    \ >= len) exit(1);\n        t = &(RBST::data[RBST::d_ptr++] = *t);\n    }\n\n\
    \    void copy(Node *&root, int l, int d, int target_l) // [target_l, )\u306B\
    [l, l+d)\u306E\u5024\u3092\u5165\u308C\u308B\n    {\n        auto p1 = RBST::split(root,\
    \ l);\n        auto p2 = RBST::split(p1.second, d);\n        root = RBST::merge(p1.first,\
    \ RBST::merge(p2.first, p2.second));\n        auto p3 = RBST::split(root, target_l);\n\
    \        auto p4 = RBST::split(p3.second, d);\n        root = RBST::merge(p3.first,\
    \ RBST::merge(p2.first, p4.second));\n    }\n};\n\nint main() {\n    constexpr\
    \ int mem_size = 13000000;\n    PersistentRBST<mem_size> rbst(0LL);\n\n    auto\
    \ S = rbst.new_tree();\n    int N, Q;\n    cin >> N >> Q;\n    REP(i, N) {\n \
    \       int xi;\n        cin >> xi;\n        rbst.insert(S, i, node(xi));\n  \
    \  }\n\n    REP(_, Q) {\n        int type, a, b, c, d, v;\n        cin >> type;\n\
    \        if (type == 1) {\n            cin >> a >> b >> v;\n            rbst.range_set(S,\
    \ a - 1, b, (lint)v);\n        }\n        if (type == 2) {\n            cin >>\
    \ a >> b >> c >> d;\n            rbst.copy(S, c - 1, b - a + 1, a - 1);\n    \
    \    }\n        if (type == 3) {\n            cin >> a >> b;\n            cout\
    \ << rbst.range_get(S, a - 1, b).val.sum << endl;\n        }\n        if (rbst.mem_used()\
    \ > mem_size * 0.8) rbst.re_alloc(S);\n    }\n}\n"
  code: "// Persistent Randomized Binary Search Tree\n// Verified : ARC033C\u30FB\
    ARC030D\n\n#include <bits/stdc++.h>\nusing namespace std;\n#define FOR(i, begin,\
    \ end) for (int i = (begin); i < (end); i++)\n#define REP(i, n) FOR(i, 0, n)\n\
    \nusing lint = long long;\nstruct node {\n    lint val, sum;\n    node() : val(0),\
    \ sum(0) {}\n    node(lint v) : val(v), sum(v) {}\n};\n\nusing VAL = node;\nusing\
    \ DVAL = lint;\ntemplate <uint32_t len> struct RandomizedBinarySearchTree {\n\
    \    // Do your RuBeSTy! \u2312\xB0( \u30FB\u03C9\u30FB)\xB0\u2312\n    /*\n \
    \   struct rand_int_ // non-deterministic\n    {\n        mt19937 mt;\n      \
    \  rand_int_() : mt(chrono::steady_clock::now().time_since_epoch().count()) {}\n\
    \        lint operator()(lint x) { return this->operator()(0, x); } // [0, x)\n\
    \        lint operator()(lint l, lint r) {\n            uniform_int_distribution<lint>\
    \ d(l, r - 1);\n            return d(mt);\n        }\n        lint operator()()\
    \ { return this->operator()(1e8); }\n    } _rand;\n    /*/\n    inline uint32_t\
    \ _rand() // XorShift\n    {\n        static uint32_t x = 123456789, y = 362436069,\
    \ z = 521288629, w = 88675123;\n        uint32_t t = x ^ (x << 11);\n        x\
    \ = y;\n        y = z;\n        z = w;\n        return w = (w ^ (w >> 19)) ^ (t\
    \ ^ (t >> 8));\n    }\n    // */\n\n    // \u5404\u30CE\u30FC\u30C9\u306B\u6301\
    \u305F\u305B\u308B\u30C7\u30FC\u30BF\u578B\u3068\u4EE3\u6570\u69CB\u9020\n   \
    \ DVAL Idval;\n    struct Node {\n        Node *l, *r;\n        uint32_t sz; //\
    \ \u81EA\u8EAB\u3092\u9802\u70B9\u3068\u3059\u308B\u90E8\u5206\u6728\u306E\u30B5\
    \u30A4\u30BA\n        VAL val; // \u81EA\u8EAB\u304Croot\u306E\u90E8\u5206\u6728\
    \u3092\u8A18\u8FF0, dval==Idval\u306E\u3068\u304D\u306E\u307F\u5358\u72EC\u3067\
    \u610F\u5473\u3092\u6301\u3064\n        DVAL dval; // \u81EA\u8EAB\u3068\u305D\
    \u306E\u90E8\u5206\u6728\u306B\u5BFE\u3059\u308B\u9045\u5EF6\u8A55\u4FA1\n   \
    \     Node(const VAL &v, const DVAL &dv) : l(nullptr), r(nullptr), sz(1), val(v),\
    \ dval(dv) {}\n        Node() {}\n    };\n    inline Node *_revise_val(Node *t)\
    \ // \uFF08t\u306E\u5B50\u306B\u95A2\u3059\u308B\u5916\u7684\u64CD\u4F5C\u5F8C\
    \u306B\u547C\u3093\u3067\uFF09sz\u3068val\u3092\u9069\u5207\u306B\u76F4\u3059\n\
    \                                      // t\u306E\u5B50\u306E\u9045\u5EF6\u8A55\
    \u4FA1\u304C\u6E08\u3093\u3067\u3044\u308B\u3068\u306F\u9650\u3089\u306A\u3044\
    \n    {\n        if (t) {\n            t->sz = size(t->l) + size(t->r) + 1;\n\
    \            t->val.sum = t->val.val + (t->l ? t->l->val.sum + t->l->sz * t->l->dval\
    \ : 0) +\n                         (t->r ? t->r->val.sum + t->r->sz * t->r->dval\
    \ : 0);\n        };\n        return t;\n    }\n    inline void _propagate_dval(DVAL\
    \ &a, DVAL b) // \u9045\u5EF6\u8A55\u4FA1\u4F1D\u64AD\n    {\n        a += b;\n\
    \    }\n    inline void _reflect_dval(Node *a, DVAL b) // \u9045\u5EF6\u8A55\u4FA1\
    \u53CD\u6620\n    {\n        a->val.val += b;\n        a->val.sum += a->sz * b;\n\
    \    }\n    vector<Node> data;\n    uint32_t d_ptr;\n\n    RandomizedBinarySearchTree(DVAL\
    \ idval) : Idval(idval), d_ptr(0) { data.resize(len); }\n\n    Node *new_tree()\
    \ { return nullptr; } // \u65B0\u305F\u306A\u6728\u3092\u4F5C\u6210\n    static\
    \ inline uint32_t size(const Node *t) { return t ? t->sz : 0; }\n    inline int\
    \ mem_used() { return (int)d_ptr; }\n    inline bool empty(Node *t) { return !t;\
    \ }\n    inline Node *_make_node(const VAL &val) {\n        if (d_ptr >= len)\
    \ exit(1);\n        return &(data[d_ptr++] = Node(val, Idval));\n    }\n    virtual\
    \ void _duplicate_node(Node *&) {}\n\n    inline void _resolve_dval(Node *&t)\
    \ // \u5BFE\u8C61\u306E\u9045\u5EF6\u8A55\u4FA1\u3092\u89E3\u6C7A\n    {\n   \
    \     if (!t) return;\n        _duplicate_node(t);\n        if (t->dval != Idval)\
    \ {\n            if (t->l) {\n                _duplicate_node(t->l);\n       \
    \         _propagate_dval(t->l->dval, t->dval);\n            }\n            if\
    \ (t->r) {\n                _duplicate_node(t->r);\n                _propagate_dval(t->r->dval,\
    \ t->dval);\n            }\n            _reflect_dval(t, t->dval);\n         \
    \   t->dval = Idval;\n        }\n    }\n\n    // l\u3068r\u3092root\u3068\u3059\
    \u308B\u6728\u540C\u58EB\u3092\u7D50\u5408\u3057\u3066\uFF0C\u65B0\u305F\u306A\
    root\u3092\u8FD4\u3059\n    Node *merge(Node *l, Node *r) {\n        if (l ==\
    \ nullptr || r == nullptr) return l ? l : r;\n        if (_rand() % (l->sz + r->sz)\
    \ < l->sz) {\n            _resolve_dval(l);\n            l->r = merge(l->r, r);\n\
    \            return _revise_val(l);\n        } else {\n            _resolve_dval(r);\n\
    \            r->l = merge(l, r->l);\n            return _revise_val(r);\n    \
    \    }\n    }\n\n    // [0, k)\u306E\u6728\u3068[k, root->size())\u306E\u6728\u306B\
    \u5206\u3051\u3066\u5404root\n    // \uFF08\u90E8\u5206\u6728\u306E\u8981\u7D20\
    \u6570\u304C0\u306A\u3089nullptr\uFF09\u3092\u8FD4\u3059\n    pair<Node *, Node\
    \ *> split(Node *&root, int k) // root\u306E\u5B50\u5B6B\u304B\u3089\u3042\u3068\
    k\u500B\u6B32\u3057\u3044\n    {\n        if (root == nullptr) return make_pair(nullptr,\
    \ nullptr);\n        _resolve_dval(root);\n        if (k <= (int)size(root->l))\
    \ // left\u304B\u3089k\u500B\u62FE\u3048\u308B\n        {\n            auto p\
    \ = split(root->l, k);\n            root->l = p.second;\n            return make_pair(p.first,\
    \ _revise_val(root));\n        } else {\n            auto p = split(root->r, k\
    \ - size(root->l) - 1);\n            root->r = p.first;\n            return make_pair(_revise_val(root),\
    \ p.second);\n        }\n    }\n\n    // 0-indexed\u3067array[pos]\u306E\u624B\
    \u524D\u306B\u65B0\u305F\u306A\u8981\u7D20newval\u3092\u633F\u5165\u3059\u308B\
    \n    void insert(Node *&root, int pos, const VAL &newval) {\n        auto p =\
    \ split(root, pos);\n        root = merge(p.first, merge(_make_node(newval), p.second));\n\
    \    }\n\n    // 0-indexed\u3067array[pos]\u3092\u524A\u9664\u3059\u308B\uFF08\
    \u5148\u982D\u304B\u3089pos+1\u500B\u76EE\u306E\u8981\u7D20\uFF09\n    void erase(Node\
    \ *&root, int pos) {\n        auto p = split(root, pos);\n        auto p2 = split(p.second,\
    \ 1);\n        root = merge(p.first, p2.second);\n    }\n\n    // 1\u70B9\u66F4\
    \u65B0 array[pos].val\u306Bupdval\u3092\u5165\u308C\u308B\n    void set(Node *&root,\
    \ int pos, const VAL &updval) {\n        auto p = split(root, pos);\n        auto\
    \ p2 = split(p.second, 1);\n        root = merge(p.first, merge(_make_node(updval),\
    \ p2.second));\n    }\n\n    // \u9045\u5EF6\u8A55\u4FA1\u3092\u5229\u7528\u3057\
    \u305F\u7BC4\u56F2\u66F4\u65B0 [l, r)\n    void range_set(Node *&root, int l,\
    \ int r, const DVAL &adddval) {\n        auto p = split(root, l);\n        auto\
    \ p2 = split(p.second, r - l);\n        _propagate_dval(p2.first->dval, adddval);\n\
    \        root = merge(p.first, merge(p2.first, p2.second));\n    }\n\n    // array[pos].val\u3092\
    \u53D6\u5F97\u3059\u308B\n    Node range_get(Node *&root, int l, int r) {\n  \
    \      auto p = split(root, l);\n        auto p2 = split(p.second, r - l);\n \
    \       _resolve_dval(p2.first);\n        Node res = *p2.first;\n        root\
    \ = merge(p.first, merge(p2.first, p2.second));\n        return res;\n    }\n\
    \    Node get(Node *&root, int pos) { return range_get(root, pos, pos + 1); }\n\
    \n    // \u666E\u901A\u306Elower_bound\n    int lower_bound(Node *root, const\
    \ VAL &v) {\n        if (root == nullptr) return 0;\n        return (v <= root->val)\
    \ ? lower_bound(root->l, v)\n                                : lower_bound(root->r,\
    \ v) + size(root->l) + 1;\n    }\n\n    // \u30C7\u30FC\u30BF\u3092\u58CA\u3057\
    \u3066\u65B0\u898F\u306Binit\u306E\u5185\u5BB9\u3092\u8A70\u3081\u308B\n    void\
    \ assign(Node *&root, const vector<VAL> &init) {\n        d_ptr = 0;\n       \
    \ int N = init.size();\n        root = N ? _assign_range(0, N, init) : new_tree();\n\
    \    }\n    Node *_assign_range(int l, int r, const vector<VAL> &init) {\n   \
    \     if (r - l == 1) {\n            auto t = _make_node(init[l]);\n         \
    \   return _revise_val(t);\n        }\n        return merge(_assign_range(l, (l\
    \ + r) / 2, init), _assign_range((l + r) / 2, r, init));\n    }\n\n    // \u30C7\
    \u30FC\u30BF\u3092vec\u3078\u66F8\u304D\u51FA\u3057\n    void dump(Node *t, vector<VAL>\
    \ &vec) {\n        if (t == nullptr) return;\n        _resolve_dval(t);\n    \
    \    dump(t->l, vec);\n        vec.push_back(t->val);\n        dump(t->r, vec);\n\
    \    }\n\n    // gc\n    void re_alloc(Node *&root) {\n        vector<VAL> mem;\n\
    \        dump(root, mem);\n        assign(root, mem);\n    }\n};\n\n// \u6C38\u7D9A\
    \u5316\ntemplate <uint32_t len> struct PersistentRBST : RandomizedBinarySearchTree<len>\
    \ {\n    using RBST = RandomizedBinarySearchTree<len>;\n    using Node = typename\
    \ RBST::Node;\n    PersistentRBST(DVAL idval) : RBST(idval) {}\n\n    void _duplicate_node(Node\
    \ *&t) override {\n        if (t == nullptr) return;\n        if (RBST::d_ptr\
    \ >= len) exit(1);\n        t = &(RBST::data[RBST::d_ptr++] = *t);\n    }\n\n\
    \    void copy(Node *&root, int l, int d, int target_l) // [target_l, )\u306B\
    [l, l+d)\u306E\u5024\u3092\u5165\u308C\u308B\n    {\n        auto p1 = RBST::split(root,\
    \ l);\n        auto p2 = RBST::split(p1.second, d);\n        root = RBST::merge(p1.first,\
    \ RBST::merge(p2.first, p2.second));\n        auto p3 = RBST::split(root, target_l);\n\
    \        auto p4 = RBST::split(p3.second, d);\n        root = RBST::merge(p3.first,\
    \ RBST::merge(p2.first, p4.second));\n    }\n};\n\nint main() {\n    constexpr\
    \ int mem_size = 13000000;\n    PersistentRBST<mem_size> rbst(0LL);\n\n    auto\
    \ S = rbst.new_tree();\n    int N, Q;\n    cin >> N >> Q;\n    REP(i, N) {\n \
    \       int xi;\n        cin >> xi;\n        rbst.insert(S, i, node(xi));\n  \
    \  }\n\n    REP(_, Q) {\n        int type, a, b, c, d, v;\n        cin >> type;\n\
    \        if (type == 1) {\n            cin >> a >> b >> v;\n            rbst.range_set(S,\
    \ a - 1, b, (lint)v);\n        }\n        if (type == 2) {\n            cin >>\
    \ a >> b >> c >> d;\n            rbst.copy(S, c - 1, b - a + 1, a - 1);\n    \
    \    }\n        if (type == 3) {\n            cin >> a >> b;\n            cout\
    \ << rbst.range_get(S, a - 1, b).val.sum << endl;\n        }\n        if (rbst.mem_used()\
    \ > mem_size * 0.8) rbst.re_alloc(S);\n    }\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/rbst_fast.cpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data_structure/rbst_fast.cpp
layout: document
redirect_from:
- /library/data_structure/rbst_fast.cpp
- /library/data_structure/rbst_fast.cpp.html
title: data_structure/rbst_fast.cpp
---
