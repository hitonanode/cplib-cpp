#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det"
#include <iostream>
#include "linear_algebra_matrix/linalg_longlong.hpp"
using namespace std;

int main()
{
    int N;
    cin >> N;
    vector<vector<long long int>> M(N, vector<long long int>(N));
    for (int i = 0; i < N * N; i++) cin >> M[i / N][i % N];
    cout << mod_determinant(M, 998244353) << endl;
}
