#define PROBLEM "https://yukicoder.me/problems/no/2713"

#include "../submodular_optimization_via_graph_cut.hpp"

#include <iostream>
#include <utility>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    SubmodularOptimizationViaGraphCut so;

    for (int i = 0; i < N; ++i) {
        int a;
        cin >> a;
        so.Impose(i, true, a);
    }

    vector<int> B(M);
    for (auto &b : B) cin >> b;

    for (int i = 0; i < M; ++i) {
        int K;
        cin >> K;
        vector<pair<int, bool>> consts;
        while (K--) {
            int c;
            cin >> c;
            consts.emplace_back(c - 1, true);
        }

        so.ImposeIfNotAll(consts, B.at(i));
        so.Impose(-B.at(i));
    }

    const auto res = so.Solve();

    cout << -res.total_cost << '\n';
}
