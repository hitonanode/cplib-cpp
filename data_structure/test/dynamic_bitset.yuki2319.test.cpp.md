---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/dynamic_bitset.hpp
    title: "Dynamic Bitset \uFF08\u52D5\u7684\u30B5\u30A4\u30BA bitset\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/2319
    links:
    - https://yukicoder.me/problems/no/2319
  bundledCode: "#line 1 \"data_structure/test/dynamic_bitset.yuki2319.test.cpp\"\n\
    #define PROBLEM \"https://yukicoder.me/problems/no/2319\"\n#line 2 \"data_structure/dynamic_bitset.hpp\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <initializer_list>\n#include\
    \ <string>\n#include <vector>\n\nstruct dynamic_bitset {\n    using ull = unsigned\
    \ long long;\n    static constexpr int W = 64;\n\n    int n = 0;          // number\
    \ of bits\n    int m = 0;          // number of 64-bit blocks\n    std::vector<ull>\
    \ a; // blocks\n\n    dynamic_bitset() = default;\n    explicit dynamic_bitset(int\
    \ n_, bool init_one = false) { reset_size(n_, init_one); }\n    explicit dynamic_bitset(const\
    \ std::string &s) : dynamic_bitset(int(s.size())) {\n        const char *p = s.data();\n\
    \        for (int blk = 0; blk < m; ++blk) {\n            int l = std::max(0,\
    \ n - ((blk + 1) << 6));\n            int r = n - (blk << 6);\n            ull\
    \ x = 0;\n            for (int i = l; i < r; ++i) x = (x << 1) | ull(p[i] == '1');\n\
    \            a[blk] = x;\n        }\n    }\n\n    void reset_size(int n_, bool\
    \ init_one = false) {\n        n = n_;\n        m = (n + W - 1) / W;\n       \
    \ a.assign(m, init_one ? ~0ULL : 0ULL);\n        trim();\n    }\n\n    int size()\
    \ const { return n; }\n\n    // ---- low-level helpers ----\n    ull last_mask()\
    \ const {\n        int r = n & (W - 1);\n        if (r == 0) return ~0ULL;\n \
    \       return (r == 64 ? ~0ULL : ((1ULL << r) - 1ULL));\n    }\n    void trim()\
    \ {\n        if (m == 0) return;\n        a.back() &= last_mask();\n    }\n\n\
    \    static inline int ctz64(ull x) { return __builtin_ctzll(x); }\n    static\
    \ inline int clz64(ull x) { return __builtin_clzll(x); }\n    static inline int\
    \ msb_index64(ull x) { return 63 - clz64(x); } // x != 0\n    void assert_index(int\
    \ i) const { assert(0 <= i && i < n); }\n    void assert_same_size(const dynamic_bitset\
    \ &o) const { assert(n == o.n); }\n\n    // ---- basic bit ops ----\n    bool\
    \ test(int i) const {\n        assert_index(i);\n        return (a[i >> 6] >>\
    \ (i & 63)) & 1ULL;\n    }\n    void set(int i) {\n        assert_index(i);\n\
    \        a[i >> 6] |= (1ULL << (i & 63));\n    }\n    void reset(int i) {\n  \
    \      assert_index(i);\n        a[i >> 6] &= ~(1ULL << (i & 63));\n    }\n  \
    \  void flip(int i) {\n        assert_index(i);\n        a[i >> 6] ^= (1ULL <<\
    \ (i & 63));\n    }\n    void set(int i, bool v) { v ? set(i) : reset(i); }\n\n\
    \    void reset_all() { std::fill(a.begin(), a.end(), 0ULL); }\n    void set_all()\
    \ {\n        std::fill(a.begin(), a.end(), ~0ULL);\n        trim();\n    }\n \
    \   void flip_all() {\n        for (auto &x : a) x = ~x;\n        trim();\n  \
    \  }\n\n    // count (optional but handy)\n    int popcount() const {\n      \
    \  int s = 0;\n        for (ull x : a) s += __builtin_popcountll(x);\n       \
    \ return s;\n    }\n    int count() const { return popcount(); }\n\n    // ----\
    \ bitwise ops ----\n    // ---- any / none ----\n    bool any() const {\n    \
    \    for (ull x : a)\n            if (x) return true;\n        return false;\n\
    \    }\n    bool none() const { return !any(); }\n\n    // ---- bitwise assign\
    \ ops ----\n    dynamic_bitset &operator^=(const dynamic_bitset &o) {\n      \
    \  assert_same_size(o);\n        for (int i = 0; i < m; i++) a[i] ^= o.a[i];\n\
    \        trim();\n        return *this;\n    }\n    dynamic_bitset &operator|=(const\
    \ dynamic_bitset &o) {\n        assert_same_size(o);\n        for (int i = 0;\
    \ i < m; i++) a[i] |= o.a[i];\n        trim();\n        return *this;\n    }\n\
    \    dynamic_bitset &operator&=(const dynamic_bitset &o) {\n        assert_same_size(o);\n\
    \        for (int i = 0; i < m; i++) a[i] &= o.a[i];\n        trim();\n      \
    \  return *this;\n    }\n\n    friend dynamic_bitset operator^(dynamic_bitset\
    \ l, const dynamic_bitset &r) {\n        l ^= r;\n        return l;\n    }\n \
    \   friend dynamic_bitset operator|(dynamic_bitset l, const dynamic_bitset &r)\
    \ {\n        l |= r;\n        return l;\n    }\n    friend dynamic_bitset operator&(dynamic_bitset\
    \ l, const dynamic_bitset &r) {\n        l &= r;\n        return l;\n    }\n\n\
    \    bool operator==(const dynamic_bitset &o) const { return n == o.n && a ==\
    \ o.a; }\n    bool operator!=(const dynamic_bitset &o) const { return !(*this\
    \ == o); }\n    int compare(const dynamic_bitset &o) const {\n        if (n !=\
    \ o.n) return n < o.n ? -1 : 1;\n        for (int i = m - 1; i >= 0; --i) {\n\
    \            if (a[i] != o.a[i]) return a[i] < o.a[i] ? -1 : 1;\n        }\n \
    \       return 0;\n    }\n    bool operator<(const dynamic_bitset &o) const {\
    \ return compare(o) < 0; }\n    bool operator<=(const dynamic_bitset &o) const\
    \ { return compare(o) <= 0; }\n    bool operator>(const dynamic_bitset &o) const\
    \ { return compare(o) > 0; }\n    bool operator>=(const dynamic_bitset &o) const\
    \ { return compare(o) >= 0; }\n\n    // returns bitset b with b.test(i) == test(l\
    \ + i) for 0 <= i < r - l\n    dynamic_bitset slice(int l, int r) const {\n  \
    \      l = std::clamp(l, 0, n);\n        r = std::clamp(r, 0, n);\n        if\
    \ (l >= r) return dynamic_bitset();\n\n        dynamic_bitset res(r - l);\n  \
    \      int ws = l >> 6;\n        int bs = l & 63;\n        for (int i = 0; i <\
    \ res.m; ++i) {\n            ull lo = (ws + i < m ? (a[ws + i] >> bs) : 0ULL);\n\
    \            ull hi = (bs && ws + i + 1 < m ? (a[ws + i + 1] << (W - bs)) : 0ULL);\n\
    \            res.a[i] = lo | hi;\n        }\n        res.trim();\n        return\
    \ res;\n    }\n\nprivate:\n    template <class Range> static dynamic_bitset join_range(const\
    \ Range &xs) {\n        int total = 0;\n        for (const auto &x : xs) total\
    \ += x.n;\n\n        dynamic_bitset res(total);\n        int cur = 0;\n      \
    \  for (const auto &x : xs) {\n            int ws = cur >> 6;\n            int\
    \ bs = cur & 63;\n            for (int i = 0; i < x.m; ++i) {\n              \
    \  ull v = x.a[i];\n                if (!v) continue;\n                res.a[ws\
    \ + i] |= v << bs;\n                if (bs && ws + i + 1 < res.m) res.a[ws + i\
    \ + 1] |= v >> (W - bs);\n            }\n            cur += x.n;\n        }\n\
    \        res.trim();\n        return res;\n    }\n\npublic:\n    static dynamic_bitset\
    \ join(const std::vector<dynamic_bitset> &xs) { return join_range(xs); }\n   \
    \ static dynamic_bitset join(std::initializer_list<dynamic_bitset> xs) { return\
    \ join_range(xs); }\n    static dynamic_bitset join(const dynamic_bitset &a, const\
    \ dynamic_bitset &b) {\n        return join({a, b});\n    }\n\n    dynamic_bitset\
    \ operator~() const {\n        dynamic_bitset r = *this;\n        for (auto &x\
    \ : r.a) x = ~x;\n        r.trim();\n        return r;\n    }\n\n    // ---- shifts\
    \ ----\n    dynamic_bitset &operator<<=(int k) {\n        if (k <= 0 || n == 0)\
    \ return *this;\n        if (k >= n) {\n            reset_all();\n           \
    \ return *this;\n        }\n        int ws = k >> 6;\n        int bs = k & 63;\n\
    \n        if (ws) {\n            for (int i = m - 1; i >= 0; --i) {\n        \
    \        ull v = (i - ws >= 0) ? a[i - ws] : 0ULL;\n                a[i] = v;\n\
    \            }\n        }\n        if (bs) {\n            for (int i = m - 1;\
    \ i >= 0; --i) {\n                ull hi = a[i] << bs;\n                ull lo\
    \ = (i ? (a[i - 1] >> (64 - bs)) : 0ULL);\n                a[i] = hi | lo;\n \
    \           }\n        }\n        // zero-fill lower words introduced by ws shift\n\
    \        if (ws) {\n            for (int i = 0; i < ws && i < m; ++i) a[i] = 0ULL;\n\
    \        }\n        trim();\n        return *this;\n    }\n\n    dynamic_bitset\
    \ &operator>>=(int k) {\n        if (k <= 0 || n == 0) return *this;\n       \
    \ if (k >= n) {\n            reset_all();\n            return *this;\n       \
    \ }\n        int ws = k >> 6;\n        int bs = k & 63;\n\n        if (ws) {\n\
    \            for (int i = 0; i < m; ++i) {\n                ull v = (i + ws <\
    \ m) ? a[i + ws] : 0ULL;\n                a[i] = v;\n            }\n        }\n\
    \        if (bs) {\n            for (int i = 0; i < m; ++i) {\n              \
    \  ull lo = a[i] >> bs;\n                ull hi = (i + 1 < m ? (a[i + 1] << (64\
    \ - bs)) : 0ULL);\n                a[i] = lo | hi;\n            }\n        }\n\
    \        // zero-fill upper words introduced by ws shift\n        if (ws) {\n\
    \            for (int i = m - ws; i < m; ++i)\n                if (0 <= i && i\
    \ < m) a[i] = 0ULL;\n        }\n        trim();\n        return *this;\n    }\n\
    \n    friend dynamic_bitset operator<<(dynamic_bitset b, int k) {\n        b <<=\
    \ k;\n        return b;\n    }\n    friend dynamic_bitset operator>>(dynamic_bitset\
    \ b, int k) {\n        b >>= k;\n        return b;\n    }\n\n    // ---- find\
    \ set bits ----\n    // returns smallest i with bit=1, or size()\n    int first()\
    \ const {\n        for (int i = 0; i < m; ++i) {\n            ull x = a[i];\n\
    \            if (x) return (i << 6) + ctz64(x);\n        }\n        return size();\n\
    \    }\n\n    // returns smallest j > i with bit=1, or size()\n    int next(int\
    \ i) const {\n        if (n == 0) return size();\n        int j = i + 1;\n   \
    \     if (j <= 0) return first();\n        if (j >= n) return size();\n\n    \
    \    int b = j >> 6;\n        int off = j & 63;\n\n        // mask out bits <\
    \ off\n        ull x = a[b] & (~0ULL << off);\n        if (x) return (b << 6)\
    \ + ctz64(x);\n\n        for (int bb = b + 1; bb < m; ++bb) {\n            ull\
    \ y = a[bb];\n            if (y) return (bb << 6) + ctz64(y);\n        }\n   \
    \     return size();\n    }\n\n    // returns largest i with bit=1, or -1\n  \
    \  int last() const {\n        for (int i = m - 1; i >= 0; --i) {\n          \
    \  ull x = a[i];\n            if (i == m - 1) x &= last_mask();\n            if\
    \ (x) return (i << 6) + msb_index64(x);\n        }\n        return -1;\n    }\n\
    \n    // returns largest j < i with bit=1, or -1\n    int prev(int i) const {\n\
    \        if (n == 0) return -1;\n        int j = i - 1;\n        if (j < 0) return\
    \ -1;\n        if (j >= n) return last();\n\n        int b = j >> 6;\n       \
    \ int off = j & 63;\n\n        ull mask = (off == 63) ? ~0ULL : ((1ULL << (off\
    \ + 1)) - 1ULL);\n        ull x = a[b] & mask;\n        if (x) return (b << 6)\
    \ + msb_index64(x);\n\n        for (int bb = b - 1; bb >= 0; --bb) {\n       \
    \     ull y = a[bb];\n            if (y) return (bb << 6) + msb_index64(y);\n\
    \        }\n        return -1;\n    }\n};\n#line 3 \"data_structure/test/dynamic_bitset.yuki2319.test.cpp\"\
    \n#include <iostream>\n#line 5 \"data_structure/test/dynamic_bitset.yuki2319.test.cpp\"\
    \nusing namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \    int N, M;\n    cin >> N >> M;\n    vector<dynamic_bitset> is_friend(N, dynamic_bitset(N)),\
    \ world_has(N, dynamic_bitset(N));\n    vector<int> P(N);\n\n    for (int i =\
    \ 0; i < N; ++i) cin >> P.at(i), P.at(i)--, world_has.at(P.at(i)).set(i);\n\n\
    \    while (M--) {\n        int a, b;\n        cin >> a >> b;\n        --a, --b;\n\
    \        is_friend.at(a).set(b);\n        is_friend.at(b).set(a);\n    }\n\n \
    \   int Q;\n    cin >> Q;\n    while (Q--) {\n        int x, y;\n        cin >>\
    \ x >> y;\n        --x, --y;\n        if (P.at(x) != P.at(y) and (world_has.at(P.at(y))\
    \ & is_friend.at(x)).any()) {\n            puts(\"Yes\");\n            world_has.at(P.at(x)).reset(x);\n\
    \            P.at(x) = P.at(y);\n            world_has.at(P.at(x)).set(x);\n \
    \       } else {\n            puts(\"No\");\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/2319\"\n#include \"../dynamic_bitset.hpp\"\
    \n#include <iostream>\n#include <vector>\nusing namespace std;\n\nint main() {\n\
    \    cin.tie(nullptr), ios::sync_with_stdio(false);\n    int N, M;\n    cin >>\
    \ N >> M;\n    vector<dynamic_bitset> is_friend(N, dynamic_bitset(N)), world_has(N,\
    \ dynamic_bitset(N));\n    vector<int> P(N);\n\n    for (int i = 0; i < N; ++i)\
    \ cin >> P.at(i), P.at(i)--, world_has.at(P.at(i)).set(i);\n\n    while (M--)\
    \ {\n        int a, b;\n        cin >> a >> b;\n        --a, --b;\n        is_friend.at(a).set(b);\n\
    \        is_friend.at(b).set(a);\n    }\n\n    int Q;\n    cin >> Q;\n    while\
    \ (Q--) {\n        int x, y;\n        cin >> x >> y;\n        --x, --y;\n    \
    \    if (P.at(x) != P.at(y) and (world_has.at(P.at(y)) & is_friend.at(x)).any())\
    \ {\n            puts(\"Yes\");\n            world_has.at(P.at(x)).reset(x);\n\
    \            P.at(x) = P.at(y);\n            world_has.at(P.at(x)).set(x);\n \
    \       } else {\n            puts(\"No\");\n        }\n    }\n}\n"
  dependsOn:
  - data_structure/dynamic_bitset.hpp
  isVerificationFile: true
  path: data_structure/test/dynamic_bitset.yuki2319.test.cpp
  requiredBy: []
  timestamp: '2026-03-02 01:35:44+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: data_structure/test/dynamic_bitset.yuki2319.test.cpp
layout: document
redirect_from:
- /verify/data_structure/test/dynamic_bitset.yuki2319.test.cpp
- /verify/data_structure/test/dynamic_bitset.yuki2319.test.cpp.html
title: data_structure/test/dynamic_bitset.yuki2319.test.cpp
---
