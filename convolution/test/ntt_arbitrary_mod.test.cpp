#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"
#include "../ntt.hpp"
#include "../../modint.hpp"
#include "../../number/modint_runtime.hpp"
#include <iostream>
using namespace std;

constexpr int MOD = 1000000007;
using mint = ModInt<MOD>;
using mintr = ModIntRuntime;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    mintr::set_mod(MOD);
    int N, M;
    cin >> N >> M;
    vector<mint> A(N), B(M);
    vector<mintr> Ar(N), Br(M);
    for (int i = 0; i < N; i++) cin >> A[i], Ar[i] = A[i].val();
    for (int i = 0; i < M; i++) cin >> B[i], Br[i] = B[i].val();

    vector<mint> ret = nttconv(A, B);
    vector<mintr> retr = nttconv(Ar, Br);

    for (int i = 0; i < N + M - 1; i++) {
        assert(ret[i].val() == retr[i].val());
        cout << ret[i].val() << ' ';
    }
}
