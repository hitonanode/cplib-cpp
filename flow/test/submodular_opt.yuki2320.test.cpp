#define PROBLEM "https://yukicoder.me/problems/no/2320"

#include "../submodular_optimization_via_graph_cut.hpp"

#include <iostream>
using namespace std;

int main() {
    int N, S, T;
    cin >> N >> S >> T;
    constexpr long long inf = 1LL << 40;

    SubmodularOptimizationViaGraphCut so;

    while (S--) {
        int e;
        cin >> e;
        so.Impose(e - 1, true, inf);
    }
    while (T--) {
        int r;
        cin >> r;
        so.Impose(r - 1, false, inf);
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int c;
            cin >> c;
            if (c == 0) continue;
            if (i < j) so.ImposeIfSame(i, j, -c);
        }
    }

    cout << -so.Solve().total_cost << '\n';
}
