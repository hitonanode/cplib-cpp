#pragma once
#include <algorithm>
#include <map>
#include <numeric>
#include <tuple>
#include <vector>

// Manhattan MST: 二次元平面上の頂点たちのマンハッタン距離による minimum spanning tree の O(N) 本の候補辺を列挙
// Complexity: O(N log N)
// output: [(weight_uv, u, v), ...]
// Verified: https://judge.yosupo.jp/problem/manhattanmst, https://www.codechef.com/problems/HKRMAN
// Reference:
// [1] H. Zhou, N. Shenoy, W. Nicholls,
//     "Efficient minimum spanning tree construction without Delaunay triangulation,"
//     Information Processing Letters, 81(5), 271-276, 2002.
template <typename T> std::vector<std::tuple<T, int, int>> manhattan_mst(std::vector<T> xs, std::vector<T> ys) {
    const int n = xs.size();
    std::vector<int> idx(n);
    std::iota(idx.begin(), idx.end(), 0);
    std::vector<std::tuple<T, int, int>> ret;
    for (int s = 0; s < 2; s++) {
        for (int t = 0; t < 2; t++) {
            auto cmp = [&](int i, int j) { return xs[i] + ys[i] < xs[j] + ys[j]; };
            std::sort(idx.begin(), idx.end(), cmp);
            std::map<T, int> sweep;
            for (int i : idx) {
                for (auto it = sweep.lower_bound(-ys[i]); it != sweep.end(); it = sweep.erase(it)) {
                    int j = it->second;
                    if (xs[i] - xs[j] < ys[i] - ys[j]) break;
                    ret.emplace_back(std::abs(xs[i] - xs[j]) + std::abs(ys[i] - ys[j]), i, j);
                }
                sweep[-ys[i]] = i;
            }
            std::swap(xs, ys);
        }
        for (auto &x : xs) x = -x;
    }
    std::sort(ret.begin(), ret.end());
    return ret;
}
