---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: other_data_structures/fibonacci_heap.hpp
    title: other_data_structures/fibonacci_heap.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A
  bundledCode: "#line 2 \"other_data_structures/fibonacci_heap.hpp\"\n#include <array>\n\
    #include <cassert>\n#include <iostream>\n#include <list>\n\n// CUT begin\n// Fibonacci\
    \ heap\n// - Complexity:\n//   - empty(), size(), top(), push(), meld(): O(1)\n\
    //   - pop(), decrease(): O(lg N) amortized\n// - Reference:\n//   - \"Introduction\
    \ to Algorithms, Third Edition\", Chapter 19\n//   - <https://www.cs.princeton.edu/~wayne/teaching/fibonacci-heap.pdf>\n\
    //   - <https://rsk0315.hatenablog.com/entry/2019/10/29/151823>\ntemplate <typename\
    \ Tp> struct fibonacci_heap {\n    struct Node {\n        Tp val;\n        int\
    \ deg;\n        Node *parent, *left, *right, *child;\n        bool mark;\n   \
    \     Node() = default;\n        Node(Node const &) = default;\n        Node(Node\
    \ &&) = default;\n        Node &operator=(Node const &) = default;\n        Node\
    \ &operator=(Node &&) = default;\n        Node(Tp v) : val(v), deg(0), parent(nullptr),\
    \ left(nullptr), right(nullptr), child(nullptr), mark(false) {}\n        friend\
    \ std::ostream &operator<<(std::ostream &os, const Node &n) {\n            os\
    \ << '(' << n.val << ',';\n            if (n.child != nullptr) os << *(n.child)\
    \ << ',';\n            Node *now = n.right;\n            while (now != &n) {\n\
    \                os << now->val << ',';\n                if (now->child != nullptr)\
    \ os << *now->child << ',';\n                now = now->right;\n            }\n\
    \            os << ')';\n            return os;\n        }\n    };\n\n    int\
    \ sz;\n    std::list<Node *> roots;\n    Node *ptop;\n    inline void _chmin(Node\
    \ *cand) noexcept {\n        if (ptop == nullptr or cand->val < ptop->val) ptop\
    \ = cand;\n    }\n    fibonacci_heap() : sz(0), roots({}), ptop(nullptr) {}\n\n\
    \    bool empty() const noexcept { return sz == 0; }\n    int size() const noexcept\
    \ { return sz; }\n\n    void _consolidate() {\n        std::array<Node *, 30>\
    \ arr;\n        arr.fill(nullptr);\n\n        auto fmerge = [&](auto &&func, Node\
    \ *ptr) -> void {\n            int d = ptr->deg;\n            if (arr[d] == nullptr)\n\
    \                arr[d] = ptr;\n            else {\n                Node *cptr\
    \ = arr[d];\n                if (cptr->val < ptr->val) std::swap(ptr, cptr);\n\
    \                ptr->deg++;\n                cptr->parent = ptr;\n          \
    \      if (ptr->child == nullptr)\n                    ptr->child = cptr;\n  \
    \              else {\n                    Node *cl = ptr->child, *cr = ptr->child->right;\n\
    \                    assert(cl->right == cr and cr->left == cl);\n           \
    \         cptr->left = cl, cptr->right = cr, cl->right = cr->left = cptr;\n  \
    \              }\n                arr[d] = nullptr;\n                func(func,\
    \ ptr);\n            }\n        };\n        for (auto ptr : roots)\n         \
    \   if (ptr != nullptr) {\n                if (ptr->deg < 0)\n               \
    \     delete ptr;\n                else\n                    fmerge(fmerge, ptr);\n\
    \            }\n        roots.clear(), ptop = nullptr;\n        for (auto ptr\
    \ : arr)\n            if (ptr != nullptr) _add_tree(ptr);\n    }\n\n    void _add_tree(Node\
    \ *root) noexcept {\n        root->parent = nullptr;\n        root->left = root->right\
    \ = root;\n        roots.emplace_back(root);\n        _chmin(root);\n    }\n\n\
    \    Node *push(const Tp &val) noexcept {\n        sz++;\n        Node *ptr =\
    \ new Node(val);\n        _add_tree(ptr);\n        return ptr;\n    }\n\n    void\
    \ meld(fibonacci_heap &&hp) {\n        sz += hp.sz;\n        roots.splice(roots.end(),\
    \ hp.roots);\n        if (hp.ptop != nullptr) _chmin(hp.ptop);\n    }\n\n    void\
    \ pop() {\n        assert(sz > 0);\n        sz--;\n        Node *ch1 = ptop->child;\n\
    \        if (ch1 != nullptr) {\n            Node *now = ch1;\n            while\
    \ (true) {\n                Node *nxt = now->right;\n                _add_tree(now);\n\
    \                now = nxt;\n                if (now == ch1) break;\n        \
    \    }\n        }\n        ptop->deg = -1;\n        _consolidate();\n    }\n\n\
    \    void clear() {\n        auto deldfs = [&](auto &&f, Node *now) -> void {\n\
    \            while (now != nullptr) {\n                if (now->child != nullptr)\
    \ f(f, now->child);\n                Node *nxt = now->right;\n               \
    \ delete now;\n                now = nxt;\n            }\n        };\n       \
    \ for (auto root : roots) { deldfs(deldfs, root); }\n        sz = 0;\n       \
    \ roots.clear();\n        ptop = nullptr;\n    }\n\n    void _cut(Node *x) noexcept\
    \ {\n        Node *y = x->parent;\n        assert(y != nullptr and y->deg > 0);\n\
    \        Node *xr = x->right, *xl = x->left;\n        if (x == xr) {\n       \
    \     y->child = nullptr;\n        } else {\n            y->child = xr;\n    \
    \        xl->right = xr, xr->left = xl;\n        }\n        y->deg--;\n      \
    \  _add_tree(x);\n        x->mark = false;\n    }\n    void _cascading_cut(Node\
    \ *now) noexcept {\n        assert(now != nullptr);\n        Node *par = now->parent;\n\
    \        if (par == nullptr) return;\n        if (!now->mark)\n            now->mark\
    \ = true;\n        else {\n            _cut(now);\n            _cascading_cut(par);\n\
    \        }\n    }\n    void erase(Node *r) {\n        if (r->parent != nullptr)\
    \ {\n            Node *rpar = r->parent;\n            _cut(r);\n            _cascading_cut(rpar);\n\
    \        }\n        ptop = r;\n        pop();\n    }\n    bool decrease(Node *r,\
    \ const Tp new_val) {\n        assert(r != nullptr);\n        if (!(new_val <\
    \ r->val)) return false;\n        r->val = new_val;\n        if (r->parent !=\
    \ nullptr and new_val < r->parent->val) {\n            Node *rpar = r->parent;\n\
    \            _cut(r);\n            _cascading_cut(rpar);\n        }\n        _chmin(r);\n\
    \        return true;\n    }\n    Tp top() const {\n        assert(ptop != nullptr);\n\
    \        return ptop->val;\n    }\n    friend std::ostream &operator<<(std::ostream\
    \ &os, const fibonacci_heap &hp) {\n        os << \"[(fibonacci_heap: sz=\" <<\
    \ hp.sz << \", top=\" << hp.ptop->val << \", #tree = \" << hp.roots.size() <<\
    \ \")\";\n        for (auto x : hp.roots) { os << *x << \", \"; }\n        os\
    \ << ']';\n        return os;\n    }\n};\n\n#include <utility>\n#include <vector>\n\
    template <typename Tp> struct heap {\n    using P = std::pair<Tp, int>;\n    fibonacci_heap<P>\
    \ _heap;\n    std::vector<typename fibonacci_heap<P>::Node *> vp;\n    std::vector<Tp>\
    \ result;\n    void initialize(int N, Tp initval) {\n        _heap.clear();\n\
    \        vp.resize(N);\n        result.assign(N, initval);\n        for (int i\
    \ = 0; i < N; i++) { vp[i] = _heap.push(std::make_pair(initval, i)); }\n    }\n\
    \    heap(int N, Tp initval) { initialize(N, initval); }\n    bool chmin(int i,\
    \ Tp val) {\n        if (val < result[i]) {\n            result[i] = val;\n  \
    \          if (vp[i] == nullptr) {\n                vp[i] = _heap.push(std::make_pair(result[i],\
    \ i));\n            } else {\n                _heap.decrease(vp[i], std::make_pair(result[i],\
    \ i));\n            }\n            return true;\n        }\n        return false;\n\
    \    }\n    Tp operator[](int i) const { return result.at(i); }\n    P top() {\
    \ return _heap.top(); }\n    P pop() {\n        P ret = _heap.top();\n       \
    \ _heap.pop();\n        return ret;\n    }\n    int size() { return _heap.size();\
    \ }\n    bool empty() { return _heap.empty(); }\n};\n#line 2 \"other_data_structures/test/fibonacci_heap_dijkstra.test.cpp\"\
    \n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A\"\
    \n\n#line 6 \"other_data_structures/test/fibonacci_heap_dijkstra.test.cpp\"\n\
    using namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    int V, E, R;\n    cin >> V >> E >> R;\n\n    using lint = long long;\n \
    \   using plint = pair<lint, lint>;\n    heap<lint> fib(V, 1e18);\n    fib.chmin(R,\
    \ 0);\n\n    vector<vector<plint>> to(V);\n    while (E--) {\n        int s, t,\
    \ d;\n        cin >> s >> t >> d;\n        to[s].emplace_back(t, d);\n    }\n\
    \    while (fib.size()) {\n        int now = fib.pop().second;\n        for (auto\
    \ p : to[now]) fib.chmin(p.first, fib[now] + p.second);\n    }\n\n    for (auto\
    \ x : fib.result) {\n        if (x == 1e18)\n            cout << \"INF\\n\";\n\
    \        else\n            cout << x << '\\n';\n    }\n}\n"
  code: "#include \"other_data_structures/fibonacci_heap.hpp\"\n#define PROBLEM \"\
    http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A\"\n\n#include\
    \ <iostream>\n#include <vector>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n\n    int V, E, R;\n    cin >> V >> E >> R;\n\n\
    \    using lint = long long;\n    using plint = pair<lint, lint>;\n    heap<lint>\
    \ fib(V, 1e18);\n    fib.chmin(R, 0);\n\n    vector<vector<plint>> to(V);\n  \
    \  while (E--) {\n        int s, t, d;\n        cin >> s >> t >> d;\n        to[s].emplace_back(t,\
    \ d);\n    }\n    while (fib.size()) {\n        int now = fib.pop().second;\n\
    \        for (auto p : to[now]) fib.chmin(p.first, fib[now] + p.second);\n   \
    \ }\n\n    for (auto x : fib.result) {\n        if (x == 1e18)\n            cout\
    \ << \"INF\\n\";\n        else\n            cout << x << '\\n';\n    }\n}\n"
  dependsOn:
  - other_data_structures/fibonacci_heap.hpp
  isVerificationFile: true
  path: other_data_structures/test/fibonacci_heap_dijkstra.test.cpp
  requiredBy: []
  timestamp: '2020-11-18 20:25:12+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: other_data_structures/test/fibonacci_heap_dijkstra.test.cpp
layout: document
redirect_from:
- /verify/other_data_structures/test/fibonacci_heap_dijkstra.test.cpp
- /verify/other_data_structures/test/fibonacci_heap_dijkstra.test.cpp.html
title: other_data_structures/test/fibonacci_heap_dijkstra.test.cpp
---
