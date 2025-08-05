#define PROBLEM "https://yukicoder.me/problems/no/957"

#include "../submodular_optimization_via_graph_cut.hpp"

#include <iostream>
#include <utility>
using namespace std;

int main() {
    int H, W;
    cin >> H >> W;

    SubmodularOptimizationViaGraphCut<pair<int, int>> so;
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            int G;
            cin >> G;
            so.Impose({i, j}, true, G);
        }
    }

    for (int i = 0; i < H; ++i) {
        int R;
        cin >> R;

        vector<pair<pair<int, int>, bool>> row;
        for (int j = 0; j < W; ++j) row.push_back({{i, j}, true});
        so.Impose(-R);
        so.ImposeIfNotAll(row, R);
    }

    for (int j = 0; j < W; ++j) {
        int C;
        cin >> C;

        vector<pair<pair<int, int>, bool>> col;
        for (int i = 0; i < H; ++i) col.push_back({{i, j}, true});
        so.Impose(-C);
        so.ImposeIfNotAll(col, C);
    }

    const auto res = so.Solve();
    assert(res.solved);

    cout << -res.total_cost << '\n';
}
