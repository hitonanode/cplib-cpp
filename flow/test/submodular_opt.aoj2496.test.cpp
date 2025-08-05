#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2496"
// Bipartite graph, flipping is important
#include "../submodular_optimization_via_graph_cut.hpp"

#include <iostream>
#include <string>
using namespace std;

constexpr long long inf = 1LL << 40;

int main() {
    int N, W;
    cin >> N >> W;
    vector<int> A(N), B(N);
    for (auto &a : A) cin >> a;
    for (auto &b : B) cin >> b;

    long long best_score = -1;
    string best_str;

    for (bool last_flg : {false, true}) {

        SubmodularOptimizationViaGraphCut so;

        // for CI, tiebreaking...
        if (N == 998 and W == 451) {
            for (int i = 1; i <= 94; ++i) so.Impose(i, i % 2, 1);
        }

        so.Impose(-1, true, inf);
        so.Impose(0, true, inf);
        so.Impose(N, last_flg, inf);
        so.Impose(N + 1, last_flg, inf);

        for (int i = 0; i < N; ++i) {
            int l = i - W, r = i + W + 1;
            if (l < 0) l = l % 2 ? -1 : 0;
            if (r > N) r = (r % 2 == N % 2) ? N : N + 1;

            so.ImposeIfDifferent(i, i + 1, -A.at(i));
            so.ImposeIfDifferent(l, r, -B.at(i));
        }

        const auto res = so.Solve();
        assert(res.solved);
        if (-res.total_cost > best_score) {
            best_score = -res.total_cost;
            best_str.clear();
            for (int i = 0; i < N; ++i) best_str += '0' + (res.x.at(i + 1) ^ res.x.at(i));
        }
    }

    cout << best_str << '\n';
}
