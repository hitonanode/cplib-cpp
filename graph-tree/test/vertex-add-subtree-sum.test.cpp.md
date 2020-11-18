---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph-tree/eulertour.hpp
    title: graph-tree/eulertour.hpp
  - icon: ':question:'
    path: segmenttree/point-update-range-get_nonrecursive.hpp
    title: segmenttree/point-update-range-get_nonrecursive.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/vertex_add_subtree_sum
    links:
    - https://judge.yosupo.jp/problem/vertex_add_subtree_sum
  bundledCode: "#line 2 \"graph-tree/eulertour.hpp\"\n#include <cassert>\n#include\
    \ <vector>\n\n// CUT begin\n// Preorder Euler Tour\n// \uFF08\u884C\u304D\u304C\
    \u3051\u9806\uFF0C\u90E8\u5206\u6728\u306E\u9802\u70B9\u30AF\u30A8\u30EA\u7B49\
    \u306B\u6709\u7528\uFF09\nstruct PreorderEulerTour {\n    int V; // # of vertices\
    \ of tree\n    int root;\n    std::vector<std::vector<int>> edges;\n    std::vector<int>\
    \ subtree_begin, subtree_end;\n    std::vector<int> vis_order;\n\n    void _build_dfs(int\
    \ now, int prv) {\n        subtree_begin[now] = vis_order.size();\n        vis_order.push_back(now);\n\
    \        for (auto nxt : edges[now])\n            if (nxt != prv) _build_dfs(nxt,\
    \ now);\n        subtree_end[now] = vis_order.size();\n    }\n    PreorderEulerTour()\
    \ = default;\n    PreorderEulerTour(const std::vector<std::vector<int>> &to, int\
    \ root) : V(to.size()), root(root), edges(to) {\n        assert(root >= 0 and\
    \ root < V);\n        subtree_begin.resize(V);\n        subtree_end.resize(V);\n\
    \        _build_dfs(root, -1);\n    }\n};\n#line 2 \"segmenttree/point-update-range-get_nonrecursive.hpp\"\
    \n#include <algorithm>\n#line 4 \"segmenttree/point-update-range-get_nonrecursive.hpp\"\
    \n#include <functional>\n#include <iostream>\n#include <stack>\n#line 8 \"segmenttree/point-update-range-get_nonrecursive.hpp\"\
    \n\n// CUT begin\n// Nonrecursive Segment Tree (point-update, range-get)\n// -\
    \ Conditions for operations:\n//   - merge_data: [TDATA, TDATA] -> TDATA, e(x,\
    \ y) == e(y, x)\n//   - data2ret: [TDATA, TQUERY] -> TRET\n//   - merge_ret: [TRET,\
    \ TRET] -> TRET, g(defaultRET, x) == x, g(x, y) = g(y, x)\n//   - commutability\
    \ f(e(x, y), q) == g(f(x, q), f(y, q))\ntemplate <typename TDATA, typename TRET,\
    \ typename TQUERY> struct NonrecursiveSegmentTree {\n    int N;\n    TRET defaultRET;\n\
    \    virtual TDATA merge_data(const TDATA &, const TDATA &) = 0;\n    virtual\
    \ TRET data2ret(const TDATA &, const TQUERY &) = 0;\n    virtual TRET merge_ret(const\
    \ TRET &, const TRET &) = 0;\n    std::vector<TDATA> data;\n    inline TDATA &at(int\
    \ i) { return data[i]; }\n\n    inline void _merge(int i) { at(i) = merge_data(at(i\
    \ << 1), at((i << 1) + 1)); }\n    void initialize(const std::vector<TDATA> &seq,\
    \ TRET RET_ZERO) {\n        N = seq.size();\n        defaultRET = RET_ZERO;\n\
    \        data = seq;\n        data.insert(data.end(), seq.begin(), seq.end());\n\
    \        for (int i = N - 1; i; i--) _merge(i);\n    }\n    NonrecursiveSegmentTree()\
    \ = default;\n    void update(int pos, const TDATA &x) {\n        assert(pos >=\
    \ 0 and pos < N);\n        at(pos + N) = x;\n        for (int i = pos + N; i >\
    \ 1;) i >>= 1, _merge(i);\n    }\n\n    // [l, r), 0-indexed\n    TRET get(int\
    \ l, int r, TQUERY query = NULL) {\n        assert(l >= 0 and r <= N);\n     \
    \   TRET retl = defaultRET, retr = defaultRET;\n        l += N, r += N;\n    \
    \    while (l < r) {\n            if (l & 1) retl = merge_ret(retl, data2ret(data[l++],\
    \ query));\n            if (r & 1) retr = merge_ret(data2ret(data[--r], query),\
    \ retr);\n            l >>= 1, r >>= 1;\n        }\n        return merge_ret(retl,\
    \ retr);\n    }\n\n    // Calculate smallest r that satisfies condition(g(f(x_l,\
    \ q), ..., f(x_{r - 1}, q)) == true\n    // Assumption: Monotonicity of g(x_l,\
    \ ..., x_r) about r (l: fixed)\n    // Complexity: O(log N)\n    int binary_search(int\
    \ l, std::function<bool(TRET)> condition, TQUERY query = NULL) {\n        std::stack<int>\
    \ rs;\n        l += N;\n        int r = N * 2;\n        TRET retl = defaultRET;\n\
    \        if (condition(retl)) return l - N;\n        while (l < r) {\n       \
    \     if (l & 1) {\n                TRET ret_tmp = merge_ret(retl, data2ret(data[l],\
    \ query));\n                if (condition(ret_tmp)) {\n                    while\
    \ (l * 2 < N * 2) {\n                        ret_tmp = merge_ret(retl, data2ret(data[l\
    \ * 2], query));\n                        if (condition(ret_tmp))\n          \
    \                  l *= 2;\n                        else\n                   \
    \         retl = ret_tmp, l = l * 2 + 1;\n                    }\n            \
    \        return l - N;\n                }\n                l++;\n            \
    \    retl = ret_tmp;\n            }\n            if (r & 1) rs.push(--r);\n  \
    \          l >>= 1, r >>= 1;\n        }\n        while (!rs.empty()) {\n     \
    \       l = rs.top();\n            rs.pop();\n            TRET ret_tmp = merge_ret(retl,\
    \ data2ret(data[l], query));\n            if (condition(ret_tmp)) {\n        \
    \        while (l * 2 < N * 2) {\n                    ret_tmp = merge_ret(retl,\
    \ data2ret(data[l * 2], query));\n                    if (condition(ret_tmp))\n\
    \                        l *= 2;\n                    else\n                 \
    \       retl = ret_tmp, l = l * 2 + 1;\n                }\n                return\
    \ l - N;\n            }\n            retl = ret_tmp;\n        }\n        return\
    \ N;\n    }\n\n    template <typename T1, typename T2, typename T3> friend std::ostream\
    \ &operator<<(std::ostream &os, NonrecursiveSegmentTree<T1, T2, T3> s) {\n   \
    \     os << \"[SegmentTree (len: \" << s.N << ')';\n        for (int i = 0; i\
    \ < s.N; i++) os << s.at(i + s.N) << ',';\n        os << \"]\";\n        return\
    \ os;\n    }\n};\n\n// Range Minimum Query\n// - get: return min(x_l, ..., x_{r\
    \ - 1})\ntemplate <typename T> struct RangeMinimumQuery : public NonrecursiveSegmentTree<T,\
    \ T, bool> {\n    using SegTree = NonrecursiveSegmentTree<T, T, bool>;\n    T\
    \ merge_data(const T &vl, const T &vr) override { return std::min(vl, vr); };\n\
    \    T data2ret(const T &v, const bool &q) override { return v; }\n    T merge_ret(const\
    \ T &vl, const T &vr) override { return std::min(vl, vr); };\n    RangeMinimumQuery(const\
    \ std::vector<T> &seq, T defaultmin) : SegTree::NonrecursiveSegmentTree() { SegTree::initialize(seq,\
    \ defaultmin); };\n};\n\n// Range Maximum Query\n// - get: return max(x_l, ...,\
    \ x_{r - 1})\ntemplate <typename T> struct RangeMaximumQuery : public NonrecursiveSegmentTree<T,\
    \ T, bool> {\n    using SegTree = NonrecursiveSegmentTree<T, T, bool>;\n    T\
    \ merge_data(const T &vl, const T &vr) override { return std::max(vl, vr); };\n\
    \    T data2ret(const T &v, const bool &q) override { return v; }\n    T merge_ret(const\
    \ T &vl, const T &vr) override { return std::max(vl, vr); };\n    RangeMaximumQuery(const\
    \ std::vector<T> &seq, T defaultmax) : SegTree::NonrecursiveSegmentTree() { SegTree::initialize(seq,\
    \ defaultmax); };\n};\n\ntemplate <typename T> struct PointUpdateRangeSum : public\
    \ NonrecursiveSegmentTree<T, T, bool> {\n    using SegTree = NonrecursiveSegmentTree<T,\
    \ T, bool>;\n    T merge_data(const T &vl, const T &vr) override { return vl +\
    \ vr; };\n    T data2ret(const T &v, const bool &q) override { return v; }\n \
    \   T merge_ret(const T &vl, const T &vr) override { return vl + vr; };\n    PointUpdateRangeSum(const\
    \ std::vector<T> &seq, T zero) : SegTree::NonrecursiveSegmentTree() { SegTree::initialize(seq,\
    \ zero); };\n};\n\n// Range Counting less than q Query\n// - get: return (#{i\
    \ | l <= i < r, x_i < q}, total sum of them).\ntemplate <typename T> struct CountAndSumLessThan\
    \ : public NonrecursiveSegmentTree<std::vector<std::pair<T, T>>, std::pair<int,\
    \ T>, T> {\n    using TDATA = std::vector<std::pair<T, T>>;\n    using TRET =\
    \ std::pair<int, T>;\n    using TQUERY = T;\n    TDATA merge_data(const TDATA\
    \ &vl, const TDATA &vr) override {\n        TDATA ret = vl;\n        ret.insert(ret.end(),\
    \ vr.begin(), vr.end());\n        std::sort(ret.begin(), ret.end());\n       \
    \ if (ret.size()) {\n            ret[0].second = ret[0].first;\n            for\
    \ (size_t i = 1; i < ret.size(); i++) ret[i].second = ret[i - 1].second + ret[i].first;\n\
    \        }\n        return ret;\n    }\n    TRET data2ret(const TDATA &vec, const\
    \ TQUERY &q) override {\n        int i = std::lower_bound(vec.begin(), vec.end(),\
    \ std::make_pair(q, q)) - vec.begin();\n        if (!i)\n            return std::make_pair(0,\
    \ 0);\n        else\n            return std::make_pair(i, vec[i - 1].second);\n\
    \    }\n    TRET merge_ret(const TRET &l, const TRET &r) override { return std::make_pair(l.first\
    \ + r.first, l.second + r.second); }\n    using SegTree = NonrecursiveSegmentTree<TDATA,\
    \ TRET, TQUERY>;\n    CountAndSumLessThan(const std::vector<T> &seq) : SegTree::NonrecursiveSegmentTree()\
    \ {\n        std::vector<TDATA> init;\n        for (auto x : seq) init.emplace_back(TDATA{std::pair<T,\
    \ T>(x, x)});\n        SegTree::initialize(init, TRET(0, 0));\n    }\n};\n#line\
    \ 3 \"graph-tree/test/vertex-add-subtree-sum.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_add_subtree_sum\"\
    \n#line 6 \"graph-tree/test/vertex-add-subtree-sum.test.cpp\"\nusing namespace\
    \ std;\n\nint main() {\n    int N, Q;\n    cin >> N >> Q;\n    vector<long long\
    \ int> A(N);\n    vector<vector<int>> to(N);\n    for (auto &a : A) cin >> a;\n\
    \    for (int i = 1; i < N; i++) {\n        int p;\n        cin >> p;\n      \
    \  to[p].push_back(i);\n        to[i].push_back(p);\n    }\n\n    PreorderEulerTour\
    \ tour(to, 0);\n    vector<long long int> v;\n    for (auto i : tour.vis_order)\
    \ v.push_back(A[i]);\n    assert(int(v.size()) == N);\n    PointUpdateRangeSum<long\
    \ long int> rsq(v, 0);\n\n    while (Q--) {\n        int q;\n        cin >> q;\n\
    \        if (q) {\n            int u;\n            cin >> u;\n            printf(\"\
    %lld\\n\", rsq.get(tour.subtree_begin[u], tour.subtree_end[u]));\n        } else\
    \ {\n            int u, x;\n            cin >> u >> x;\n            A[u] += x;\n\
    \            rsq.update(tour.subtree_begin[u], A[u]);\n        }\n    }\n}\n"
  code: "#include \"graph-tree/eulertour.hpp\"\n#include \"segmenttree/point-update-range-get_nonrecursive.hpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_add_subtree_sum\"\n\
    #include <cassert>\n#include <iostream>\nusing namespace std;\n\nint main() {\n\
    \    int N, Q;\n    cin >> N >> Q;\n    vector<long long int> A(N);\n    vector<vector<int>>\
    \ to(N);\n    for (auto &a : A) cin >> a;\n    for (int i = 1; i < N; i++) {\n\
    \        int p;\n        cin >> p;\n        to[p].push_back(i);\n        to[i].push_back(p);\n\
    \    }\n\n    PreorderEulerTour tour(to, 0);\n    vector<long long int> v;\n \
    \   for (auto i : tour.vis_order) v.push_back(A[i]);\n    assert(int(v.size())\
    \ == N);\n    PointUpdateRangeSum<long long int> rsq(v, 0);\n\n    while (Q--)\
    \ {\n        int q;\n        cin >> q;\n        if (q) {\n            int u;\n\
    \            cin >> u;\n            printf(\"%lld\\n\", rsq.get(tour.subtree_begin[u],\
    \ tour.subtree_end[u]));\n        } else {\n            int u, x;\n          \
    \  cin >> u >> x;\n            A[u] += x;\n            rsq.update(tour.subtree_begin[u],\
    \ A[u]);\n        }\n    }\n}\n"
  dependsOn:
  - graph-tree/eulertour.hpp
  - segmenttree/point-update-range-get_nonrecursive.hpp
  isVerificationFile: true
  path: graph-tree/test/vertex-add-subtree-sum.test.cpp
  requiredBy: []
  timestamp: '2020-11-18 20:25:12+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: graph-tree/test/vertex-add-subtree-sum.test.cpp
layout: document
redirect_from:
- /verify/graph-tree/test/vertex-add-subtree-sum.test.cpp
- /verify/graph-tree/test/vertex-add-subtree-sum.test.cpp.html
title: graph-tree/test/vertex-add-subtree-sum.test.cpp
---
