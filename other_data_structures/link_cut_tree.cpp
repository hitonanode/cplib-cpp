#include <bits/stdc++.h>
using namespace std;
struct fast_ios {
    fast_ios() {
        cin.tie(0);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(20);
    };
} fast_ios_;
#define FOR(i, begin, end) for (int i = (begin), i##_end_ = (end); i < i##_end_; i++)
#define REP(i, n) FOR(i, 0, n)

// using VAL = pair<lint, lint>;
using VAL = long long;
using LAZY = long long;
constexpr LAZY lazy_0 = 0;
struct LinkCutTree {
    struct Node {
        Node *l, *r, *p;
        VAL key;
        LAZY lazy;
        bool is_reversed;
        uint32_t sz;
        Node(VAL val) : l(nullptr), r(nullptr), p(nullptr), key(val), lazy(lazy_0), is_reversed(false), sz(1) {}
        bool is_root() const { return !p || (p->l != this and p->r != this); }
        friend ostream &operator<<(ostream &os, const Node &n) {
            os << "[";
            if (n.l) os << *(n.l) << ",";
            os << n.key << ",";
            if (n.r) os << *(n.r);
            os << "]";
            return os;
        }
    };
    inline Node *_revise_val(Node *t) {
        if (t) {
            t->sz = 1;
            // t->key.second = t->key.first;
            if (t->l) {
                t->sz += t->l->sz;
                // t->key.second += t->l->key.second;
            }
            if (t->r) {
                t->sz += t->r->sz;
                // t->key.second += t->r->key.second;
            }
        }
        return t;
    }
    inline void _propagate_lazy(LAZY &a, LAZY b) // 遅延評価伝播
    {
        a += b;
    }
    inline void _reflect_lazy(Node *a, LAZY b) // 遅延評価反映
    {
        // a->key.first += b;
        // a->key.second += a->sz * b;
        a->key += b;
    }
    inline void _toggle(Node *t) {
        swap(t->l, t->r);
        /* key/lazy modification here */
        t->is_reversed ^= true;
    }

    inline void _resolve_lazy(Node *&t) // 対象の遅延評価を解決
    {
        if (t and t->lazy != lazy_0) {
            if (t->l) _propagate_lazy(t->l->lazy, t->lazy);
            if (t->r) _propagate_lazy(t->r->lazy, t->lazy);
            _reflect_lazy(t, t->lazy);
            t->lazy = lazy_0;
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
        _revise_val(x), _revise_val(t);
        if ((t->p = y)) {
            if (y->l == x) y->l = t;
            if (y->r == x) y->r = t;
            _revise_val(y);
        }
    }
    void _rot_l(Node *t) {
        Node *x = t->p, *y = x->p;
        if ((x->r = t->l)) t->l->p = x;
        t->l = x, x->p = t;
        _revise_val(x), _revise_val(t);
        if ((t->p = y)) {
            if (y->l == x) y->l = t;
            if (y->r == x) y->r = t;
            _revise_val(y);
        }
    }

    void _splay(Node *t) {
        _resolve_lazy(t);
        while (!t->is_root()) {
            Node *q = t->p;
            if (q->is_root()) {
                _resolve_lazy(q), _resolve_lazy(t);
                if (q->l == t)
                    _rot_r(t);
                else
                    _rot_l(t);
            } else {
                Node *r = q->p;
                _resolve_lazy(r), _resolve_lazy(q), _resolve_lazy(t);
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

    Node *make_node(VAL val) { return new Node(val); }

    Node *expose(Node *t) {
        Node *rp = nullptr;
        for (Node *cur = t; cur; cur = cur->p) {
            _splay(cur);
            cur->r = rp;
            _revise_val(cur);
            rp = cur;
        }
        _splay(t);
        return rp;
    }
    void link(Node *chi, Node *par) {
        expose(chi);
        expose(par);
        chi->p = par;
        par->r = chi;
        _revise_val(par);
    }
    void cut(Node *chi) {
        expose(chi);
        Node *par = chi->l;
        chi->l = nullptr;
        _revise_val(chi);
        par->p = nullptr;
    }
    void evert(Node *t) {
        expose(t);
        _toggle(t);
        _resolve_lazy(t);
    }
    Node *lca(Node *u, Node *v) {
        expose(u);
        return expose(v);
    }
    void add_lazy(Node *t, const LAZY &x) {
        expose(t);
        _propagate_lazy(t->lazy, x);
        _resolve_lazy(t);
    }
};

int main() {
    int N;
    cin >> N;
    LinkCutTree lct;
    vector<LinkCutTree::Node *> vec(N);
    REP(i, N) vec[i] = lct.make_node(i);
    REP(i, N) {
        int K;
        cin >> K;
        REP(_, K) {
            int T;
            cin >> T;
            lct.link(vec[i], vec[T]);
        }
    }
    int Q;
    cin >> Q;
    REP(_, Q) {
        int U, V;
        cin >> U >> V;
        cout << lct.lca(vec[V], vec[U])->key << endl;
    }
}
