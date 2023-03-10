#include "../enumerate_cliques.hpp"
#include "../../modint.hpp"
#include <iostream>
#include <vector>
using namespace std;

#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_cliques"

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, M;
    cin >> N >> M;
    using mint = ModInt998244353;
    vector<mint> X(N);
    for (auto &x : X) cin >> x;

    enumerate_cliques ec(N);
    while (M--) {
        int u, v;
        cin >> u >> v;
        ec.add_bi_edge(u, v);
    }
    mint ret = mint();

    auto op = [&](const std::vector<int> &clique) -> void {
        mint tmp = 1;
        for (int x : clique) tmp *= X.at(x);
        ret += tmp;
    };
    ec.run(op);

    cout << ret << endl;
}
