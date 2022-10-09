#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_C"
#include "../../number/modint_mersenne61.hpp"
#include "../rolling_hash_2d.hpp"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int H, W;
    cin >> H >> W;
    vector<string> S(H);
    for (auto &s : S) cin >> s;

    int X, Y;
    cin >> X >> Y;
    vector<string> T(X);
    for (auto &t : T) cin >> t;

    const ModIntMersenne61 b1(418672), b2(956731);

    rolling_hash_2d<ModIntMersenne61> rhs(S, b1, b2);

    const auto tgt = rolling_hash_2d<ModIntMersenne61>(T, b1, b2).get(0, X, 0, Y);

    for (int i = 0; i + X <= H; ++i) {
        for (int j = 0; j + Y <= W; ++j) {
            if (rhs.get(i, i + X, j, j + Y) == tgt) cout << i << ' ' << j << '\n';
        }
    }
}
