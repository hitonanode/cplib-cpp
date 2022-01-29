#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A" // DUMMY
#include "../zeta_moebius_transform.hpp"
#include "../../modint.hpp"
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

using mint = ModInt<1000000007>;

long long state = 1;
mint rndgen() {
    state = (state * 1234567 + 890123) % mint::mod();
    return mint(state);
}
vector<mint> vecgen(int n) {
    vector<mint> ret(n + 1);
    for (int i = 1; i <= n; ++i) ret[i] = rndgen();
    return ret;
}

void test_divisor_zeta() {
    for (int n = 1; n <= 100; ++n) {
        for (int iter = 0; iter < 10; ++iter) {
            vector<mint> x = vecgen(n), y(n + 1);
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= i; ++j) {
                    if (i % j == 0) y[i] += x[j];
                }
            }
            divisor_zeta(x);
            assert(x == y);
        }
    }
}

void test_divisor_moebius() {
    for (int n = 1; n <= 100; ++n) {
        for (int iter = 0; iter < 10; ++iter) {
            vector<mint> x = vecgen(n), y = x;
            divisor_zeta(x);
            divisor_moebius(x);
            assert(x == y);
        }
    }
}

void test_multiple_zeta() {
    for (int n = 1; n <= 100; ++n) {
        for (int iter = 0; iter < 10; ++iter) {
            vector<mint> x = vecgen(n), y(n + 1);
            for (int i = 1; i <= n; ++i) {
                for (int j = i; j <= n; ++j) {
                    if (j % i == 0) y[i] += x[j];
                }
            }
            multiple_zeta(x);
            assert(x == y);
        }
    }
}

void test_multiple_moebius() {
    for (int n = 1; n <= 100; ++n) {
        for (int iter = 0; iter < 10; ++iter) {
            vector<mint> x = vecgen(n), y = x;
            multiple_zeta(x);
            multiple_moebius(x);
            assert(x == y);
        }
    }
}

void test_gcdconv() {
    for (int n = 1; n <= 100; ++n) {
        for (int iter = 0; iter < 10; ++iter) {
            vector<mint> x = vecgen(n), y = vecgen(n), z(n + 1);
            auto conv = gcdconv(x, y);
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) z[__gcd(i, j)] += x[i] * y[j];
            }
            assert(conv == z);
        }
    }
}

void test_lcmconv() {
    for (int n = 1; n <= 100; ++n) {
        for (int iter = 0; iter < 10; ++iter) {
            vector<mint> x = vecgen(n), y = vecgen(n), z(n + 1);
            auto conv = lcmconv(x, y);
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    int l = i * j / __gcd(i, j);
                    if (l <= n) z[l] += x[i] * y[j];
                }
            }
            assert(conv == z);
        }
    }
}

int main() {
    test_divisor_zeta();
    test_divisor_moebius();
    test_multiple_zeta();
    test_multiple_moebius();
    test_gcdconv();
    test_lcmconv();
    cout << "Hello World\n";
}
