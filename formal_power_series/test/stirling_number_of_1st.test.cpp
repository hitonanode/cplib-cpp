#define PROBLEM "https://judge.yosupo.jp/problem/stirling_number_of_the_first_kind"
#include "formal_power_series/formal_power_series.hpp"
#include "modint.hpp"
#include <iostream>
using namespace std;

int main()
{
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N;
    cin >> N;
    using fps = FormalPowerSeries<ModInt<998244353>>;

    auto solve = [&](auto&& self, int N) -> fps {
        // Calculate \prod_{i=0}^{N-1} (x-i)
        if (N == 0) {
            return { 1 };
        }
        if (N == 1) {
            return { 0, 1 };
        }
        int k = N / 2;
        fps f = self(self, k);
        f *= f.shift(-k);
        if (N % 2) {
            f *= fps { -(N - 1), 1 };
        }
        return f;
    };

    fps ret = solve(solve, N);
    for (int i = 0; i <= N; i++) {
        cout << ret.coeff(i) << (i == N ? '\n' : ' ');
    }
}
