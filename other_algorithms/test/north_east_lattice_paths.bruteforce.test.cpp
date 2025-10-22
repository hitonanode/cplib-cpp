#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A" // DUMMY

#include "../north_east_lattice_paths.hpp"
#include "../../modint.hpp"
#include "../../convolution/ntt.hpp"

using mint = ModInt998244353;

#include <iostream>
#include <map>
#include <utility>
using namespace std;

void Check() {
    const int n = 30, d = 10;
    vector<mint> init(d);
    for (int i = 0; i < d; ++i) init[i] = mint(2).pow(i);

    map<pair<int, int>, mint> dp;
    for (int x = 0; x < d; ++x) dp[{x, 0}] = init[x];

    for (int x = -n; x <= n; ++x) {
        for (int y = -n; y <= n; ++y) {
            if (x + 1 <= n) dp[{x + 1, y}] += dp[{x, y}];
            if (y + 1 <= n) dp[{x, y + 1}] += dp[{x, y}];
        }
    }

    for (int dx_init = -n; dx_init <= n; ++dx_init) {
        for (int y = -n; y <= n; ++y) {
            for (int len = 1; dx_init + len - 1 <= n; ++len) {
                vector<mint> expected(len);
                for (int i = 0; i < len; ++i) expected[i] = dp[{dx_init + i, y}];

                auto res = NorthEastLatticePathsParallel<mint>(
                    init, dx_init, y, len, [&](auto &&a, auto &&b) { return nttconv(a, b); });
                if (res != expected) {
                    cerr << "Failed Parallel: " << dx_init << ' ' << y << ' ' << len
                         << "\nExpected: ";
                    for (auto e : expected) cerr << " " << e;
                    cerr << "\nResult: ";
                    for (auto e : res) cerr << " " << e;
                    cerr << '\n';
                    exit(1);
                }
            }
        }
    }

    for (int x = -n; x <= n; ++x) {
        for (int dy_init = -n; dy_init <= n; ++dy_init) {
            for (int len = 1; dy_init + len - 1 <= n; ++len) {
                vector<mint> expected(len);
                for (int i = 0; i < len; ++i) expected[i] = dp[{x, dy_init + i}];

                auto res = NorthEastLatticePathsVertical<mint>(
                    init, x, dy_init, len, [&](auto &&a, auto &&b) { return nttconv(a, b); });
                if (res != expected) {
                    cerr << "Failed Vertical: " << x << ' ' << dy_init << ' ' << len
                         << "\nExpected: ";
                    for (auto e : expected) cerr << " " << e;
                    cerr << "\nResult: ";
                    for (auto e : res) cerr << " " << e;
                    cerr << '\n';
                    exit(1);
                }
            }
        }
    }
}

int main() {
    Check();
    puts("Hello World");
}
