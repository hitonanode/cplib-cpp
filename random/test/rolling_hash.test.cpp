#include "random/rand_nondeterministic.hpp"
#include "random/rolling_hash_1d_general.hpp"
#include <iostream>
#include <string>
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B"
using namespace std;

int main() {
    DoubleHash b(rnd(1, 1000000), rnd(1, 1000000));

    string T, P;
    cin >> T >> P;
    rolling_hash<DoubleHash> rh_T(T, b), rh_P(P, b);

    for (int l = 0; l < (int)(T.length() - P.length() + 1); l++) {
        if (rh_T.get_hash(l, l + P.length()) == rh_P.get_hash(0, P.length())) { cout << l << endl; }
    }
}
