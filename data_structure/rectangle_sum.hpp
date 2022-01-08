#pragma once
#include "../segmenttree/binary_indexed_tree.hpp"
#include <algorithm>
#include <tuple>
#include <vector>

// CUT begin
// Rectangle Sum: calculate sum of weights inside rectangles
// Sample: https://judge.yosupo.jp/submission/40312 (2e5 points, 2e5 rectangles, 566 ms)
// `add_point(x, y, weight)`: Add point at (x, y)
// `add_query(L, R, D, U)`: Add query rectangle [L, R) x [D, U)
template <typename Int, typename Weight> struct RectangleSum {
    RectangleSum() = default;
    struct Rectangle {
        Int L, R, D, U;
    };
    std::vector<Rectangle> queries;
    std::vector<std::tuple<Int, Int, Weight>> points;

    void add_point(Int x, Int y, Weight weight) noexcept {
        points.push_back({x + 1, y + 1, weight});
    }
    void add_query(Int L, Int R, Int D, Int U) noexcept { queries.push_back({L, R, D, U}); }

    std::vector<Weight> solve() const {
        std::vector<Int> xs, ys;
        for (auto rect : queries) {
            xs.push_back(rect.L);
            xs.push_back(rect.R);
            ys.push_back(rect.D);
            ys.push_back(rect.U);
        }

        std::sort(xs.begin(), xs.end());
        std::sort(ys.begin(), ys.end());
        xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
        ys.erase(std::unique(ys.begin(), ys.end()), ys.end());

        std::vector<std::vector<std::tuple<int, int, Weight>>> ops(ys.size()); // q, x, weight
        for (auto p : points) {
            int i = std::lower_bound(xs.begin(), xs.end(), std::get<0>(p)) - xs.begin();
            int j = std::lower_bound(ys.begin(), ys.end(), std::get<1>(p)) - ys.begin();
            if (j < int(ops.size())) ops[j].push_back({-1, i, std::get<2>(p)});
        }

        for (int q = 0; q < int(queries.size()); q++) {
            int il = std::lower_bound(xs.begin(), xs.end(), queries[q].L) - xs.begin();
            int ir = std::lower_bound(xs.begin(), xs.end(), queries[q].R) - xs.begin();
            int jd = std::lower_bound(ys.begin(), ys.end(), queries[q].D) - ys.begin();
            int ju = std::lower_bound(ys.begin(), ys.end(), queries[q].U) - ys.begin();
            ops[jd].push_back({q, il, 1});
            ops[jd].push_back({q, ir, -1});
            ops[ju].push_back({q, il, -1});
            ops[ju].push_back({q, ir, 1});
        }

        std::vector<Weight> ret(queries.size());
        BIT<Weight> bit(xs.size());
        for (auto &&op : ops) {
            for (auto p : op) {
                const auto q = std::get<0>(p), x = std::get<1>(p);
                const auto w = std::get<2>(p);
                if (q == -1) {
                    bit.add(x, w);
                } else {
                    ret[q] += bit.sum(x + 1) * w;
                }
            }
        }
        return ret;
    }
};
