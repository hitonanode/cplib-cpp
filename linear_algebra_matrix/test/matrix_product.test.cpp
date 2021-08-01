#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product"
#include "../../modint.hpp"
#include "../../utilities/reader.hpp"
#include "../matrix.hpp"
#include <iostream>
using namespace std;

int main() {
    int N = rdi(), M = rdi(), K = rdi();
    matrix<ModInt<998244353>> A(N, M), B(M, K);
    for (auto &x : A.elem) x = rdi();
    for (auto &x : B.elem) x = rdi();
    auto C = A * B;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < K; j++) cout << C[i][j] << ' ';
        cout << '\n';
    }
}
