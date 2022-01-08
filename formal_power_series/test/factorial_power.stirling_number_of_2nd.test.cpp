#define PROBLEM "https://judge.yosupo.jp/problem/stirling_number_of_the_second_kind"
#include "../../modint.hpp"
#include "../../number/sieve.hpp"
#include "../factorial_power.hpp"
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N;
    cin >> N;
    using mint = ModInt<998244353>;
    auto ys = Sieve(N).enumerate_kth_pows<mint>(N, N);
    const auto stirling_number_of_2nd = ys_to_factorial(ys);
    for (auto a : stirling_number_of_2nd) cout << a << ' ';
    cout << '\n';
}
