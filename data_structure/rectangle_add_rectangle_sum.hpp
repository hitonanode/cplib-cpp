#pragma once
#include "../segmenttree/binary_indexed_tree.hpp"
#include <algorithm>
#include <tuple>
#include <vector>

// Static rectangle add rectangle sum
// Calculate sums of rectangular weights inside the given rectangles
// Complexity: O(q log q), q = # of rectangles / queries
template <class Int, class T> class RectangleAddRectangleSum {
    struct AddQuery {
        Int xl, xr, yl, yr;
        T val;
    };
    struct SumQuery {
        Int xl, xr, yl, yr;
    };
    std::vector<AddQuery> add_queries;
    std::vector<SumQuery> sum_queries;

public:
    RectangleAddRectangleSum() = default;

    // A[x][y] += val for (x, y) in [xl, xr) * [yl, yr)
    void add_rectangle(Int xl, Int xr, Int yl, Int yr, T val) {
        add_queries.push_back(AddQuery{xl, xr, yl, yr, val});
    }

    // Get sum of A[x][y] for (x, y) in [xl, xr) * [yl, yr)
    void add_query(Int xl, Int xr, Int yl, Int yr) {
        sum_queries.push_back(SumQuery{xl, xr, yl, yr});
    }

    std::vector<T> solve() const {
        std::vector<Int> ys;
        for (const auto &a : add_queries) {
            ys.push_back(a.yl);
            ys.push_back(a.yr);
        }
        std::sort(ys.begin(), ys.end());
        ys.erase(std::unique(ys.begin(), ys.end()), ys.end());

        const int Y = ys.size();

        std::vector<std::tuple<Int, int, int>> ops;
        for (int q = 0; q < int(sum_queries.size()); ++q) {
            ops.emplace_back(sum_queries[q].xl, 0, q);
            ops.emplace_back(sum_queries[q].xr, 1, q);
        }
        for (int q = 0; q < int(add_queries.size()); ++q) {
            ops.emplace_back(add_queries[q].xl, 2, q);
            ops.emplace_back(add_queries[q].xr, 3, q);
        }
        std::sort(ops.begin(), ops.end());

        BIT<T> b00(Y), b01(Y), b10(Y), b11(Y);
        std::vector<T> ret(sum_queries.size());
        for (auto o : ops) {
            int qtype = std::get<1>(o), q = std::get<2>(o);
            if (qtype >= 2) {
                const AddQuery &query = add_queries.at(q);
                int i = std::lower_bound(ys.begin(), ys.end(), query.yl) - ys.begin();
                int j = std::lower_bound(ys.begin(), ys.end(), query.yr) - ys.begin();
                T x = std::get<0>(o);
                T yi = query.yl, yj = query.yr;
                if (qtype & 1) std::swap(i, j), std::swap(yi, yj);

                b00.add(i, x * yi * query.val);
                b01.add(i, -x * query.val);
                b10.add(i, -yi * query.val);
                b11.add(i, query.val);
                b00.add(j, -x * yj * query.val);
                b01.add(j, x * query.val);
                b10.add(j, yj * query.val);
                b11.add(j, -query.val);
            } else {
                const SumQuery &query = sum_queries.at(q);
                int i = std::lower_bound(ys.begin(), ys.end(), query.yl) - ys.begin();
                int j = std::lower_bound(ys.begin(), ys.end(), query.yr) - ys.begin();
                T x = std::get<0>(o);
                T yi = query.yl, yj = query.yr;
                if (qtype & 1) std::swap(i, j), std::swap(yi, yj);

                ret[q] += b00.sum(i) + b01.sum(i) * yi + b10.sum(i) * x + b11.sum(i) * x * yi;
                ret[q] -= b00.sum(j) + b01.sum(j) * yj + b10.sum(j) * x + b11.sum(j) * x * yj;
            }
        }
        return ret;
    }
};
