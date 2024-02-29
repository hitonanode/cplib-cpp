#define PROBLEM "https://yukicoder.me/problems/no/901"
#include "../auxiliary_tree.hpp"
#include "../../graph/shortest_path.hpp"
#include <cassert>
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N;
    cin >> N;
    vector<vector<int>> to(N);

    shortest_path<long long> sp(N);

    for (int e = 0; e < N - 1; ++e) {
        int u, v, w;
        cin >> u >> v >> w;
        to.at(u).push_back(v);
        to.at(v).push_back(u);
        sp.add_bi_edge(u, v, w);
    }

    const int root = 0;

    auxiliary_tree at(to, root);

    sp.solve(root);

    int Q;
    cin >> Q;
    while (Q--) {
        int k;
        cin >> k;
        vector<int> xs(k);
        for (auto &x : xs) cin >> x;

        for (int x : xs) at.activate(x);

        long long ret = 0;

        auto rec = [&](auto &&self, int now) -> void {
            for (int nxt : at.get_children(now)) {
                self(self, nxt);
                ret += sp.dist.at(nxt) - sp.dist.at(now);
            }
        };

        rec(rec, at.auxiliary_root());

        for (int x : xs) at.deactivate(x);

        cout << ret << '\n';
    }
}
