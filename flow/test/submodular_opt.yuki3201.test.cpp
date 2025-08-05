#define PROBLEM "https://yukicoder.me/problems/no/3201"

#include "../submodular_optimization_via_graph_cut.hpp"

#include <iostream>
using namespace std;

int main() {
    int N;
    cin >> N;

    SubmodularOptimizationViaGraphCut so;

    for (int i = 0; i < N; ++i) {
        int p;
        cin >> p;
        so.Impose(i, true, -p);
    }

    int M;
    cin >> M;
    while (M--) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        so.Impose(v, true, u, false, 1LL << 55);
    }

    int K;
    cin >> K;
    while (K--) {
        int a, b, s;
        cin >> a >> b >> s;
        --a, --b;
        so.ImposeIfNotAll({{a, true}, {b, true}}, s);
        so.Impose(-s);
    }

    cout << -so.Solve().total_cost << '\n';
}
