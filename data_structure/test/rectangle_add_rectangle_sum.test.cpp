#define PROBLEM "https://judge.yosupo.jp/problem/rectangle_sum"
#include "../rectangle_add_rectangle_sum.hpp"
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    RectangleAddRectangleSum<int, unsigned long long> rect_sum;

    const int bias = 500000000;

    int N, Q;
    cin >> N >> Q;

    while (N--) {
        int x, y, w;
        cin >> x >> y >> w;
        x -= bias;
        y -= bias;
        rect_sum.add_rectangle(x, x + 1, y, y + 1, w);
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
