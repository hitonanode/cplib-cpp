#include <iostream>
#include <string>
#include "random/rolling_hash_1d_general.hpp"
#include "modulus/modint_fixed.hpp"
#include "random/xorshift.hpp"
#define PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B
using namespace std;

int main()
{
    mint b1(rand_int() % 1000000 + 1), b2(rand_int() % 1000000 + 1);

    string T, P;
    cin >> T >> P;
    rolling_hash<mint> rh_T1(T, b1),rh_P1(P, b1);
    rolling_hash<mint> rh_T2(T, b2),rh_P2(P, b2);

    for (int l = 0; l < (int)(T.length() - P.length() + 1); l++)
    {
        if (rh_T1.get_hash(l, l + P.length()) == rh_P1.get_hash(0, P.length())
            and rh_T2.get_hash(l, l + P.length()) == rh_P2.get_hash(0, P.length()))
        {
            cout << l << endl;
        }
    }
}
