#pragma once
#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

// Hilbert order of given 2D point (x, y)
// constraints: 0 <= x, y < 2^32
// Reference: https://take44444.github.io/Algorithm-Book/range/mo/main.html#mos-algorithm
unsigned long long hilbert_order(unsigned x, unsigned y) {
    unsigned long long ret = 0;
    for (unsigned s = 1U << 31; s; s >>= 1) {
        unsigned rx = (x & s) > 0, ry = (y & s) > 0;
        ret += (unsigned long long)s * s * ((3 * rx) ^ ry);

        if (ry == 0) {
            if (rx == 1) {
                x = -x - 1;
                y = -y - 1;
            }
            std::swap(x, y);
        }
    }

    return ret;
}

// Given queries of 2D points, return the indices sorted by Hilbert order
// Can be used for Mo's algorithm
template <class Int>
std::vector<int> sort_by_hilbert_order(const std::vector<std::pair<Int, Int>> &points) {
    static_assert(std::is_integral<Int>::value, "Int must be integral");
    static_assert(sizeof(Int) <= 4, "Int must be 32-bit integer");

    if (points.empty()) return {};

    // Int min_x = points[0].first, min_y = points[0].second;
    Int min_x = Int(), min_y = Int();
    for (auto [x, y] : points) {
        if (x < min_x) min_x = x;
        if (y < min_y) min_y = y;
    }

    std::vector<unsigned long long> hilbert_values(points.size());
    for (int i = 0; i < (int)points.size(); ++i) {
        hilbert_values[i] = hilbert_order(points[i].first - min_x, points[i].second - min_y);
    }

    std::vector<int> indices(points.size());
    std::iota(indices.begin(), indices.end(), 0);
    std::sort(indices.begin(), indices.end(),
              [&](int i, int j) { return hilbert_values[i] < hilbert_values[j]; });

    return indices;
}

// Mo's algorithm with Hilbert order
// - add(x, y) : Add (x, y) as query.
// - run(IncX, DecX, IncY, DecY, Query) : run Mo's algorithm.
// - run(Add, Remove, Query) : run Mo's algorithm with Add, Remove, and Query functions. add(x, y) means [x, y).
struct MosAlgorithmHilbertOrder {
    int cx, cy;
    std::vector<std::pair<int, int>> queries;

    MosAlgorithmHilbertOrder(int x_init, int y_init) : cx(x_init), cy(y_init) {}

    void add(int x, int y) { queries.emplace_back(x, y); }

    template <class IncX, class DecX, class IncY, class DecY, class Query>
    void run(IncX inc_x, DecX dec_x, IncY inc_y, DecY dec_y, Query query) {

        std::vector<int> indices = sort_by_hilbert_order(queries);
        int x = cx, y = cy;

        for (int q : indices) {
            while (y < queries[q].second) inc_y(y, y + 1), ++y;
            while (x > queries[q].first) dec_x(x, x - 1), --x;
            while (y > queries[q].second) dec_y(y, y - 1), --y;
            while (x < queries[q].first) inc_x(x, x + 1), ++x;
            query(q);
        }
    }

    template <typename F1, typename F3, typename F5> void run(F1 Add, F3 Remove, F5 Query) {
        run([&](int x, int) { Remove(x); }, [&](int, int x) { Add(x); },
            [&](int y, int) { Add(y); }, [&](int, int y) { Remove(y); }, Query);
    }
};
