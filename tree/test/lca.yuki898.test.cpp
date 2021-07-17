#include "../lowest_common_ancestor.hpp"
#include <iostream>
#define PROBLEM "https://yukicoder.me/problems/no/898"
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N;
    cin >> N;
    UndirectedWeightedTree<long long> g(N);
    for (int i = 1; i <= N - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g.add_edge(u, v, w);
    }
    g.fix_root(0);

    int Q;
    cin >> Q;

    while (Q--) {
        int x, y, z;
        cin >> x >> y >> z;
        int xy = g.lowest_common_ancestor(x, y);
        int xyz = g.lowest_common_ancestor(xy, z);
        if (xy != xyz) {
            cout << g.path_length(xy, z) + g.path_length(x, y) << '\n';
        } else {
            int v = g.lowest_common_ancestor(x, z) + g.lowest_common_ancestor(y, z) - xy;
            cout << g.path_length(x, y) + g.path_length(z, v) << '\n';
        }
    }
}
