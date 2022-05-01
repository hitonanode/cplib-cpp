#include "../../modint.hpp"
#include "../sliding_window_aggregation.hpp"
#define PROBLEM "https://judge.yosupo.jp/problem/queue_operate_all_composite"
#include <iostream>
using namespace std;

using mint = ModInt<998244353>;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
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
            cout << (f.first * x + f.second).val() << '\n';
        }
    }
}
