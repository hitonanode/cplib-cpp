#pragma once
#include <algorithm>
#include <bit>
#include <cassert>
#include <cstdint>
#include <optional>
#include <vector>

template <class Int> class wavelet_matrix {

    class bit_vector {
        static constexpr int WSIZE = 64;
        int n = 0;
        int cnt0 = 0;
        std::vector<uint64_t> bits;
        std::vector<int> count_cumsum; // need build()

    public:
        bit_vector(int n_) : n(n_), cnt0(n_) {
            assert(n >= 0);
            bits.assign((n + WSIZE - 1) / WSIZE, 0);
        }

        int size() const { return n; }

        void set(int i) {
            assert(0 <= i and i < n);
            bits[i / WSIZE] |= (1ULL << (i % WSIZE));
        }

        void reset(int i) {
            assert(0 <= i and i < n);
            bits[i / WSIZE] &= ~(1ULL << (i % WSIZE));
        }

        void build() {
            cnt0 = n;
            for (int i = 0; i < (int)bits.size(); ++i) cnt0 -= std::popcount(bits[i]);
            count_cumsum.assign(bits.size(), 0);
            for (int i = 1; i < (int)bits.size(); ++i) {
                count_cumsum[i] = count_cumsum[i - 1] + std::popcount(bits[i - 1]);
            }
        }

        int count0() const { return cnt0; }

        int count1() const { return n - cnt0; }

        // get i-th bit
        bool access(int i) const {
            assert(0 <= i and i < n);
            return bits[i / WSIZE] & (1ULL << (i % WSIZE));
        }

        // count of 0s in [0, i)
        int rank0(int i) const {
            assert(0 <= i and i <= n);
            return i - rank1(i);
        }

        // count of 1s in [0, i)
        int rank1(int i) const {
            assert(0 <= i and i <= n);
            if (i == n) return count1();
            return count_cumsum[i / WSIZE] +
                   std::popcount(bits[i / WSIZE] & ((1ULL << (i % WSIZE)) - 1));
        }

        // get the position of i-th element after stable sort
        int sorted_pos(int i) const { return access(i) ? (rank1(i) + count0()) : rank0(i); }

        template <class OStream> friend OStream &operator<<(OStream &os, const bit_vector &bv) {
            os << "bit_vector[" << bv.n << "]: ";
            for (int i = 0; i < bv.n; ++i) {
                os << (bv.bits[i / WSIZE] & (1ULL << (i % WSIZE)) ? '1' : '0');
            }
            os << " (cnt0: " << bv.cnt0 << ")";
            return os;
        }
    };

    std::vector<bit_vector> bits;

    std::vector<std::pair<Int, Int>> points;
    std::vector<Int> distinct_ys;

    int to_index_x(Int x) const {
        return std::lower_bound(points.cbegin(), points.cend(), std::make_pair(x, Int{}),
                                [](const auto &l, const auto &r) { return l.first < r.first; }) -
               points.cbegin();
    }

    int to_index_y(Int y) const {
        return std::lower_bound(distinct_ys.cbegin(), distinct_ys.cend(), y) - distinct_ys.cbegin();
    }

    bool is_built() const { return !bits.empty(); }

public:
    wavelet_matrix() = default;

    wavelet_matrix(const std::vector<Int> &ys) {
        for (int x = 0; x < (int)ys.size(); ++x) {
            assert(ys[x] >= 0);
            add_point(x, ys[x]);
        }
        build();
    }

    void add_point(Int x, Int y) {
        assert(bits.empty()); // confirm that build() is not called yet
        points.emplace_back(x, y);
        distinct_ys.emplace_back(y);
    }

    void build() {
        std::sort(points.begin(), points.end());
        points.erase(std::unique(points.begin(), points.end()), points.end());

        std::sort(distinct_ys.begin(), distinct_ys.end());
        distinct_ys.erase(std::unique(distinct_ys.begin(), distinct_ys.end()), distinct_ys.end());

        int d = 1;
        while ((1 << d) < (int)distinct_ys.size()) ++d;
        bits.assign(d, bit_vector(N()));

        std::vector<int> a;
        for (auto p : points) a.push_back(to_index_y(p.second));
        auto nxt = a;

        for (int d = D() - 1; d >= 0; --d) {
            for (int i = 0; i < N(); ++i) {
                if ((a[i] >> d) & 1) bits[d].set(i);
            }
            bits[d].build();

            for (int i = 0; i < N(); ++i) nxt[bits[d].sorted_pos(i)] = a[i];

            std::swap(a, nxt);
        }
    }

    int N() const { return points.size(); }

    int D() const { return bits.size(); }

    // get v_i
    int index_access(int i) const {
        assert(0 <= i and i < N());
        assert(is_built());

        int ret = 0;
        for (int d = D() - 1; d >= 0; --d) {
            ret |= (int)bits[d].access(i) << d;
            i = bits[d].sorted_pos(i);
        }
        return ret;
    }

    Int access(int i) const {
        assert(0 <= i and i < N());
        assert(is_built());
        return distinct_ys.at(index_access(i));
    }

    // callback(d, i) means "update d-th segment's i-th element"
    void index_apply(int i, auto callback) const {
        assert(0 <= i and i < N());
        assert(is_built());

        for (int d = D() - 1; d >= 0; --d) {
            i = bits[d].sorted_pos(i);
            callback(d, i);
        }
    }

    // Update weight associated to point (x, y)
    // callback(d, i) means "update d-th segment's i-th element"
    void apply(Int x, Int y, auto callback) const {
        const int i = std::lower_bound(points.cbegin(), points.cend(), std::make_pair(x, y)) -
                      points.cbegin();
        assert(i < N() and points[i] == std::make_pair(x, y));
        index_apply(i, callback);
    }

    void index_prod(int l, int r, int yr, auto callback) const {
        assert(0 <= l and l <= r and r <= N());
        assert(0 <= yr and yr <= (int)distinct_ys.size());
        assert(is_built());

        if (yr & (1 << D())) {
            const int d = D() - 1;
            const int l0 = bits[d].rank0(l), r0 = bits[d].rank0(r);
            callback(d, l0, r0);
            const int l1 = bits[d].rank1(l) + bits[d].count0();
            const int r1 = bits[d].rank1(r) + bits[d].count0();
            callback(d, l1, r1);
            return;
        }

        for (int d = D() - 1; d >= 0; --d) {
            if (l == r) break;
            const int l0 = bits[d].rank0(l), r0 = bits[d].rank0(r);
            if ((yr >> d) & 1) {
                callback(d, l0, r0);
                // l = bits[d].rank1(l) + bits[d].count0();
                l += bits[d].count0() - l0;
                // r = bits[d].rank1(r) + bits[d].count0();
                r += bits[d].count0() - r0;
            } else {
                l = l0, r = r0;
            }
        }
    }

    // Get product of weights associated to elements in [xl, xr) * [-inf, yr)
    // callback(d, l, r) means "use d-th segment's [l, r) elements"
    void prod(Int xl, Int xr, Int yr, auto callback) const {
        index_prod(to_index_x(xl), to_index_x(xr), to_index_y(yr), callback);
    }

    // Get k-th smallest v_i, i in [l, r) (0-indexed, duplicates are counted)]
    int index_kth_smallest(int l, int r, int k) const {
        assert(0 <= l and l <= r and r <= N());
        assert(0 <= k and k < r - l);
        assert(is_built());

        int ret = 0;
        for (int d = D() - 1; d >= 0; --d) {
            const int l0 = bits[d].rank0(l), r0 = bits[d].rank0(r);
            if (k < r0 - l0) {
                l = l0, r = r0;
            } else {
                k -= r0 - l0;
                ret |= 1 << d;
                l = bits[d].rank1(l) + bits[d].count0();
                r = bits[d].rank1(r) + bits[d].count0();
            }
        }

        return ret;
    }

    // Get k-th largest v_i, i in [l, r) (0-indexed, duplicates are counted)
    int index_kth_largest(int l, int r, int k) const {
        assert(0 <= l and l <= r and r <= N());
        assert(0 <= k and k < r - l);
        return index_kth_smallest(l, r, (r - l - 1) - k);
    }

    // count i s.t. i in [l, r) and v_i < upper_bound
    int index_range_freq(int l, int r, int upper_bound) const {
        assert(0 <= l and l <= r and r <= N());
        assert(is_built());
        if (upper_bound <= 0) return 0;
        if (upper_bound >= (int)distinct_ys.size()) return r - l;

        int ret = 0;
        for (int d = D() - 1; d >= 0; --d) {
            const int l0 = bits[d].rank0(l), r0 = bits[d].rank0(r);
            if ((upper_bound >> d) & 1) {
                ret += r0 - l0;
                l = bits[d].rank1(l) + bits[d].count0();
                r = bits[d].rank1(r) + bits[d].count0();
            } else {
                l = l0, r = r0;
            }
        }

        return ret;
    }

    // Get k-th smallest y in [xl, xr) (0-indexed, duplicates are counted)
    std::optional<Int> kth_smallest(Int xl, Int xr, int k) const {
        const int l = to_index_x(xl), r = to_index_x(xr);
        if (k < 0 or k >= r - l) return std::nullopt;
        return distinct_ys.at(index_kth_smallest(l, r, k));
    }

    // Get k-th largest y in [xl, xr) (0-indexed, duplicates are counted)
    std::optional<Int> kth_largest(Int xl, Int xr, int k) const {
        const int l = to_index_x(xl), r = to_index_x(xr);
        if (k < 0 or k >= r - l) return std::nullopt;
        return distinct_ys.at(index_kth_largest(l, r, k));
    }

    // count points in [xl, xr) * [-inf, yr)
    int range_freq(Int xl, Int xr, Int yr) const {
        return index_range_freq(to_index_x(xl), to_index_x(xr), to_index_y(yr));
    }

    // max v_i s.t. i in [l, r), v_i < upper_bound
    std::optional<int> index_prev_value(int l, int r, int upper_bound) const {
        assert(0 <= l and l <= r and r <= N());
        assert(is_built());
        if (upper_bound <= 0) return std::nullopt;

        const int n = index_range_freq(l, r, upper_bound);
        return n == 0 ? std::nullopt : index_kth_smallest(l, r, n - 1);
    }

    // max y s.t. x in [xl, xr), y < yr
    std::optional<Int> prev_value(Int xl, Int xr, Int yr) const {
        const int l = to_index_x(xl), r = to_index_x(xr), ub = to_index_y(yr);
        const auto idx = index_prev_value(l, r, ub);
        return idx ? distinct_ys.at(*idx) : std::nullopt;
    }

    // min v_i s.t. i in [l, r), v_i >= lower_bound
    std::optional<int> index_next_value(int l, int r, int lower_bound) const {
        assert(0 <= l and l <= r and r <= N());
        assert(is_built());
        if (lower_bound >= (int)distinct_ys.size()) return std::nullopt;
        const int n = index_range_freq(l, r, lower_bound);
        return n >= (r - l) ? std::nullopt : index_kth_smallest(l, r, n);
    }

    // min y s.t. x in [xl, xr), y >= yl
    std::optional<Int> next_value(Int l, Int r, Int yl) const {
        const int xl = to_index_x(l), xr = to_index_x(r), yl_idx = to_index_y(yl);
        const auto idx = index_next_value(xl, xr, yl_idx);
        return idx ? distinct_ys.at(*idx) : std::nullopt;
    }
};
/* Sample usage:
wavelet_matrix<int> wm;

wm.build();
vector tmp(wm.D(), vector<BIT<T>>(wm.N()));
wm.apply(i, j, [&](int d, int idx) { tmp[d].add(idx, wx); });  // point add
T ret{};
wm.prod(l, r, u, [&](int d, int l0, int r0) { ret += tmp[d].sum(l0, r0); }); // range sum
*/
