#define PROBLEM                                                                                   \
    "https://judge.yosupo.jp/problem/number_of_increasing_sequences_between_two_sequences"

#include "../north_east_lattice_paths.hpp"
#include "../../modint.hpp"
#include "../../convolution/ntt.hpp"

#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, M;
    cin >> N >> M;
    vector<int> lb(N), ub(N);
    for (auto &x : lb) cin >> x;
    for (auto &x : ub) cin >> x;

    auto conv = [&](const vector<ModInt998244353> &a, const vector<ModInt998244353> &b) {
        return nttconv<ModInt998244353>(a, b);
    };

    cout << CountBoundedMonotoneSequence<ModInt998244353>(lb, ub, conv) << '\n';
}
