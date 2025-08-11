#define PROBLEM "https://yukicoder.me/problems/no/114"
#include "../minimum_steiner_tree.hpp"

#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, M, T;
    cin >> N >> M >> T;

    vector<tuple<int, int, int>> edges(M);
    for (auto &[u, v, w] : edges) cin >> u >> v >> w, --u, --v;

    vector<int> terminals(T);
    for (auto &v : terminals) cin >> v, --v;

    const auto [cost, used_edges] = MinimumSteinerTree(N, edges, terminals);
    cout << cost << '\n';
}
