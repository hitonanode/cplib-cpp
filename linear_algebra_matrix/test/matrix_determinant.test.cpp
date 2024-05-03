#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det"
#include "../../modint.hpp"
#include "../matrix.hpp"
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int N;
    cin >> N;
    matrix<ModInt<998244353>> M(N, N);
    cin >> M;
    cout << M.gauss_jordan().determinant_of_upper_triangle() << '\n';
}
