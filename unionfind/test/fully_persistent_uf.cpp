#include "unionfind/fully_persistent_uf.hpp"
#include <iostream>
#define PROBLEM "https://judge.yosupo.jp/problem/persistent_unionfind"
using namespace std;

int main()
{
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, Q;
    cin >> N >> Q;
    PersistentUnionFind uf(N);
    while (Q--) {
        int t, k, u, v;
        cin >> t >> k >> u >> v;
        if (t == 0) {
            uf.unite(k + 1, u, v);
        } else {
            uf.unite(k + 1, 0, 0);
            cout << uf.same(k + 1, u, v) << '\n';
        }
    }
}
