#pragma once
#include <algorithm>
#include <limits>
#include <vector>

// CUT begin
// StarrySkyTree: segment tree for Range Minimum Query & Range Add Query
// Complexity: $O(N)$ (construction), $O(\log N)$ (add / get / prod)
// - RangeAddRangeMin(std::vector<Tp> data_init) : Initialize array x by data_init.
// - add(int begin, int end, Tp vadd) : Update x[i] <- x[i] + vadd for all begin <= i < end.
// - get(int pos) : Get x[pos].
// - prod(int begin, int end) : Get min(x[begin], ..., x[end - 1]).
template <typename Tp, Tp defaultT = std::numeric_limits<Tp>::max() / 2> struct RangeAddRangeMin {
    int N, head;
    std::vector<Tp> range_min, range_add;
    static inline Tp f(Tp x, Tp y) noexcept { return std::min(x, y); }

    inline void _merge(int pos) {
        range_min[pos] = f(range_min[pos * 2] + range_add[pos * 2], range_min[pos * 2 + 1] + range_add[pos * 2 + 1]);
    }
    void initialize(const std::vector<Tp> &data_init) {
        N = data_init.size(), head = 1;
        while (head < N) head <<= 1;
        range_min.assign(head * 2, defaultT);
        range_add.assign(head * 2, 0);
        std::copy(data_init.begin(), data_init.end(), range_min.begin() + head);
        for (int pos = head; --pos;) _merge(pos);
    }
    RangeAddRangeMin() = default;
    RangeAddRangeMin(const std::vector<Tp> &data_init) { initialize(data_init); }
    void _add(int begin, int end, int pos, int l, int r, Tp vadd) noexcept {
        if (r <= begin or end <= l) return;
        if (begin <= l and r <= end) {
            range_add[pos] += vadd;
            return;
        }
        _add(begin, end, pos * 2, l, (l + r) / 2, vadd);
        _add(begin, end, pos * 2 + 1, (l + r) / 2, r, vadd);
        _merge(pos);
    }
    // Add `vadd` to (x_begin, ..., x_{end - 1})
    void add(int begin, int end, Tp vadd) noexcept { return _add(begin, end, 1, 0, head, vadd); }
    Tp _get(int begin, int end, int pos, int l, int r) const noexcept {
        if (r <= begin or end <= l) return defaultT;
        if (begin <= l and r <= end) return range_min[pos] + range_add[pos];
        return f(_get(begin, end, pos * 2, l, (l + r) / 2), _get(begin, end, pos * 2 + 1, (l + r) / 2, r)) + range_add[pos];
    }
    // Return f(x_begin, ..., x_{end - 1})
    Tp get(int pos) const noexcept { return prod(pos, pos + 1); }
    Tp prod(int begin, int end) const noexcept { return _get(begin, end, 1, 0, head); }
};
