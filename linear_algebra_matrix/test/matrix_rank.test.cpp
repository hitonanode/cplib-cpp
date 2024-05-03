#define PROBLEM "https://judge.yosupo.jp/problem/matrix_rank"
#include "../../modint.hpp"
#include "../matrix.hpp"
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int N, M;
    cin >> N >> M;
    matrix<ModInt<998244353>> mat(N, M);
    cin >> mat;
    cout << mat.gauss_jordan().rank_of_gauss_jordan() << '\n';
}
