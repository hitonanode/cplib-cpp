---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':heavy_check_mark:'
    path: other_algorithms/permutation_tree.hpp
    title: "Permutation tree \uFF08\u9806\u5217\u6728\uFF09"
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
    PROBLEM: https://yukicoder.me/problems/no/1720
    links:
    - https://yukicoder.me/problems/no/1720
  bundledCode: "#line 1 \"other_algorithms/test/permutation_tree.yuki1720.test.cpp\"\
    \n#define PROBLEM \"https://yukicoder.me/problems/no/1720\"\n#line 2 \"segmenttree/range-add-range-min.hpp\"\
    \n#include <algorithm>\n#include <limits>\n#include <vector>\n\n// CUT begin\n\
    // StarrySkyTree: segment tree for Range Minimum Query & Range Add Query\n// Complexity:\
    \ $O(N)$ (construction), $O(\\log N)$ (add / get / prod)\n// - RangeAddRangeMin(std::vector<Tp>\
    \ data_init) : Initialize array x by data_init.\n// - add(int begin, int end,\
    \ Tp vadd) : Update x[i] <- x[i] + vadd for all begin <= i < end.\n// - get(int\
    \ pos) : Get x[pos].\n// - prod(int begin, int end) : Get min(x[begin], ..., x[end\
    \ - 1]).\ntemplate <typename Tp, Tp defaultT = std::numeric_limits<Tp>::max()\
    \ / 2> struct RangeAddRangeMin {\n    int N, head;\n    std::vector<Tp> range_min,\
    \ range_add;\n    static inline Tp f(Tp x, Tp y) noexcept { return std::min(x,\
    \ y); }\n\n    inline void _merge(int pos) {\n        range_min[pos] = f(range_min[pos\
    \ * 2] + range_add[pos * 2],\n                           range_min[pos * 2 + 1]\
    \ + range_add[pos * 2 + 1]);\n    }\n    void initialize(const std::vector<Tp>\
    \ &data_init) {\n        N = data_init.size(), head = 1;\n        while (head\
    \ < N) head <<= 1;\n        range_min.assign(head * 2, defaultT);\n        range_add.assign(head\
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
    n\";\n        ss.close();\n    }\n};\n#line 2 \"modint.hpp\"\n#include <iostream>\n\
    #include <set>\n#line 5 \"modint.hpp\"\n\n// CUT begin\ntemplate <int md> struct\
    \ ModInt {\n#if __cplusplus >= 201402L\n#define MDCONST constexpr\n#else\n#define\
    \ MDCONST\n#endif\n    using lint = long long;\n    MDCONST static int mod() {\
    \ return md; }\n    static int get_primitive_root() {\n        static int primitive_root\
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
    \ + x.val); }\n    MDCONST ModInt operator-(const ModInt &x) const {\n       \
    \ return ModInt()._setval((lint)val - x.val + md);\n    }\n    MDCONST ModInt\
    \ operator*(const ModInt &x) const {\n        return ModInt()._setval((lint)val\
    \ * x.val % md);\n    }\n    MDCONST ModInt operator/(const ModInt &x) const {\n\
    \        return ModInt()._setval((lint)val * x.inv() % md);\n    }\n    MDCONST\
    \ ModInt operator-() const { return ModInt()._setval(md - val); }\n    MDCONST\
    \ ModInt &operator+=(const ModInt &x) { return *this = *this + x; }\n    MDCONST\
    \ ModInt &operator-=(const ModInt &x) { return *this = *this - x; }\n    MDCONST\
    \ ModInt &operator*=(const ModInt &x) { return *this = *this * x; }\n    MDCONST\
    \ ModInt &operator/=(const ModInt &x) { return *this = *this / x; }\n    friend\
    \ MDCONST ModInt operator+(lint a, const ModInt &x) {\n        return ModInt()._setval(a\
    \ % md + x.val);\n    }\n    friend MDCONST ModInt operator-(lint a, const ModInt\
    \ &x) {\n        return ModInt()._setval(a % md - x.val + md);\n    }\n    friend\
    \ MDCONST ModInt operator*(lint a, const ModInt &x) {\n        return ModInt()._setval(a\
    \ % md * x.val % md);\n    }\n    friend MDCONST ModInt operator/(lint a, const\
    \ ModInt &x) {\n        return ModInt()._setval(a % md * x.inv() % md);\n    }\n\
    \    MDCONST bool operator==(const ModInt &x) const { return val == x.val; }\n\
    \    MDCONST bool operator!=(const ModInt &x) const { return val != x.val; }\n\
    \    MDCONST bool operator<(const ModInt &x) const {\n        return val < x.val;\n\
    \    } // To use std::map<ModInt, T>\n    friend std::istream &operator>>(std::istream\
    \ &is, ModInt &x) {\n        lint t;\n        return is >> t, x = ModInt(t), is;\n\
    \    }\n    MDCONST friend std::ostream &operator<<(std::ostream &os, const ModInt\
    \ &x) {\n        return os << x.val;\n    }\n    MDCONST ModInt pow(lint n) const\
    \ {\n        ModInt ans = 1, tmp = *this;\n        while (n) {\n            if\
    \ (n & 1) ans *= tmp;\n            tmp *= tmp, n >>= 1;\n        }\n        return\
    \ ans;\n    }\n\n    static std::vector<ModInt> facs, facinvs, invs;\n    MDCONST\
    \ static void _precalculation(int N) {\n        int l0 = facs.size();\n      \
    \  if (N > md) N = md;\n        if (N <= l0) return;\n        facs.resize(N),\
    \ facinvs.resize(N), invs.resize(N);\n        for (int i = l0; i < N; i++) facs[i]\
    \ = facs[i - 1] * i;\n        facinvs[N - 1] = facs.back().pow(md - 2);\n    \
    \    for (int i = N - 2; i >= l0; i--) facinvs[i] = facinvs[i + 1] * (i + 1);\n\
    \        for (int i = N - 1; i >= l0; i--) invs[i] = facinvs[i] * facs[i - 1];\n\
    \    }\n    MDCONST lint inv() const {\n        if (this->val < std::min(md >>\
    \ 1, 1 << 21)) {\n            while (this->val >= int(facs.size())) _precalculation(facs.size()\
    \ * 2);\n            return invs[this->val].val;\n        } else {\n         \
    \   return this->pow(md - 2).val;\n        }\n    }\n    MDCONST ModInt fac()\
    \ const {\n        while (this->val >= int(facs.size())) _precalculation(facs.size()\
    \ * 2);\n        return facs[this->val];\n    }\n    MDCONST ModInt facinv() const\
    \ {\n        while (this->val >= int(facs.size())) _precalculation(facs.size()\
    \ * 2);\n        return facinvs[this->val];\n    }\n    MDCONST ModInt doublefac()\
    \ const {\n        lint k = (this->val + 1) / 2;\n        return (this->val &\
    \ 1) ? ModInt(k * 2).fac() / (ModInt(2).pow(k) * ModInt(k).fac())\n          \
    \                     : ModInt(k).fac() * ModInt(2).pow(k);\n    }\n    MDCONST\
    \ ModInt nCr(const ModInt &r) const {\n        return (this->val < r.val) ? 0\
    \ : this->fac() * (*this - r).facinv() * r.facinv();\n    }\n    MDCONST ModInt\
    \ nPr(const ModInt &r) const {\n        return (this->val < r.val) ? 0 : this->fac()\
    \ * (*this - r).facinv();\n    }\n\n    ModInt sqrt() const {\n        if (val\
    \ == 0) return 0;\n        if (md == 2) return val;\n        if (pow((md - 1)\
    \ / 2) != 1) return 0;\n        ModInt b = 1;\n        while (b.pow((md - 1) /\
    \ 2) == 1) b += 1;\n        int e = 0, m = md - 1;\n        while (m % 2 == 0)\
    \ m >>= 1, e++;\n        ModInt x = pow((m - 1) / 2), y = (*this) * x * x;\n \
    \       x *= (*this);\n        ModInt z = b.pow(m);\n        while (y != 1) {\n\
    \            int j = 0;\n            ModInt t = y;\n            while (t != 1)\
    \ j++, t *= t;\n            z = z.pow(1LL << (e - j - 1));\n            x *= z,\
    \ z *= z, y *= z;\n            e = j;\n        }\n        return ModInt(std::min(x.val,\
    \ md - x.val));\n    }\n};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facs\
    \ = {1};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facinvs = {1};\n\
    template <int md> std::vector<ModInt<md>> ModInt<md>::invs = {0};\n// using mint\
    \ = ModInt<998244353>;\n// using mint = ModInt<1000000007>;\n#line 5 \"other_algorithms/test/permutation_tree.yuki1720.test.cpp\"\
    \n\nusing mint = ModInt<998244353>;\nusing namespace std;\n\nint N, K;\npermutation_tree\
    \ tree;\nvector<vector<mint>> dp;\n\nvoid rec(int now) {\n    const auto &v =\
    \ tree.nodes[now];\n    if (v.tp == permutation_tree::Cut or v.tp == permutation_tree::Leaf)\
    \ {\n        for (int k = 0; k < K; ++k) dp[k + 1][v.R] += dp[k][v.L];\n    }\n\
    \n    vector<mint> sum(K);\n    for (auto ch : v.child) {\n        rec(ch);\n\
    \        if (v.tp == permutation_tree::JoinAsc or v.tp == permutation_tree::JoinDesc)\
    \ {\n            for (int k = 0; k < K; ++k) {\n                dp[k + 1][tree.nodes[ch].R]\
    \ += sum[k];\n                sum[k] += dp[k][tree.nodes[ch].L];\n           \
    \ }\n        }\n    }\n};\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    cin >> N >> K;\n    vector<int> P(N);\n\n    for (auto &x : P) cin >> x;\n\
    \    for (auto &x : P) x--;\n\n    tree = permutation_tree(P);\n\n    dp.assign(K\
    \ + 1, vector<mint>(N + 1));\n    dp[0][0] = 1;\n\n    rec(tree.root);\n\n   \
    \ for (int i = 1; i <= K; i++) cout << dp[i][N] << '\\n';\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/1720\"\n#include \"../permutation_tree.hpp\"\
    \n#include \"../../modint.hpp\"\n#include <iostream>\n\nusing mint = ModInt<998244353>;\n\
    using namespace std;\n\nint N, K;\npermutation_tree tree;\nvector<vector<mint>>\
    \ dp;\n\nvoid rec(int now) {\n    const auto &v = tree.nodes[now];\n    if (v.tp\
    \ == permutation_tree::Cut or v.tp == permutation_tree::Leaf) {\n        for (int\
    \ k = 0; k < K; ++k) dp[k + 1][v.R] += dp[k][v.L];\n    }\n\n    vector<mint>\
    \ sum(K);\n    for (auto ch : v.child) {\n        rec(ch);\n        if (v.tp ==\
    \ permutation_tree::JoinAsc or v.tp == permutation_tree::JoinDesc) {\n       \
    \     for (int k = 0; k < K; ++k) {\n                dp[k + 1][tree.nodes[ch].R]\
    \ += sum[k];\n                sum[k] += dp[k][tree.nodes[ch].L];\n           \
    \ }\n        }\n    }\n};\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    cin >> N >> K;\n    vector<int> P(N);\n\n    for (auto &x : P) cin >> x;\n\
    \    for (auto &x : P) x--;\n\n    tree = permutation_tree(P);\n\n    dp.assign(K\
    \ + 1, vector<mint>(N + 1));\n    dp[0][0] = 1;\n\n    rec(tree.root);\n\n   \
    \ for (int i = 1; i <= K; i++) cout << dp[i][N] << '\\n';\n}\n"
  dependsOn:
  - other_algorithms/permutation_tree.hpp
  - segmenttree/range-add-range-min.hpp
  - modint.hpp
  isVerificationFile: true
  path: other_algorithms/test/permutation_tree.yuki1720.test.cpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: other_algorithms/test/permutation_tree.yuki1720.test.cpp
layout: document
redirect_from:
- /verify/other_algorithms/test/permutation_tree.yuki1720.test.cpp
- /verify/other_algorithms/test/permutation_tree.yuki1720.test.cpp.html
title: other_algorithms/test/permutation_tree.yuki1720.test.cpp
---
