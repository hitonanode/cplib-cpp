#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3058"

#include "../submodular_optimization_via_graph_cut.hpp"

#include <iostream>
#include <string>
#include <utility>
using namespace std;

int main() {
    int N, M;
    string U;
    cin >> N >> M >> U;

    SubmodularOptimizationViaGraphCut so;

    for (int i = 0; i < N; ++i) {
        int a;
        cin >> a;
        if (U.at(i) == 'L') {
            so.Impose(i, true, a);
        } else {
            so.Impose(i, false, a);
        }
    }

    while (M--) {
        int s, t, b;
        cin >> s >> t >> b;
        --s, --t;

        if (s > t) swap(s, t);

        so.Impose(s, true, t, false, b);
    }

    const auto res = so.Solve();

    cout << res.total_cost << '\n';
}
