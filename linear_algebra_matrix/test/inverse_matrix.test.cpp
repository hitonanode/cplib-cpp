#define PROBLEM "https://judge.yosupo.jp/problem/inverse_matrix"
#include "../../modint.hpp"
#include "../matrix.hpp"
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N;
    cin >> N;
    matrix<ModInt<998244353>> M(N, N);
    cin >> M;
    int rank = M.inverse();
    if (rank < N) {
        cout << -1 << '\n';
    } else {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) cout << M[i][j] << ' ';
            cout << '\n';
        }
    }
}
