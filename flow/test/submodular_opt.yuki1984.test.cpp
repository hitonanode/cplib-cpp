#define PROBLEM "https://yukicoder.me/problems/no/1984"

#include "../submodular_optimization_via_graph_cut.hpp"

#include <iostream>
#include <string>
#include <utility>
using namespace std;

int main() {
    int N, M, K, P;
    cin >> N >> M >> K >> P;
    constexpr long long inf = 1LL << 50;

    SubmodularOptimizationViaGraphCut<pair<string, int>, long long> so;

    const std::string Goal = "Goal";
    const std::string Action = "Action";
    const std::string Preparation = "Preparation";
    for (int i = 1; i <= N; ++i) {
        int Ei;
        cin >> Ei;
        so.Impose({Goal, i}, true, -Ei);
    }

    for (int i = 1; i <= M; ++i) {
        int Fi;
        cin >> Fi;
        so.Impose({Action, i}, true, -Fi);
    }

    for (int i = 1; i <= K; ++i) {
        int Vi;
        cin >> Vi;
        so.Impose({Preparation, i}, true, Vi);
    }

    for (int i = 1; i <= N; ++i) {
        int L;
        cin >> L;
        while (L--) {
            int A;
            cin >> A;
            so.Impose({Goal, i}, true, {Preparation, A}, false, inf);
        }
    }

    while (P--) {
        int I, J;
        cin >> I >> J;
        so.Impose({Goal, I}, true, {Action, J}, true, inf);
    }

    const auto res = so.Solve();

    vector<pair<string, int>> ans;
    for (const auto &[var_name, val] : res.x) {
        if (val) ans.emplace_back(var_name);
    }

    std::sort(ans.begin(), ans.end(), [](const auto &a, const auto &b) {
        if (a.first != b.first) return a.first > b.first;
        return a.second < b.second;
    });

    cout << -res.total_cost << '\n';
    cout << ans.size() << '\n';
    for (const auto &[var_name, val] : ans) cout << var_name << ' ' << val << '\n';
}
