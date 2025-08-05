#define PROBLEM "https://yukicoder.me/problems/no/1541"

#include "../submodular_optimization_via_graph_cut.hpp"

#include <iostream>
#include <utility>
#include <vector>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    SubmodularOptimizationViaGraphCut so;

    for (int i = 1; i <= N; ++i) {
        int k, C;
        cin >> k >> C;
        so.Impose(i, true, C - M);

        vector<pair<int, int>> AB(k);
        for (auto &[a, b] : AB) cin >> a;
        for (auto &[a, b] : AB) cin >> b;
        for (auto [a, b] : AB) so.Impose(i, true, a, true, -b);
    }

    const auto res = so.Solve();
    assert(res.solved);

    cout << -res.total_cost << '\n';
}
