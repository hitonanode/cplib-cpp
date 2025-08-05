#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2943"
// Bipartite graph, flipping is important
#include "../submodular_optimization_via_graph_cut.hpp"

#include <iostream>
#include <string>
#include <utility>
using namespace std;

int main() {
    int h, w, W;
    cin >> h >> w >> W;
    vector B(h, vector<int>(w));
    for (auto &row : B) {
        for (auto &b : row) cin >> b;
    }

    auto isin = [&](int i, int j) { return 0 <= i and i < h and 0 <= j and j < w; };

    SubmodularOptimizationViaGraphCut<pair<int, int>> so;

    for (int i = 0; i + 1 < h; ++i) {
        for (int j = 0; j + 1 < w; ++j) {
            if ((i + j) % 2) continue;

            auto f = W - ((long long)B.at(i).at(j) + B.at(i + 1).at(j) + B.at(i).at(j + 1) +
                          B.at(i + 1).at(j + 1));

            so.Impose({i, j}, true, f);

            for (int dx : {1}) {
                for (int dy : {1, -1}) {
                    const int ni = i + dx, nj = j + dy;
                    const int x = (i + ni + 1) / 2, y = (j + nj + 1) / 2;
                    if (isin(x, y)) so.Impose({i, j}, true, {ni, nj}, true, B.at(x).at(y));
                }
            }
        }
    }
    const auto res = so.Solve();
    cout << -res.total_cost << '\n';
}
