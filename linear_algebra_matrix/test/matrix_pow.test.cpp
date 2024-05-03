#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_matrix"
#include "../../modint.hpp"
#include "../matrix.hpp"
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int N;
    long long K;
    cin >> N >> K;
    matrix<ModInt<998244353>> M(N, N);
    cin >> M;
    M = M.pow(K);
    for (int i = 0; i < N; ++i) {
        cout << M[i][0];
        for (int j = 1; j < N; ++j) cout << ' ' << M[i][j];
        cout << '\n';
    }
}
