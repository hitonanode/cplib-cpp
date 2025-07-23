#define PROBLEM "https://judge.yosupo.jp/problem/point_add_rectangle_sum"
#include "../../segmenttree/binary_indexed_tree.hpp"
#include "../wavelet_matrix.hpp"
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N, Q;
    cin >> N >> Q;

    wavelet_matrix<int> wm;
    vector<tuple<int, int, int>> points(N);
    vector<tuple<int, int, int, int, int>> queries(Q);

    for (auto &[i, j, x] : points) {
        cin >> i >> j >> x;
        wm.add_point(i, j);
    }

    for (auto &[tp, a, b, c, d] : queries) {
        cin >> tp;
        if (tp == 0) {
            cin >> a >> b >> c;
            d = -1;
            wm.add_point(a, b);
        } else {
            cin >> a >> b >> c >> d;
        }
    }

    wm.build();

    vector weights(wm.D(), BIT<long long>(wm.N()));

    for (auto [i, j, x] : points) {
        wm.apply(i, j, [&weights, x](int d, int idx) { weights[d].add(idx, x); });
    }

    for (auto [tp, l, d, r, u] : queries) {
        if (tp == 0) {
            wm.apply(l, d, [&weights, r](int d, int idx) { weights[d].add(idx, r); });
        } else {
            long long ans = 0;
            wm.prod(l, r, u,
                    [&weights, &ans](int d, int l0, int r0) { ans += weights[d].sum(l0, r0); });
            wm.prod(l, r, d,
                    [&weights, &ans](int d, int l0, int r0) { ans -= weights[d].sum(l0, r0); });
            cout << ans << '\n';
        }
    }
}
