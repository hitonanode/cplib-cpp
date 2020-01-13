#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"
#include <iostream>
#include "convolution/ntt_arbitrary_mod.hpp"
#include "modulus/modint_fixed.hpp"
#include "modulus/modint_runtime.hpp"
using namespace std;
constexpr int MOD = 1000000007;

int main()
{
    int N, M;
    cin >> N >> M;
    using mint = ModInt<MOD>;
    using mintr = ModIntRuntime;
    mintr::set_mod(MOD);
    vector<mint> A(N), B(M);
    vector<mintr> Ar(N), Br(M);
    for (int i = 0; i < N; i++) { cin >> A[i];  Ar[i] = A[i].val; }
    for (int i = 0; i < M; i++) { cin >> B[i];  Br[i] = B[i].val; }
    auto ret = nttconv(A, B);
    auto retr = nttconv(Ar, Br);
    for (int i = 0; i < N + M - 1; i++) {
        assert(ret[i].val == retr[i].val);
        printf("%d ", ret[i].val);
    }
}
