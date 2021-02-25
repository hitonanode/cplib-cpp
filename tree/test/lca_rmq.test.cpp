#include "../lca_rmq.hpp"
#include <iostream>
#define PROBLEM "https://judge.yosupo.jp/problem/lca"
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, Q, p, u, v;
    cin >> N >> Q;
    TreeLCA tree(N);
    for (int i = 1; i <= N - 1; i++) cin >> p, tree.add_edge(i, p);

    while (Q--) cout << tree.lca((cin >> u, u), (cin >> v, v)) << '\n';
}
