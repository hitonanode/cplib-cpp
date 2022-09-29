#include "../../number/modint_mersenne61.hpp"
#include "../rolling_hash_1d.hpp"
#include <iostream>
#include <string>
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B"
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    string T, P;
    cin >> T >> P;
    rolling_hash<ModIntMersenne61> rh_T(T), rh_P(P);

    for (int l = 0; l < (int)(T.length() - P.length() + 1); l++) {
        if (rh_T.get(l, l + P.length()) == rh_P.get(0, P.length())) cout << l << '\n';
    }
}
