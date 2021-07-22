#pragma once

// CUT begin
// Link-Cut Tree
// Reference:
// - https://www.slideshare.net/iwiwi/2-12188845
// - https://ei1333.github.io/library/structure/lct/link-cut-tree-lazy-path.cpp
template <class S, class F, S (*op)(S, S), S (*reversal)(S), S (*mapping)(F, S), F (*composition)(F, F), F (*id)()>
class lazy_linkcuttree {
public:
    struct Node {
        Node *l, *r, *p;
        S d, sum;
        F lz;
        bool is_reversed;
        int sz;
        Node(S val)
            : l(nullptr), r(nullptr), p(nullptr), d(val), sum(val), lz(id()), is_reversed(false), sz(1) {}
        bool is_root() const { return !p || (p->l != this and p->r != this); }
        template <class OStream> friend OStream &operator<<(OStream &os, const Node &n) {
            os << '[';
            if (n.l) os << *(n.l) << ',';
            os << n.d << ',';
            if (n.r) os << *(n.r);
            return os << ']';
        }
    };

protected:
    void update(Node *t) {
        if (t == nullptr) return;
        t->sz = 1;
        t->sum = t->d;
        if (t->l) {
            t->sz += t->l->sz;
            t->sum = op(t->l->sum, t->sum);
        }
        if (t->r) {
            t->sz += t->r->sz;
            t->sum = op(t->sum, t->r->sum);
        }
    }
    void all_apply(Node *a, F b) {
        a->d = mapping(b, a->d);
        a->sum = mapping(b, a->sum);
        a->lz = composition(b, a->lz);
    }
    void _toggle(Node *t) {
        auto tmp = t->l;
        t->l = t->r, t->r = tmp;
        t->sum = reversal(t->sum);
        t->is_reversed ^= true;
    }

    void push(Node *&t) {
        if (t and t->lz != id()) {
            if (t->l) all_apply(t->l, t->lz);
            if (t->r) all_apply(t->r, t->lz);
            t->lz = id();
        }
        if (t->is_reversed) {
            if (t->l) _toggle(t->l);
            if (t->r) _toggle(t->r);
            t->is_reversed = false;
        }
    }

    void _rot_r(Node *t) {
        Node *x = t->p, *y = x->p;
        if ((x->l = t->r)) t->r->p = x;
        t->r = x, x->p = t;
        update(x), update(t);
        if ((t->p = y)) {
            if (y->l == x) y->l = t;
            if (y->r == x) y->r = t;
            update(y);
        }
    }
    void _rot_l(Node *t) {
        Node *x = t->p, *y = x->p;
        if ((x->r = t->l)) t->l->p = x;
        t->l = x, x->p = t;
        update(x), update(t);
        if ((t->p = y)) {
            if (y->l == x) y->l = t;
            if (y->r == x) y->r = t;
            update(y);
        }
    }

    void _splay(Node *t) {
        push(t);
        while (!t->is_root()) {
            Node *q = t->p;
            if (q->is_root()) {
                push(q), push(t);
                if (q->l == t)
                    _rot_r(t);
                else
                    _rot_l(t);
            } else {
                Node *r = q->p;
                push(r), push(q), push(t);
                if (r->l == q) {
                    if (q->l == t)
                        _rot_r(q), _rot_r(t);
                    else
                        _rot_l(t), _rot_r(t);
                } else {
                    if (q->r == t)
                        _rot_l(q), _rot_l(t);
                    else
                        _rot_r(t), _rot_l(t);
                }
            }
        }
    }

public:
    [[nodiscard]] Node *make_node(S val) { return new Node(val); }

    void evert(Node *t) { expose(t), _toggle(t), push(t); }

    Node *expose(Node *t) {
        Node *rp = nullptr;
        for (Node *cur = t; cur; cur = cur->p) {
            _splay(cur);
            cur->r = rp;
            update(cur);
            rp = cur;
        }
        _splay(t);
        return rp;
    }

    void link(Node *u, Node *v) {
        if (u->p != nullptr) evert(u);
        if (v->p != nullptr) evert(v);
        expose(v);
        u->p = v;
        v->r = u;
        update(v);
    }

    void cut(Node *chi) {
        expose(chi);
        Node *par = chi->l;
        chi->l = nullptr;
        update(chi);
        par->p = nullptr;
    }

    void cut(Node *u, Node *v) { evert(u), cut(v); }

    Node *lca(Node *u, Node *v) { return expose(u), expose(v); }

    void set(Node *t, S x) { expose(t), t->d = x, update(t); }

    S get(Node *t) { return expose(t), t->d; }

    void apply(Node *u, Node *v, const F &x) {
        evert(u);
        expose(v);
        all_apply(v, x);
        push(v);
    }

    S prod(Node *u, Node *v) {
        evert(u);
        expose(v);
        return v->sum;
    }
};
/* example usage:
struct S {
    int sz, sum, lhi, rhi, inhi;
    S(int x) : sz(1), sum(x), lhi(x), rhi(x), inhi(x) {}
    S(int sz_, int sum_, int lhi_, int rhi_, int inhi_)
        : sz(sz_), sum(sum_), lhi(lhi_), rhi(rhi_), inhi(inhi_) {}
};
using F = pair<bool, int>;
S op(S l, S r) {
    return S(l.sz + r.sz, l.sum + r.sum, max(l.sum + r.lhi, l.lhi), max(l.rhi + r.sum, r.rhi), max<int>({l.inhi, r.inhi, l.rhi + r.lhi}));
}
S reversal(S x) { return S(x.sz, x.sum, x.rhi, x.lhi, x.inhi); }
S mapping(F f, S x) {
    if (f.first) {
        auto v = f.second;
        auto sum = x.sz * v;
        return S{x.sz, sum, max(v, sum), max(v, sum), max(v, sum)};
    } else {
        return x;
    }
}
F composition(F fnew, F gold) { return fnew.first ? fnew : gold; }
F id() { return {false, 0}; }
using LCT = lazy_linkcuttree<S, F, op, reversal, mapping, composition, id>;
vector<LCT::Node*> vs;
*/
