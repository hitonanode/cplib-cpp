#define PROBLEM "https://judge.yosupo.jp/problem/sparse_matrix_det"
#include "../../modint.hpp"
#include "../blackbox_algorithm.hpp"
#include "../blackbox_matrices.hpp"
#include <iostream>
using namespace std;
using mint = ModInt<998244353>;

int main() {
    int N, K;
    cin >> N >> K;
    sparse_matrix<mint> M(N, N);
    while (K--) {
        int a, b, c;
        cin >> a >> b >> c;
        M.add_element(a, b, c);
    }
    cout << blackbox_determinant<sparse_matrix<mint>, mint>(M) << '\n';
}
