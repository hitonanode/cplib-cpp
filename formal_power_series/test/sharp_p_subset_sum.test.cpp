#define PROBLEM "https://judge.yosupo.jp/problem/sharp_p_subset_sum"
#include "formal_power_series/formal_power_series.hpp"
#include "modint.hpp"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, T;
    cin >> N >> T;
    vector<int> cnt(T + 1);
    while (N--) {
        int s;
        cin >> s;
        cnt[s]++;
    }
    FormalPowerSeries<ModInt<998244353>> A(T + 1), invs(T + 1);
    for (int i = 1; i <= T; i++) invs[i] = (invs[i] + i).inv();

    for (int i = 1; i <= T; i++) {
        if (cnt[i]) {
            for (int j = 1; j * i <= T; j++) {
                if (j % 2)
                    A[j * i] += cnt[i] * invs[j];
                else
                    A[j * i] -= cnt[i] * invs[j];
            }
        }
    }
    A = A.exp(T + 1);
    for (int t = 1; t <= T; t++) cout << A.coeff(t) << ' ';
    cout << '\n';
}
