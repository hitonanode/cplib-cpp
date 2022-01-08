#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial"
#include "../sum_of_exponential_times_polynomial.hpp"
#include "../../modint.hpp"
#include "../../number/sieve.hpp"
#include <cassert>
#include <iostream>
using namespace std;
using mint = ModInt<998244353>;

int main() {
    int r, d;
    long long n;
    cin >> r >> d >> n;
    mint::_precalculation(d + 10);
    auto initial_terms = Sieve(d).enumerate_kth_pows<mint>(d, d);
    cout << sum_of_exponential_times_polynomial<mint>(r, initial_terms, n) << '\n';
}
