#include "linear_algebra_matrix/linalg_longlong.hpp"
#include <iostream>
#include <numeric>
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2624"

template <typename T> istream &operator>>(istream &is, vector<T> &vec) {
    for (auto &v : vec) is >> v;
    return is;
}

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, T;
    cin >> N;
    vector<vector<lint>> A(N, vector<lint>(N));
    cin >> A;
    vector<lint> v(N);
    cin >> v >> T;
    A = matpower(A, T, 2);
    vector<vector<lint>> B = A;
    for (int i = 0; i < N; i++) B[i].push_back(v[i]);
    B = gauss_jordan(B, 2);
    for (int i = 0; i < N; i++) {
        if (accumulate(B[i].begin(), B[i].begin() + N, 0) == 0 and B[i][N]) {
            cout << "none\n";
            return 0;
        }
    }
    int rnk = rank_gauss_jordan(B);
    if (rnk < N) {
        cout << "ambiguous\n";
        return 0;
    }
    vector<lint> ret(N);
    for (int i = N - 1; i >= 0; i--) {
        int a = 0;
        for (int j = i + 1; j < N; j++) a += ret[j] * B[i][j];
        ret[i] = (a % 2 != B[i][N]);
    }

    for (int i = 0; i < N; i++) cout << ret[i] << (i + 1 == N ? '\n' : ' ');
}
