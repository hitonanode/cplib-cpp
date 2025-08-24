---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/link_cut_tree.hpp
    title: Link-Cut tree
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
    PROBLEM: https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite
    links:
    - https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite
  bundledCode: "#line 1 \"data_structure/test/link_cut_tree.composition.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite\"\
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
    \ id>;\nvector<LCT::Node*> vs;\n*/\n#line 2 \"modint.hpp\"\n#include <cassert>\n\
    #include <iostream>\n#include <set>\n#include <vector>\n\ntemplate <int md> struct\
    \ ModInt {\n    static_assert(md > 1);\n    using lint = long long;\n    constexpr\
    \ static int mod() { return md; }\n    static int get_primitive_root() {\n   \
    \     static int primitive_root = 0;\n        if (!primitive_root) {\n       \
    \     primitive_root = [&]() {\n                std::set<int> fac;\n         \
    \       int v = md - 1;\n                for (lint i = 2; i * i <= v; i++)\n \
    \                   while (v % i == 0) fac.insert(i), v /= i;\n              \
    \  if (v > 1) fac.insert(v);\n                for (int g = 1; g < md; g++) {\n\
    \                    bool ok = true;\n                    for (auto i : fac)\n\
    \                        if (ModInt(g).pow((md - 1) / i) == 1) {\n           \
    \                 ok = false;\n                            break;\n          \
    \              }\n                    if (ok) return g;\n                }\n \
    \               return -1;\n            }();\n        }\n        return primitive_root;\n\
    \    }\n    int val_;\n    int val() const noexcept { return val_; }\n    constexpr\
    \ ModInt() : val_(0) {}\n    constexpr ModInt &_setval(lint v) { return val_ =\
    \ (v >= md ? v - md : v), *this; }\n    constexpr ModInt(lint v) { _setval(v %\
    \ md + md); }\n    constexpr explicit operator bool() const { return val_ != 0;\
    \ }\n    constexpr ModInt operator+(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ + x.val_);\n    }\n    constexpr ModInt operator-(const ModInt &x) const {\n\
    \        return ModInt()._setval((lint)val_ - x.val_ + md);\n    }\n    constexpr\
    \ ModInt operator*(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ * x.val_ % md);\n    }\n    constexpr ModInt operator/(const ModInt &x) const\
    \ {\n        return ModInt()._setval((lint)val_ * x.inv().val() % md);\n    }\n\
    \    constexpr ModInt operator-() const { return ModInt()._setval(md - val_);\
    \ }\n    constexpr ModInt &operator+=(const ModInt &x) { return *this = *this\
    \ + x; }\n    constexpr ModInt &operator-=(const ModInt &x) { return *this = *this\
    \ - x; }\n    constexpr ModInt &operator*=(const ModInt &x) { return *this = *this\
    \ * x; }\n    constexpr ModInt &operator/=(const ModInt &x) { return *this = *this\
    \ / x; }\n    friend constexpr ModInt operator+(lint a, const ModInt &x) { return\
    \ ModInt(a) + x; }\n    friend constexpr ModInt operator-(lint a, const ModInt\
    \ &x) { return ModInt(a) - x; }\n    friend constexpr ModInt operator*(lint a,\
    \ const ModInt &x) { return ModInt(a) * x; }\n    friend constexpr ModInt operator/(lint\
    \ a, const ModInt &x) { return ModInt(a) / x; }\n    constexpr bool operator==(const\
    \ ModInt &x) const { return val_ == x.val_; }\n    constexpr bool operator!=(const\
    \ ModInt &x) const { return val_ != x.val_; }\n    constexpr bool operator<(const\
    \ ModInt &x) const {\n        return val_ < x.val_;\n    } // To use std::map<ModInt,\
    \ T>\n    friend std::istream &operator>>(std::istream &is, ModInt &x) {\n   \
    \     lint t;\n        return is >> t, x = ModInt(t), is;\n    }\n    constexpr\
    \ friend std::ostream &operator<<(std::ostream &os, const ModInt &x) {\n     \
    \   return os << x.val_;\n    }\n\n    constexpr ModInt pow(lint n) const {\n\
    \        ModInt ans = 1, tmp = *this;\n        while (n) {\n            if (n\
    \ & 1) ans *= tmp;\n            tmp *= tmp, n >>= 1;\n        }\n        return\
    \ ans;\n    }\n\n    static constexpr int cache_limit = std::min(md, 1 << 21);\n\
    \    static std::vector<ModInt> facs, facinvs, invs;\n\n    constexpr static void\
    \ _precalculation(int N) {\n        const int l0 = facs.size();\n        if (N\
    \ > md) N = md;\n        if (N <= l0) return;\n        facs.resize(N), facinvs.resize(N),\
    \ invs.resize(N);\n        for (int i = l0; i < N; i++) facs[i] = facs[i - 1]\
    \ * i;\n        facinvs[N - 1] = facs.back().pow(md - 2);\n        for (int i\
    \ = N - 2; i >= l0; i--) facinvs[i] = facinvs[i + 1] * (i + 1);\n        for (int\
    \ i = N - 1; i >= l0; i--) invs[i] = facinvs[i] * facs[i - 1];\n    }\n\n    constexpr\
    \ ModInt inv() const {\n        if (this->val_ < cache_limit) {\n            if\
    \ (facs.empty()) facs = {1}, facinvs = {1}, invs = {0};\n            while (this->val_\
    \ >= int(facs.size())) _precalculation(facs.size() * 2);\n            return invs[this->val_];\n\
    \        } else {\n            return this->pow(md - 2);\n        }\n    }\n\n\
    \    constexpr static ModInt fac(int n) {\n        assert(n >= 0);\n        if\
    \ (n >= md) return ModInt(0);\n        while (n >= int(facs.size())) _precalculation(facs.size()\
    \ * 2);\n        return facs[n];\n    }\n\n    constexpr static ModInt facinv(int\
    \ n) {\n        assert(n >= 0);\n        if (n >= md) return ModInt(0);\n    \
    \    while (n >= int(facs.size())) _precalculation(facs.size() * 2);\n       \
    \ return facinvs[n];\n    }\n\n    constexpr static ModInt doublefac(int n) {\n\
    \        assert(n >= 0);\n        if (n >= md) return ModInt(0);\n        long\
    \ long k = (n + 1) / 2;\n        return (n & 1) ? ModInt::fac(k * 2) / (ModInt(2).pow(k)\
    \ * ModInt::fac(k))\n                       : ModInt::fac(k) * ModInt(2).pow(k);\n\
    \    }\n\n    constexpr static ModInt nCr(int n, int r) {\n        assert(n >=\
    \ 0);\n        if (r < 0 or n < r) return ModInt(0);\n        return ModInt::fac(n)\
    \ * ModInt::facinv(r) * ModInt::facinv(n - r);\n    }\n\n    constexpr static\
    \ ModInt nPr(int n, int r) {\n        assert(n >= 0);\n        if (r < 0 or n\
    \ < r) return ModInt(0);\n        return ModInt::fac(n) * ModInt::facinv(n - r);\n\
    \    }\n\n    static ModInt binom(int n, int r) {\n        static long long bruteforce_times\
    \ = 0;\n\n        if (r < 0 or n < r) return ModInt(0);\n        if (n <= bruteforce_times\
    \ or n < (int)facs.size()) return ModInt::nCr(n, r);\n\n        r = std::min(r,\
    \ n - r);\n\n        ModInt ret = ModInt::facinv(r);\n        for (int i = 0;\
    \ i < r; ++i) ret *= n - i;\n        bruteforce_times += r;\n\n        return\
    \ ret;\n    }\n\n    // Multinomial coefficient, (k_1 + k_2 + ... + k_m)! / (k_1!\
    \ k_2! ... k_m!)\n    // Complexity: O(sum(ks))\n    template <class Vec> static\
    \ ModInt multinomial(const Vec &ks) {\n        ModInt ret{1};\n        int sum\
    \ = 0;\n        for (int k : ks) {\n            assert(k >= 0);\n            ret\
    \ *= ModInt::facinv(k), sum += k;\n        }\n        return ret * ModInt::fac(sum);\n\
    \    }\n    template <class... Args> static ModInt multinomial(Args... args) {\n\
    \        int sum = (0 + ... + args);\n        ModInt result = (1 * ... * ModInt::facinv(args));\n\
    \        return ModInt::fac(sum) * result;\n    }\n\n    // Catalan number, C_n\
    \ = binom(2n, n) / (n + 1) = # of Dyck words of length 2n\n    // C_0 = 1, C_1\
    \ = 1, C_2 = 2, C_3 = 5, C_4 = 14, ...\n    // https://oeis.org/A000108\n    //\
    \ Complexity: O(n)\n    static ModInt catalan(int n) {\n        if (n < 0) return\
    \ ModInt(0);\n        return ModInt::fac(n * 2) * ModInt::facinv(n + 1) * ModInt::facinv(n);\n\
    \    }\n\n    ModInt sqrt() const {\n        if (val_ == 0) return 0;\n      \
    \  if (md == 2) return val_;\n        if (pow((md - 1) / 2) != 1) return 0;\n\
    \        ModInt b = 1;\n        while (b.pow((md - 1) / 2) == 1) b += 1;\n   \
    \     int e = 0, m = md - 1;\n        while (m % 2 == 0) m >>= 1, e++;\n     \
    \   ModInt x = pow((m - 1) / 2), y = (*this) * x * x;\n        x *= (*this);\n\
    \        ModInt z = b.pow(m);\n        while (y != 1) {\n            int j = 0;\n\
    \            ModInt t = y;\n            while (t != 1) j++, t *= t;\n        \
    \    z = z.pow(1LL << (e - j - 1));\n            x *= z, z *= z, y *= z;\n   \
    \         e = j;\n        }\n        return ModInt(std::min(x.val_, md - x.val_));\n\
    \    }\n};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facs = {1};\n\
    template <int md> std::vector<ModInt<md>> ModInt<md>::facinvs = {1};\ntemplate\
    \ <int md> std::vector<ModInt<md>> ModInt<md>::invs = {0};\n\nusing ModInt998244353\
    \ = ModInt<998244353>;\n// using mint = ModInt<998244353>;\n// using mint = ModInt<1000000007>;\n\
    #line 5 \"data_structure/test/link_cut_tree.composition.test.cpp\"\n#include <tuple>\n\
    #include <utility>\nusing namespace std;\n\nusing mint = ModInt<998244353>;\n\
    using S = pair<pair<mint, mint>, pair<mint, mint>>;\nusing F = tuple<>;\n\nS reversal(S\
    \ x) { return {x.second, x.first}; }\npair<mint, mint> opS(pair<mint, mint> l,\
    \ pair<mint, mint> r) {\n    return {l.first * r.first, r.second + r.first * l.second};\n\
    }\nS op(S l, S r) { return {opS(l.first, r.first), opS(r.second, l.second)}; }\n\
    S mapping(F, S x) { return x; }\nF id() { return {}; }\nF composition(F, F) {\
    \ return id(); }\nusing LCT = lazy_linkcuttree<S, F, op, reversal, mapping, composition,\
    \ id>;\n\nLCT::Node *vs[200000];\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \    int N, Q;\n    cin >> N >> Q;\n    LCT lct;\n    for (int i = 0; i < N; i++)\
    \ {\n        mint a, b;\n        cin >> a >> b;\n        vs[i] = lct.make_node({{a,\
    \ b}, {a, b}});\n    }\n    for (int e = 0; e < N - 1; e++) {\n        int u,\
    \ v;\n        cin >> u >> v;\n        lct.link(vs[u], vs[v]);\n    }\n    while\
    \ (Q--) {\n        int tp;\n        cin >> tp;\n        if (tp == 0) {\n     \
    \       int u, v, w, x;\n            cin >> u >> v >> w >> x;\n            lct.cut(vs[u],\
    \ vs[v]);\n            lct.link(vs[x], vs[w]);\n        }\n        if (tp == 1)\
    \ {\n            int p;\n            mint c, d;\n            cin >> p >> c >>\
    \ d;\n            lct.set(vs[p], {{c, d}, {c, d}});\n        }\n        if (tp\
    \ == 2) {\n            int u, v;\n            mint x;\n            cin >> u >>\
    \ v >> x;\n            auto p = lct.prod(vs[u], vs[v]).first;\n            cout\
    \ << x * p.first + p.second << '\\n';\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite\"\
    \n#include \"../link_cut_tree.hpp\"\n#include \"../../modint.hpp\"\n#include <iostream>\n\
    #include <tuple>\n#include <utility>\nusing namespace std;\n\nusing mint = ModInt<998244353>;\n\
    using S = pair<pair<mint, mint>, pair<mint, mint>>;\nusing F = tuple<>;\n\nS reversal(S\
    \ x) { return {x.second, x.first}; }\npair<mint, mint> opS(pair<mint, mint> l,\
    \ pair<mint, mint> r) {\n    return {l.first * r.first, r.second + r.first * l.second};\n\
    }\nS op(S l, S r) { return {opS(l.first, r.first), opS(r.second, l.second)}; }\n\
    S mapping(F, S x) { return x; }\nF id() { return {}; }\nF composition(F, F) {\
    \ return id(); }\nusing LCT = lazy_linkcuttree<S, F, op, reversal, mapping, composition,\
    \ id>;\n\nLCT::Node *vs[200000];\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \    int N, Q;\n    cin >> N >> Q;\n    LCT lct;\n    for (int i = 0; i < N; i++)\
    \ {\n        mint a, b;\n        cin >> a >> b;\n        vs[i] = lct.make_node({{a,\
    \ b}, {a, b}});\n    }\n    for (int e = 0; e < N - 1; e++) {\n        int u,\
    \ v;\n        cin >> u >> v;\n        lct.link(vs[u], vs[v]);\n    }\n    while\
    \ (Q--) {\n        int tp;\n        cin >> tp;\n        if (tp == 0) {\n     \
    \       int u, v, w, x;\n            cin >> u >> v >> w >> x;\n            lct.cut(vs[u],\
    \ vs[v]);\n            lct.link(vs[x], vs[w]);\n        }\n        if (tp == 1)\
    \ {\n            int p;\n            mint c, d;\n            cin >> p >> c >>\
    \ d;\n            lct.set(vs[p], {{c, d}, {c, d}});\n        }\n        if (tp\
    \ == 2) {\n            int u, v;\n            mint x;\n            cin >> u >>\
    \ v >> x;\n            auto p = lct.prod(vs[u], vs[v]).first;\n            cout\
    \ << x * p.first + p.second << '\\n';\n        }\n    }\n}\n"
  dependsOn:
  - data_structure/link_cut_tree.hpp
  - modint.hpp
  isVerificationFile: true
  path: data_structure/test/link_cut_tree.composition.test.cpp
  requiredBy: []
  timestamp: '2025-08-25 00:44:48+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: data_structure/test/link_cut_tree.composition.test.cpp
layout: document
redirect_from:
- /verify/data_structure/test/link_cut_tree.composition.test.cpp
- /verify/data_structure/test/link_cut_tree.composition.test.cpp.html
title: data_structure/test/link_cut_tree.composition.test.cpp
---
