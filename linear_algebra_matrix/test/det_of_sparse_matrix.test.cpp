#define PROBLEM "https://judge.yosupo.jp/problem/sparse_matrix_det"
#include "../../modint.hpp"
#include "../det_of_sparse_matrix.hpp"
#include <iostream>

int main() {
    int N, K;
    std::cin >> N >> K;
    sparse_matrix<ModInt<998244353>> M(N, N);
    while (K--) {
        int a, b, c;
        std::cin >> a >> b >> c;
        M.add_element(a, b, c);
    }
    std::cout << M.Determinant() << '\n';
}
