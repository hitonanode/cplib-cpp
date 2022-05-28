#define PROBLEM "https://yukicoder.me/problems/no/1939"
#include "../pow_of_sparse_fps.hpp"
#include "../../modint.hpp"
#include <iostream>
#include <vector>
using namespace std;
using mint = ModInt<998244353>;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N, M;
    cin >> N >> M;
    vector<mint> f(N + 1);
    f[0] = 1;
    while (M--) {
        int l;
        cin >> l;
        f[l] += 1;
    }
    cout << pow_of_sparse_fps(f, N, N + 1)[N] / (N + 1) << '\n';
}
