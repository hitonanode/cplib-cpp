#include "../../modint.hpp"
#include "../coeff_of_rational_function.hpp"
#define PROBLEM "https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence"
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int D;
    long long K;
    cin >> D >> K;
    vector<ModInt<998244353>> A(D), C(D + 1, 1);
    for (auto &x : A) cin >> x;
    for (int d = 1; d <= D; d++) {
        cin >> C[d];
        C[d] *= -1;
    }

    auto ret = find_kth_term(A, C, K);
    cout << ret << '\n';
}
