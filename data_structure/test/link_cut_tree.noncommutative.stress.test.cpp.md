---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/link_cut_tree.hpp
    title: Link-Cut tree
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/matrix.hpp
    title: linear_algebra_matrix/matrix.hpp
  - icon: ':question:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':question:'
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
  bundledCode: "#line 1 \"data_structure/test/link_cut_tree.noncommutative.stress.test.cpp\"\
    \n// \u30D1\u30B9\u4E0A\u306E\u9802\u70B9\u66F4\u65B0\u30FB\u30D1\u30B9\u4E0A\u306E\
    \u9802\u70B9\u7A4D\u53D6\u5F97\u304C\u53EF\u80FD\u306A Link-Cut tree\n// \u5404\
    \u9802\u70B9\u306B 2x2 \u884C\u5217\u3092\u8F09\u305B\uFF0C\u6F14\u7B97\u3068\u3057\
    \u3066\u884C\u5217\u7A4D\u304C\u5165\u308B\u975E\u53EF\u63DB\u30FB\u30D1\u30B9\
    \u4E0A\u66F4\u65B0\u306E\u4F8B\uFF0E\n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \ // DUMMY\n#line 2 \"data_structure/link_cut_tree.hpp\"\n\n// CUT begin\n// Link-Cut\
    \ Tree\n// Reference:\n// - https://www.slideshare.net/iwiwi/2-12188845\n// -\
    \ https://ei1333.github.io/library/structure/lct/link-cut-tree-lazy-path.cpp\n\
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
    \ id>;\nvector<LCT::Node*> vs;\n*/\n#line 2 \"linear_algebra_matrix/matrix.hpp\"\
    \n#include <algorithm>\n#include <cassert>\n#include <cmath>\n#include <iterator>\n\
    #include <type_traits>\n#include <utility>\n#include <vector>\n\nnamespace matrix_\
    \ {\nstruct has_id_method_impl {\n    template <class T_> static auto check(T_\
    \ *) -> decltype(T_::id(), std::true_type());\n    template <class T_> static\
    \ auto check(...) -> std::false_type;\n};\ntemplate <class T_> struct has_id :\
    \ decltype(has_id_method_impl::check<T_>(nullptr)) {};\n} // namespace matrix_\n\
    \ntemplate <typename T> struct matrix {\n    int H, W;\n    std::vector<T> elem;\n\
    \    typename std::vector<T>::iterator operator[](int i) { return elem.begin()\
    \ + i * W; }\n    inline T &at(int i, int j) { return elem[i * W + j]; }\n   \
    \ inline T get(int i, int j) const { return elem[i * W + j]; }\n    int height()\
    \ const { return H; }\n    int width() const { return W; }\n    std::vector<std::vector<T>>\
    \ vecvec() const {\n        std::vector<std::vector<T>> ret(H);\n        for (int\
    \ i = 0; i < H; i++) {\n            std::copy(elem.begin() + i * W, elem.begin()\
    \ + (i + 1) * W, std::back_inserter(ret[i]));\n        }\n        return ret;\n\
    \    }\n    operator std::vector<std::vector<T>>() const { return vecvec(); }\n\
    \    matrix() = default;\n    matrix(int H, int W) : H(H), W(W), elem(H * W) {}\n\
    \    matrix(const std::vector<std::vector<T>> &d) : H(d.size()), W(d.size() ?\
    \ d[0].size() : 0) {\n        for (auto &raw : d) std::copy(raw.begin(), raw.end(),\
    \ std::back_inserter(elem));\n    }\n\n    template <typename T2, typename std::enable_if<matrix_::has_id<T2>::value>::type\
    \ * = nullptr>\n    static T2 _T_id() {\n        return T2::id();\n    }\n   \
    \ template <typename T2, typename std::enable_if<!matrix_::has_id<T2>::value>::type\
    \ * = nullptr>\n    static T2 _T_id() {\n        return T2(1);\n    }\n\n    static\
    \ matrix Identity(int N) {\n        matrix ret(N, N);\n        for (int i = 0;\
    \ i < N; i++) ret.at(i, i) = _T_id<T>();\n        return ret;\n    }\n\n    matrix\
    \ operator-() const {\n        matrix ret(H, W);\n        for (int i = 0; i <\
    \ H * W; i++) ret.elem[i] = -elem[i];\n        return ret;\n    }\n    matrix\
    \ operator*(const T &v) const {\n        matrix ret = *this;\n        for (auto\
    \ &x : ret.elem) x *= v;\n        return ret;\n    }\n    matrix operator/(const\
    \ T &v) const {\n        matrix ret = *this;\n        const T vinv = _T_id<T>()\
    \ / v;\n        for (auto &x : ret.elem) x *= vinv;\n        return ret;\n   \
    \ }\n    matrix operator+(const matrix &r) const {\n        matrix ret = *this;\n\
    \        for (int i = 0; i < H * W; i++) ret.elem[i] += r.elem[i];\n        return\
    \ ret;\n    }\n    matrix operator-(const matrix &r) const {\n        matrix ret\
    \ = *this;\n        for (int i = 0; i < H * W; i++) ret.elem[i] -= r.elem[i];\n\
    \        return ret;\n    }\n    matrix operator*(const matrix &r) const {\n \
    \       matrix ret(H, r.W);\n        for (int i = 0; i < H; i++) {\n         \
    \   for (int k = 0; k < W; k++) {\n                for (int j = 0; j < r.W; j++)\
    \ ret.at(i, j) += this->get(i, k) * r.get(k, j);\n            }\n        }\n \
    \       return ret;\n    }\n    matrix &operator*=(const T &v) { return *this\
    \ = *this * v; }\n    matrix &operator/=(const T &v) { return *this = *this /\
    \ v; }\n    matrix &operator+=(const matrix &r) { return *this = *this + r; }\n\
    \    matrix &operator-=(const matrix &r) { return *this = *this - r; }\n    matrix\
    \ &operator*=(const matrix &r) { return *this = *this * r; }\n    bool operator==(const\
    \ matrix &r) const { return H == r.H and W == r.W and elem == r.elem; }\n    bool\
    \ operator!=(const matrix &r) const { return H != r.H or W != r.W or elem != r.elem;\
    \ }\n    bool operator<(const matrix &r) const { return elem < r.elem; }\n   \
    \ matrix pow(int64_t n) const {\n        matrix ret = Identity(H);\n        bool\
    \ ret_is_id = true;\n        if (n == 0) return ret;\n        for (int i = 63\
    \ - __builtin_clzll(n); i >= 0; i--) {\n            if (!ret_is_id) ret *= ret;\n\
    \            if ((n >> i) & 1) ret *= (*this), ret_is_id = false;\n        }\n\
    \        return ret;\n    }\n    std::vector<T> pow_vec(int64_t n, std::vector<T>\
    \ vec) const {\n        matrix x = *this;\n        while (n) {\n            if\
    \ (n & 1) vec = x * vec;\n            x *= x;\n            n >>= 1;\n        }\n\
    \        return vec;\n    };\n    matrix transpose() const {\n        matrix ret(W,\
    \ H);\n        for (int i = 0; i < H; i++) {\n            for (int j = 0; j <\
    \ W; j++) ret.at(j, i) = this->get(i, j);\n        }\n        return ret;\n  \
    \  }\n    // Gauss-Jordan elimination\n    // - Require inverse for every non-zero\
    \ element\n    // - Complexity: O(H^2 W)\n    template <typename T2, typename\
    \ std::enable_if<std::is_floating_point<T2>::value>::type * = nullptr>\n    static\
    \ int choose_pivot(const matrix<T2> &mtr, int h, int c) noexcept {\n        int\
    \ piv = -1;\n        for (int j = h; j < mtr.H; j++) {\n            if (mtr.get(j,\
    \ c) and (piv < 0 or std::abs(mtr.get(j, c)) > std::abs(mtr.get(piv, c))))\n \
    \               piv = j;\n        }\n        return piv;\n    }\n    template\
    \ <typename T2, typename std::enable_if<!std::is_floating_point<T2>::value>::type\
    \ * = nullptr>\n    static int choose_pivot(const matrix<T2> &mtr, int h, int\
    \ c) noexcept {\n        for (int j = h; j < mtr.H; j++) {\n            if (mtr.get(j,\
    \ c) != T2()) return j;\n        }\n        return -1;\n    }\n    matrix gauss_jordan()\
    \ const {\n        int c = 0;\n        matrix mtr(*this);\n        std::vector<int>\
    \ ws;\n        ws.reserve(W);\n        for (int h = 0; h < H; h++) {\n       \
    \     if (c == W) break;\n            int piv = choose_pivot(mtr, h, c);\n   \
    \         if (piv == -1) {\n                c++;\n                h--;\n     \
    \           continue;\n            }\n            if (h != piv) {\n          \
    \      for (int w = 0; w < W; w++) {\n                    std::swap(mtr[piv][w],\
    \ mtr[h][w]);\n                    mtr.at(piv, w) *= -_T_id<T>(); // To preserve\
    \ sign of determinant\n                }\n            }\n            ws.clear();\n\
    \            for (int w = c; w < W; w++) {\n                if (mtr.at(h, w) !=\
    \ T()) ws.emplace_back(w);\n            }\n            const T hcinv = _T_id<T>()\
    \ / mtr.at(h, c);\n            for (int hh = 0; hh < H; hh++)\n              \
    \  if (hh != h) {\n                    const T coeff = mtr.at(hh, c) * hcinv;\n\
    \                    for (auto w : ws) mtr.at(hh, w) -= mtr.at(h, w) * coeff;\n\
    \                    mtr.at(hh, c) = T();\n                }\n            c++;\n\
    \        }\n        return mtr;\n    }\n    int rank_of_gauss_jordan() const {\n\
    \        for (int i = H * W - 1; i >= 0; i--) {\n            if (elem[i] != 0)\
    \ return i / W + 1;\n        }\n        return 0;\n    }\n    int rank() const\
    \ { return gauss_jordan().rank_of_gauss_jordan(); }\n\n    T determinant_of_upper_triangle()\
    \ const {\n        T ret = _T_id<T>();\n        for (int i = 0; i < H; i++) ret\
    \ *= get(i, i);\n        return ret;\n    }\n    int inverse() {\n        assert(H\
    \ == W);\n        std::vector<std::vector<T>> ret = Identity(H), tmp = *this;\n\
    \        int rank = 0;\n        for (int i = 0; i < H; i++) {\n            int\
    \ ti = i;\n            while (ti < H and tmp[ti][i] == 0) ti++;\n            if\
    \ (ti == H) {\n                continue;\n            } else {\n             \
    \   rank++;\n            }\n            ret[i].swap(ret[ti]), tmp[i].swap(tmp[ti]);\n\
    \            T inv = _T_id<T>() / tmp[i][i];\n            for (int j = 0; j <\
    \ W; j++) ret[i][j] *= inv;\n            for (int j = i + 1; j < W; j++) tmp[i][j]\
    \ *= inv;\n            for (int h = 0; h < H; h++) {\n                if (i ==\
    \ h) continue;\n                const T c = -tmp[h][i];\n                for (int\
    \ j = 0; j < W; j++) ret[h][j] += ret[i][j] * c;\n                for (int j =\
    \ i + 1; j < W; j++) tmp[h][j] += tmp[i][j] * c;\n            }\n        }\n \
    \       *this = ret;\n        return rank;\n    }\n    friend std::vector<T> operator*(const\
    \ matrix &m, const std::vector<T> &v) {\n        assert(m.W == int(v.size()));\n\
    \        std::vector<T> ret(m.H);\n        for (int i = 0; i < m.H; i++) {\n \
    \           for (int j = 0; j < m.W; j++) ret[i] += m.get(i, j) * v[j];\n    \
    \    }\n        return ret;\n    }\n    friend std::vector<T> operator*(const\
    \ std::vector<T> &v, const matrix &m) {\n        assert(int(v.size()) == m.H);\n\
    \        std::vector<T> ret(m.W);\n        for (int i = 0; i < m.H; i++) {\n \
    \           for (int j = 0; j < m.W; j++) ret[j] += v[i] * m.get(i, j);\n    \
    \    }\n        return ret;\n    }\n    std::vector<T> prod(const std::vector<T>\
    \ &v) const { return (*this) * v; }\n    std::vector<T> prod_left(const std::vector<T>\
    \ &v) const { return v * (*this); }\n    template <class OStream> friend OStream\
    \ &operator<<(OStream &os, const matrix &x) {\n        os << \"[(\" << x.H <<\
    \ \" * \" << x.W << \" matrix)\";\n        os << \"\\n[column sums: \";\n    \
    \    for (int j = 0; j < x.W; j++) {\n            T s = 0;\n            for (int\
    \ i = 0; i < x.H; i++) s += x.get(i, j);\n            os << s << \",\";\n    \
    \    }\n        os << \"]\";\n        for (int i = 0; i < x.H; i++) {\n      \
    \      os << \"\\n[\";\n            for (int j = 0; j < x.W; j++) os << x.get(i,\
    \ j) << \",\";\n            os << \"]\";\n        }\n        os << \"]\\n\";\n\
    \        return os;\n    }\n    template <class IStream> friend IStream &operator>>(IStream\
    \ &is, matrix &x) {\n        for (auto &v : x.elem) is >> v;\n        return is;\n\
    \    }\n};\n#line 2 \"modint.hpp\"\n#include <iostream>\n#include <set>\n#line\
    \ 5 \"modint.hpp\"\n\ntemplate <int md> struct ModInt {\n#if __cplusplus >= 201402L\n\
    #define MDCONST constexpr\n#else\n#define MDCONST\n#endif\n    using lint = long\
    \ long;\n    MDCONST static int mod() { return md; }\n    static int get_primitive_root()\
    \ {\n        static int primitive_root = 0;\n        if (!primitive_root) {\n\
    \            primitive_root = [&]() {\n                std::set<int> fac;\n  \
    \              int v = md - 1;\n                for (lint i = 2; i * i <= v; i++)\n\
    \                    while (v % i == 0) fac.insert(i), v /= i;\n             \
    \   if (v > 1) fac.insert(v);\n                for (int g = 1; g < md; g++) {\n\
    \                    bool ok = true;\n                    for (auto i : fac)\n\
    \                        if (ModInt(g).pow((md - 1) / i) == 1) {\n           \
    \                 ok = false;\n                            break;\n          \
    \              }\n                    if (ok) return g;\n                }\n \
    \               return -1;\n            }();\n        }\n        return primitive_root;\n\
    \    }\n    int val_;\n    int val() const noexcept { return val_; }\n    MDCONST\
    \ ModInt() : val_(0) {}\n    MDCONST ModInt &_setval(lint v) { return val_ = (v\
    \ >= md ? v - md : v), *this; }\n    MDCONST ModInt(lint v) { _setval(v % md +\
    \ md); }\n    MDCONST explicit operator bool() const { return val_ != 0; }\n \
    \   MDCONST ModInt operator+(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ + x.val_);\n    }\n    MDCONST ModInt operator-(const ModInt &x) const {\n \
    \       return ModInt()._setval((lint)val_ - x.val_ + md);\n    }\n    MDCONST\
    \ ModInt operator*(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ * x.val_ % md);\n    }\n    MDCONST ModInt operator/(const ModInt &x) const\
    \ {\n        return ModInt()._setval((lint)val_ * x.inv().val() % md);\n    }\n\
    \    MDCONST ModInt operator-() const { return ModInt()._setval(md - val_); }\n\
    \    MDCONST ModInt &operator+=(const ModInt &x) { return *this = *this + x; }\n\
    \    MDCONST ModInt &operator-=(const ModInt &x) { return *this = *this - x; }\n\
    \    MDCONST ModInt &operator*=(const ModInt &x) { return *this = *this * x; }\n\
    \    MDCONST ModInt &operator/=(const ModInt &x) { return *this = *this / x; }\n\
    \    friend MDCONST ModInt operator+(lint a, const ModInt &x) {\n        return\
    \ ModInt()._setval(a % md + x.val_);\n    }\n    friend MDCONST ModInt operator-(lint\
    \ a, const ModInt &x) {\n        return ModInt()._setval(a % md - x.val_ + md);\n\
    \    }\n    friend MDCONST ModInt operator*(lint a, const ModInt &x) {\n     \
    \   return ModInt()._setval(a % md * x.val_ % md);\n    }\n    friend MDCONST\
    \ ModInt operator/(lint a, const ModInt &x) {\n        return ModInt()._setval(a\
    \ % md * x.inv().val() % md);\n    }\n    MDCONST bool operator==(const ModInt\
    \ &x) const { return val_ == x.val_; }\n    MDCONST bool operator!=(const ModInt\
    \ &x) const { return val_ != x.val_; }\n    MDCONST bool operator<(const ModInt\
    \ &x) const {\n        return val_ < x.val_;\n    } // To use std::map<ModInt,\
    \ T>\n    friend std::istream &operator>>(std::istream &is, ModInt &x) {\n   \
    \     lint t;\n        return is >> t, x = ModInt(t), is;\n    }\n    MDCONST\
    \ friend std::ostream &operator<<(std::ostream &os, const ModInt &x) {\n     \
    \   return os << x.val_;\n    }\n    MDCONST ModInt pow(lint n) const {\n    \
    \    ModInt ans = 1, tmp = *this;\n        while (n) {\n            if (n & 1)\
    \ ans *= tmp;\n            tmp *= tmp, n >>= 1;\n        }\n        return ans;\n\
    \    }\n\n    static std::vector<ModInt> facs, facinvs, invs;\n    MDCONST static\
    \ void _precalculation(int N) {\n        int l0 = facs.size();\n        if (N\
    \ > md) N = md;\n        if (N <= l0) return;\n        facs.resize(N), facinvs.resize(N),\
    \ invs.resize(N);\n        for (int i = l0; i < N; i++) facs[i] = facs[i - 1]\
    \ * i;\n        facinvs[N - 1] = facs.back().pow(md - 2);\n        for (int i\
    \ = N - 2; i >= l0; i--) facinvs[i] = facinvs[i + 1] * (i + 1);\n        for (int\
    \ i = N - 1; i >= l0; i--) invs[i] = facinvs[i] * facs[i - 1];\n    }\n    MDCONST\
    \ ModInt inv() const {\n        if (this->val_ < std::min(md >> 1, 1 << 21)) {\n\
    \            if (facs.empty()) facs = {1}, facinvs = {1}, invs = {0};\n      \
    \      while (this->val_ >= int(facs.size())) _precalculation(facs.size() * 2);\n\
    \            return invs[this->val_];\n        } else {\n            return this->pow(md\
    \ - 2);\n        }\n    }\n    MDCONST ModInt fac() const {\n        while (this->val_\
    \ >= int(facs.size())) _precalculation(facs.size() * 2);\n        return facs[this->val_];\n\
    \    }\n    MDCONST ModInt facinv() const {\n        while (this->val_ >= int(facs.size()))\
    \ _precalculation(facs.size() * 2);\n        return facinvs[this->val_];\n   \
    \ }\n    MDCONST ModInt doublefac() const {\n        lint k = (this->val_ + 1)\
    \ / 2;\n        return (this->val_ & 1) ? ModInt(k * 2).fac() / (ModInt(2).pow(k)\
    \ * ModInt(k).fac())\n                                : ModInt(k).fac() * ModInt(2).pow(k);\n\
    \    }\n    MDCONST ModInt nCr(const ModInt &r) const {\n        return (this->val_\
    \ < r.val_) ? 0 : this->fac() * (*this - r).facinv() * r.facinv();\n    }\n  \
    \  MDCONST ModInt nPr(const ModInt &r) const {\n        return (this->val_ < r.val_)\
    \ ? 0 : this->fac() * (*this - r).facinv();\n    }\n\n    ModInt sqrt() const\
    \ {\n        if (val_ == 0) return 0;\n        if (md == 2) return val_;\n   \
    \     if (pow((md - 1) / 2) != 1) return 0;\n        ModInt b = 1;\n        while\
    \ (b.pow((md - 1) / 2) == 1) b += 1;\n        int e = 0, m = md - 1;\n       \
    \ while (m % 2 == 0) m >>= 1, e++;\n        ModInt x = pow((m - 1) / 2), y = (*this)\
    \ * x * x;\n        x *= (*this);\n        ModInt z = b.pow(m);\n        while\
    \ (y != 1) {\n            int j = 0;\n            ModInt t = y;\n            while\
    \ (t != 1) j++, t *= t;\n            z = z.pow(1LL << (e - j - 1));\n        \
    \    x *= z, z *= z, y *= z;\n            e = j;\n        }\n        return ModInt(std::min(x.val_,\
    \ md - x.val_));\n    }\n};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facs\
    \ = {1};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facinvs = {1};\n\
    template <int md> std::vector<ModInt<md>> ModInt<md>::invs = {0};\n\nusing ModInt998244353\
    \ = ModInt<998244353>;\n// using mint = ModInt<998244353>;\n// using mint = ModInt<1000000007>;\n\
    #line 2 \"random/xorshift.hpp\"\n#include <cstdint>\n\n// CUT begin\nuint32_t\
    \ rand_int() // XorShift random integer generator\n{\n    static uint32_t x =\
    \ 123456789, y = 362436069, z = 521288629, w = 88675123;\n    uint32_t t = x ^\
    \ (x << 11);\n    x = y;\n    y = z;\n    z = w;\n    return w = (w ^ (w >> 19))\
    \ ^ (t ^ (t >> 8));\n}\ndouble rand_double() { return (double)rand_int() / UINT32_MAX;\
    \ }\n#line 8 \"data_structure/test/link_cut_tree.noncommutative.stress.test.cpp\"\
    \n\n#line 11 \"data_structure/test/link_cut_tree.noncommutative.stress.test.cpp\"\
    \n#include <cstdio>\n#include <unordered_set>\n#line 14 \"data_structure/test/link_cut_tree.noncommutative.stress.test.cpp\"\
    \nusing namespace std;\n\nconstexpr int md = 998244353;\nconst int NTRY = 1000;\n\
    const int VMAX = 50;\nconst int QPERTRY = 1000;\nconst int dim = 2;\nusing mint\
    \ = ModInt<md>;\n\nusing S = tuple<int, matrix<mint>, matrix<mint>>;\nusing F\
    \ = pair<bool, matrix<mint>>;\nS op(S l, S r) {\n    int sl, sr;\n    matrix<mint>\
    \ ml1, ml2, mr1, mr2;\n    tie(sl, ml1, ml2) = l;\n    tie(sr, mr1, mr2) = r;\n\
    \    return {sl + sr, mr1 * ml1, ml2 * mr2};\n}\nS mapping(F f, S x) {\n    int\
    \ sz = get<0>(x);\n    if (sz) {\n        auto m = f.second.pow(sz);\n       \
    \ return {sz, m, m};\n    }\n    return x;\n}\nS reversal(S x) { return {get<0>(x),\
    \ get<2>(x), get<1>(x)}; }\nF composition(F f, F g) { return f.first ? f : g;\
    \ }\nF id() { return {false, matrix<mint>::Identity(dim)}; }\nusing LCT = lazy_linkcuttree<S,\
    \ F, op, reversal, mapping, composition, id>;\n\nvector<int> connected_vertices(int\
    \ N, int r, const vector<unordered_set<int>> &to) {\n    vector<int> visited(N);\n\
    \    vector<int> ret, tmp{r};\n    while (tmp.size()) {\n        int now = tmp.back();\n\
    \        tmp.pop_back();\n        ret.push_back(now);\n        visited[now] =\
    \ 1;\n        for (auto nxt : to[now]) {\n            if (!visited[nxt]) tmp.push_back(nxt);\n\
    \        }\n    }\n    return ret;\n}\n\nvector<int> get_rev_path(int s, int t,\
    \ int prv, const vector<unordered_set<int>> &to) {\n    if (s == t) return {s};\n\
    \    for (auto nxt : to[s]) {\n        if (nxt == prv) continue;\n        auto\
    \ v = get_rev_path(nxt, t, s, to);\n        if (v.size()) {\n            v.push_back(s);\n\
    \            return v;\n        }\n    }\n    return {};\n}\n\nS gen_rand_a()\
    \ {\n    matrix<mint> ret(dim, dim);\n    for (int i = 0; i < dim; i++) {\n  \
    \      for (int j = 0; j < dim; j++) ret[i][j] = rand_int() % md;\n    }\n   \
    \ return {1, ret, ret};\n}\n\nint main() {\n    for (int ntry = 0; ntry < NTRY;\
    \ ntry++) {\n        const int N = 2 + rand_int() % (VMAX - 1);\n\n        vector<S>\
    \ A(N);\n        LCT tree;\n        vector<LCT::Node *> nodes;\n\n        for\
    \ (int i = 0; i < N; i++) {\n            A[i] = gen_rand_a();\n            nodes.push_back(tree.make_node(A[i]));\n\
    \        }\n        vector<pair<int, int>> edges;\n        vector<unordered_set<int>>\
    \ to(N);\n\n        auto try_to_add_edge = [&]() {\n            int a = rand_int()\
    \ % N;\n            vector<int> is_cmp(N, 1);\n            for (auto i : connected_vertices(N,\
    \ a, to)) is_cmp[i] = 0;\n            vector<int> cmp;\n            for (int i\
    \ = 0; i < N; i++) {\n                if (is_cmp[i]) cmp.push_back(i);\n     \
    \       }\n            if (cmp.empty()) return;\n            int b = cmp[rand_int()\
    \ % cmp.size()];\n\n            edges.emplace_back(a, b);\n            to[a].insert(b),\
    \ to[b].insert(a);\n            tree.link(nodes[a], nodes[b]);\n        };\n\n\
    \        for (int i = 0; i < N / 2; i++) try_to_add_edge();\n\n        for (int\
    \ q = 0; q < QPERTRY; q++) {\n            const int tp = rand_int() % 6;\n   \
    \         if (tp == 0) {\n                // cut() if possible\n             \
    \   if (edges.empty()) continue;\n                int e = rand_int() % edges.size();\n\
    \                int a = edges[e].first, b = edges[e].second;\n\n            \
    \    edges.erase(edges.begin() + e);\n                to[a].erase(b), to[b].erase(a);\n\
    \                tree.cut(nodes[a], nodes[b]);\n\n            } else if (tp ==\
    \ 1) {\n                // link() if possible\n                try_to_add_edge();\n\
    \n            } else if (tp == 2) {\n                // apply()\n            \
    \    const int u = rand_int() % N;\n                auto conn = connected_vertices(N,\
    \ u, to);\n                int v = conn[rand_int() % conn.size()];\n         \
    \       const auto a = gen_rand_a();\n                tree.apply(nodes[u], nodes[v],\
    \ {true, get<1>(a)});\n\n                for (auto i : get_rev_path(u, v, -1,\
    \ to)) A[i] = a;\n\n            } else if (tp == 3) {\n                // prod()\n\
    \                const int u = rand_int() % N;\n                auto conn = connected_vertices(N,\
    \ u, to);\n                int v = conn[rand_int() % conn.size()];\n         \
    \       S ret1 = tree.prod(nodes[u], nodes[v]);\n\n                auto ret2 =\
    \ S(A[u]);\n                for (auto i : get_rev_path(v, u, -1, to)) {\n    \
    \                if (i != u) ret2 = op(ret2, A[i]);\n                }\n     \
    \           assert(ret1 == ret2);\n\n            } else if (tp == 4) {\n     \
    \           // set()\n                const int u = rand_int() % N;\n        \
    \        const auto a = gen_rand_a();\n                tree.set(nodes[u], a);\n\
    \                A[u] = a;\n\n            } else if (tp == 5) {\n            \
    \    // get()\n                const int u = rand_int() % N;\n               \
    \ const S a = tree.get(nodes[u]);\n                assert(a == A[u]);\n      \
    \      } else {\n                exit(8);\n            }\n        }\n    }\n \
    \   puts(\"Hello World\");\n}\n"
  code: "// \u30D1\u30B9\u4E0A\u306E\u9802\u70B9\u66F4\u65B0\u30FB\u30D1\u30B9\u4E0A\
    \u306E\u9802\u70B9\u7A4D\u53D6\u5F97\u304C\u53EF\u80FD\u306A Link-Cut tree\n//\
    \ \u5404\u9802\u70B9\u306B 2x2 \u884C\u5217\u3092\u8F09\u305B\uFF0C\u6F14\u7B97\
    \u3068\u3057\u3066\u884C\u5217\u7A4D\u304C\u5165\u308B\u975E\u53EF\u63DB\u30FB\
    \u30D1\u30B9\u4E0A\u66F4\u65B0\u306E\u4F8B\uFF0E\n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \ // DUMMY\n#include \"../link_cut_tree.hpp\"\n#include \"../../linear_algebra_matrix/matrix.hpp\"\
    \n#include \"../../modint.hpp\"\n#include \"../../random/xorshift.hpp\"\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <cstdio>\n#include <unordered_set>\n\
    #include <utility>\nusing namespace std;\n\nconstexpr int md = 998244353;\nconst\
    \ int NTRY = 1000;\nconst int VMAX = 50;\nconst int QPERTRY = 1000;\nconst int\
    \ dim = 2;\nusing mint = ModInt<md>;\n\nusing S = tuple<int, matrix<mint>, matrix<mint>>;\n\
    using F = pair<bool, matrix<mint>>;\nS op(S l, S r) {\n    int sl, sr;\n    matrix<mint>\
    \ ml1, ml2, mr1, mr2;\n    tie(sl, ml1, ml2) = l;\n    tie(sr, mr1, mr2) = r;\n\
    \    return {sl + sr, mr1 * ml1, ml2 * mr2};\n}\nS mapping(F f, S x) {\n    int\
    \ sz = get<0>(x);\n    if (sz) {\n        auto m = f.second.pow(sz);\n       \
    \ return {sz, m, m};\n    }\n    return x;\n}\nS reversal(S x) { return {get<0>(x),\
    \ get<2>(x), get<1>(x)}; }\nF composition(F f, F g) { return f.first ? f : g;\
    \ }\nF id() { return {false, matrix<mint>::Identity(dim)}; }\nusing LCT = lazy_linkcuttree<S,\
    \ F, op, reversal, mapping, composition, id>;\n\nvector<int> connected_vertices(int\
    \ N, int r, const vector<unordered_set<int>> &to) {\n    vector<int> visited(N);\n\
    \    vector<int> ret, tmp{r};\n    while (tmp.size()) {\n        int now = tmp.back();\n\
    \        tmp.pop_back();\n        ret.push_back(now);\n        visited[now] =\
    \ 1;\n        for (auto nxt : to[now]) {\n            if (!visited[nxt]) tmp.push_back(nxt);\n\
    \        }\n    }\n    return ret;\n}\n\nvector<int> get_rev_path(int s, int t,\
    \ int prv, const vector<unordered_set<int>> &to) {\n    if (s == t) return {s};\n\
    \    for (auto nxt : to[s]) {\n        if (nxt == prv) continue;\n        auto\
    \ v = get_rev_path(nxt, t, s, to);\n        if (v.size()) {\n            v.push_back(s);\n\
    \            return v;\n        }\n    }\n    return {};\n}\n\nS gen_rand_a()\
    \ {\n    matrix<mint> ret(dim, dim);\n    for (int i = 0; i < dim; i++) {\n  \
    \      for (int j = 0; j < dim; j++) ret[i][j] = rand_int() % md;\n    }\n   \
    \ return {1, ret, ret};\n}\n\nint main() {\n    for (int ntry = 0; ntry < NTRY;\
    \ ntry++) {\n        const int N = 2 + rand_int() % (VMAX - 1);\n\n        vector<S>\
    \ A(N);\n        LCT tree;\n        vector<LCT::Node *> nodes;\n\n        for\
    \ (int i = 0; i < N; i++) {\n            A[i] = gen_rand_a();\n            nodes.push_back(tree.make_node(A[i]));\n\
    \        }\n        vector<pair<int, int>> edges;\n        vector<unordered_set<int>>\
    \ to(N);\n\n        auto try_to_add_edge = [&]() {\n            int a = rand_int()\
    \ % N;\n            vector<int> is_cmp(N, 1);\n            for (auto i : connected_vertices(N,\
    \ a, to)) is_cmp[i] = 0;\n            vector<int> cmp;\n            for (int i\
    \ = 0; i < N; i++) {\n                if (is_cmp[i]) cmp.push_back(i);\n     \
    \       }\n            if (cmp.empty()) return;\n            int b = cmp[rand_int()\
    \ % cmp.size()];\n\n            edges.emplace_back(a, b);\n            to[a].insert(b),\
    \ to[b].insert(a);\n            tree.link(nodes[a], nodes[b]);\n        };\n\n\
    \        for (int i = 0; i < N / 2; i++) try_to_add_edge();\n\n        for (int\
    \ q = 0; q < QPERTRY; q++) {\n            const int tp = rand_int() % 6;\n   \
    \         if (tp == 0) {\n                // cut() if possible\n             \
    \   if (edges.empty()) continue;\n                int e = rand_int() % edges.size();\n\
    \                int a = edges[e].first, b = edges[e].second;\n\n            \
    \    edges.erase(edges.begin() + e);\n                to[a].erase(b), to[b].erase(a);\n\
    \                tree.cut(nodes[a], nodes[b]);\n\n            } else if (tp ==\
    \ 1) {\n                // link() if possible\n                try_to_add_edge();\n\
    \n            } else if (tp == 2) {\n                // apply()\n            \
    \    const int u = rand_int() % N;\n                auto conn = connected_vertices(N,\
    \ u, to);\n                int v = conn[rand_int() % conn.size()];\n         \
    \       const auto a = gen_rand_a();\n                tree.apply(nodes[u], nodes[v],\
    \ {true, get<1>(a)});\n\n                for (auto i : get_rev_path(u, v, -1,\
    \ to)) A[i] = a;\n\n            } else if (tp == 3) {\n                // prod()\n\
    \                const int u = rand_int() % N;\n                auto conn = connected_vertices(N,\
    \ u, to);\n                int v = conn[rand_int() % conn.size()];\n         \
    \       S ret1 = tree.prod(nodes[u], nodes[v]);\n\n                auto ret2 =\
    \ S(A[u]);\n                for (auto i : get_rev_path(v, u, -1, to)) {\n    \
    \                if (i != u) ret2 = op(ret2, A[i]);\n                }\n     \
    \           assert(ret1 == ret2);\n\n            } else if (tp == 4) {\n     \
    \           // set()\n                const int u = rand_int() % N;\n        \
    \        const auto a = gen_rand_a();\n                tree.set(nodes[u], a);\n\
    \                A[u] = a;\n\n            } else if (tp == 5) {\n            \
    \    // get()\n                const int u = rand_int() % N;\n               \
    \ const S a = tree.get(nodes[u]);\n                assert(a == A[u]);\n      \
    \      } else {\n                exit(8);\n            }\n        }\n    }\n \
    \   puts(\"Hello World\");\n}\n"
  dependsOn:
  - data_structure/link_cut_tree.hpp
  - linear_algebra_matrix/matrix.hpp
  - modint.hpp
  - random/xorshift.hpp
  isVerificationFile: true
  path: data_structure/test/link_cut_tree.noncommutative.stress.test.cpp
  requiredBy: []
  timestamp: '2022-07-12 00:34:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: data_structure/test/link_cut_tree.noncommutative.stress.test.cpp
layout: document
redirect_from:
- /verify/data_structure/test/link_cut_tree.noncommutative.stress.test.cpp
- /verify/data_structure/test/link_cut_tree.noncommutative.stress.test.cpp.html
title: data_structure/test/link_cut_tree.noncommutative.stress.test.cpp
---
