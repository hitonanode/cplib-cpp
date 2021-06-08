#define PROBLEM "https://judge.yosupo.jp/problem/point_add_rectangle_sum"
#include "../rangetree.hpp"
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

using S = unsigned long long;
S e() noexcept { return 0; }
void opadd(S &l, S r) noexcept { l += r; }
void opsub(S &l, S r) noexcept { l -= r; }

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N, Q;
    cin >> N >> Q;
    std::vector<int> x(N), y(N), w(N);
    rangetree<S, opadd, opsub, e, int> tree;

    for (int i = 0; i < N; i++) {
        cin >> x[i] >> y[i] >> w[i];
        tree.add_point(x[i], y[i]);
    }
    std::vector<std::tuple<int, int, int, int, int>> qs;
    for (int i = 0; i < Q; i++) {
        int t;
        cin >> t;
        if (t == 0) {
            int x, y, w;
            cin >> x >> y >> w;
            qs.emplace_back(t, x, y, w, 0);
            tree.add_point(x, y);
        } else {
            int l, d, r, u;
            cin >> l >> d >> r >> u;
            qs.emplace_back(t, l, r, d, u);
        }
    }
    tree.build();
    for (int i = 0; i < N; i++) tree.add(x[i], y[i], w[i]);
    for (auto q : qs) {
        if (std::get<0>(q) == 0) {
            int t, x, y, w, z;
            tie(t, x, y, w, z) = q;
            tree.add(x, y, w);
        } else {
            int t, l, r, d, u;
            tie(t, l, r, d, u) = q;
            cout << tree.sum(l, r, d, u) << '\n';
        }
    }
}