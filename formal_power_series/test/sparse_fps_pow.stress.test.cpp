#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A" // DUMMY
#include "../sparse_fps.hpp"
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

                        const fps init = fps(f.begin(), f.end());

                        const vector<mint> ret1 = sparse_fps::pow(f, degout, k);
                        const fps ret2 = sparse_fps::pow(init, degout, k);
                        const fps ret_fps = init.pow(k, degout + 1);

                        for (int i = 0; i <= degout; ++i) {
                            if (ret1[i] != ret_fps.coeff(i) or ret2[i] != ret_fps.coeff(i)) {
                                cerr << nin << ' ' << d0 << ' ' << degout << ' ' << k << ' '
                                     << iter << ' ' << i << ' ' << ret1[i] << ' ' << ret2[i] << ' '
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
