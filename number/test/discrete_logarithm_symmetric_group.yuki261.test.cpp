#define PROBLEM "https://yukicoder.me/problems/no/261"
#include "number/discrete_logarithm.hpp"

#include <iostream>
#include <numeric>
#include <set>
#include <utility>
using namespace std;

constexpr int D = 100;
using S = std::array<int, D>;

S e() {
    S res;
    iota(res.begin(), res.end(), 0);
    return res;
}

S op(S l, S r) {
    S res = e();
    for (int i = 0; i < D; ++i) res[i] = l[r[i]];
    return res;
}

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, K;
    cin >> N >> K;

    S f = e();
    while (K--) {
        int x, y;
        cin >> x >> y;
        --x, --y;
        swap(f[x], f[y]);
    }

    int Q;
    cin >> Q;
    while (Q--) {
        S g = e();
        for (int i = 0; i < N; ++i) cin >> g.at(i), g.at(i)--;
        cout << DiscreteLogarithmNonzero<S, set<S>>(f, g, op, 1LL << 30) << '\n';
    }
}
