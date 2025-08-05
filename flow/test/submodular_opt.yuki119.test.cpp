#define PROBLEM "https://yukicoder.me/problems/no/119"

#include "../submodular_optimization_via_graph_cut.hpp"

#include <iostream>
#include <utility>
using namespace std;

int main() {
    int N;
    cin >> N;

    SubmodularOptimizationViaGraphCut<pair<int, int>> so;

    constexpr long long inf = 1LL << 30;

    // 0 = Go country but not visit
    // 1 = No-go
    // 2 = Go country and visit
    std::vector<decltype(so)::IntVar> vars;
    for (int i = 0; i < N; ++i) {
        long long B, C;
        cin >> B >> C;
        const auto iv = so.GenIntVar({{i, 0}, {i, 1}}, inf);
        so.Impose(iv, {-C, 0LL, -B});
        vars.push_back(iv);
    }

    int M;
    cin >> M;
    while (M--) {
        int D, E;
        cin >> D >> E;
        so.ImposeLbUb(vars.at(D), 2, vars.at(E), 0, inf);
    }

    const auto res = so.Solve();
    assert(res.solved);

    cout << -res.total_cost << '\n';
}
