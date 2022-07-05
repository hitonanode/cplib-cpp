#define PROBLEM "https://judge.yosupo.jp/problem/static_rectangle_add_rectangle_sum"
#include "../rectangle_add_rectangle_sum.hpp"
#include "../../modint.hpp"
#include <iostream>
using namespace std;
using mint = ModInt<998244353>;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    RectangleAddRectangleSum<int, mint> rect_sum;

    const int bias = 500000000;

    int N, Q;
    cin >> N >> Q;

    while (N--) {
        int l, r, d, u;
        mint w;
        cin >> l >> d >> r >> u >> w;
        l -= bias;
        d -= bias;
        r -= bias;
        u -= bias;
        rect_sum.add_rectangle(l, r, d, u, w);
    }

    while (Q--) {
        int l, r, d, u;
        cin >> l >> d >> r >> u;
        l -= bias;
        d -= bias;
        r -= bias;
        u -= bias;
        rect_sum.add_query(l, r, d, u);
    }

    auto ret = rect_sum.solve();
    for (auto x : ret) cout << x << '\n';
}
