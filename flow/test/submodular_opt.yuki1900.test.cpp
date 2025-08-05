#define PROBLEM "https://yukicoder.me/problems/no/1900"

#include "../submodular_optimization_via_graph_cut.hpp"

#include <iostream>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> A(N);
    for (auto &a : A) cin >> a;

    SubmodularOptimizationViaGraphCut so;
    for (int i = 0; i < N; ++i) {
        so.Impose(i, true, -1);

        for (int j = 0; j < i; ++j) {
            if (__builtin_popcount(A[i] ^ A[j]) == 1) so.Impose(i, true, j, true, 1LL << 30);
        }
    }

    const auto res = so.Solve();
    cout << -res.total_cost << '\n';
}
