#define PROBLEM "https://judge.yosupo.jp/problem/jump_on_tree"
#include "../lowest_common_ancestor.hpp"
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N, Q;
    cin >> N >> Q;
    UndirectedWeightedTree<int> tree(N);
    for (int e = 0; e < N - 1; ++e) {
        int a, b;
        cin >> a >> b;
        tree.add_edge(a, b, 1);
    }

    tree.fix_root(0);

    while (Q--) {
        int s, t, i;
        cin >> s >> t >> i;
        cout << tree.s_to_t_by_k_steps(s, t, i) << '\n';
    }
}
