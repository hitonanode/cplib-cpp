#pragma once
#include <cassert>
#include <functional>
#include <vector>

// finding minimum element for each row of N*M matrix
// Constraints: the solution is monotonically non-decreasing
// Complexity: O(NM logM)
// Reference:
// https://topcoder-g-hatena-ne-jp.jag-icpc.org/spaghetti_source/20120923/1348327542.html
// Verify: https://mofecoder.com/contests/monoxercon_202508/tasks/monoxercon_202508_k
template <class T>
std::vector<std::pair<int, T>>
MonotoneMinima(int N, int M, const std::function<T(int i, int j)> &weight) {
    std::vector<std::pair<int, T>> minima(N);

    auto rec = [&](auto &&self, int il, int ir, int jl, int jr) -> void {
        if (il >= ir or jl >= jr) return;
        const int im = (il + ir) / 2;
        T w = weight(im, jl);
        int j_argmin = jl;
        for (int j = jl + 1; j < jr; ++j) {
            if (T wt = weight(im, j); wt < w) w = wt, j_argmin = j;
        }
        minima[im] = {j_argmin, w};
        self(self, il, im, jl, j_argmin + 1);
        self(self, im + 1, ir, j_argmin, jr);
    };
    rec(rec, 0, N, 0, M);

    return minima;
}
