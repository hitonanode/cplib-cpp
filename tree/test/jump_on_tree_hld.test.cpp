#define PROBLEM "https://judge.yosupo.jp/problem/jump_on_tree"
#include "../heavy_light_decomposition.hpp"
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N, Q;
    cin >> N >> Q;
    vector<pair<int, int>> edges;
    for (int e = 0; e < N - 1; ++e) {
        int a, b;
        cin >> a >> b;
        edges.emplace_back(a, b);
    }

    heavy_light_decomposition tree(N, edges);
    tree.build({0});

    while (Q--) {
        int s, t, i;
        cin >> s >> t >> i;
        cout << tree.s_to_t_by_k_steps(s, t, i) << '\n';
    }
}
