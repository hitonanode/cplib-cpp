---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: data_structure/test/lazy_rbst.stress.test.cpp
    title: data_structure/test/lazy_rbst.stress.test.cpp
  - icon: ':heavy_check_mark:'
    path: data_structure/test/lazy_rbst.test.cpp
    title: data_structure/test/lazy_rbst.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://atcoder.jp/contests/arc030/tasks/arc030_4
    - https://yosupo.hatenablog.com/entry/2015/10/29/222536
  bundledCode: "#line 2 \"data_structure/lazy_rbst.hpp\"\n#include <array>\n#include\
    \ <cassert>\n#include <chrono>\n#include <utility>\n#include <vector>\n\n// Lazy\
    \ randomized binary search tree\ntemplate <int LEN, class S, S (*op)(S, S), class\
    \ F, S (*reversal)(S), S (*mapping)(F, S),\n          F (*composition)(F, F),\
    \ F (*id)()>\nstruct lazy_rbst {\n    // Do your RuBeSTy! \u2312\xB0( \u30FB\u03C9\
    \u30FB)\xB0\u2312\n    inline uint32_t _rand() { // XorShift\n        static uint32_t\
    \ x = 123456789, y = 362436069, z = 521288629, w = 88675123;\n        uint32_t\
    \ t = x ^ (x << 11);\n        x = y;\n        y = z;\n        z = w;\n       \
    \ return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));\n    }\n\n    struct Node {\n \
    \       Node *l, *r;\n        S val, sum;\n        F lz;\n        bool is_reversed;\n\
    \        int sz;\n        Node(const S &v)\n            : l(nullptr), r(nullptr),\
    \ val(v), sum(v), lz(id()), is_reversed(false), sz(1) {}\n        Node() : l(nullptr),\
    \ r(nullptr), lz(id()), is_reversed(false), sz(0) {}\n        template <class\
    \ OStream> friend OStream &operator<<(OStream &os, const Node &n) {\n        \
    \    os << '[';\n            if (n.l) os << *(n.l) << ',';\n            os <<\
    \ n.val << ',';\n            if (n.r) os << *(n.r);\n            return os <<\
    \ ']';\n        }\n    };\n    using Nptr = Node *;\n    std::array<Node, LEN>\
    \ data;\n    int d_ptr;\n\n    int size(Nptr t) const { return t != nullptr ?\
    \ t->sz : 0; }\n\n    lazy_rbst() : d_ptr(0) {}\n\nprotected:\n    Nptr update(Nptr\
    \ t) {\n        t->sz = 1;\n        t->sum = t->val;\n        if (t->l) {\n  \
    \          t->sz += t->l->sz;\n            t->sum = op(t->l->sum, t->sum);\n \
    \       }\n        if (t->r) {\n            t->sz += t->r->sz;\n            t->sum\
    \ = op(t->sum, t->r->sum);\n        }\n        return t;\n    }\n\n    void all_apply(Nptr\
    \ t, F f) {\n        t->val = mapping(f, t->val);\n        t->sum = mapping(f,\
    \ t->sum);\n        t->lz = composition(f, t->lz);\n    }\n    void _toggle(Nptr\
    \ t) {\n        auto tmp = t->l;\n        t->l = t->r, t->r = tmp;\n        t->sum\
    \ = reversal(t->sum);\n        t->is_reversed ^= true;\n    }\n\n    void push(Nptr\
    \ &t) {\n        _duplicate_node(t);\n        if (t->lz != id()) {\n         \
    \   if (t->l) {\n                _duplicate_node(t->l);\n                all_apply(t->l,\
    \ t->lz);\n            }\n            if (t->r) {\n                _duplicate_node(t->r);\n\
    \                all_apply(t->r, t->lz);\n            }\n            t->lz = id();\n\
    \        }\n        if (t->is_reversed) {\n            if (t->l) _toggle(t->l);\n\
    \            if (t->r) _toggle(t->r);\n            t->is_reversed = false;\n \
    \       }\n    }\n\n    virtual void _duplicate_node(Nptr &) {}\n\n    Nptr _make_node(const\
    \ S &val) {\n        if (d_ptr >= LEN) throw;\n        return &(data[d_ptr++]\
    \ = Node(val));\n    }\n\npublic:\n    Nptr new_tree() { return nullptr; } //\
    \ \u65B0\u305F\u306A\u6728\u3092\u4F5C\u6210\n\n    int mem_used() const { return\
    \ d_ptr; }\n    bool empty(Nptr t) const { return t == nullptr; }\n\n    // l\u3068\
    r\u3092root\u3068\u3059\u308B\u6728\u540C\u58EB\u3092\u7D50\u5408\u3057\u3066\uFF0C\
    \u65B0\u305F\u306Aroot\u3092\u8FD4\u3059\n    Nptr merge(Nptr l, Nptr r) {\n \
    \       if (l == nullptr or r == nullptr) return l != nullptr ? l : r;\n     \
    \   if (_rand() % uint32_t(l->sz + r->sz) < uint32_t(l->sz)) {\n            push(l);\n\
    \            l->r = merge(l->r, r);\n            return update(l);\n        }\
    \ else {\n            push(r);\n            r->l = merge(l, r->l);\n         \
    \   return update(r);\n        }\n    }\n\n    // [0, k)\u306E\u6728\u3068[k,\
    \ root->size())\u306E\u6728\u306B\u5206\u3051\u3066\u5404root\n    // \uFF08\u90E8\
    \u5206\u6728\u306E\u8981\u7D20\u6570\u304C0\u306A\u3089nullptr\uFF09\u3092\u8FD4\
    \u3059\n    std::pair<Nptr, Nptr> split(Nptr &root, int k) { // root\u306E\u5B50\
    \u5B6B\u304B\u3089\u3042\u3068k\u500B\u6B32\u3057\u3044\n        if (root == nullptr)\
    \ return std::make_pair(nullptr, nullptr);\n        push(root);\n        if (k\
    \ <= size(root->l)) { // left\u304B\u3089k\u500B\u62FE\u3048\u308B\n         \
    \   auto p = split(root->l, k);\n            root->l = p.second;\n           \
    \ return std::make_pair(p.first, update(root));\n        } else {\n          \
    \  auto p = split(root->r, k - size(root->l) - 1);\n            root->r = p.first;\n\
    \            return std::make_pair(update(root), p.second);\n        }\n    }\n\
    \n    // 0-indexed\u3067array[pos]\u306E\u624B\u524D\u306B\u65B0\u305F\u306A\u8981\
    \u7D20 x \u3092\u633F\u5165\u3059\u308B\n    void insert(Nptr &root, int pos,\
    \ const S &x) {\n        auto p = split(root, pos);\n        root = merge(p.first,\
    \ merge(_make_node(x), p.second));\n    }\n\n    // 0-indexed\u3067array[pos]\u3092\
    \u524A\u9664\u3059\u308B\uFF08\u5148\u982D\u304B\u3089pos+1\u500B\u76EE\u306E\u8981\
    \u7D20\uFF09\n    void erase(Nptr &root, int pos) {\n        auto p = split(root,\
    \ pos);\n        auto p2 = split(p.second, 1);\n        root = merge(p.first,\
    \ p2.second);\n    }\n\n    // 1\u70B9\u66F4\u65B0 array[pos].val\u306Bupdval\u3092\
    \u5165\u308C\u308B\n    void set(Nptr &root, int pos, const S &x) {\n        auto\
    \ p = split(root, pos);\n        auto p2 = split(p.second, 1);\n        _duplicate_node(p2.first);\n\
    \        *p2.first = Node(x);\n        root = merge(p.first, merge(p2.first, p2.second));\n\
    \    }\n\n    // \u9045\u5EF6\u8A55\u4FA1\u3092\u5229\u7528\u3057\u305F\u7BC4\u56F2\
    \u66F4\u65B0 [l, r)\n    void apply(Nptr &root, int l, int r, const F &f) {\n\
    \        if (l == r) return;\n        auto p = split(root, l);\n        auto p2\
    \ = split(p.second, r - l);\n        all_apply(p2.first, f);\n        root = merge(p.first,\
    \ merge(p2.first, p2.second));\n    }\n\n    S prod(Nptr &root, int l, int r)\
    \ {\n        assert(l < r);\n        auto p = split(root, l);\n        auto p2\
    \ = split(p.second, r - l);\n        if (p2.first != nullptr) push(p2.first);\n\
    \        S res = p2.first->sum;\n        root = merge(p.first, merge(p2.first,\
    \ p2.second));\n        return res;\n    }\n\n    // array[pos].val\u3092\u53D6\
    \u5F97\u3059\u308B\n    S get(Nptr &root, int pos) { return prod(root, pos, pos\
    \ + 1); }\n\n    template <bool (*g)(S)> int max_right(Nptr root, const S &e)\
    \ {\n        return max_right(root, e, [](S x) { return g(x); });\n    }\n   \
    \ template <class G> int max_right(Nptr root, const S &e, G g) {\n        assert(g(e));\n\
    \        if (root == nullptr) return 0;\n        push(root);\n        Nptr now\
    \ = root;\n        S prod_now = e;\n        int sz = 0;\n        while (true)\
    \ {\n            if (now->l != nullptr) {\n                push(now->l);\n   \
    \             auto pl = op(prod_now, now->l->sum);\n                if (g(pl))\
    \ {\n                    prod_now = pl;\n                    sz += now->l->sz;\n\
    \                } else {\n                    now = now->l;\n               \
    \     continue;\n                }\n            }\n            auto pl = op(prod_now,\
    \ now->val);\n            if (!g(pl)) return sz;\n            prod_now = pl, sz++;\n\
    \            if (now->r == nullptr) return sz;\n            push(now->r);\n  \
    \          now = now->r;\n        }\n    }\n\n    template <bool (*g)(S)> int\
    \ min_left(Nptr root, const S &e) {\n        return min_left(root, e, [](S x)\
    \ { return g(x); });\n    }\n    template <class G> int min_left(Nptr root, const\
    \ S &e, G g) {\n        assert(g(e));\n        if (root == nullptr) return 0;\n\
    \        push(root);\n        Nptr now = root;\n        S prod_now = e;\n    \
    \    int sz = size(root);\n        while (true) {\n            if (now->r != nullptr)\
    \ {\n                push(now->r);\n                auto pr = op(now->r->sum,\
    \ prod_now);\n                if (g(pr)) {\n                    prod_now = pr;\n\
    \                    sz -= now->r->sz;\n                } else {\n           \
    \         now = now->r;\n                    continue;\n                }\n  \
    \          }\n            auto pr = op(now->val, prod_now);\n            if (!g(pr))\
    \ return sz;\n            prod_now = pr, sz--;\n            if (now->l == nullptr)\
    \ return sz;\n            push(now->l);\n            now = now->l;\n        }\n\
    \    }\n\n    void reverse(Nptr &root) { _duplicate_node(root), _toggle(root);\
    \ }\n    void reverse(Nptr &root, int l, int r) {\n        auto p2 = split(root,\
    \ r);\n        auto p1 = split(p2.first, l);\n        reverse(p1.second);\n  \
    \      root = merge(merge(p1.first, p1.second), p2.second);\n    }\n\n    // \u30C7\
    \u30FC\u30BF\u3092\u58CA\u3057\u3066\u65B0\u898F\u306Binit\u306E\u5185\u5BB9\u3092\
    \u8A70\u3081\u308B\n    void assign(Nptr &root, const std::vector<S> &init) {\n\
    \        int N = init.size();\n        root = N ? _assign_range(0, N, init) :\
    \ new_tree();\n    }\n    Nptr _assign_range(int l, int r, const std::vector<S>\
    \ &init) {\n        if (r - l == 1) {\n            Nptr t = _make_node(init[l]);\n\
    \            return update(t);\n        }\n        return merge(_assign_range(l,\
    \ (l + r) / 2, init), _assign_range((l + r) / 2, r, init));\n    }\n\n    // \u30C7\
    \u30FC\u30BF\u3092vec\u3078\u66F8\u304D\u51FA\u3057\n    void dump(Nptr &t, std::vector<S>\
    \ &vec) {\n        if (t == nullptr) return;\n        push(t);\n        dump(t->l,\
    \ vec);\n        vec.push_back(t->val);\n        dump(t->r, vec);\n    }\n\n \
    \   // gc\n    void re_alloc(Nptr &root) {\n        std::vector<S> mem;\n    \
    \    dump(root, mem);\n        d_ptr = 0;\n        assign(root, mem);\n    }\n\
    };\n\n// Persistent lazy randomized binary search tree\n// Verified: https://atcoder.jp/contests/arc030/tasks/arc030_4\n\
    // CAUTION: https://yosupo.hatenablog.com/entry/2015/10/29/222536\ntemplate <int\
    \ LEN, class S, S (*op)(S, S), class F, S (*reversal)(S), S (*mapping)(F, S),\n\
    \          F (*composition)(F, F), F (*id)()>\nstruct persistent_lazy_rbst : lazy_rbst<LEN,\
    \ S, op, F, reversal, mapping, composition, id> {\n    using RBST = lazy_rbst<LEN,\
    \ S, op, F, reversal, mapping, composition, id>;\n    using Node = typename RBST::Node;\n\
    \    using Nptr = typename RBST::Nptr;\n    persistent_lazy_rbst() : RBST() {}\n\
    \nprotected:\n    void _duplicate_node(Nptr &t) override {\n        if (t == nullptr)\
    \ return;\n        if (RBST::d_ptr >= LEN) throw;\n        t = &(RBST::data[RBST::d_ptr++]\
    \ = *t);\n    }\n\npublic:\n    void copy(Nptr &root, int l, int d, int target_l)\
    \ { // [target_l, )\u306B[l, l+d)\u306E\u5024\u3092\u5165\u308C\u308B\n      \
    \  auto p1 = RBST::split(root, l);\n        auto p2 = RBST::split(p1.second, d);\n\
    \        root = RBST::merge(p1.first, RBST::merge(p2.first, p2.second));\n   \
    \     auto p3 = RBST::split(root, target_l);\n        auto p4 = RBST::split(p3.second,\
    \ d);\n        root = RBST::merge(p3.first, RBST::merge(p2.first, p4.second));\n\
    \    }\n};\n"
  code: "#pragma once\n#include <array>\n#include <cassert>\n#include <chrono>\n#include\
    \ <utility>\n#include <vector>\n\n// Lazy randomized binary search tree\ntemplate\
    \ <int LEN, class S, S (*op)(S, S), class F, S (*reversal)(S), S (*mapping)(F,\
    \ S),\n          F (*composition)(F, F), F (*id)()>\nstruct lazy_rbst {\n    //\
    \ Do your RuBeSTy! \u2312\xB0( \u30FB\u03C9\u30FB)\xB0\u2312\n    inline uint32_t\
    \ _rand() { // XorShift\n        static uint32_t x = 123456789, y = 362436069,\
    \ z = 521288629, w = 88675123;\n        uint32_t t = x ^ (x << 11);\n        x\
    \ = y;\n        y = z;\n        z = w;\n        return w = (w ^ (w >> 19)) ^ (t\
    \ ^ (t >> 8));\n    }\n\n    struct Node {\n        Node *l, *r;\n        S val,\
    \ sum;\n        F lz;\n        bool is_reversed;\n        int sz;\n        Node(const\
    \ S &v)\n            : l(nullptr), r(nullptr), val(v), sum(v), lz(id()), is_reversed(false),\
    \ sz(1) {}\n        Node() : l(nullptr), r(nullptr), lz(id()), is_reversed(false),\
    \ sz(0) {}\n        template <class OStream> friend OStream &operator<<(OStream\
    \ &os, const Node &n) {\n            os << '[';\n            if (n.l) os << *(n.l)\
    \ << ',';\n            os << n.val << ',';\n            if (n.r) os << *(n.r);\n\
    \            return os << ']';\n        }\n    };\n    using Nptr = Node *;\n\
    \    std::array<Node, LEN> data;\n    int d_ptr;\n\n    int size(Nptr t) const\
    \ { return t != nullptr ? t->sz : 0; }\n\n    lazy_rbst() : d_ptr(0) {}\n\nprotected:\n\
    \    Nptr update(Nptr t) {\n        t->sz = 1;\n        t->sum = t->val;\n   \
    \     if (t->l) {\n            t->sz += t->l->sz;\n            t->sum = op(t->l->sum,\
    \ t->sum);\n        }\n        if (t->r) {\n            t->sz += t->r->sz;\n \
    \           t->sum = op(t->sum, t->r->sum);\n        }\n        return t;\n  \
    \  }\n\n    void all_apply(Nptr t, F f) {\n        t->val = mapping(f, t->val);\n\
    \        t->sum = mapping(f, t->sum);\n        t->lz = composition(f, t->lz);\n\
    \    }\n    void _toggle(Nptr t) {\n        auto tmp = t->l;\n        t->l = t->r,\
    \ t->r = tmp;\n        t->sum = reversal(t->sum);\n        t->is_reversed ^= true;\n\
    \    }\n\n    void push(Nptr &t) {\n        _duplicate_node(t);\n        if (t->lz\
    \ != id()) {\n            if (t->l) {\n                _duplicate_node(t->l);\n\
    \                all_apply(t->l, t->lz);\n            }\n            if (t->r)\
    \ {\n                _duplicate_node(t->r);\n                all_apply(t->r, t->lz);\n\
    \            }\n            t->lz = id();\n        }\n        if (t->is_reversed)\
    \ {\n            if (t->l) _toggle(t->l);\n            if (t->r) _toggle(t->r);\n\
    \            t->is_reversed = false;\n        }\n    }\n\n    virtual void _duplicate_node(Nptr\
    \ &) {}\n\n    Nptr _make_node(const S &val) {\n        if (d_ptr >= LEN) throw;\n\
    \        return &(data[d_ptr++] = Node(val));\n    }\n\npublic:\n    Nptr new_tree()\
    \ { return nullptr; } // \u65B0\u305F\u306A\u6728\u3092\u4F5C\u6210\n\n    int\
    \ mem_used() const { return d_ptr; }\n    bool empty(Nptr t) const { return t\
    \ == nullptr; }\n\n    // l\u3068r\u3092root\u3068\u3059\u308B\u6728\u540C\u58EB\
    \u3092\u7D50\u5408\u3057\u3066\uFF0C\u65B0\u305F\u306Aroot\u3092\u8FD4\u3059\n\
    \    Nptr merge(Nptr l, Nptr r) {\n        if (l == nullptr or r == nullptr) return\
    \ l != nullptr ? l : r;\n        if (_rand() % uint32_t(l->sz + r->sz) < uint32_t(l->sz))\
    \ {\n            push(l);\n            l->r = merge(l->r, r);\n            return\
    \ update(l);\n        } else {\n            push(r);\n            r->l = merge(l,\
    \ r->l);\n            return update(r);\n        }\n    }\n\n    // [0, k)\u306E\
    \u6728\u3068[k, root->size())\u306E\u6728\u306B\u5206\u3051\u3066\u5404root\n\
    \    // \uFF08\u90E8\u5206\u6728\u306E\u8981\u7D20\u6570\u304C0\u306A\u3089nullptr\uFF09\
    \u3092\u8FD4\u3059\n    std::pair<Nptr, Nptr> split(Nptr &root, int k) { // root\u306E\
    \u5B50\u5B6B\u304B\u3089\u3042\u3068k\u500B\u6B32\u3057\u3044\n        if (root\
    \ == nullptr) return std::make_pair(nullptr, nullptr);\n        push(root);\n\
    \        if (k <= size(root->l)) { // left\u304B\u3089k\u500B\u62FE\u3048\u308B\
    \n            auto p = split(root->l, k);\n            root->l = p.second;\n \
    \           return std::make_pair(p.first, update(root));\n        } else {\n\
    \            auto p = split(root->r, k - size(root->l) - 1);\n            root->r\
    \ = p.first;\n            return std::make_pair(update(root), p.second);\n   \
    \     }\n    }\n\n    // 0-indexed\u3067array[pos]\u306E\u624B\u524D\u306B\u65B0\
    \u305F\u306A\u8981\u7D20 x \u3092\u633F\u5165\u3059\u308B\n    void insert(Nptr\
    \ &root, int pos, const S &x) {\n        auto p = split(root, pos);\n        root\
    \ = merge(p.first, merge(_make_node(x), p.second));\n    }\n\n    // 0-indexed\u3067\
    array[pos]\u3092\u524A\u9664\u3059\u308B\uFF08\u5148\u982D\u304B\u3089pos+1\u500B\
    \u76EE\u306E\u8981\u7D20\uFF09\n    void erase(Nptr &root, int pos) {\n      \
    \  auto p = split(root, pos);\n        auto p2 = split(p.second, 1);\n       \
    \ root = merge(p.first, p2.second);\n    }\n\n    // 1\u70B9\u66F4\u65B0 array[pos].val\u306B\
    updval\u3092\u5165\u308C\u308B\n    void set(Nptr &root, int pos, const S &x)\
    \ {\n        auto p = split(root, pos);\n        auto p2 = split(p.second, 1);\n\
    \        _duplicate_node(p2.first);\n        *p2.first = Node(x);\n        root\
    \ = merge(p.first, merge(p2.first, p2.second));\n    }\n\n    // \u9045\u5EF6\u8A55\
    \u4FA1\u3092\u5229\u7528\u3057\u305F\u7BC4\u56F2\u66F4\u65B0 [l, r)\n    void\
    \ apply(Nptr &root, int l, int r, const F &f) {\n        if (l == r) return;\n\
    \        auto p = split(root, l);\n        auto p2 = split(p.second, r - l);\n\
    \        all_apply(p2.first, f);\n        root = merge(p.first, merge(p2.first,\
    \ p2.second));\n    }\n\n    S prod(Nptr &root, int l, int r) {\n        assert(l\
    \ < r);\n        auto p = split(root, l);\n        auto p2 = split(p.second, r\
    \ - l);\n        if (p2.first != nullptr) push(p2.first);\n        S res = p2.first->sum;\n\
    \        root = merge(p.first, merge(p2.first, p2.second));\n        return res;\n\
    \    }\n\n    // array[pos].val\u3092\u53D6\u5F97\u3059\u308B\n    S get(Nptr\
    \ &root, int pos) { return prod(root, pos, pos + 1); }\n\n    template <bool (*g)(S)>\
    \ int max_right(Nptr root, const S &e) {\n        return max_right(root, e, [](S\
    \ x) { return g(x); });\n    }\n    template <class G> int max_right(Nptr root,\
    \ const S &e, G g) {\n        assert(g(e));\n        if (root == nullptr) return\
    \ 0;\n        push(root);\n        Nptr now = root;\n        S prod_now = e;\n\
    \        int sz = 0;\n        while (true) {\n            if (now->l != nullptr)\
    \ {\n                push(now->l);\n                auto pl = op(prod_now, now->l->sum);\n\
    \                if (g(pl)) {\n                    prod_now = pl;\n          \
    \          sz += now->l->sz;\n                } else {\n                    now\
    \ = now->l;\n                    continue;\n                }\n            }\n\
    \            auto pl = op(prod_now, now->val);\n            if (!g(pl)) return\
    \ sz;\n            prod_now = pl, sz++;\n            if (now->r == nullptr) return\
    \ sz;\n            push(now->r);\n            now = now->r;\n        }\n    }\n\
    \n    template <bool (*g)(S)> int min_left(Nptr root, const S &e) {\n        return\
    \ min_left(root, e, [](S x) { return g(x); });\n    }\n    template <class G>\
    \ int min_left(Nptr root, const S &e, G g) {\n        assert(g(e));\n        if\
    \ (root == nullptr) return 0;\n        push(root);\n        Nptr now = root;\n\
    \        S prod_now = e;\n        int sz = size(root);\n        while (true) {\n\
    \            if (now->r != nullptr) {\n                push(now->r);\n       \
    \         auto pr = op(now->r->sum, prod_now);\n                if (g(pr)) {\n\
    \                    prod_now = pr;\n                    sz -= now->r->sz;\n \
    \               } else {\n                    now = now->r;\n                \
    \    continue;\n                }\n            }\n            auto pr = op(now->val,\
    \ prod_now);\n            if (!g(pr)) return sz;\n            prod_now = pr, sz--;\n\
    \            if (now->l == nullptr) return sz;\n            push(now->l);\n  \
    \          now = now->l;\n        }\n    }\n\n    void reverse(Nptr &root) { _duplicate_node(root),\
    \ _toggle(root); }\n    void reverse(Nptr &root, int l, int r) {\n        auto\
    \ p2 = split(root, r);\n        auto p1 = split(p2.first, l);\n        reverse(p1.second);\n\
    \        root = merge(merge(p1.first, p1.second), p2.second);\n    }\n\n    //\
    \ \u30C7\u30FC\u30BF\u3092\u58CA\u3057\u3066\u65B0\u898F\u306Binit\u306E\u5185\
    \u5BB9\u3092\u8A70\u3081\u308B\n    void assign(Nptr &root, const std::vector<S>\
    \ &init) {\n        int N = init.size();\n        root = N ? _assign_range(0,\
    \ N, init) : new_tree();\n    }\n    Nptr _assign_range(int l, int r, const std::vector<S>\
    \ &init) {\n        if (r - l == 1) {\n            Nptr t = _make_node(init[l]);\n\
    \            return update(t);\n        }\n        return merge(_assign_range(l,\
    \ (l + r) / 2, init), _assign_range((l + r) / 2, r, init));\n    }\n\n    // \u30C7\
    \u30FC\u30BF\u3092vec\u3078\u66F8\u304D\u51FA\u3057\n    void dump(Nptr &t, std::vector<S>\
    \ &vec) {\n        if (t == nullptr) return;\n        push(t);\n        dump(t->l,\
    \ vec);\n        vec.push_back(t->val);\n        dump(t->r, vec);\n    }\n\n \
    \   // gc\n    void re_alloc(Nptr &root) {\n        std::vector<S> mem;\n    \
    \    dump(root, mem);\n        d_ptr = 0;\n        assign(root, mem);\n    }\n\
    };\n\n// Persistent lazy randomized binary search tree\n// Verified: https://atcoder.jp/contests/arc030/tasks/arc030_4\n\
    // CAUTION: https://yosupo.hatenablog.com/entry/2015/10/29/222536\ntemplate <int\
    \ LEN, class S, S (*op)(S, S), class F, S (*reversal)(S), S (*mapping)(F, S),\n\
    \          F (*composition)(F, F), F (*id)()>\nstruct persistent_lazy_rbst : lazy_rbst<LEN,\
    \ S, op, F, reversal, mapping, composition, id> {\n    using RBST = lazy_rbst<LEN,\
    \ S, op, F, reversal, mapping, composition, id>;\n    using Node = typename RBST::Node;\n\
    \    using Nptr = typename RBST::Nptr;\n    persistent_lazy_rbst() : RBST() {}\n\
    \nprotected:\n    void _duplicate_node(Nptr &t) override {\n        if (t == nullptr)\
    \ return;\n        if (RBST::d_ptr >= LEN) throw;\n        t = &(RBST::data[RBST::d_ptr++]\
    \ = *t);\n    }\n\npublic:\n    void copy(Nptr &root, int l, int d, int target_l)\
    \ { // [target_l, )\u306B[l, l+d)\u306E\u5024\u3092\u5165\u308C\u308B\n      \
    \  auto p1 = RBST::split(root, l);\n        auto p2 = RBST::split(p1.second, d);\n\
    \        root = RBST::merge(p1.first, RBST::merge(p2.first, p2.second));\n   \
    \     auto p3 = RBST::split(root, target_l);\n        auto p4 = RBST::split(p3.second,\
    \ d);\n        root = RBST::merge(p3.first, RBST::merge(p2.first, p4.second));\n\
    \    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/lazy_rbst.hpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - data_structure/test/lazy_rbst.test.cpp
  - data_structure/test/lazy_rbst.stress.test.cpp
documentation_of: data_structure/lazy_rbst.hpp
layout: document
title: Randomized binary search tree with lazy propagation
---

> Do your RuBeSTy! ⌒°( ・ω・)°⌒

Randomized binary search tree を用いた動的な列に対するクエリを扱うデータ構造．インターフェースを `atcoder::lazy_segtree` に寄せている．一応 [D - グラフではない](https://atcoder.jp/contests/arc030/tasks/arc030_4) のために作成した永続版も残しているが [計算量の保証はない](https://yosupo.hatenablog.com/entry/2015/10/29/222536)．

## 使用方法

内部で `evert()` を使用する関数は根を変更してしまうので注意．

```cpp
struct S {
    mint sum;
    int sz;
};
using F = pair<bool, pair<mint, mint>>;
S op(S l, S r);
S mapping(F f, S x);
S reversal(S x);
F composition(F fnew, F gold);
F id();

lazy_rbst<1000001, S, op, F, reversal, mapping, composition, id> rbst;
vector<S> A(N);
auto root = rbst.new_tree();
rbst.assign(root, A);
rbst.insert(root, i, S{x, 1});
rbst.erase(root, i);
rbst.reverse(root, l, r);
rbst.apply(root, l, r, F{true, {b, c}});

const S e;  // 単位元
int i = rbst.max_right(root, e, [](S f) { return e < f; }); // rbst.prod(root, 0, i) が true となるような最大の i を返す．単調性を仮定．atcoder::lazy_segtree と同じ．
int j = rbst.min_left(root, e, [](S f) { return e < f; }); // rbst.prod(root, j, size(root)) が true となるような最小の j を返す．単調性を仮定．atcoder::lazy_segtree と同じ．
cout << rbst.prod(root, l, r).sum << '\n';
```

## 問題例

- [D - グラフではない](https://atcoder.jp/contests/arc030/tasks/arc030_4)
- [Dashboard - Algorithms Thread Treaps Contest - Codeforces](https://codeforces.com/gym/102787)
- [Codeforces Round #740 (Div. 1, based on VK Cup 2021 - Final (Engine)) D. Top-Notch Insertions - Codeforces](https://codeforces.com/contest/1558/problem/D)

## 参考文献・リンク・参考にした実装

- [RBSTがコピー可能は嘘という疑惑 - よすぽの日記](https://yosupo.hatenablog.com/entry/2015/10/29/222536)
- [永続 RBST を撃墜するケース \| mitaki28.info blog](http://blog.mitaki28.info/1446205599273/)
