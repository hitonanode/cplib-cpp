#include "../../modint.hpp"
#include "../rolling_hash_1d.hpp"
#include <iostream>
#include <string>
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B"
using namespace std;

using mint1 = ModInt<998244353>;
using mint2 = ModInt<1000000007>;
int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    mint1 b1 = 51152368;
    mint2 b2 = 1537689;

    string T, P;
    cin >> T >> P;
    rolling_hash<mint1> rh_T1(T, b1), rh_P1(P, b1);
    rolling_hash<mint2> rh_T2(T, b2), rh_P2(P, b2);

    for (int l = 0; l < (int)(T.length() - P.length() + 1); l++) {
        if (rh_T1.get(l, l + P.length()) == rh_P1.get(0, P.length()) and rh_T2.get(l, l + P.length()) == rh_P2.get(0, P.length())) {
            cout << l << '\n';
        }
    }
}
