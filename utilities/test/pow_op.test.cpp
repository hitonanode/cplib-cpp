#define PROBLEM "https://yukicoder.me/problems/no/2396"

#include "../../convolution/ntt.hpp"
#include "../../number/modint_runtime.hpp"
#include "../pow_op.hpp"

#include <iostream>
using namespace std;

using mint = ModIntRuntime;

int main() {
    int L, K, B;
    long long N, M;

    cin >> N >> M >> L >> K >> B;
    mint::set_mod(B);
    const mint m = M;

    vector<mint> trans{mint(1), mint(1)};

    auto trun = [&](vector<mint> &vec) {
        while (vec.size() > L) {
            vec.at(vec.size() - 1 - L) += vec.back() * m;
            vec.pop_back();
        }
    };

    auto op = [&](vector<mint> l, const vector<mint> &r) {
        l = nttconv(l, r);
        trun(l);
        return l;
    };

    trun(trans);
    trans = pow_op(trans, N, op);
    trans.resize(L);

    cout << trans.at(K).val() << '\n';
}
