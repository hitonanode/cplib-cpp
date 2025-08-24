#define PROBLEM "https://yukicoder.me/problems/no/3170"
#include "number/discrete_logarithm.hpp"

#include <array>
#include <iostream>
#include <set>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        using S = array<int, 4>;

        int P;
        cin >> P;

        auto op = [&](S l, S r) -> S {
            return S{(int)(((long long)l[0b00] * r[0b00] + (long long)l[0b01] * r[0b10]) % P),
                     (int)(((long long)l[0b00] * r[0b01] + (long long)l[0b01] * r[0b11]) % P),
                     (int)(((long long)l[0b10] * r[0b00] + (long long)l[0b11] * r[0b10]) % P),
                     (int)(((long long)l[0b10] * r[0b01] + (long long)l[0b11] * r[0b11]) % P)};
        };
        array<int, 4> A, B;
        for (auto &x : A) cin >> x;
        for (auto &x : B) cin >> x;

        auto res = DiscreteLogarithm<S, S, set<S>>(A, S{1, 0, 0, 1}, B, op, op, (long long)P * P);
        cout << res << '\n';
    }
}
