#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3335"

#include "../north_east_lattice_paths.hpp"
#include "../../modint.hpp"
#include "../../convolution/ntt.hpp"

#include <iostream>
#include <string>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    string S;
    cin >> S;

    int ub = 1;
    vector<int> A{1};

    for (auto c : S) {
        if (c == '0') {
            ++ub;
        } else {
            A.push_back(ub);
        }
    }

    auto conv = [&](const vector<ModInt998244353> &a, const vector<ModInt998244353> &b) {
        return nttconv<ModInt998244353>(a, b);
    };

    cout << CountBoundedMonotoneSequence<ModInt998244353>(A, conv) << '\n';
}
