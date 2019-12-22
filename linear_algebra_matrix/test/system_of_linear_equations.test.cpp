#define PROBLEM "https://judge.yosupo.jp/problem/system_of_linear_equations"
#include "modulus/modint_fixed.hpp"
#include "linear_algebra_matrix/system_of_linear_equations.hpp"
#include <iostream>
using mint = ModInt<998244353>;
using namespace std;

int main()
{
    int N, M;
    cin >> N >> M;
    matrix<mint> A(N, M);
    cin >> A;
    vector<mint> b(N);
    for (int i = 0; i < N; i++) cin >> b[i];
    auto ret = system_of_linear_equations(A, b);
    if (ret.first.empty()) cout << -1 << "\n";
    else
    {
        cout << ret.second.size() << "\n";
        for (auto x : ret.first) cout << x << " ";
        cout << "\n";

        for (auto vec : ret.second) {
            for (auto e : vec) cout << e << " ";
            cout << "\n";
        }
    }
}
