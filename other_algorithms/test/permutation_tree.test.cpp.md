---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other_algorithms/permutation_tree.hpp
    title: "Common interval decomposition tree / \"Permutation tree\" \uFF08\u9806\
      \u5217\u6728\uFF09"
  - icon: ':heavy_check_mark:'
    path: segmenttree/range-add-range-min.hpp
    title: Range Add Range Min (known as the Starry sky tree)
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/common_interval_decomposition_tree
    links:
    - https://judge.yosupo.jp/problem/common_interval_decomposition_tree
  bundledCode: "#line 1 \"other_algorithms/test/permutation_tree.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/common_interval_decomposition_tree\"\
    \n#line 2 \"segmenttree/range-add-range-min.hpp\"\n#include <algorithm>\n#include\
    \ <limits>\n#include <vector>\n\n// CUT begin\n// StarrySkyTree: segment tree\
    \ for Range Minimum Query & Range Add Query\n// Complexity: $O(N)$ (construction),\
    \ $O(\\log N)$ (add / get / prod)\n// - RangeAddRangeMin(std::vector<Tp> data_init)\
    \ : Initialize array x by data_init.\n// - add(int begin, int end, Tp vadd) :\
    \ Update x[i] <- x[i] + vadd for all begin <= i < end.\n// - get(int pos) : Get\
    \ x[pos].\n// - prod(int begin, int end) : Get min(x[begin], ..., x[end - 1]).\n\
    template <typename Tp, Tp defaultT = std::numeric_limits<Tp>::max() / 2> struct\
    \ RangeAddRangeMin {\n    int N, head;\n    std::vector<Tp> range_min, range_add;\n\
    \    static inline Tp f(Tp x, Tp y) noexcept { return std::min(x, y); }\n\n  \
    \  inline void _merge(int pos) {\n        range_min[pos] = f(range_min[pos * 2]\
    \ + range_add[pos * 2],\n                           range_min[pos * 2 + 1] + range_add[pos\
    \ * 2 + 1]);\n    }\n    void initialize(const std::vector<Tp> &data_init) {\n\
    \        N = data_init.size(), head = 1;\n        while (head < N) head <<= 1;\n\
    \        range_min.assign(head * 2, defaultT);\n        range_add.assign(head\
    \ * 2, 0);\n        std::copy(data_init.begin(), data_init.end(), range_min.begin()\
    \ + head);\n        for (int pos = head; --pos;) _merge(pos);\n    }\n    RangeAddRangeMin()\
    \ = default;\n    RangeAddRangeMin(const std::vector<Tp> &data_init) { initialize(data_init);\
    \ }\n    void _add(int begin, int end, int pos, int l, int r, Tp vadd) noexcept\
    \ {\n        if (r <= begin or end <= l) return;\n        if (begin <= l and r\
    \ <= end) {\n            range_add[pos] += vadd;\n            return;\n      \
    \  }\n        _add(begin, end, pos * 2, l, (l + r) / 2, vadd);\n        _add(begin,\
    \ end, pos * 2 + 1, (l + r) / 2, r, vadd);\n        _merge(pos);\n    }\n    //\
    \ Add `vadd` to (x_begin, ..., x_{end - 1})\n    void add(int begin, int end,\
    \ Tp vadd) noexcept { return _add(begin, end, 1, 0, head, vadd); }\n    Tp _get(int\
    \ begin, int end, int pos, int l, int r) const noexcept {\n        if (r <= begin\
    \ or end <= l) return defaultT;\n        if (begin <= l and r <= end) return range_min[pos]\
    \ + range_add[pos];\n        return f(_get(begin, end, pos * 2, l, (l + r) / 2),\n\
    \                 _get(begin, end, pos * 2 + 1, (l + r) / 2, r)) +\n         \
    \      range_add[pos];\n    }\n    // Return f(x_begin, ..., x_{end - 1})\n  \
    \  Tp get(int pos) const noexcept { return prod(pos, pos + 1); }\n    Tp prod(int\
    \ begin, int end) const noexcept { return _get(begin, end, 1, 0, head); }\n};\n\
    #line 4 \"other_algorithms/permutation_tree.hpp\"\n#include <cassert>\n#include\
    \ <fstream>\n#include <string>\n#line 8 \"other_algorithms/permutation_tree.hpp\"\
    \n\n// Permutation tree\n// Complexity: O(N log N)\n// https://codeforces.com/blog/entry/78898\
    \ https://judge.yosupo.jp/problem/common_interval_decomposition_tree\nstruct permutation_tree\
    \ {\n    enum NodeType {\n        JoinAsc,\n        JoinDesc,\n        Cut,\n\
    \        Leaf,\n        None,\n    };\n    struct Node {\n        NodeType tp;\n\
    \        int L, R;       // i in [L, R)\n        int mini, maxi; // A[i] in [mini,\
    \ maxi]\n        int par_id = -1;\n        std::vector<int> child;\n        int\
    \ sz() const { return R - L; }\n        template <class OStream> friend OStream\
    \ &operator<<(OStream &os, const Node &n) {\n            os << \"[[\" << n.L <<\
    \ ',' << n.R << \")(ch:\";\n            for (auto i : n.child) os << i << ',';\n\
    \            return os << \")(tp=\" << n.tp << \")]\";\n        }\n    };\n\n\
    \    int root;\n    std::vector<int> A;\n    std::vector<Node> nodes;\n\n    void\
    \ _add_child(int par_id, int chid) {\n        nodes[par_id].child.push_back(chid);\n\
    \        nodes[par_id].L = std::min(nodes[par_id].L, nodes[chid].L);\n       \
    \ nodes[par_id].R = std::max(nodes[par_id].R, nodes[chid].R);\n        nodes[par_id].mini\
    \ = std::min(nodes[par_id].mini, nodes[chid].mini);\n        nodes[par_id].maxi\
    \ = std::max(nodes[par_id].maxi, nodes[chid].maxi);\n    }\n\n    permutation_tree()\
    \ : root(-1) {}\n    permutation_tree(const std::vector<int> &A_) : root(-1),\
    \ A(A_) { // A: nonempty perm., 0-origin\n        assert(!A.empty());\n      \
    \  RangeAddRangeMin<int> seg((std::vector<int>(A.size())));\n\n        std::vector<int>\
    \ hi{-1}, lo{-1};\n        std::vector<int> st;\n        for (int i = 0; i < int(A.size());\
    \ ++i) {\n            while (hi.back() >= 0 and A[i] > A[hi.back()]) {\n     \
    \           seg.add(hi[hi.size() - 2] + 1, hi.back() + 1, A[i] - A[hi.back()]);\n\
    \                hi.pop_back();\n            }\n            hi.push_back(i);\n\
    \            while (lo.back() >= 0 and A[i] < A[lo.back()]) {\n              \
    \  seg.add(lo[lo.size() - 2] + 1, lo.back() + 1, A[lo.back()] - A[i]);\n     \
    \           lo.pop_back();\n            }\n            lo.push_back(i);\n\n  \
    \          int h = nodes.size();\n            nodes.push_back({NodeType::Leaf,\
    \ i, i + 1, A[i], A[i], -1, std::vector<int>{}});\n\n            while (true)\
    \ {\n                NodeType join_tp = NodeType::None;\n                if (!st.empty()\
    \ and nodes[st.back()].maxi + 1 == nodes[h].mini) join_tp = JoinAsc;\n       \
    \         if (!st.empty() and nodes[h].maxi + 1 == nodes[st.back()].mini) join_tp\
    \ = JoinDesc;\n\n                if (!st.empty() and join_tp != NodeType::None)\
    \ {\n                    const Node &vtp = nodes[st.back()];\n               \
    \     // Insert v as the child of the top node in the stack\n                \
    \    if (join_tp == vtp.tp) {\n                        // Append child to existing\
    \ Join node\n                        _add_child(st.back(), h);\n             \
    \           h = st.back();\n                        st.pop_back();\n         \
    \           } else {\n                        // Make new join node (with exactly\
    \ two children)\n                        int j = st.back();\n                \
    \        nodes.push_back(\n                            {join_tp, nodes[j].L, nodes[j].R,\
    \ nodes[j].mini, nodes[j].maxi, -1, {j}});\n                        st.pop_back();\n\
    \                        _add_child(nodes.size() - 1, h);\n                  \
    \      h = nodes.size() - 1;\n                    }\n                } else if\
    \ (seg.prod(0, i + 1 - nodes[h].sz()) == 0) {\n                    // Make Cut\
    \ node\n                    int L = nodes[h].L, R = nodes[h].R, maxi = nodes[h].maxi,\
    \ mini = nodes[h].mini;\n                    nodes.push_back({NodeType::Cut, L,\
    \ R, mini, maxi, -1, {h}});\n                    h = nodes.size() - 1;\n     \
    \               do {\n                        _add_child(h, st.back());\n    \
    \                    st.pop_back();\n                    } while (nodes[h].maxi\
    \ - nodes[h].mini + 1 != nodes[h].sz());\n                    std::reverse(nodes[h].child.begin(),\
    \ nodes[h].child.end());\n                } else {\n                    break;\n\
    \                }\n            }\n            st.push_back(h);\n            seg.add(0,\
    \ i + 1, -1);\n        }\n        assert(st.size() == 1);\n\n        for (int\
    \ i = 0; i < int(nodes.size()); i++) {\n            for (auto ch : nodes[i].child)\
    \ nodes[ch].par_id = i;\n        }\n\n        root = st[0];\n    }\n\n    void\
    \ to_DOT(std::string filename = \"\") const {\n        if (filename.empty()) filename\
    \ = \"permutation_tree_v=\" + std::to_string(A.size()) + \".DOT\";\n\n       \
    \ std::ofstream ss(filename);\n        ss << \"digraph{\\n\";\n        int nleaf\
    \ = 0;\n        for (int i = 0; i < int(nodes.size()); i++) {\n            ss\
    \ << i << \"[\\n\";\n            std::string lbl;\n            if (nodes[i].tp\
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
    n\";\n        ss.close();\n    }\n};\n#line 3 \"other_algorithms/test/permutation_tree.test.cpp\"\
    \n\n#include <iostream>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n    int N;\n    cin >> N;\n\n    vector<int> P(N);\n\
    \    for (auto &p : P) cin >> p;\n\n    const permutation_tree pt(P);\n\n    cout\
    \ << pt.nodes.size() << '\\n';\n\n    for (const auto &node : pt.nodes) {\n  \
    \      cout << node.par_id << ' ' << node.L << ' ' << node.R - 1 << ' '\n    \
    \         << (node.tp == permutation_tree::Cut ? \"prime\" : \"linear\") << '\\\
    n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/common_interval_decomposition_tree\"\
    \n#include \"../permutation_tree.hpp\"\n\n#include <iostream>\nusing namespace\
    \ std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n \
    \   int N;\n    cin >> N;\n\n    vector<int> P(N);\n    for (auto &p : P) cin\
    \ >> p;\n\n    const permutation_tree pt(P);\n\n    cout << pt.nodes.size() <<\
    \ '\\n';\n\n    for (const auto &node : pt.nodes) {\n        cout << node.par_id\
    \ << ' ' << node.L << ' ' << node.R - 1 << ' '\n             << (node.tp == permutation_tree::Cut\
    \ ? \"prime\" : \"linear\") << '\\n';\n    }\n}\n"
  dependsOn:
  - other_algorithms/permutation_tree.hpp
  - segmenttree/range-add-range-min.hpp
  isVerificationFile: true
  path: other_algorithms/test/permutation_tree.test.cpp
  requiredBy: []
  timestamp: '2025-12-03 22:27:21+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: other_algorithms/test/permutation_tree.test.cpp
layout: document
redirect_from:
- /verify/other_algorithms/test/permutation_tree.test.cpp
- /verify/other_algorithms/test/permutation_tree.test.cpp.html
title: other_algorithms/test/permutation_tree.test.cpp
---
