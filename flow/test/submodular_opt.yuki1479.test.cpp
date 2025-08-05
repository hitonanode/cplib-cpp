#define PROBLEM "https://yukicoder.me/problems/no/1479"
#include "../submodular_optimization_via_graph_cut.hpp"

#include <iostream>
#include <map>
#include <set>
#include <utility>
using namespace std;

int main() {
    int H, W;
    cin >> H >> W;

    map<int, vector<pair<int, int>>> val2grid;
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            int a;
            cin >> a;
            if (a) val2grid[a].emplace_back(i, j);
        }
    }

    int ret = 0;
    for (const auto &[val, points] : val2grid) {
        SubmodularOptimizationViaGraphCut<pair<char, int>> so;

        set<int> xs, ys;
        for (auto [x, y] : points) {
            xs.insert(x);
            ys.insert(y);
            so.Impose({'r', x}, false, {'c', y}, false, 1 << 20);
        }
        for (int x : xs) so.Impose({'r', x}, true, 1);
        for (int y : ys) so.Impose({'c', y}, true, 1);

        const auto res = so.Solve();
        ret += res.total_cost;
    }

    cout << ret << '\n';
}
