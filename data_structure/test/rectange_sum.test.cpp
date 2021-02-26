#define PROBLEM "https://judge.yosupo.jp/problem/rectangle_sum"
#include "../rectangle_sum.hpp"
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    RectangleSum<int, unsigned long long> rect_sum;

    int N, Q;
    cin >> N >> Q;
    while (N--) {
        int x, y, w;
        cin >> x >> y >> w;
        rect_sum.add_point(x, y, w);
    }
    while (Q--) {
        int l, r, d, u;
        cin >> l >> d >> r >> u;
        rect_sum.add_query(l, r, d, u);
    }

    auto ret = rect_sum.solve();
    for (auto x : ret) cout << x << '\n';
}
