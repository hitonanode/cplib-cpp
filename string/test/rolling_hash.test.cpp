#include "../../modint.hpp"
#include "../rolling_hash_1d.hpp"
#include <cassert>
#include <iostream>
#include <string>
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B"
using namespace std;

template <class Hash> vector<int> solve(const string T, const string P) {
    rolling_hash<Hash> rh_T(T), rh_P(P);
    vector<int> ret;
    for (int l = 0; l < (int)(T.length() - P.length() + 1); l++) {
        if (rh_T.get(l, l + P.length()) == rh_P.get(0, P.length())) ret.push_back(l);
    }
    return ret;
}

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    string T, P;
    cin >> T >> P;
    using PH = PairHash<ModInt998244353, ModInt998244353>;
    auto sol1 = solve<PH>(T, P);
    assert(sol1 == (solve<TupleHash3<ModInt998244353, ModInt998244353, ModInt998244353>>(T, P)));
    assert(sol1 == (solve<TupleHash3<PH, ModInt998244353, PH>>(T, P)));
    assert(sol1 == (solve<PairHash<PH, PairHash<ModInt998244353, ModInt998244353>>>(T, P)));

    for (auto x : sol1) cout << x << '\n';
}
