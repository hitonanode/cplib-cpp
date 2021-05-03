#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial_limit"
#include "../../modint.hpp"
#include "../../number/sieve.hpp"
#include "../multipoint_evaluation.hpp"
#include "../sum_of_exponential_times_polynomial_limit.hpp"
#include <cassert>
#include <iostream>
using namespace std;
using mint = ModInt<998244353>;

int main() {
    int r, d;
    cin >> r >> d;
    mint::_precalculation(d + 10);
    auto initial_terms = Sieve(d).enumerate_kth_pows<mint>(d, d);
    if (d > 0 and d <= 100000) {
        vector<mint> xs(d + 1);
        for (int i = 0; i <= d; i++) xs[i] = i;
        vector<mint> f(d + 1);
        f[d] = 1;
        assert(MultipointEvaluation<mint>(xs).evaluate_polynomial(f) == initial_terms);
    }
    cout << sum_of_exponential_times_polynomial_limit<mint>(r, initial_terms) << '\n';
}
