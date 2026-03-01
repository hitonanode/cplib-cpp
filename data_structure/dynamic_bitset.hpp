#pragma once

#include <algorithm>
#include <cassert>
#include <initializer_list>
#include <string>
#include <vector>

struct dynamic_bitset {
    using ull = unsigned long long;
    static constexpr int W = 64;

    int n = 0;          // number of bits
    int m = 0;          // number of 64-bit blocks
    std::vector<ull> a; // blocks

    dynamic_bitset() = default;
    explicit dynamic_bitset(int n_, bool init_one = false) { reset_size(n_, init_one); }
    explicit dynamic_bitset(const std::string &s) : dynamic_bitset(int(s.size())) {
        const char *p = s.data();
        for (int blk = 0; blk < m; ++blk) {
            int l = std::max(0, n - ((blk + 1) << 6));
            int r = n - (blk << 6);
            ull x = 0;
            for (int i = l; i < r; ++i) x = (x << 1) | ull(p[i] == '1');
            a[blk] = x;
        }
    }

    void reset_size(int n_, bool init_one = false) {
        n = n_;
        m = (n + W - 1) / W;
        a.assign(m, init_one ? ~0ULL : 0ULL);
        trim();
    }

    int size() const { return n; }

    // ---- low-level helpers ----
    ull last_mask() const {
        int r = n & (W - 1);
        if (r == 0) return ~0ULL;
        return (r == 64 ? ~0ULL : ((1ULL << r) - 1ULL));
    }
    void trim() {
        if (m == 0) return;
        a.back() &= last_mask();
    }

    static inline int ctz64(ull x) { return __builtin_ctzll(x); }
    static inline int clz64(ull x) { return __builtin_clzll(x); }
    static inline int msb_index64(ull x) { return 63 - clz64(x); } // x != 0
    void assert_index(int i) const { assert(0 <= i && i < n); }
    void assert_same_size(const dynamic_bitset &o) const { assert(n == o.n); }

    // ---- basic bit ops ----
    bool test(int i) const {
        assert_index(i);
        return (a[i >> 6] >> (i & 63)) & 1ULL;
    }
    void set(int i) {
        assert_index(i);
        a[i >> 6] |= (1ULL << (i & 63));
    }
    void reset(int i) {
        assert_index(i);
        a[i >> 6] &= ~(1ULL << (i & 63));
    }
    void flip(int i) {
        assert_index(i);
        a[i >> 6] ^= (1ULL << (i & 63));
    }
    void set(int i, bool v) { v ? set(i) : reset(i); }

    void reset_all() { std::fill(a.begin(), a.end(), 0ULL); }
    void set_all() {
        std::fill(a.begin(), a.end(), ~0ULL);
        trim();
    }
    void flip_all() {
        for (auto &x : a) x = ~x;
        trim();
    }

    // count (optional but handy)
    int popcount() const {
        int s = 0;
        for (ull x : a) s += __builtin_popcountll(x);
        return s;
    }
    int count() const { return popcount(); }

    // ---- bitwise ops ----
    // ---- any / none ----
    bool any() const {
        for (ull x : a)
            if (x) return true;
        return false;
    }
    bool none() const { return !any(); }

    // ---- bitwise assign ops ----
    dynamic_bitset &operator^=(const dynamic_bitset &o) {
        assert_same_size(o);
        for (int i = 0; i < m; i++) a[i] ^= o.a[i];
        trim();
        return *this;
    }
    dynamic_bitset &operator|=(const dynamic_bitset &o) {
        assert_same_size(o);
        for (int i = 0; i < m; i++) a[i] |= o.a[i];
        trim();
        return *this;
    }
    dynamic_bitset &operator&=(const dynamic_bitset &o) {
        assert_same_size(o);
        for (int i = 0; i < m; i++) a[i] &= o.a[i];
        trim();
        return *this;
    }

    friend dynamic_bitset operator^(dynamic_bitset l, const dynamic_bitset &r) {
        l ^= r;
        return l;
    }
    friend dynamic_bitset operator|(dynamic_bitset l, const dynamic_bitset &r) {
        l |= r;
        return l;
    }
    friend dynamic_bitset operator&(dynamic_bitset l, const dynamic_bitset &r) {
        l &= r;
        return l;
    }

    bool operator==(const dynamic_bitset &o) const { return n == o.n && a == o.a; }
    bool operator!=(const dynamic_bitset &o) const { return !(*this == o); }
    int compare(const dynamic_bitset &o) const {
        if (n != o.n) return n < o.n ? -1 : 1;
        for (int i = m - 1; i >= 0; --i) {
            if (a[i] != o.a[i]) return a[i] < o.a[i] ? -1 : 1;
        }
        return 0;
    }
    bool operator<(const dynamic_bitset &o) const { return compare(o) < 0; }
    bool operator<=(const dynamic_bitset &o) const { return compare(o) <= 0; }
    bool operator>(const dynamic_bitset &o) const { return compare(o) > 0; }
    bool operator>=(const dynamic_bitset &o) const { return compare(o) >= 0; }

    // returns bitset b with b.test(i) == test(l + i) for 0 <= i < r - l
    dynamic_bitset slice(int l, int r) const {
        l = std::clamp(l, 0, n);
        r = std::clamp(r, 0, n);
        if (l >= r) return dynamic_bitset();

        dynamic_bitset res(r - l);
        int ws = l >> 6;
        int bs = l & 63;
        for (int i = 0; i < res.m; ++i) {
            ull lo = (ws + i < m ? (a[ws + i] >> bs) : 0ULL);
            ull hi = (bs && ws + i + 1 < m ? (a[ws + i + 1] << (W - bs)) : 0ULL);
            res.a[i] = lo | hi;
        }
        res.trim();
        return res;
    }

private:
    template <class Range> static dynamic_bitset join_range(const Range &xs) {
        int total = 0;
        for (const auto &x : xs) total += x.n;

        dynamic_bitset res(total);
        int cur = 0;
        for (const auto &x : xs) {
            int ws = cur >> 6;
            int bs = cur & 63;
            for (int i = 0; i < x.m; ++i) {
                ull v = x.a[i];
                if (!v) continue;
                res.a[ws + i] |= v << bs;
                if (bs && ws + i + 1 < res.m) res.a[ws + i + 1] |= v >> (W - bs);
            }
            cur += x.n;
        }
        res.trim();
        return res;
    }

public:
    static dynamic_bitset join(const std::vector<dynamic_bitset> &xs) { return join_range(xs); }
    static dynamic_bitset join(std::initializer_list<dynamic_bitset> xs) { return join_range(xs); }
    static dynamic_bitset join(const dynamic_bitset &a, const dynamic_bitset &b) {
        return join({a, b});
    }

    dynamic_bitset operator~() const {
        dynamic_bitset r = *this;
        for (auto &x : r.a) x = ~x;
        r.trim();
        return r;
    }

    // ---- shifts ----
    dynamic_bitset &operator<<=(int k) {
        if (k <= 0 || n == 0) return *this;
        if (k >= n) {
            reset_all();
            return *this;
        }
        int ws = k >> 6;
        int bs = k & 63;

        if (ws) {
            for (int i = m - 1; i >= 0; --i) {
                ull v = (i - ws >= 0) ? a[i - ws] : 0ULL;
                a[i] = v;
            }
        }
        if (bs) {
            for (int i = m - 1; i >= 0; --i) {
                ull hi = a[i] << bs;
                ull lo = (i ? (a[i - 1] >> (64 - bs)) : 0ULL);
                a[i] = hi | lo;
            }
        }
        // zero-fill lower words introduced by ws shift
        if (ws) {
            for (int i = 0; i < ws && i < m; ++i) a[i] = 0ULL;
        }
        trim();
        return *this;
    }

    dynamic_bitset &operator>>=(int k) {
        if (k <= 0 || n == 0) return *this;
        if (k >= n) {
            reset_all();
            return *this;
        }
        int ws = k >> 6;
        int bs = k & 63;

        if (ws) {
            for (int i = 0; i < m; ++i) {
                ull v = (i + ws < m) ? a[i + ws] : 0ULL;
                a[i] = v;
            }
        }
        if (bs) {
            for (int i = 0; i < m; ++i) {
                ull lo = a[i] >> bs;
                ull hi = (i + 1 < m ? (a[i + 1] << (64 - bs)) : 0ULL);
                a[i] = lo | hi;
            }
        }
        // zero-fill upper words introduced by ws shift
        if (ws) {
            for (int i = m - ws; i < m; ++i)
                if (0 <= i && i < m) a[i] = 0ULL;
        }
        trim();
        return *this;
    }

    friend dynamic_bitset operator<<(dynamic_bitset b, int k) {
        b <<= k;
        return b;
    }
    friend dynamic_bitset operator>>(dynamic_bitset b, int k) {
        b >>= k;
        return b;
    }

    // ---- find set bits ----
    // returns smallest i with bit=1, or size()
    int first() const {
        for (int i = 0; i < m; ++i) {
            ull x = a[i];
            if (x) return (i << 6) + ctz64(x);
        }
        return size();
    }

    // returns smallest j > i with bit=1, or size()
    int next(int i) const {
        if (n == 0) return size();
        int j = i + 1;
        if (j <= 0) return first();
        if (j >= n) return size();

        int b = j >> 6;
        int off = j & 63;

        // mask out bits < off
        ull x = a[b] & (~0ULL << off);
        if (x) return (b << 6) + ctz64(x);

        for (int bb = b + 1; bb < m; ++bb) {
            ull y = a[bb];
            if (y) return (bb << 6) + ctz64(y);
        }
        return size();
    }

    // returns largest i with bit=1, or -1
    int last() const {
        for (int i = m - 1; i >= 0; --i) {
            ull x = a[i];
            if (i == m - 1) x &= last_mask();
            if (x) return (i << 6) + msb_index64(x);
        }
        return -1;
    }

    // returns largest j < i with bit=1, or -1
    int prev(int i) const {
        if (n == 0) return -1;
        int j = i - 1;
        if (j < 0) return -1;
        if (j >= n) return last();

        int b = j >> 6;
        int off = j & 63;

        ull mask = (off == 63) ? ~0ULL : ((1ULL << (off + 1)) - 1ULL);
        ull x = a[b] & mask;
        if (x) return (b << 6) + msb_index64(x);

        for (int bb = b - 1; bb >= 0; --bb) {
            ull y = a[bb];
            if (y) return (bb << 6) + msb_index64(y);
        }
        return -1;
    }
};
