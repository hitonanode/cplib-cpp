---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: data_structure/test/dynamic_bitset.yuki1444.test.cpp
    title: data_structure/test/dynamic_bitset.yuki1444.test.cpp
  - icon: ':heavy_check_mark:'
    path: data_structure/test/dynamic_bitset.yuki1514.test.cpp
    title: data_structure/test/dynamic_bitset.yuki1514.test.cpp
  - icon: ':heavy_check_mark:'
    path: data_structure/test/dynamic_bitset.yuki1560.test.cpp
    title: data_structure/test/dynamic_bitset.yuki1560.test.cpp
  - icon: ':heavy_check_mark:'
    path: data_structure/test/dynamic_bitset.yuki1782.test.cpp
    title: data_structure/test/dynamic_bitset.yuki1782.test.cpp
  - icon: ':heavy_check_mark:'
    path: data_structure/test/dynamic_bitset.yuki1861.test.cpp
    title: data_structure/test/dynamic_bitset.yuki1861.test.cpp
  - icon: ':heavy_check_mark:'
    path: data_structure/test/dynamic_bitset.yuki2319.test.cpp
    title: data_structure/test/dynamic_bitset.yuki2319.test.cpp
  - icon: ':heavy_check_mark:'
    path: data_structure/test/dynamic_bitset.yuki2542.test.cpp
    title: data_structure/test/dynamic_bitset.yuki2542.test.cpp
  - icon: ':heavy_check_mark:'
    path: data_structure/test/dynamic_bitset.yuki3041.test.cpp
    title: data_structure/test/dynamic_bitset.yuki3041.test.cpp
  - icon: ':heavy_check_mark:'
    path: data_structure/test/dynamic_bitset.yuki3060.test.cpp
    title: data_structure/test/dynamic_bitset.yuki3060.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"data_structure/dynamic_bitset.hpp\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <initializer_list>\n#include <string>\n#include <vector>\n\
    \nstruct dynamic_bitset {\n    using ull = unsigned long long;\n    static constexpr\
    \ int W = 64;\n\n    int n = 0;          // number of bits\n    int m = 0;   \
    \       // number of 64-bit blocks\n    std::vector<ull> a; // blocks\n\n    dynamic_bitset()\
    \ = default;\n    explicit dynamic_bitset(int n_, bool init_one = false) { reset_size(n_,\
    \ init_one); }\n    explicit dynamic_bitset(const std::string &s) : dynamic_bitset(int(s.size()))\
    \ {\n        const char *p = s.data();\n        for (int blk = 0; blk < m; ++blk)\
    \ {\n            int l = std::max(0, n - ((blk + 1) << 6));\n            int r\
    \ = n - (blk << 6);\n            ull x = 0;\n            for (int i = l; i < r;\
    \ ++i) x = (x << 1) | ull(p[i] == '1');\n            a[blk] = x;\n        }\n\
    \    }\n\n    void reset_size(int n_, bool init_one = false) {\n        n = n_;\n\
    \        m = (n + W - 1) / W;\n        a.assign(m, init_one ? ~0ULL : 0ULL);\n\
    \        trim();\n    }\n\n    int size() const { return n; }\n\n    // ---- low-level\
    \ helpers ----\n    ull last_mask() const {\n        int r = n & (W - 1);\n  \
    \      if (r == 0) return ~0ULL;\n        return (r == 64 ? ~0ULL : ((1ULL <<\
    \ r) - 1ULL));\n    }\n    void trim() {\n        if (m == 0) return;\n      \
    \  a.back() &= last_mask();\n    }\n\n    static inline int ctz64(ull x) { return\
    \ __builtin_ctzll(x); }\n    static inline int clz64(ull x) { return __builtin_clzll(x);\
    \ }\n    static inline int msb_index64(ull x) { return 63 - clz64(x); } // x !=\
    \ 0\n    void assert_index(int i) const { assert(0 <= i && i < n); }\n    void\
    \ assert_same_size(const dynamic_bitset &o) const { assert(n == o.n); }\n\n  \
    \  // ---- basic bit ops ----\n    bool test(int i) const {\n        assert_index(i);\n\
    \        return (a[i >> 6] >> (i & 63)) & 1ULL;\n    }\n    void set(int i) {\n\
    \        assert_index(i);\n        a[i >> 6] |= (1ULL << (i & 63));\n    }\n \
    \   void reset(int i) {\n        assert_index(i);\n        a[i >> 6] &= ~(1ULL\
    \ << (i & 63));\n    }\n    void flip(int i) {\n        assert_index(i);\n   \
    \     a[i >> 6] ^= (1ULL << (i & 63));\n    }\n    void set(int i, bool v) { v\
    \ ? set(i) : reset(i); }\n\n    void reset_all() { std::fill(a.begin(), a.end(),\
    \ 0ULL); }\n    void set_all() {\n        std::fill(a.begin(), a.end(), ~0ULL);\n\
    \        trim();\n    }\n    void flip_all() {\n        for (auto &x : a) x =\
    \ ~x;\n        trim();\n    }\n\n    // count (optional but handy)\n    int popcount()\
    \ const {\n        int s = 0;\n        for (ull x : a) s += __builtin_popcountll(x);\n\
    \        return s;\n    }\n    int count() const { return popcount(); }\n\n  \
    \  // ---- bitwise ops ----\n    // ---- any / none ----\n    bool any() const\
    \ {\n        for (ull x : a)\n            if (x) return true;\n        return\
    \ false;\n    }\n    bool none() const { return !any(); }\n\n    // ---- bitwise\
    \ assign ops ----\n    dynamic_bitset &operator^=(const dynamic_bitset &o) {\n\
    \        assert_same_size(o);\n        for (int i = 0; i < m; i++) a[i] ^= o.a[i];\n\
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
    \        }\n        return -1;\n    }\n};\n"
  code: "#pragma once\n\n#include <algorithm>\n#include <cassert>\n#include <initializer_list>\n\
    #include <string>\n#include <vector>\n\nstruct dynamic_bitset {\n    using ull\
    \ = unsigned long long;\n    static constexpr int W = 64;\n\n    int n = 0;  \
    \        // number of bits\n    int m = 0;          // number of 64-bit blocks\n\
    \    std::vector<ull> a; // blocks\n\n    dynamic_bitset() = default;\n    explicit\
    \ dynamic_bitset(int n_, bool init_one = false) { reset_size(n_, init_one); }\n\
    \    explicit dynamic_bitset(const std::string &s) : dynamic_bitset(int(s.size()))\
    \ {\n        const char *p = s.data();\n        for (int blk = 0; blk < m; ++blk)\
    \ {\n            int l = std::max(0, n - ((blk + 1) << 6));\n            int r\
    \ = n - (blk << 6);\n            ull x = 0;\n            for (int i = l; i < r;\
    \ ++i) x = (x << 1) | ull(p[i] == '1');\n            a[blk] = x;\n        }\n\
    \    }\n\n    void reset_size(int n_, bool init_one = false) {\n        n = n_;\n\
    \        m = (n + W - 1) / W;\n        a.assign(m, init_one ? ~0ULL : 0ULL);\n\
    \        trim();\n    }\n\n    int size() const { return n; }\n\n    // ---- low-level\
    \ helpers ----\n    ull last_mask() const {\n        int r = n & (W - 1);\n  \
    \      if (r == 0) return ~0ULL;\n        return (r == 64 ? ~0ULL : ((1ULL <<\
    \ r) - 1ULL));\n    }\n    void trim() {\n        if (m == 0) return;\n      \
    \  a.back() &= last_mask();\n    }\n\n    static inline int ctz64(ull x) { return\
    \ __builtin_ctzll(x); }\n    static inline int clz64(ull x) { return __builtin_clzll(x);\
    \ }\n    static inline int msb_index64(ull x) { return 63 - clz64(x); } // x !=\
    \ 0\n    void assert_index(int i) const { assert(0 <= i && i < n); }\n    void\
    \ assert_same_size(const dynamic_bitset &o) const { assert(n == o.n); }\n\n  \
    \  // ---- basic bit ops ----\n    bool test(int i) const {\n        assert_index(i);\n\
    \        return (a[i >> 6] >> (i & 63)) & 1ULL;\n    }\n    void set(int i) {\n\
    \        assert_index(i);\n        a[i >> 6] |= (1ULL << (i & 63));\n    }\n \
    \   void reset(int i) {\n        assert_index(i);\n        a[i >> 6] &= ~(1ULL\
    \ << (i & 63));\n    }\n    void flip(int i) {\n        assert_index(i);\n   \
    \     a[i >> 6] ^= (1ULL << (i & 63));\n    }\n    void set(int i, bool v) { v\
    \ ? set(i) : reset(i); }\n\n    void reset_all() { std::fill(a.begin(), a.end(),\
    \ 0ULL); }\n    void set_all() {\n        std::fill(a.begin(), a.end(), ~0ULL);\n\
    \        trim();\n    }\n    void flip_all() {\n        for (auto &x : a) x =\
    \ ~x;\n        trim();\n    }\n\n    // count (optional but handy)\n    int popcount()\
    \ const {\n        int s = 0;\n        for (ull x : a) s += __builtin_popcountll(x);\n\
    \        return s;\n    }\n    int count() const { return popcount(); }\n\n  \
    \  // ---- bitwise ops ----\n    // ---- any / none ----\n    bool any() const\
    \ {\n        for (ull x : a)\n            if (x) return true;\n        return\
    \ false;\n    }\n    bool none() const { return !any(); }\n\n    // ---- bitwise\
    \ assign ops ----\n    dynamic_bitset &operator^=(const dynamic_bitset &o) {\n\
    \        assert_same_size(o);\n        for (int i = 0; i < m; i++) a[i] ^= o.a[i];\n\
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
    \        }\n        return -1;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/dynamic_bitset.hpp
  requiredBy: []
  timestamp: '2026-03-02 01:35:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - data_structure/test/dynamic_bitset.yuki3060.test.cpp
  - data_structure/test/dynamic_bitset.yuki2319.test.cpp
  - data_structure/test/dynamic_bitset.yuki1861.test.cpp
  - data_structure/test/dynamic_bitset.yuki1560.test.cpp
  - data_structure/test/dynamic_bitset.yuki1514.test.cpp
  - data_structure/test/dynamic_bitset.yuki3041.test.cpp
  - data_structure/test/dynamic_bitset.yuki2542.test.cpp
  - data_structure/test/dynamic_bitset.yuki1782.test.cpp
  - data_structure/test/dynamic_bitset.yuki1444.test.cpp
documentation_of: data_structure/dynamic_bitset.hpp
layout: document
title: "Dynamic Bitset \uFF08\u52D5\u7684\u30B5\u30A4\u30BA bitset\uFF09"
---

実行時にサイズを決定できる bitset．64 ビット整数のブロック列で表現し，ビット演算・シフト・集合探索を $O(n/64)$ で処理する．`std::bitset` はテンプレート引数でサイズをコンパイル時に固定する必要があるが，`dynamic_bitset` は `int n` を受け取って動的に確保する．

## 使用方法

```cpp
dynamic_bitset bs(n);          // n ビット，全 0 で初期化
dynamic_bitset bs(n, true);    // n ビット，全 1 で初期化
dynamic_bitset bs("1010");     // 文字列から構築（最下位ビット = s[size-1]）
```

### 個別ビット操作

```cpp
bs.test(i);       // i ビット目の値（bool）
bs.set(i);        // i ビット目を 1 に
bs.reset(i);      // i ビット目を 0 に
bs.flip(i);       // i ビット目を反転
bs.set(i, v);     // i ビット目を v に設定
```

### 全体操作

```cpp
bs.set_all();     // 全ビットを 1 に
bs.reset_all();   // 全ビットを 0 に
bs.flip_all();    // 全ビットを反転
```

### ビット演算

```cpp
bs1 &= bs2;  bs1 |= bs2;  bs1 ^= bs2;  // 代入形式
bs1 & bs2;   bs1 | bs2;   bs1 ^ bs2;   // コピー形式（同サイズが必要）
~bs;                                    // 反転
bs <<= k;  bs >>= k;                    // シフト（k ビット左右）
bs << k;   bs >> k;
```

### カウントと判定

```cpp
bs.popcount();  // （= bs.count()）立っているビット数
bs.any();       // 1 ビット以上立っているか
bs.none();      // 全ビットが 0 か
bs.size();      // ビット数 n
```

### 部分ビット列・連結

```cpp
// bs の [l, r) に対応する (r-l) ビットの bitset を返す
dynamic_bitset sub = bs.slice(l, r);

// 複数の bitset を低ビット側から順に連結
dynamic_bitset joined = dynamic_bitset::join(a, b);
dynamic_bitset joined = dynamic_bitset::join({a, b, c});          // 初期化リスト
dynamic_bitset joined = dynamic_bitset::join(vector_of_bitsets);  // vector
```

### 立っているビットの探索

```cpp
bs.first();     // 最小の 1 ビットのインデックス（なければ size()）
bs.next(i);     // i より大きい最小の 1 ビット（なければ size()）
bs.last();      // 最大の 1 ビットのインデックス（なければ -1）
bs.prev(i);     // i より小さい最大の 1 ビット（なければ -1）
```

`first` / `next` を使った列挙例:

```cpp
for (int i = bs.first(); i < bs.size(); i = bs.next(i)) {
    // i は立っているビット
}
```

## 問題例

- [No.1444 !Andd - yukicoder](https://yukicoder.me/problems/no/1444)
- [No.1514 Squared Matching - yukicoder](https://yukicoder.me/problems/no/1514)
- [No.1560 majority x majority - yukicoder](https://yukicoder.me/problems/no/1560)
- [No.1782 ManyCoins - yukicoder](https://yukicoder.me/problems/no/1782)
- [No.1861 Required Number - yukicoder](https://yukicoder.me/problems/no/1861)
- [No.2319 Friends+ - yukicoder](https://yukicoder.me/problems/no/2319)
- [No.2542 Yokan for Two - yukicoder](https://yukicoder.me/problems/no/2542)
- [No.3041 非対称じゃんけん - yukicoder](https://yukicoder.me/problems/no/3041)
- [No.3060 Erase Binary Matrix - yukicoder](https://yukicoder.me/problems/no/3060)
