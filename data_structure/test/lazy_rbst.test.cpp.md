---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/lazy_rbst.hpp
    title: Randomized binary search tree with lazy propagation
  - icon: ':heavy_check_mark:'
    path: modint.hpp
    title: modint.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum
    links:
    - https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum
  bundledCode: "#line 1 \"data_structure/test/lazy_rbst.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum\"\n\
    #line 2 \"data_structure/lazy_rbst.hpp\"\n#include <array>\n#include <cassert>\n\
    #include <chrono>\n#include <utility>\n#include <vector>\n\n// Lazy randomized\
    \ binary search tree\ntemplate <int LEN, class S, S (*op)(S, S), class F, S (*reversal)(S),\
    \ S (*mapping)(F, S), F (*composition)(F, F), F (*id)()>\nstruct lazy_rbst {\n\
    \    // Do your RuBeSTy! \u2312\xB0( \u30FB\u03C9\u30FB)\xB0\u2312\n    inline\
    \ uint32_t _rand() { // XorShift\n        static uint32_t x = 123456789, y = 362436069,\
    \ z = 521288629, w = 88675123;\n        uint32_t t = x ^ (x << 11);\n        x\
    \ = y;\n        y = z;\n        z = w;\n        return w = (w ^ (w >> 19)) ^ (t\
    \ ^ (t >> 8));\n    }\n\n    struct Node {\n        Node *l, *r;\n        S val,\
    \ sum;\n        F lz;\n        bool is_reversed;\n        int sz;\n        Node(const\
    \ S &v) : l(nullptr), r(nullptr), val(v), sum(v), lz(id()), is_reversed(false),\
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
    \ LEN, class S, S (*op)(S, S), class F, S (*reversal)(S), S (*mapping)(F, S),\
    \ F (*composition)(F, F), F (*id)()>\nstruct persistent_lazy_rbst : lazy_rbst<LEN,\
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
    \    }\n};\n#line 2 \"modint.hpp\"\n#include <iostream>\n#include <set>\n#line\
    \ 5 \"modint.hpp\"\n\n// CUT begin\ntemplate <int md> struct ModInt {\n#if __cplusplus\
    \ >= 201402L\n#define MDCONST constexpr\n#else\n#define MDCONST\n#endif\n    using\
    \ lint = long long;\n    MDCONST static int mod() { return md; }\n    static int\
    \ get_primitive_root() {\n        static int primitive_root = 0;\n        if (!primitive_root)\
    \ {\n            primitive_root = [&]() {\n                std::set<int> fac;\n\
    \                int v = md - 1;\n                for (lint i = 2; i * i <= v;\
    \ i++)\n                    while (v % i == 0) fac.insert(i), v /= i;\n      \
    \          if (v > 1) fac.insert(v);\n                for (int g = 1; g < md;\
    \ g++) {\n                    bool ok = true;\n                    for (auto i\
    \ : fac)\n                        if (ModInt(g).pow((md - 1) / i) == 1) {\n  \
    \                          ok = false;\n                            break;\n \
    \                       }\n                    if (ok) return g;\n           \
    \     }\n                return -1;\n            }();\n        }\n        return\
    \ primitive_root;\n    }\n    int val;\n    MDCONST ModInt() : val(0) {}\n   \
    \ MDCONST ModInt &_setval(lint v) { return val = (v >= md ? v - md : v), *this;\
    \ }\n    MDCONST ModInt(lint v) { _setval(v % md + md); }\n    MDCONST explicit\
    \ operator bool() const { return val != 0; }\n    MDCONST ModInt operator+(const\
    \ ModInt &x) const { return ModInt()._setval((lint)val + x.val); }\n    MDCONST\
    \ ModInt operator-(const ModInt &x) const { return ModInt()._setval((lint)val\
    \ - x.val + md); }\n    MDCONST ModInt operator*(const ModInt &x) const { return\
    \ ModInt()._setval((lint)val * x.val % md); }\n    MDCONST ModInt operator/(const\
    \ ModInt &x) const { return ModInt()._setval((lint)val * x.inv() % md); }\n  \
    \  MDCONST ModInt operator-() const { return ModInt()._setval(md - val); }\n \
    \   MDCONST ModInt &operator+=(const ModInt &x) { return *this = *this + x; }\n\
    \    MDCONST ModInt &operator-=(const ModInt &x) { return *this = *this - x; }\n\
    \    MDCONST ModInt &operator*=(const ModInt &x) { return *this = *this * x; }\n\
    \    MDCONST ModInt &operator/=(const ModInt &x) { return *this = *this / x; }\n\
    \    friend MDCONST ModInt operator+(lint a, const ModInt &x) { return ModInt()._setval(a\
    \ % md + x.val); }\n    friend MDCONST ModInt operator-(lint a, const ModInt &x)\
    \ { return ModInt()._setval(a % md - x.val + md); }\n    friend MDCONST ModInt\
    \ operator*(lint a, const ModInt &x) { return ModInt()._setval(a % md * x.val\
    \ % md); }\n    friend MDCONST ModInt operator/(lint a, const ModInt &x) {\n \
    \       return ModInt()._setval(a % md * x.inv() % md);\n    }\n    MDCONST bool\
    \ operator==(const ModInt &x) const { return val == x.val; }\n    MDCONST bool\
    \ operator!=(const ModInt &x) const { return val != x.val; }\n    MDCONST bool\
    \ operator<(const ModInt &x) const { return val < x.val; } // To use std::map<ModInt,\
    \ T>\n    friend std::istream &operator>>(std::istream &is, ModInt &x) {\n   \
    \     lint t;\n        return is >> t, x = ModInt(t), is;\n    }\n    MDCONST\
    \ friend std::ostream &operator<<(std::ostream &os, const ModInt &x) { return\
    \ os << x.val; }\n    MDCONST ModInt pow(lint n) const {\n        ModInt ans =\
    \ 1, tmp = *this;\n        while (n) {\n            if (n & 1) ans *= tmp;\n \
    \           tmp *= tmp, n >>= 1;\n        }\n        return ans;\n    }\n\n  \
    \  static std::vector<ModInt> facs, facinvs, invs;\n    MDCONST static void _precalculation(int\
    \ N) {\n        int l0 = facs.size();\n        if (N > md) N = md;\n        if\
    \ (N <= l0) return;\n        facs.resize(N), facinvs.resize(N), invs.resize(N);\n\
    \        for (int i = l0; i < N; i++) facs[i] = facs[i - 1] * i;\n        facinvs[N\
    \ - 1] = facs.back().pow(md - 2);\n        for (int i = N - 2; i >= l0; i--) facinvs[i]\
    \ = facinvs[i + 1] * (i + 1);\n        for (int i = N - 1; i >= l0; i--) invs[i]\
    \ = facinvs[i] * facs[i - 1];\n    }\n    MDCONST lint inv() const {\n       \
    \ if (this->val < std::min(md >> 1, 1 << 21)) {\n            while (this->val\
    \ >= int(facs.size())) _precalculation(facs.size() * 2);\n            return invs[this->val].val;\n\
    \        } else {\n            return this->pow(md - 2).val;\n        }\n    }\n\
    \    MDCONST ModInt fac() const {\n        while (this->val >= int(facs.size()))\
    \ _precalculation(facs.size() * 2);\n        return facs[this->val];\n    }\n\
    \    MDCONST ModInt facinv() const {\n        while (this->val >= int(facs.size()))\
    \ _precalculation(facs.size() * 2);\n        return facinvs[this->val];\n    }\n\
    \    MDCONST ModInt doublefac() const {\n        lint k = (this->val + 1) / 2;\n\
    \        return (this->val & 1) ? ModInt(k * 2).fac() / (ModInt(2).pow(k) * ModInt(k).fac())\n\
    \                               : ModInt(k).fac() * ModInt(2).pow(k);\n    }\n\
    \    MDCONST ModInt nCr(const ModInt &r) const {\n        return (this->val <\
    \ r.val) ? 0 : this->fac() * (*this - r).facinv() * r.facinv();\n    }\n    MDCONST\
    \ ModInt nPr(const ModInt &r) const {\n        return (this->val < r.val) ? 0\
    \ : this->fac() * (*this - r).facinv();\n    }\n\n    ModInt sqrt() const {\n\
    \        if (val == 0) return 0;\n        if (md == 2) return val;\n        if\
    \ (pow((md - 1) / 2) != 1) return 0;\n        ModInt b = 1;\n        while (b.pow((md\
    \ - 1) / 2) == 1) b += 1;\n        int e = 0, m = md - 1;\n        while (m %\
    \ 2 == 0) m >>= 1, e++;\n        ModInt x = pow((m - 1) / 2), y = (*this) * x\
    \ * x;\n        x *= (*this);\n        ModInt z = b.pow(m);\n        while (y\
    \ != 1) {\n            int j = 0;\n            ModInt t = y;\n            while\
    \ (t != 1) j++, t *= t;\n            z = z.pow(1LL << (e - j - 1));\n        \
    \    x *= z, z *= z, y *= z;\n            e = j;\n        }\n        return ModInt(std::min(x.val,\
    \ md - x.val));\n    }\n};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facs\
    \ = {1};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facinvs = {1};\n\
    template <int md> std::vector<ModInt<md>> ModInt<md>::invs = {0};\n// using mint\
    \ = ModInt<998244353>;\n// using mint = ModInt<1000000007>;\n#line 4 \"data_structure/test/lazy_rbst.test.cpp\"\
    \n#include <algorithm>\n#line 8 \"data_structure/test/lazy_rbst.test.cpp\"\nusing\
    \ namespace std;\n\nusing mint = ModInt<998244353>;\n\nstruct S {\n    mint sum;\n\
    \    int sz;\n};\nusing F = pair<bool, pair<mint, mint>>;\nS op(S l, S r) { return\
    \ S{l.sum + r.sum, l.sz + r.sz}; }\nS mapping(F f, S x) {\n    if (!f.first) return\
    \ x;\n    mint a = f.second.first, b = f.second.second;\n    return {x.sum * a\
    \ + b * x.sz, x.sz};\n}\nS reversal(S x) { return x; }\nF composition(F fnew,\
    \ F gold) {\n    if (!fnew.first) return gold;\n    if (!gold.first) return fnew;\n\
    \    auto anew = fnew.second.first, bnew = fnew.second.second;\n    auto aold\
    \ = gold.second.first, bold = gold.second.second;\n    return {true, {anew * aold,\
    \ anew * bold + bnew}};\n}\nF id() { return {false, {1, 0}}; }\n\nint main() {\n\
    \    cin.tie(nullptr), ios::sync_with_stdio(false);\n    int N, Q;\n    cin >>\
    \ N >> Q;\n    vector<S> A(N);\n    for (auto &x : A) cin >> x.sum, x.sz = 1;\n\
    \    lazy_rbst<1000001, S, op, F, reversal, mapping, composition, id> rbst;\n\n\
    \    auto root = rbst.new_tree();\n    rbst.assign(root, A);\n    while (Q--)\
    \ {\n        int tp;\n        cin >> tp;\n        if (tp == 0) {\n           \
    \ int i, x;\n            cin >> i >> x;\n            rbst.insert(root, i, S{x,\
    \ 1});\n            N++;\n        } else if (tp == 1) {\n            int i;\n\
    \            cin >> i;\n            rbst.erase(root, i);\n            N--;\n \
    \       } else if (tp == 2) {\n            int l, r;\n            cin >> l >>\
    \ r;\n            rbst.reverse(root, l, r);\n        } else if (tp == 3) {\n \
    \           int l, r, b, c;\n            cin >> l >> r >> b >> c;\n          \
    \  rbst.apply(root, l, r, {true, {b, c}});\n        } else if (tp == 4) {\n  \
    \          int l, r;\n            cin >> l >> r;\n            cout << rbst.prod(root,\
    \ l, r).sum << '\\n';\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum\"\
    \n#include \"../lazy_rbst.hpp\"\n#include \"../../modint.hpp\"\n#include <algorithm>\n\
    #include <iostream>\n#include <utility>\n#include <vector>\nusing namespace std;\n\
    \nusing mint = ModInt<998244353>;\n\nstruct S {\n    mint sum;\n    int sz;\n\
    };\nusing F = pair<bool, pair<mint, mint>>;\nS op(S l, S r) { return S{l.sum +\
    \ r.sum, l.sz + r.sz}; }\nS mapping(F f, S x) {\n    if (!f.first) return x;\n\
    \    mint a = f.second.first, b = f.second.second;\n    return {x.sum * a + b\
    \ * x.sz, x.sz};\n}\nS reversal(S x) { return x; }\nF composition(F fnew, F gold)\
    \ {\n    if (!fnew.first) return gold;\n    if (!gold.first) return fnew;\n  \
    \  auto anew = fnew.second.first, bnew = fnew.second.second;\n    auto aold =\
    \ gold.second.first, bold = gold.second.second;\n    return {true, {anew * aold,\
    \ anew * bold + bnew}};\n}\nF id() { return {false, {1, 0}}; }\n\nint main() {\n\
    \    cin.tie(nullptr), ios::sync_with_stdio(false);\n    int N, Q;\n    cin >>\
    \ N >> Q;\n    vector<S> A(N);\n    for (auto &x : A) cin >> x.sum, x.sz = 1;\n\
    \    lazy_rbst<1000001, S, op, F, reversal, mapping, composition, id> rbst;\n\n\
    \    auto root = rbst.new_tree();\n    rbst.assign(root, A);\n    while (Q--)\
    \ {\n        int tp;\n        cin >> tp;\n        if (tp == 0) {\n           \
    \ int i, x;\n            cin >> i >> x;\n            rbst.insert(root, i, S{x,\
    \ 1});\n            N++;\n        } else if (tp == 1) {\n            int i;\n\
    \            cin >> i;\n            rbst.erase(root, i);\n            N--;\n \
    \       } else if (tp == 2) {\n            int l, r;\n            cin >> l >>\
    \ r;\n            rbst.reverse(root, l, r);\n        } else if (tp == 3) {\n \
    \           int l, r, b, c;\n            cin >> l >> r >> b >> c;\n          \
    \  rbst.apply(root, l, r, {true, {b, c}});\n        } else if (tp == 4) {\n  \
    \          int l, r;\n            cin >> l >> r;\n            cout << rbst.prod(root,\
    \ l, r).sum << '\\n';\n        }\n    }\n}\n"
  dependsOn:
  - data_structure/lazy_rbst.hpp
  - modint.hpp
  isVerificationFile: true
  path: data_structure/test/lazy_rbst.test.cpp
  requiredBy: []
  timestamp: '2021-08-26 00:10:39+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: data_structure/test/lazy_rbst.test.cpp
layout: document
redirect_from:
- /verify/data_structure/test/lazy_rbst.test.cpp
- /verify/data_structure/test/lazy_rbst.test.cpp.html
title: data_structure/test/lazy_rbst.test.cpp
---
