#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A" // DUMMY
#include "../../modint.hpp"
#include "../../random/xorshift.hpp"
#include "../subset_convolution.hpp"
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

void test_subset_exp() {
    using mint = ModInt<7>;
    for (int lglen = 0; lglen < 6; lglen++) {
        const int len = 1 << lglen;
        for (int t = 0; t < 200000; t++) {
            vector<mint> f(len);
            for (auto &x : f) x = rand_int() % mint::mod();
            f[0] = 0;
            auto g1 = f, g2 = f;
            subset_exp(g1);
            subset_func(g2, poly_exp<mint>);
            assert(g1 == g2);
        }
    }
}

int main() {
    test_subset_exp();
    cout << "Hello World\n";
}
