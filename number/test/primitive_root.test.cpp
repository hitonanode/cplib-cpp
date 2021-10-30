#define PROBLEM "https://yukicoder.me/problems/no/931"
#include "../primitive_root.hpp"
#include "../../convolution/ntt.hpp"
#include "../../modint.hpp"
#include <iostream>
#include <vector>
using namespace std;

using mint = ModInt<998244353>;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int P;
    cin >> P;
    vector<mint> A(P - 1), B(P - 1);
    for (auto &x : A) cin >> x;
    for (auto &x : B) cin >> x;
    if (P == 2) {
        cout << A[0] * B[0] << '\n';
        return 0;
    }
    int b = find_smallest_primitive_root(P);
    vector<long long> pp(P, 1), ppinv(P);
    for (int i = 1; i < P; ++i) pp[i] = pp[i - 1] * b % P;
    for (int i = 0; i < P; ++i) ppinv[pp[i]] = i;

    vector<mint> AS(P), BS(P);
    for (int i = 0; i < P - 1; ++i) AS[ppinv[i + 1]] = A[i];
    for (int i = 0; i < P - 1; ++i) BS[ppinv[i + 1]] = B[i];
    auto v = nttconv(AS, BS);
    vector<mint> ret(P + 1);
    for (int i = 1; i < int(v.size()); ++i) ret[pow_mod(b, i, P)] += v[i];
    for (int i = 1; i < P; ++i) cout << ret[i] << (i + 1 == P ? '\n' : ' ');
}
