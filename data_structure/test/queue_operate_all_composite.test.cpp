#include "../../modint.hpp"
#include "../sliding_window_aggregation.hpp"
#define PROBLEM "https://judge.yosupo.jp/problem/queue_operate_all_composite"
#include <iostream>

using mint = ModInt<998244353>;
int main() {
    LinearFunctionQueue<mint> swag;
    int Q;
    cin >> Q;
    while (Q--) {
        int q;
        cin >> q;
        if (q == 0) {
            mint a, b;
            cin >> a >> b;
            swag.push({a, b});
        }
        if (q == 1) swag.pop();
        if (q == 2) {
            mint x;
            cin >> x;
            pair<mint, mint> f = swag.fold_all();
            printf("%d\n", (f.first * x + f.second).val);
        }
    }
}
