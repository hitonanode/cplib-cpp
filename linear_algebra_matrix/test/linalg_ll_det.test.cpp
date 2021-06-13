#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det"
#include "../linalg_longlong.hpp"
#include <iostream>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<vector<long long>> M(N, vector<long long>(N));
    for (int i = 0; i < N * N; i++) cin >> M[i / N][i % N];
    cout << mod_determinant(M, 998244353) << endl;
}
