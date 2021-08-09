#include "../mincostflow_nonegativeloop.hpp"
#define PROBLEM "https://judge.yosupo.jp/problem/assignment"
#include <algorithm>
#include <iostream>

template <typename TC> std::pair<TC, std::vector<int>> AssignmentProblem(std::vector<std::vector<TC>> cost) {
    int N = cost.size();
    MinCostFlow<int, TC> mcf(N * 2 + 2);
    int S = N * 2, T = N * 2 + 1;
    TC bias_total_cost = 0;
    for (int i = 0; i < N; i++) {
        TC lo = *min_element(cost[i].begin(), cost[i].end());
        bias_total_cost += lo;
        mcf.add_edge(S, i, 1, 0);
        mcf.add_edge(N + i, T, 1, 0);
        for (int j = 0; j < N; j++) mcf.add_edge(i, N + j, 1, cost[i][j] - lo);
    }
    auto total_cost = mcf.flow(S, T, N).second + bias_total_cost;
    std::vector<int> ret;

    for (int i = 0; i < N; i++) {
        for (const auto &g : mcf.g[i]) {
            if (g.to != S and !g.cap) {
                ret.emplace_back(g.to - N);
                break;
            }
        }
    }
    return std::make_pair(total_cost, ret);
}

int main() {
    int N;
    std::cin >> N;
    std::vector<std::vector<long long>> A(N, std::vector<long long>(N));
    for (auto &vec : A) {
        for (auto &x : vec) { std::cin >> x; }
    }
    auto ret = AssignmentProblem(A);
    std::cout << ret.first << '\n';
    for (auto x : ret.second) std::cout << x << ' ';
    std::cout << '\n';
}
