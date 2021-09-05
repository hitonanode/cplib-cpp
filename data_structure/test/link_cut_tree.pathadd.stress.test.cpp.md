---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/link_cut_tree.hpp
    title: Link-Cut tree
  - icon: ':question:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':heavy_check_mark:'
    path: random/xorshift.hpp
    title: random/xorshift.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
  bundledCode: "#line 1 \"data_structure/test/link_cut_tree.pathadd.stress.test.cpp\"\
    \n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \ // DUMMY\n#line 2 \"data_structure/link_cut_tree.hpp\"\n\n// CUT begin\n// Link-Cut\
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
    \ id>;\nvector<LCT::Node*> vs;\n*/\n#line 2 \"modint.hpp\"\n#include <iostream>\n\
    #include <set>\n#include <vector>\n\n// CUT begin\ntemplate <int md> struct ModInt\
    \ {\n#if __cplusplus >= 201402L\n#define MDCONST constexpr\n#else\n#define MDCONST\n\
    #endif\n    using lint = long long;\n    MDCONST static int mod() { return md;\
    \ }\n    static int get_primitive_root() {\n        static int primitive_root\
    \ = 0;\n        if (!primitive_root) {\n            primitive_root = [&]() {\n\
    \                std::set<int> fac;\n                int v = md - 1;\n       \
    \         for (lint i = 2; i * i <= v; i++)\n                    while (v % i\
    \ == 0) fac.insert(i), v /= i;\n                if (v > 1) fac.insert(v);\n  \
    \              for (int g = 1; g < md; g++) {\n                    bool ok = true;\n\
    \                    for (auto i : fac)\n                        if (ModInt(g).pow((md\
    \ - 1) / i) == 1) {\n                            ok = false;\n               \
    \             break;\n                        }\n                    if (ok) return\
    \ g;\n                }\n                return -1;\n            }();\n      \
    \  }\n        return primitive_root;\n    }\n    int val;\n    MDCONST ModInt()\
    \ : val(0) {}\n    MDCONST ModInt &_setval(lint v) { return val = (v >= md ? v\
    \ - md : v), *this; }\n    MDCONST ModInt(lint v) { _setval(v % md + md); }\n\
    \    MDCONST explicit operator bool() const { return val != 0; }\n    MDCONST\
    \ ModInt operator+(const ModInt &x) const { return ModInt()._setval((lint)val\
    \ + x.val); }\n    MDCONST ModInt operator-(const ModInt &x) const { return ModInt()._setval((lint)val\
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
    \ = ModInt<998244353>;\n// using mint = ModInt<1000000007>;\n#line 2 \"random/xorshift.hpp\"\
    \n#include <cstdint>\n\n// CUT begin\nuint32_t rand_int() // XorShift random integer\
    \ generator\n{\n    static uint32_t x = 123456789, y = 362436069, z = 521288629,\
    \ w = 88675123;\n    uint32_t t = x ^ (x << 11);\n    x = y;\n    y = z;\n   \
    \ z = w;\n    return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));\n}\ndouble rand_double()\
    \ { return (double)rand_int() / UINT32_MAX; }\n#line 5 \"data_structure/test/link_cut_tree.pathadd.stress.test.cpp\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <cstdio>\n#include <unordered_set>\n\
    #include <utility>\nusing namespace std;\n\nconstexpr int md = 998244353;\nconst\
    \ int NTRY = 10000;\nconst int VMAX = 100;\nconst int QPERTRY = 500;\nusing mint\
    \ = ModInt<md>;\n\nusing S = pair<int, mint>;\nusing F = pair<bool, mint>;\nS\
    \ op(S l, S r) { return {l.first + r.first, l.second + r.second}; }\nS mapping(F\
    \ f, S x) { return f.first ? S{x.first, x.second + x.first * f.second} : x; }\n\
    S reversal(S x) { return x; }\nF composition(F fnew, F gold) { return fnew.first\
    \ ? F{true, fnew.second + gold.second} : gold; }\nF id() { return F{false, 0};\
    \ }\nusing LCT = lazy_linkcuttree<S, F, op, reversal, mapping, composition, id>;\n\
    \nvector<int> connected_vertices(int N, int r, const vector<unordered_set<int>>\
    \ &to) {\n    vector<int> visited(N);\n    vector<int> ret, tmp{r};\n    while\
    \ (tmp.size()) {\n        int now = tmp.back();\n        tmp.pop_back();\n   \
    \     ret.push_back(now);\n        visited[now] = 1;\n        for (auto nxt :\
    \ to[now]) {\n            if (!visited[nxt]) tmp.push_back(nxt);\n        }\n\
    \    }\n    return ret;\n}\n\nvector<int> get_rev_path(int s, int t, int prv,\
    \ const vector<unordered_set<int>> &to) {\n    if (s == t) return {s};\n    for\
    \ (auto nxt : to[s]) {\n        if (nxt == prv) continue;\n        auto v = get_rev_path(nxt,\
    \ t, s, to);\n        if (v.size()) {\n            v.push_back(s);\n         \
    \   return v;\n        }\n    }\n    return {};\n}\n\nmint gen_random_mint() {\
    \ return mint(rand_int() % mint::mod()); }\n\nint main() {\n    for (int ntry\
    \ = 0; ntry < NTRY; ntry++) {\n        const int N = 2 + rand_int() % (VMAX -\
    \ 1);\n        const int W = rand_int() % N + 1;\n        vector<mint> A(N);\n\
    \        LCT tree;\n        vector<LCT::Node *> nodes;\n\n        for (int i =\
    \ 0; i < N; i++) {\n            A[i] = gen_random_mint();\n            nodes.push_back(tree.make_node({1,\
    \ A[i]}));\n        }\n        vector<pair<int, int>> edges;\n        vector<unordered_set<int>>\
    \ to(N);\n\n        for (int i = 1; i < N; i++) {\n            int j = max<int>(0,\
    \ i - 1 - rand_int() % W);\n            edges.emplace_back(i, j);\n          \
    \  to[i].insert(j);\n            to[j].insert(i);\n            tree.link(nodes[i],\
    \ nodes[j]);\n        }\n\n        for (int q = 0; q < QPERTRY; q++) {\n     \
    \       const int tp = rand_int() % 5;\n            if (tp == 0) {\n         \
    \       // cut() & link()\n                int e = rand_int() % edges.size();\n\
    \                int a = edges[e].first, b = edges[e].second;\n\n            \
    \    to[a].erase(b), to[b].erase(a);\n                tree.cut(nodes[a], nodes[b]);\n\
    \n                vector<int> va = connected_vertices(N, a, to), vb = connected_vertices(N,\
    \ b, to);\n                assert(int(va.size() + vb.size()) == N);\n        \
    \        a = va[rand_int() % va.size()], b = vb[rand_int() % vb.size()];\n   \
    \             to[a].insert(b), to[b].insert(a);\n                edges[e] = {a,\
    \ b};\n                tree.link(nodes[a], nodes[b]);\n            } else if (tp\
    \ == 1) {\n                // apply()\n                const int u = rand_int()\
    \ % N, v = rand_int() % N;\n                const auto a = gen_random_mint();\n\
    \                tree.apply(nodes[u], nodes[v], {true, a});\n\n              \
    \  for (auto i : get_rev_path(u, v, -1, to)) A[i] += a;\n\n            } else\
    \ if (tp == 2) {\n                // prod()\n                const int u = rand_int()\
    \ % N, v = rand_int() % N;\n                mint ret1 = tree.prod(nodes[u], nodes[v]).second,\
    \ ret2 = 0;\n                for (auto i : get_rev_path(v, u, -1, to)) ret2 +=\
    \ A[i];\n                assert(ret1 == ret2);\n\n            } else if (tp ==\
    \ 3) {\n                // set()\n                const int u = rand_int() % N;\n\
    \                const auto a = gen_random_mint();\n                tree.set(nodes[u],\
    \ {1, a});\n                A[u] = a;\n\n            } else if (tp == 4) {\n \
    \               // get()\n                const int u = rand_int() % N;\n    \
    \            const mint a = tree.get(nodes[u]).second;\n                assert(a\
    \ == A[u]);\n            } else {\n                exit(8);\n            }\n \
    \       }\n    }\n    puts(\"Hello World\");\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \ // DUMMY\n#include \"../link_cut_tree.hpp\"\n#include \"../../modint.hpp\"\n\
    #include \"../../random/xorshift.hpp\"\n\n#include <algorithm>\n#include <cassert>\n\
    #include <cstdio>\n#include <unordered_set>\n#include <utility>\nusing namespace\
    \ std;\n\nconstexpr int md = 998244353;\nconst int NTRY = 10000;\nconst int VMAX\
    \ = 100;\nconst int QPERTRY = 500;\nusing mint = ModInt<md>;\n\nusing S = pair<int,\
    \ mint>;\nusing F = pair<bool, mint>;\nS op(S l, S r) { return {l.first + r.first,\
    \ l.second + r.second}; }\nS mapping(F f, S x) { return f.first ? S{x.first, x.second\
    \ + x.first * f.second} : x; }\nS reversal(S x) { return x; }\nF composition(F\
    \ fnew, F gold) { return fnew.first ? F{true, fnew.second + gold.second} : gold;\
    \ }\nF id() { return F{false, 0}; }\nusing LCT = lazy_linkcuttree<S, F, op, reversal,\
    \ mapping, composition, id>;\n\nvector<int> connected_vertices(int N, int r, const\
    \ vector<unordered_set<int>> &to) {\n    vector<int> visited(N);\n    vector<int>\
    \ ret, tmp{r};\n    while (tmp.size()) {\n        int now = tmp.back();\n    \
    \    tmp.pop_back();\n        ret.push_back(now);\n        visited[now] = 1;\n\
    \        for (auto nxt : to[now]) {\n            if (!visited[nxt]) tmp.push_back(nxt);\n\
    \        }\n    }\n    return ret;\n}\n\nvector<int> get_rev_path(int s, int t,\
    \ int prv, const vector<unordered_set<int>> &to) {\n    if (s == t) return {s};\n\
    \    for (auto nxt : to[s]) {\n        if (nxt == prv) continue;\n        auto\
    \ v = get_rev_path(nxt, t, s, to);\n        if (v.size()) {\n            v.push_back(s);\n\
    \            return v;\n        }\n    }\n    return {};\n}\n\nmint gen_random_mint()\
    \ { return mint(rand_int() % mint::mod()); }\n\nint main() {\n    for (int ntry\
    \ = 0; ntry < NTRY; ntry++) {\n        const int N = 2 + rand_int() % (VMAX -\
    \ 1);\n        const int W = rand_int() % N + 1;\n        vector<mint> A(N);\n\
    \        LCT tree;\n        vector<LCT::Node *> nodes;\n\n        for (int i =\
    \ 0; i < N; i++) {\n            A[i] = gen_random_mint();\n            nodes.push_back(tree.make_node({1,\
    \ A[i]}));\n        }\n        vector<pair<int, int>> edges;\n        vector<unordered_set<int>>\
    \ to(N);\n\n        for (int i = 1; i < N; i++) {\n            int j = max<int>(0,\
    \ i - 1 - rand_int() % W);\n            edges.emplace_back(i, j);\n          \
    \  to[i].insert(j);\n            to[j].insert(i);\n            tree.link(nodes[i],\
    \ nodes[j]);\n        }\n\n        for (int q = 0; q < QPERTRY; q++) {\n     \
    \       const int tp = rand_int() % 5;\n            if (tp == 0) {\n         \
    \       // cut() & link()\n                int e = rand_int() % edges.size();\n\
    \                int a = edges[e].first, b = edges[e].second;\n\n            \
    \    to[a].erase(b), to[b].erase(a);\n                tree.cut(nodes[a], nodes[b]);\n\
    \n                vector<int> va = connected_vertices(N, a, to), vb = connected_vertices(N,\
    \ b, to);\n                assert(int(va.size() + vb.size()) == N);\n        \
    \        a = va[rand_int() % va.size()], b = vb[rand_int() % vb.size()];\n   \
    \             to[a].insert(b), to[b].insert(a);\n                edges[e] = {a,\
    \ b};\n                tree.link(nodes[a], nodes[b]);\n            } else if (tp\
    \ == 1) {\n                // apply()\n                const int u = rand_int()\
    \ % N, v = rand_int() % N;\n                const auto a = gen_random_mint();\n\
    \                tree.apply(nodes[u], nodes[v], {true, a});\n\n              \
    \  for (auto i : get_rev_path(u, v, -1, to)) A[i] += a;\n\n            } else\
    \ if (tp == 2) {\n                // prod()\n                const int u = rand_int()\
    \ % N, v = rand_int() % N;\n                mint ret1 = tree.prod(nodes[u], nodes[v]).second,\
    \ ret2 = 0;\n                for (auto i : get_rev_path(v, u, -1, to)) ret2 +=\
    \ A[i];\n                assert(ret1 == ret2);\n\n            } else if (tp ==\
    \ 3) {\n                // set()\n                const int u = rand_int() % N;\n\
    \                const auto a = gen_random_mint();\n                tree.set(nodes[u],\
    \ {1, a});\n                A[u] = a;\n\n            } else if (tp == 4) {\n \
    \               // get()\n                const int u = rand_int() % N;\n    \
    \            const mint a = tree.get(nodes[u]).second;\n                assert(a\
    \ == A[u]);\n            } else {\n                exit(8);\n            }\n \
    \       }\n    }\n    puts(\"Hello World\");\n}\n"
  dependsOn:
  - data_structure/link_cut_tree.hpp
  - modint.hpp
  - random/xorshift.hpp
  isVerificationFile: true
  path: data_structure/test/link_cut_tree.pathadd.stress.test.cpp
  requiredBy: []
  timestamp: '2021-07-23 17:14:41+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: data_structure/test/link_cut_tree.pathadd.stress.test.cpp
layout: document
redirect_from:
- /verify/data_structure/test/link_cut_tree.pathadd.stress.test.cpp
- /verify/data_structure/test/link_cut_tree.pathadd.stress.test.cpp.html
title: data_structure/test/link_cut_tree.pathadd.stress.test.cpp
---
