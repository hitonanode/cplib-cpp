---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: segmenttree/range-add-range-min.hpp
    title: Range Add Range Min (known as the Starry sky tree)
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: other_algorithms/test/permutation_tree.yuki1720.test.cpp
    title: other_algorithms/test/permutation_tree.yuki1720.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://codeforces.com/blog/entry/78898
    - https://yukicoder.me/problems/no/1720
  bundledCode: "#line 2 \"segmenttree/range-add-range-min.hpp\"\n#include <algorithm>\n\
    #include <limits>\n#include <vector>\n\n// CUT begin\n// StarrySkyTree: segment\
    \ tree for Range Minimum Query & Range Add Query\n// Complexity: $O(N)$ (construction),\
    \ $O(\\log N)$ (add / get / prod)\n// - RangeAddRangeMin(std::vector<Tp> data_init)\
    \ : Initialize array x by data_init.\n// - add(int begin, int end, Tp vadd) :\
    \ Update x[i] <- x[i] + vadd for all begin <= i < end.\n// - get(int pos) : Get\
    \ x[pos].\n// - prod(int begin, int end) : Get min(x[begin], ..., x[end - 1]).\n\
    template <typename Tp, Tp defaultT = std::numeric_limits<Tp>::max() / 2> struct\
    \ RangeAddRangeMin {\n    int N, head;\n    std::vector<Tp> range_min, range_add;\n\
    \    static inline Tp f(Tp x, Tp y) noexcept { return std::min(x, y); }\n\n  \
    \  inline void _merge(int pos) {\n        range_min[pos] = f(range_min[pos * 2]\
    \ + range_add[pos * 2], range_min[pos * 2 + 1] + range_add[pos * 2 + 1]);\n  \
    \  }\n    void initialize(const std::vector<Tp> &data_init) {\n        N = data_init.size(),\
    \ head = 1;\n        while (head < N) head <<= 1;\n        range_min.assign(head\
    \ * 2, defaultT);\n        range_add.assign(head * 2, 0);\n        std::copy(data_init.begin(),\
    \ data_init.end(), range_min.begin() + head);\n        for (int pos = head; --pos;)\
    \ _merge(pos);\n    }\n    RangeAddRangeMin() = default;\n    RangeAddRangeMin(const\
    \ std::vector<Tp> &data_init) { initialize(data_init); }\n    void _add(int begin,\
    \ int end, int pos, int l, int r, Tp vadd) noexcept {\n        if (r <= begin\
    \ or end <= l) return;\n        if (begin <= l and r <= end) {\n            range_add[pos]\
    \ += vadd;\n            return;\n        }\n        _add(begin, end, pos * 2,\
    \ l, (l + r) / 2, vadd);\n        _add(begin, end, pos * 2 + 1, (l + r) / 2, r,\
    \ vadd);\n        _merge(pos);\n    }\n    // Add `vadd` to (x_begin, ..., x_{end\
    \ - 1})\n    void add(int begin, int end, Tp vadd) noexcept { return _add(begin,\
    \ end, 1, 0, head, vadd); }\n    Tp _get(int begin, int end, int pos, int l, int\
    \ r) const noexcept {\n        if (r <= begin or end <= l) return defaultT;\n\
    \        if (begin <= l and r <= end) return range_min[pos] + range_add[pos];\n\
    \        return f(_get(begin, end, pos * 2, l, (l + r) / 2), _get(begin, end,\
    \ pos * 2 + 1, (l + r) / 2, r)) + range_add[pos];\n    }\n    // Return f(x_begin,\
    \ ..., x_{end - 1})\n    Tp get(int pos) const noexcept { return prod(pos, pos\
    \ + 1); }\n    Tp prod(int begin, int end) const noexcept { return _get(begin,\
    \ end, 1, 0, head); }\n};\n#line 4 \"other_algorithms/permutation_tree.hpp\"\n\
    #include <cassert>\n#include <fstream>\n#include <string>\n#line 8 \"other_algorithms/permutation_tree.hpp\"\
    \n\n// Permutation tree\n// Complexity: O(N log N)\n// https://codeforces.com/blog/entry/78898\
    \ https://yukicoder.me/problems/no/1720\nstruct permutation_tree {\n    enum NodeType\
    \ {\n        JoinAsc,\n        JoinDesc,\n        Cut,\n        Leaf,\n      \
    \  None,\n    };\n    struct node {\n        NodeType tp;\n        int L, R; \
    \      // i in [L, R)\n        int mini, maxi; // A[i] in [mini, maxi]\n     \
    \   std::vector<int> child;\n        int sz() const { return R - L; }\n      \
    \  template <class OStream> friend OStream &operator<<(OStream &os, const node\
    \ &n) {\n            os << \"[[\" << n.L << ',' << n.R << \")(ch:\";\n       \
    \     for (auto i : n.child) os << i << ',';\n            return os << \")(tp=\"\
    \ << n.tp << \")]\";\n        }\n    };\n\n    int root;\n    std::vector<int>\
    \ A;\n    std::vector<node> nodes;\n\n    void _add_child(int parid, int chid)\
    \ {\n        nodes[parid].child.push_back(chid);\n        nodes[parid].L = std::min(nodes[parid].L,\
    \ nodes[chid].L);\n        nodes[parid].R = std::max(nodes[parid].R, nodes[chid].R);\n\
    \        nodes[parid].mini = std::min(nodes[parid].mini, nodes[chid].mini);\n\
    \        nodes[parid].maxi = std::max(nodes[parid].maxi, nodes[chid].maxi);\n\
    \    }\n\n    permutation_tree() : root(-1) {}\n    permutation_tree(const std::vector<int>\
    \ &A_) : root(-1), A(A_) { // A: nonempty perm., 0-origin\n        assert(!A.empty());\n\
    \        RangeAddRangeMin<int> seg((std::vector<int>(A.size())));\n\n        std::vector<int>\
    \ hi{-1}, lo{-1};\n        std::vector<int> st;\n        for (int i = 0; i < int(A.size());\
    \ ++i) {\n            while (hi.back() >= 0 and A[i] > A[hi.back()]) {\n     \
    \           seg.add(hi[hi.size() - 2] + 1, hi.back() + 1, A[i] - A[hi.back()]);\n\
    \                hi.pop_back();\n            }\n            hi.push_back(i);\n\
    \            while (lo.back() >= 0 and A[i] < A[lo.back()]) {\n              \
    \  seg.add(lo[lo.size() - 2] + 1, lo.back() + 1, A[lo.back()] - A[i]);\n     \
    \           lo.pop_back();\n            }\n            lo.push_back(i);\n\n  \
    \          int h = nodes.size();\n            nodes.push_back({NodeType::Leaf,\
    \ i, i + 1, A[i], A[i], std::vector<int>{}});\n\n            while (true) {\n\
    \                NodeType join_tp = NodeType::None;\n                if (!st.empty()\
    \ and nodes[st.back()].maxi + 1 == nodes[h].mini) join_tp = JoinAsc;\n       \
    \         if (!st.empty() and nodes[h].maxi + 1 == nodes[st.back()].mini) join_tp\
    \ = JoinDesc;\n\n                if (!st.empty() and join_tp != NodeType::None)\
    \ {\n                    const node &vtp = nodes[st.back()];\n               \
    \     // Insert v as the child of the top node in the stack\n                \
    \    if (join_tp == vtp.tp) {\n                        // Append child to existing\
    \ Join node\n                        _add_child(st.back(), h);\n             \
    \           h = st.back();\n                        st.pop_back();\n         \
    \           } else {\n                        // Make new join node (with exactly\
    \ two children)\n                        int j = st.back();\n                \
    \        nodes.push_back(\n                            {join_tp, nodes[j].L, nodes[j].R,\
    \ nodes[j].mini, nodes[j].maxi, {j}});\n                        st.pop_back();\n\
    \                        _add_child(nodes.size() - 1, h);\n                  \
    \      h = nodes.size() - 1;\n                    }\n                } else if\
    \ (seg.prod(0, i + 1 - nodes[h].sz()) == 0) {\n                    // Make Cut\
    \ node\n                    int L = nodes[h].L, R = nodes[h].R, maxi = nodes[h].maxi,\
    \ mini = nodes[h].mini;\n                    nodes.push_back({NodeType::Cut, L,\
    \ R, mini, maxi, {h}});\n                    h = nodes.size() - 1;\n         \
    \           do {\n                        _add_child(h, st.back());\n        \
    \                st.pop_back();\n                    } while (nodes[h].maxi -\
    \ nodes[h].mini + 1 != nodes[h].sz());\n                    std::reverse(nodes[h].child.begin(),\
    \ nodes[h].child.end());\n                } else {\n                    break;\n\
    \                }\n            }\n            st.push_back(h);\n            seg.add(0,\
    \ i + 1, -1);\n        }\n        assert(st.size() == 1);\n        root = st[0];\n\
    \    }\n\n    void to_DOT(std::string filename = \"\") const {\n        if (filename.empty())\
    \ filename = \"permutation_tree_v=\" + std::to_string(A.size()) + \".DOT\";\n\n\
    \        std::ofstream ss(filename);\n        ss << \"digraph{\\n\";\n       \
    \ int nleaf = 0;\n        for (int i = 0; i < int(nodes.size()); i++) {\n    \
    \        ss << i << \"[\\n\";\n            std::string lbl;\n            if (nodes[i].tp\
    \ == NodeType::Leaf) {\n                lbl = \"A[\" + std::to_string(nleaf) +\
    \ \"] = \" + std::to_string(A[nleaf]), nleaf++;\n            } else {\n      \
    \          lbl += std::string(nodes[i].tp == NodeType::Cut ? \"Cut\" : \"Join\"\
    ) + \"\\\\n\";\n                lbl += \"[\" + std::to_string(nodes[i].L) + \"\
    , \" + std::to_string(nodes[i].R) + \")\";\n            }\n            ss << \"\
    label = \\\"\" << lbl << \"\\\",\\n\";\n            ss << \"]\\n\";\n        \
    \    for (const auto &ch : nodes[i].child) ss << i << \" -> \" << ch << \";\\\
    n\";\n        }\n        ss << \"{rank = same;\";\n        for (int i = 0; i <\
    \ int(nodes.size()); i++) {\n            if (nodes[i].tp == NodeType::Leaf) ss\
    \ << ' ' << i << ';';\n        }\n        ss << \"}\\n\";\n        ss << \"}\\\
    n\";\n        ss.close();\n    }\n};\n"
  code: "#pragma once\n#include \"../segmenttree/range-add-range-min.hpp\"\n#include\
    \ <algorithm>\n#include <cassert>\n#include <fstream>\n#include <string>\n#include\
    \ <vector>\n\n// Permutation tree\n// Complexity: O(N log N)\n// https://codeforces.com/blog/entry/78898\
    \ https://yukicoder.me/problems/no/1720\nstruct permutation_tree {\n    enum NodeType\
    \ {\n        JoinAsc,\n        JoinDesc,\n        Cut,\n        Leaf,\n      \
    \  None,\n    };\n    struct node {\n        NodeType tp;\n        int L, R; \
    \      // i in [L, R)\n        int mini, maxi; // A[i] in [mini, maxi]\n     \
    \   std::vector<int> child;\n        int sz() const { return R - L; }\n      \
    \  template <class OStream> friend OStream &operator<<(OStream &os, const node\
    \ &n) {\n            os << \"[[\" << n.L << ',' << n.R << \")(ch:\";\n       \
    \     for (auto i : n.child) os << i << ',';\n            return os << \")(tp=\"\
    \ << n.tp << \")]\";\n        }\n    };\n\n    int root;\n    std::vector<int>\
    \ A;\n    std::vector<node> nodes;\n\n    void _add_child(int parid, int chid)\
    \ {\n        nodes[parid].child.push_back(chid);\n        nodes[parid].L = std::min(nodes[parid].L,\
    \ nodes[chid].L);\n        nodes[parid].R = std::max(nodes[parid].R, nodes[chid].R);\n\
    \        nodes[parid].mini = std::min(nodes[parid].mini, nodes[chid].mini);\n\
    \        nodes[parid].maxi = std::max(nodes[parid].maxi, nodes[chid].maxi);\n\
    \    }\n\n    permutation_tree() : root(-1) {}\n    permutation_tree(const std::vector<int>\
    \ &A_) : root(-1), A(A_) { // A: nonempty perm., 0-origin\n        assert(!A.empty());\n\
    \        RangeAddRangeMin<int> seg((std::vector<int>(A.size())));\n\n        std::vector<int>\
    \ hi{-1}, lo{-1};\n        std::vector<int> st;\n        for (int i = 0; i < int(A.size());\
    \ ++i) {\n            while (hi.back() >= 0 and A[i] > A[hi.back()]) {\n     \
    \           seg.add(hi[hi.size() - 2] + 1, hi.back() + 1, A[i] - A[hi.back()]);\n\
    \                hi.pop_back();\n            }\n            hi.push_back(i);\n\
    \            while (lo.back() >= 0 and A[i] < A[lo.back()]) {\n              \
    \  seg.add(lo[lo.size() - 2] + 1, lo.back() + 1, A[lo.back()] - A[i]);\n     \
    \           lo.pop_back();\n            }\n            lo.push_back(i);\n\n  \
    \          int h = nodes.size();\n            nodes.push_back({NodeType::Leaf,\
    \ i, i + 1, A[i], A[i], std::vector<int>{}});\n\n            while (true) {\n\
    \                NodeType join_tp = NodeType::None;\n                if (!st.empty()\
    \ and nodes[st.back()].maxi + 1 == nodes[h].mini) join_tp = JoinAsc;\n       \
    \         if (!st.empty() and nodes[h].maxi + 1 == nodes[st.back()].mini) join_tp\
    \ = JoinDesc;\n\n                if (!st.empty() and join_tp != NodeType::None)\
    \ {\n                    const node &vtp = nodes[st.back()];\n               \
    \     // Insert v as the child of the top node in the stack\n                \
    \    if (join_tp == vtp.tp) {\n                        // Append child to existing\
    \ Join node\n                        _add_child(st.back(), h);\n             \
    \           h = st.back();\n                        st.pop_back();\n         \
    \           } else {\n                        // Make new join node (with exactly\
    \ two children)\n                        int j = st.back();\n                \
    \        nodes.push_back(\n                            {join_tp, nodes[j].L, nodes[j].R,\
    \ nodes[j].mini, nodes[j].maxi, {j}});\n                        st.pop_back();\n\
    \                        _add_child(nodes.size() - 1, h);\n                  \
    \      h = nodes.size() - 1;\n                    }\n                } else if\
    \ (seg.prod(0, i + 1 - nodes[h].sz()) == 0) {\n                    // Make Cut\
    \ node\n                    int L = nodes[h].L, R = nodes[h].R, maxi = nodes[h].maxi,\
    \ mini = nodes[h].mini;\n                    nodes.push_back({NodeType::Cut, L,\
    \ R, mini, maxi, {h}});\n                    h = nodes.size() - 1;\n         \
    \           do {\n                        _add_child(h, st.back());\n        \
    \                st.pop_back();\n                    } while (nodes[h].maxi -\
    \ nodes[h].mini + 1 != nodes[h].sz());\n                    std::reverse(nodes[h].child.begin(),\
    \ nodes[h].child.end());\n                } else {\n                    break;\n\
    \                }\n            }\n            st.push_back(h);\n            seg.add(0,\
    \ i + 1, -1);\n        }\n        assert(st.size() == 1);\n        root = st[0];\n\
    \    }\n\n    void to_DOT(std::string filename = \"\") const {\n        if (filename.empty())\
    \ filename = \"permutation_tree_v=\" + std::to_string(A.size()) + \".DOT\";\n\n\
    \        std::ofstream ss(filename);\n        ss << \"digraph{\\n\";\n       \
    \ int nleaf = 0;\n        for (int i = 0; i < int(nodes.size()); i++) {\n    \
    \        ss << i << \"[\\n\";\n            std::string lbl;\n            if (nodes[i].tp\
    \ == NodeType::Leaf) {\n                lbl = \"A[\" + std::to_string(nleaf) +\
    \ \"] = \" + std::to_string(A[nleaf]), nleaf++;\n            } else {\n      \
    \          lbl += std::string(nodes[i].tp == NodeType::Cut ? \"Cut\" : \"Join\"\
    ) + \"\\\\n\";\n                lbl += \"[\" + std::to_string(nodes[i].L) + \"\
    , \" + std::to_string(nodes[i].R) + \")\";\n            }\n            ss << \"\
    label = \\\"\" << lbl << \"\\\",\\n\";\n            ss << \"]\\n\";\n        \
    \    for (const auto &ch : nodes[i].child) ss << i << \" -> \" << ch << \";\\\
    n\";\n        }\n        ss << \"{rank = same;\";\n        for (int i = 0; i <\
    \ int(nodes.size()); i++) {\n            if (nodes[i].tp == NodeType::Leaf) ss\
    \ << ' ' << i << ';';\n        }\n        ss << \"}\\n\";\n        ss << \"}\\\
    n\";\n        ss.close();\n    }\n};\n"
  dependsOn:
  - segmenttree/range-add-range-min.hpp
  isVerificationFile: false
  path: other_algorithms/permutation_tree.hpp
  requiredBy: []
  timestamp: '2021-10-25 23:23:00+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - other_algorithms/test/permutation_tree.yuki1720.test.cpp
documentation_of: other_algorithms/permutation_tree.hpp
layout: document
title: "Permutation tree \uFF08\u9806\u5217\u6728\uFF09"
---

与えられた $[0, \dots, N - 1]$ の置換 $\mathbf{A} = [A\_0, \dots, A\_{N - 1}]$ について，この連続部分列であってその長さがそれに含まれる要素の最大値と最小値の差に $1$ を加えた値と等しくなるようなものを全て列挙するのに役立つデータ構造．

Permutation tree は区間のマージ過程を表す木として表現される．$N$ 個の葉は長さ $1$ の区間（単一の要素）に対応し，根は $\mathbf{A}$ 全体に対応する．

葉以外の全ての頂点は `Join` と `Cut` いずれかの属性を持つ．`Join` 属性を持つ頂点は，その子を $c\_1, \dots, c\_k$ とおくと，任意の $1 \le i \le j \le k$ について頂点 $(c\_i, \dots, c\_j)$ が表す区間の和集合は上記の条件を満たす．また，全ての頂点について，その頂点が表す区間全体は上記の条件を満たす．そして，上記の条件を満たす区間はこれらに限られるというのが最も重要な性質である．


## 使用方法（例）

木の各頂点の情報はメンバ変数 `std::vector<node> nodes` に格納されている．特に根が格納されている位置を示す変数が `tree.root`．

```cpp
enum NodeType {
    JoinAsc,    // Join，特に A[i] の値が増加していく
    JoinDesc,   // Join，特に A[i] の値が減少していく
    Cut,        // Cut
    Leaf,       // 葉である
    None,
};
struct node {
    NodeType tp;
    int L, R;                // [L, R) : 頂点が表す区間
    int mini, maxi;          // 区間に含まれる A[i] (L <= i < R) の最小・最大値
    std::vector<int> child;  // 子の頂点番号（昇順）
};
```

また．`to_DOT(std::string filename)` によって DOT 言語でのグラフ出力が可能．

## 問題例

### [ZeptoLab Code Rush 2015 F. Pudding Monsters - Codeforces](https://codeforces.com/contest/526/problem/F)

上記の条件を満たす区間の個数だけを求めればよい問題．

```cpp
permutation_tree tree(A);

auto rec = [&](auto &&self, int now) -> long long {
    long long ret = 1;
    const auto &v = tree.nodes[now];
    if (v.tp == permutation_tree::JoinAsc or v.tp == permutation_tree::JoinDesc) {
        ret = (long long)v.child.size() * (v.child.size() - 1) / 2;
    }
    for (auto c : v.child) ret += self(self, c);
    return ret;
};
cout << rec(rec, tree.root) << '\n';
```

### [No.1720 Division Permutation - yukicoder](https://yukicoder.me/problems/no/1720)

木上を DFS しながら DP の遷移をさせていけばよく，これは以下のように再帰的に書ける．

```cpp
permutation_tree tree(P);
vector dp(K + 1, vector<mint>(N + 1));
dp[0][0] = 1;

auto rec = [&](auto &&self, int now) -> void {
    auto &v = tree.nodes[now];
    if (v.tp == permutation_tree::Cut or v.tp == permutation_tree::Leaf) {
        for (int k = 0; k < K; ++k) dp[k + 1][v.R] += dp[k][v.L];
    }

    vector<mint> sum(K);
    for (auto ch : v.child) {
        self(self, ch);
        if (v.tp == permutation_tree::JoinAsc or v.tp == permutation_tree::JoinDesc) {
            for (int k = 0; k < K; ++k) {
                dp[k + 1][tree.nodes[ch].R] += sum[k];
                sum[k] += dp[k][tree.nodes[ch].L];
            }
        }
    }
};
rec(rec, tree.root);

for (int i = 1; i <= K; i++) cout << dp[i][N].val() << '\n';
```

## リンク

1. [Tutorial on Permutation Tree (析合树） - Codeforces](https://codeforces.com/blog/entry/78898)
