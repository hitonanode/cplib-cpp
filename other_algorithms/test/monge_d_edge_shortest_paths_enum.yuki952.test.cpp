#define PROBLEM "https://yukicoder.me/problems/no/952"

#include "../monge_d_edge_shortest_paths_enum.hpp"

#include <algorithm>
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N;
    cin >> N;
    vector<int> A(N);
    for (auto &a : A) cin >> a;

    vector<long long> cs(N + 1);
    for (int i = 0; i < N; ++i) cs.at(i + 1) = cs.at(i) + A.at(i);

    constexpr long long inf = 1LL << 60;

    auto f = [&](int i, int j) -> long long {
        long long sum = cs.at(j - 1) - cs.at(i);
        return sum * sum;
    };

    auto costs = MongeDEdgeShortestPaths<long long>(N + 2, N, f, inf);
    std::reverse(costs.begin(), costs.end());
    for (auto x : costs) cout << x << '\n';
}
