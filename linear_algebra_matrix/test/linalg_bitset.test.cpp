#include "../linalg_bitset.hpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2624"
#include <iostream>
#include <numeric>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    constexpr int Wmax = 320;
    int N, T;
    cin >> N;
    vector<bitset<Wmax>> A(N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int t;
            cin >> t;
            A[i][j] = t;
        }
    }
    bitset<Wmax> v(N);
    for (int i = 0; i < N; i++) {
        int t;
        cin >> t;
        v[i] = t;
    }

    cin >> T;
    A = f2_matpower<Wmax>(A, T);
    for (int i = 0; i < N; i++) A[i][N] = v[i];
    A = f2_gauss_jordan<Wmax>(N + 1, A);

    for (int i = 0; i < N; i++) {
        if (A[i].count() == 1 and A[i][N]) {
            cout << "none\n";
            return 0;
        }
    }
    if (!A[N - 1][N - 1]) {
        cout << "ambiguous\n";
        return 0;
    }
    bitset<Wmax> ret;
    for (int i = N - 1; i >= 0; i--) {
        int a = 0;
        for (int j = i + 1; j < N; j++) a ^= ret[j] * A[i][j];
        ret[i] = (a != A[i][N]);
    }
    for (int i = 0; i < N; i++) cout << ret[i] << (i == N - 1 ? '\n' : ' ');
}
