// Persistent Randomized Binary Search Tree
// Verified : ARC033C・ARC030D

#include <bits/stdc++.h>
using namespace std;
#define FOR(i, begin, end) for(int i=(begin);i<(end);i++)
#define REP(i, n) FOR(i,0,n)


using lint = long long;
struct node {
    lint val, sum;
    node() : val(0), sum(0) {}
    node(lint v) : val(v), sum(v) {}
};

using VAL = node;
using DVAL = lint;
template <uint32_t len>
struct RandomizedBinarySearchTree
{
    // Do your RuBeSTy! ⌒°( ・ω・)°⌒
    /*
    struct rand_int_ // non-deterministic
    {
        mt19937 mt;
        rand_int_() : mt(chrono::steady_clock::now().time_since_epoch().count()) {}
        lint operator()(lint x) { return this->operator()(0, x); } // [0, x)
        lint operator()(lint l, lint r) {
            uniform_int_distribution<lint> d(l, r - 1);
            return d(mt);
        }
        lint operator()() { return this->operator()(1e8); }
    } _rand;
    /*/
    inline uint32_t _rand() // XorShift
    {
        static uint32_t x = 123456789, y = 362436069, z = 521288629, w = 88675123;
        uint32_t t = x ^ (x << 11);
        x = y; y = z; z = w; return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
    }
    // */

    // 各ノードに持たせるデータ型と代数構造
    DVAL Idval;
    struct Node
    {
        Node *l, *r;
        uint32_t sz; // 自身を頂点とする部分木のサイズ
        VAL val; // 自身がrootの部分木を記述, dval==Idvalのときのみ単独で意味を持つ
        DVAL dval; // 自身とその部分木に対する遅延評価
        Node(const VAL &v, const DVAL &dv)
        : l(nullptr), r(nullptr), sz(1), val(v), dval(dv) {}
        Node() {}
    };
    inline Node *_revise_val(Node *t) // （tの子に関する外的操作後に呼んで）szとvalを適切に直す
    {
        if (t)
        {
            t->sz = size(t->l) + size(t->r) + 1;
            t->val.sum = t->val.val + (t->l ? t->l->val.sum + t->l->sz * t->l->dval : 0) + (t->r ? t->r->val.sum + t->r->sz * t->r->dval : 0);
        };
        return t;
    }
    inline void _propagate_dval(DVAL &a, DVAL b) // 遅延評価伝播
    {
        a += b;
    }
    inline void _reflect_dval(Node *a, DVAL b) // 遅延評価反映
    {
        a->val.val += b;
        a->val.sum += a->sz * b;
    }
    vector<Node> data;
    uint32_t d_ptr;

    RandomizedBinarySearchTree(DVAL idval)
    : Idval(idval), d_ptr(0) { data.resize(len); }

    Node *new_tree() { return nullptr; } // 新たな木を作成
    static inline uint32_t size(const Node *t) { return t ? t->sz : 0; }
    inline int mem_used() { return (int)d_ptr; }
    inline bool empty(Node *t) { return !t; }
    inline Node *_make_node(const VAL &val) { if (d_ptr >= len) exit(1); return &(data[d_ptr++] = Node(val, Idval)); }
    virtual void _duplicate_node(Node *&) {}


    inline void _resolve_dval(Node *&t) // 対象の遅延評価を解決
    {
        if (!t) return;
        _duplicate_node(t);
        if (t->dval != Idval) {
            if (t->l) {
                _duplicate_node(t->l);
                _propagate_dval(t->l->dval, t->dval);
            }
            if (t->r) {
                _duplicate_node(t->r);
                _propagate_dval(t->r->dval, t->dval);
            }
            _reflect_dval(t, t->dval);
            t->dval = Idval;
        }
    }

    // lとrをrootとする木同士を結合して，新たなrootを返す
    Node *merge(Node *l, Node *r)
    {
        if (l == nullptr || r == nullptr) return l ? l : r;
        if (_rand() % (l->sz + r->sz) < l->sz)
        {
            _resolve_dval(l);
            l->r = merge(l->r, r);
            return _revise_val(l);
        }
        else
        {
            _resolve_dval(r);
            r->l = merge(l, r->l);
            return _revise_val(r);
        }
    }

    // [0, k)の木と[k, root->size())の木に分けて各root
    // （部分木の要素数が0ならnullptr）を返す
    pair<Node*, Node*> split(Node *&root, int k) // rootの子孫からあとk個欲しい
    {
        if (root == nullptr) return make_pair(nullptr, nullptr);
        _resolve_dval(root);
        if (k <= (int)size(root->l)) // leftからk個拾える
        {
            auto p = split(root->l, k);
            root->l = p.second;
            return make_pair(p.first, _revise_val(root));
        }
        else
        {
            auto p = split(root->r, k - size(root->l) - 1);
            root->r = p.first;
            return make_pair(_revise_val(root), p.second);
        }
    }

    // 0-indexedでarray[pos]の手前に新たな要素newvalを挿入する
    void insert(Node *&root, int pos, const VAL &newval)
    {
        auto p = split(root, pos);
        root = merge(p.first, merge(_make_node(newval), p.second));
    }

    // 0-indexedでarray[pos]を削除する（先頭からpos+1個目の要素）
    void erase(Node *&root, int pos)
    {
        auto p = split(root, pos);
        auto p2 = split(p.second, 1);
        root = merge(p.first, p2.second);
    }

    // 1点更新 array[pos].valにupdvalを入れる
    void set(Node *&root, int pos, const VAL &updval)
    {
        auto p = split(root, pos);
        auto p2 = split(p.second, 1);
        root = merge(p.first, merge(_make_node(updval), p2.second));
    }

    // 遅延評価を利用した範囲更新 [l, r)
    void range_set(Node *&root, int l, int r, const DVAL &adddval)
    {
        auto p = split(root, l);
        auto p2 = split(p.second, r - l);
        _propagate_dval(p2.first->dval, adddval);
        root = merge(p.first, merge(p2.first, p2.second));
    }

    // array[pos].valを取得する
    Node range_get(Node *&root, int l, int r)
    {
        auto p = split(root, l);
        auto p2 = split(p.second, r - l);
        _resolve_dval(p2.first);
        Node res = *p2.first;
        root = merge(p.first, merge(p2.first, p2.second));
        return res;
    }
    Node get(Node *&root, int pos)
    {
        return range_get(root, pos, pos + 1);
    }

    // 普通のlower_bound
    int lower_bound(Node *root, const VAL &v)
    {
        if (root == nullptr) return 0;
        return (v <= root->val) ? lower_bound(root->l, v) : lower_bound(root->r, v) + size(root->l) + 1;
    }

    // データを壊して新規にinitの内容を詰める
    void assign(Node *&root, const vector<VAL> &init)
    {
        d_ptr = 0;
        int N = init.size();
        root = N ? _assign_range(0, N, init) : new_tree();
    }
    Node *_assign_range(int l, int r, const vector<VAL> &init)
    {
        if (r - l == 1) {
            auto t = _make_node(init[l]);
            return _revise_val(t);
        }
        return merge(_assign_range(l, (l + r) / 2, init), _assign_range((l + r) / 2, r, init));
    }

    // データをvecへ書き出し
    void dump(Node *t, vector<VAL> &vec)
    {
        if (t == nullptr) return;
        _resolve_dval(t);
        dump(t->l, vec);
        vec.push_back(t->val);
        dump(t->r, vec);
    }

    // gc
    void re_alloc(Node *&root)
    {
        vector<VAL> mem;
        dump(root, mem);
        assign(root, mem);
    }
};


// 永続化
template<uint32_t len>
struct PersistentRBST : RandomizedBinarySearchTree<len>
{
    using RBST = RandomizedBinarySearchTree<len>;
    using Node = typename RBST::Node;
    PersistentRBST(DVAL idval) : RBST(idval) {}

    void _duplicate_node(Node *&t) override
    {
        if (t == nullptr) return;
        if (RBST::d_ptr >= len) exit(1);
        t = &(RBST::data[RBST::d_ptr++] = *t);
    }

    void copy(Node *&root, int l, int d, int target_l) // [target_l, )に[l, l+d)の値を入れる
    {
        auto p1 = RBST::split(root, l);
        auto p2 = RBST::split(p1.second, d);
        root = RBST::merge(p1.first, RBST::merge(p2.first, p2.second));
        auto p3 = RBST::split(root, target_l);
        auto p4 = RBST::split(p3.second, d);
        root = RBST::merge(p3.first, RBST::merge(p2.first, p4.second));
    }
};


int main()
{
    constexpr int mem_size = 13000000;
    PersistentRBST<mem_size> rbst(0LL);

    auto S = rbst.new_tree();
    int N, Q;
    cin >> N >> Q;
    REP(i, N) {
        int xi; cin >> xi;
        rbst.insert(S, i, node(xi));
    }

    REP(_, Q)
    {
        int type, a, b, c, d, v;
        cin >> type;
        if (type == 1) {
            cin >> a >> b >> v;
            rbst.range_set(S, a - 1, b, (lint)v);
        }
        if (type == 2) {
            cin >> a >> b >> c >> d;
            rbst.copy(S, c - 1, b - a + 1, a - 1);
        }
        if (type == 3) {
            cin >> a >> b;
            cout << rbst.range_get(S, a - 1, b).val.sum << endl;
        }
        if (rbst.mem_used() > mem_size * 0.8) rbst.re_alloc(S);
    }
}
