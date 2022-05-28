#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A" // DUMMY
#include "../pow_of_sparse_fps.hpp"
#include "../../modint.hpp"
#include "../../random/xorshift.hpp"
#include "../formal_power_series.hpp"
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

using mint = ModInt<998244353>;
using fps = FormalPowerSeries<mint>;

int main() {
    for (int nin = 1; nin <= 6; ++nin) {
        for (int d0 = 0; d0 <= nin; ++d0) {
            for (int degout = 0; degout <= 12; ++degout) {
                for (int k = 1; k <= 8; ++k) {
                    for (int iter = 0; iter < 5; ++iter) {
                        vector<mint> f(nin);
                        for (int i = d0; i < nin; ++i) f[i] = rand_int();

                        auto ret = pow_of_sparse_fps(f, degout, k);
                        auto ret_fps = fps(f.begin(), f.end()).pow(k, degout + 1);
                        for (int i = 0; i <= degout; ++i) {
                            if (ret[i] != ret_fps.coeff(i)) {
                                cerr << nin << ' ' << d0 << ' ' << degout << ' ' << k << ' '
                                     << iter << ' ' << i << ' ' << ret[i] << ' '
                                     << ret_fps.coeff(i) << endl;
                                exit(1);
                            }
                        }
                    }
                }
            }
        }
    }
    puts("Hello World");
}
