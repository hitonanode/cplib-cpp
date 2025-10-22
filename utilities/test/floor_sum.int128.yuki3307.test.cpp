#define PROBLEM "https://yukicoder.me/problems/no/3307"
#include "../floor_sum.hpp"
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    long long A, B, C, D;
    cin >> A >> B >> C >> D;

    if (A * D == B * C) {
        cout << "-1\n";
        return 0;
    }

    if (A * D > C * B) swap(A, C), swap(B, D);

    // round(i * A / B) = floor(iA/B + 1/2) = floor((2iA + B)/2B)

    // A/B < C/D
    // i(A/B) + 1 <= i(C/D)
    // i(C/D - A/B) >= 1
    // i(BC - AD) >= BD

    const auto det = B * C - A * D;
    const auto ub = (B * D + det - 1) / det;

    const auto ret = floor_sum<__int128_t, __uint128_t>(ub, D * 2, C * 2, D) -
                     floor_sum<__int128_t, __uint128_t>(ub, B * 2, A * 2, B);
    cout << (long long)(ub - ret - 1) << '\n';
}
