#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"
#include <iostream>
#include "modulus/modint_fixed.hpp"
#include "convolution/fft_mod.hpp"
using namespace std;

int main()
{
    int N, M;
    cin >> N >> M;
    using mint = ModInt<998244353>;
    vector<mint> A(N), B(M);
    for (int i = 0; i < N; i++) cin >> A[i];
    for (int i = 0; i < M; i++) cin >> B[i];
    auto ret = convolution_mod(A, B);
    for (int i = 0; i < N + M - 1; i++) printf("%d ", ret[i].val);
}
