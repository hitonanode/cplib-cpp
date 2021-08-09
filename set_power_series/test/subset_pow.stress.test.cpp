// Stress test by comparing subset subset_pow(f, k) & subset_conv (x k times)
#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A" // DUMMY
#include "../../modint.hpp"
#include "../../random/xorshift.hpp"
#include "../subset_convolution.hpp"
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

void test_polylog_polyexp() {
    using mint = ModInt<11>;
    for (int len = 1; len < 10; len++) {
        for (int t = 0; t < 100000; t++) {
            vector<mint> f(len, 1);
            for (int i = 1; i < len; i++) f[i] = rand_int() % mint::mod();
            auto g = f;
            poly_log(g);
            poly_exp(g);
            assert(f == g);
        }
    }
}

void test_subset_pow() {
    using mint = ModInt<7>;
    for (int lglen = 0; lglen < 5; lglen++) {
        const int len = 1 << lglen;
        for (int t = 0; t < 100000; t++) {
            int k = rand_int() % 10;
            vector<mint> f(len);
            for (auto &x : f) x = rand_int() % mint::mod();
            auto gpow = f;
            subset_pow(gpow, k);
            vector<mint> gconv(len);
            gconv[0] = 1;
            for (int j = 0; j < k; j++) gconv = subset_convolution(gconv, f);
            assert(gpow == gconv);
        }
    }
}

int main() {
    test_polylog_polyexp();
    test_subset_pow();
    cout << "Hello World\n";
}
