#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial_limit"
#include "../../modint.hpp"
#include "../../number/sieve.hpp"
#include "../sum_of_exponential_times_polynomial_limit.hpp"
#include <iostream>
using namespace std;
using mint = ModInt<998244353>;

int main() {
    int r, d;
    cin >> r >> d;
    auto initial_terms = Sieve(d).enumerate_kth_pows<mint>(d, d);
    cout << sum_of_exponential_times_polynomial_limit<mint>(r, initial_terms) << '\n';
}
