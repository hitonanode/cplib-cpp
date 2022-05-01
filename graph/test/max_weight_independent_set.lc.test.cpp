#define PROBLEM "https://judge.yosupo.jp/problem/maximum_independent_set"
#include "../max_weight_independent_set.hpp"
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N, M;
    cin >> N >> M;
    max_weight_independent_set<int> solver(N);
    while (M--) {
        int u, v;
        cin >> u >> v;
        solver.add_edge(u, v);
    }

    cout << solver.solve() << '\n';
    for (int i = 0; i < N; ++i) {
        if ((solver.solution_set >> i) & 1) cout << i << ' ';
    }
    cout << '\n';
}
