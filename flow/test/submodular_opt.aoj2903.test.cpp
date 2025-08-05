#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2903"
// Bipartite graph, flipping is important
#include "../submodular_optimization_via_graph_cut.hpp"

#include <iostream>
#include <string>
#include <utility>
using namespace std;

int main() {
    int R, C;
    cin >> R >> C;
    vector<string> grid(R);
    for (auto &row : grid) cin >> row;

    auto isin = [&](int i, int j) {
        return 0 <= i and i < R and 0 <= j and j < C and grid.at(i).at(j) == '#';
    };
    const vector<pair<int, int>> dxdys{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    using Point = pair<int, int>;
    using Edge = pair<Point, Point>;
    SubmodularOptimizationViaGraphCut<Edge> so;

    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            if (!isin(i, j)) continue;

            so.Impose(1);

            vector<vector<Edge>> edges(2);
            for (auto [dx, dy] : dxdys) {
                const int ni = i + dx, nj = j + dy;
                if (!isin(ni, nj)) continue;

                Edge e{{i, j}, {ni, nj}};
                if (e.first < e.second) {
                    so.Impose(e, true, -1);
                } else {
                    swap(e.first, e.second);
                }
                edges[dx != 0].push_back(e);
            }

            for (auto e1 : edges.at(0)) {
                for (auto e2 : edges.at(1)) { so.Impose(e1, true, e2, true, 1 << 20); }
            }
        }
    }

    const auto res = so.Solve();
    cout << res.total_cost << '\n';
}
