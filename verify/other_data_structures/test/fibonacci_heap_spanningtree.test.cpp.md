---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :heavy_check_mark: other_data_structures/test/fibonacci_heap_spanningtree.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#9e0aaf7c24822f646f604a7599f511a1">other_data_structures/test</a>
* <a href="{{ site.github.repository_url }}/blob/master/other_data_structures/test/fibonacci_heap_spanningtree.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-30 02:04:57+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/other_data_structures/fibonacci_heap.hpp.html">other_data_structures/fibonacci_heap.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "other_data_structures/fibonacci_heap.hpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A"

#include <iostream>
#include <vector>
using namespace std;

int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int V, E;
    cin >> V >> E;
    fibonacci_heap<pair<int, int>> hp;

    vector<vector<pair<int, int>>> to(V);
    vector<int> belong(V);
    while (E--)
    {
        int s, t, w;
        cin >> s >> t >> w;
        to[s].emplace_back(w, t);
        to[t].emplace_back(w, s);
    }
    belong[0] = 1;
    for (auto p : to[0]) hp.push(p);

    int ret = 0;
    while (hp.size())
    {
        auto [ecost, i] = hp.top();
        hp.pop();
        if (belong[i]) continue;
        ret += ecost;
        belong[i] = 1;
        for (auto p : to[i]) if (!belong[p.second]) hp.push(p);
    }
    cout << ret << '\n';
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "other_data_structures/fibonacci_heap.hpp"
#include <array>
#include <cassert>
#include <iostream>
#include <list>

// CUT begin
// Fibonacci heap
// - Complexity:
//   - empty(), size(), top(), push(), meld(): O(1)
//   - pop(), decrease(): O(lg N) amortized
// - Reference:
//   - "Introduction to Algorithms, Third Edition", Chapter 19
//   - <https://www.cs.princeton.edu/~wayne/teaching/fibonacci-heap.pdf>
//   - <https://rsk0315.hatenablog.com/entry/2019/10/29/151823>
template <typename _Tp>
struct fibonacci_heap
{
    struct Node
    {
        _Tp val;
        int deg;
        Node *parent, *left, *right, *child;
        bool mark;
        Node() = default;
        Node(Node const &) = default;
        Node(Node &&) = default;
        Node &operator=(Node const &) = default;
        Node &operator=(Node &&) = default;
        Node(_Tp v) : val(v), deg(0), parent(nullptr), left(nullptr), right(nullptr), child(nullptr), mark(false) {}
        friend std::ostream &operator<<(std::ostream &os, const Node &n)
        {
            os << '(' << n.val << ',';
            if (n.child != nullptr) os << *(n.child) << ',';
            Node *now = n.right;
            while (now != &n)
            {
                os << now->val << ',';
                if (now->child != nullptr) os << *now->child  << ',';
                now = now->right;
            }
            os << ')';
            return os;
        }
    };

    int sz;
    std::list<Node*> roots;
    Node *ptop;
    inline void _chmin(Node *cand) noexcept
    {
        if (ptop == nullptr or cand->val < ptop->val) ptop = cand;
    }
    fibonacci_heap() : sz(0), roots({}), ptop(nullptr) {}

    bool empty() const noexcept { return sz == 0; }
    int size() const noexcept { return sz; }

    void _consolidate()
    {
        std::array<Node *, 30> arr;
        arr.fill(nullptr);

        auto fmerge = [&](auto &&func, Node *ptr) -> void {
            int d = ptr->deg;
            if (arr[d] == nullptr) arr[d] = ptr;
            else
            {
                Node *cptr = arr[d];
                if (cptr->val < ptr->val) std::swap(ptr, cptr);
                ptr->deg++;
                cptr->parent = ptr;
                if (ptr->child == nullptr) ptr->child = cptr;
                else
                {
                    Node *cl = ptr->child, *cr = ptr->child->right;
                    assert(cl->right == cr and cr->left == cl);
                    cptr->left = cl, cptr->right = cr, cl->right = cr->left = cptr;
                }
                arr[d] = nullptr;
                func(func, ptr);
            }
        };
        for (auto ptr : roots) if (ptr != nullptr) {
            if (ptr->deg < 0) delete ptr;
            else fmerge(fmerge, ptr);
        }
        roots.clear(), ptop = nullptr;
        for (auto ptr : arr) if (ptr != nullptr) _add_tree(ptr);
    }

    void _add_tree(Node *root) noexcept
    {
        root->parent = nullptr;
        root->left = root->right = root;
        roots.emplace_back(root);
        _chmin(root);
    }

    Node *push(const _Tp &val) noexcept
    {
        sz++;
        Node *ptr = new Node(val);
        _add_tree(ptr);
        return ptr;
    }

    void meld(fibonacci_heap &&hp)
    {
        sz += hp.sz;
        roots.splice(roots.end(), hp.roots);
        if (hp.ptop != nullptr) _chmin(hp.ptop);
    }

    void pop()
    {
        assert(sz > 0);
        sz--;
        Node* ch1 = ptop->child;
        if (ch1 != nullptr)
        {
            Node *now = ch1;
            while (true)
            {
                Node *nxt = now->right;
                _add_tree(now);
                now = nxt;
                if (now == ch1) break;
            }
        }
        ptop->deg = -1;
        _consolidate();
    }

    void clear()
    {
        auto deldfs = [&](auto &&f, Node *now) -> void {
            while (now != nullptr)
            {
                if (now->child != nullptr) f(f, now->child);
                Node *nxt = now->right;
                delete now;
                now = nxt;
            }
        };
        for (auto root : roots)
        {
            deldfs(deldfs, root);
        }
        sz = 0;
        roots.clear();
        ptop = nullptr;
    }

    void _cut(Node *x) noexcept
    {
        Node *y = x->parent;
        assert(y != nullptr and y->deg > 0);
        Node *xr = x->right, *xl = x->left;
        if (x == xr)
        {
            y->child = nullptr;
        }
        else
        {
            y->child = xr;
            xl->right = xr, xr->left = xl;
        }
        y->deg--;
        _add_tree(x);
        x->mark = false;
    }
    void _cascading_cut(Node *now) noexcept
    {
        assert(now != nullptr);
        Node *par = now->parent;
        if (par == nullptr) return;
        if (!now->mark) now->mark = true;
        else
        {
            _cut(now);
            _cascading_cut(par);
        }
    }
    void erase(Node *r)
    {
        if (r->parent != nullptr)
        {
            Node *rpar = r->parent;
            _cut(r);
            _cascading_cut(rpar);
        }
        ptop = r;
        pop();
    }
    bool decrease(Node *r, const _Tp new_val)
    {
        assert(r != nullptr);
        if (!(new_val < r->val)) return false;
        r->val = new_val;
        if (r->parent != nullptr and new_val < r->parent->val)
        {
            Node *rpar = r->parent;
            _cut(r);
            _cascading_cut(rpar);
        }
        _chmin(r);
        return true;
    }
    _Tp top() const
    {
        assert(ptop != nullptr);
        return ptop->val;
    }
    friend std::ostream &operator<<(std::ostream &os, const fibonacci_heap &hp) {
        os << "[(fibonacci_heap: sz=" << hp.sz << ", top=" << hp.ptop->val << ", #tree = " << hp.roots.size() << ")";
        for (auto x : hp.roots)
        {
            os << *x << ", ";
        }
        os << ']';
        return os;
    }
};


#include <utility>
#include <vector>
template <typename _Tp>
struct heap
{
    using P = std::pair<_Tp, int>;
    fibonacci_heap<P> _heap;
    std::vector<typename fibonacci_heap<P>::Node *> vp;
    std::vector<_Tp> result;
    void initialize(int N, _Tp initval)
    {
        _heap.clear();
        vp.resize(N);
        result.assign(N, initval);
        for (int i = 0; i < N; i++)
        {
            vp[i] = _heap.push(std::make_pair(initval, i));
        }
    }
    heap(int N, _Tp initval)
    {
        initialize(N, initval);
    }
    bool chmin(int i, _Tp val)
    {
        if (val < result[i])
        {
            result[i] = val;
            if (vp[i] == nullptr)
            {
                vp[i] = _heap.push(std::make_pair(result[i], i));
            }
            else
            {
                _heap.decrease(vp[i], std::make_pair(result[i], i));
            }
            return true;
        }
        return false;
    }
    _Tp operator[](int i) const { return result.at(i); }
    P top()
    {
        return _heap.top();
    }
    P pop()
    {
        P ret = _heap.top();
        _heap.pop();
        return ret;
    }
    int size()
    {
        return _heap.size();
    }
    bool empty()
    {
        return _heap.empty();
    }
};
#line 2 "other_data_structures/test/fibonacci_heap_spanningtree.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A"

#line 6 "other_data_structures/test/fibonacci_heap_spanningtree.test.cpp"
using namespace std;

int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int V, E;
    cin >> V >> E;
    fibonacci_heap<pair<int, int>> hp;

    vector<vector<pair<int, int>>> to(V);
    vector<int> belong(V);
    while (E--)
    {
        int s, t, w;
        cin >> s >> t >> w;
        to[s].emplace_back(w, t);
        to[t].emplace_back(w, s);
    }
    belong[0] = 1;
    for (auto p : to[0]) hp.push(p);

    int ret = 0;
    while (hp.size())
    {
        auto [ecost, i] = hp.top();
        hp.pop();
        if (belong[i]) continue;
        ret += ecost;
        belong[i] = 1;
        for (auto p : to[i]) if (!belong[p.second]) hp.push(p);
    }
    cout << ret << '\n';
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

