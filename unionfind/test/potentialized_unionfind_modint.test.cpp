#define PROBLEM "https://judge.yosupo.jp/problem/unionfind_with_potential"

#include "../potentialized_unionfind.hpp"

#include <iostream>
using namespace std;

#include <atcoder/modint>
using mint = atcoder::modint998244353;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, Q;
    cin >> N >> Q;
    PotentializedUnionFind<mint> uf(N);

    while (Q--) {
        int t, u, v;
        cin >> t >> u >> v;
        if (t == 0) {
            int x;
            cin >> x;
            if (uf.same(u, v) and uf.diff(v, u) != x) {
                cout << "0\n";
            } else {
                cout << "1\n";
                uf.unite(v, u, x);
            }
        } else {
            if (uf.same(u, v)) {
                cout << uf.diff(v, u).val() << '\n';
            } else {
                cout << "-1\n";
            }
        }
    }
}
