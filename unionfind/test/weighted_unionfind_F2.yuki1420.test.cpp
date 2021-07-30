#define PROBLEM "https://yukicoder.me/problems/no/1420"
#include "../weighted_unionfind.hpp"
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N, M;
    cin >> N >> M;

    WeightedUnionFind<F2vec<unsigned>> uf(N);
    while (M--) {
        int a, b, y;
        cin >> a >> b >> y;
        a--, b--;
        if (!uf.unite(a, b, y)) {
            cout << "-1\n";
            return 0;
        }
    }
    for (int i = 0; i < N; i++) cout << uf.weight(i) << '\n';
}
