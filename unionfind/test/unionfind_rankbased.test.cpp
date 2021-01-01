#include "../unionfind_rankbased.hpp"
#include <iostream>
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_A&lang=jp"
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    RankBasedUnionFind uf(n);
    for (int i = 0; i < q; i++) {
        int c, x, y;
        cin >> c >> x >> y;
        if (c)
            cout << (int)uf.same(x, y) << endl;
        else
            uf.unite(x, y);
    }
}
