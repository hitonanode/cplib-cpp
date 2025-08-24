#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det"
#include "../matrix.hpp"
#include <atcoder/modint>
#include <iostream>
using namespace std;
using mint = atcoder::modint998244353;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N;
    cin >> N;

    matrix<mint> mat(N, N);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int tmp;
            cin >> tmp;
            mat[i][j] = tmp;
        }
    }
    auto ret = mat.gauss_jordan().determinant_of_upper_triangle();
    cout << ret.val() << '\n';
}
