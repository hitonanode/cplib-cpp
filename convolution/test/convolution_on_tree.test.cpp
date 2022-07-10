#define PROBLEM "https://yukicoder.me/problems/no/2004"
#include "../convolution_on_tree.hpp"
#include "../../modint.hpp"
#include "../ntt.hpp"

#include <iostream>
using namespace std;
using mint = ModInt<998244353>;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N;
    long long K;
    cin >> N >> K;
    vector<mint> A(N + 1);
    vector<int> par(N);
    for (auto &x : A) cin >> x;
    for (auto &p : par) cin >> p;
    par.insert(par.begin(), -1);

    vector<mint> trans(N + 1);
    mint tmp = 1;
    for (int i = 0; i < int(trans.size()); ++i) {
        trans[i] = tmp;
        tmp = tmp * (mint(K) - i) / (i + 1);
    }
    while (trans.size() and trans.back() == mint()) trans.pop_back();

    auto convolve = [&](vector<mint> &l, vector<mint> &r) { return nttconv(l, r); };

    for (auto x : ConvolutionOnTree(par).run(A, trans, convolve)) cout << x << '\n';
}
