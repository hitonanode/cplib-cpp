#define PROBLEM "https://judge.yosupo.jp/problem/lcm_convolution"
#include "../../modint.hpp"
#include "../zeta_moebius_transform.hpp"
#include <iostream>
#include <vector>
using namespace std;
using mint = ModInt<998244353>;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N;
    cin >> N;
    std::vector<mint> A(N + 1), B(N + 1);
    for (int i = 1; i <= N; ++i) cin >> A[i];
    for (int i = 1; i <= N; ++i) cin >> B[i];
    auto ret = lcmconv(A, B);
    for (int i = 1; i <= N; ++i) cout << ret[i] << (i == N ? '\n' : ' ');
}
