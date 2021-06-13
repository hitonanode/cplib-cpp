#include "../linalg_longlong.hpp"
#include <iostream>
using namespace std;
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_7_D"
using lint = long long;

int main() {
    int N, M, L;
    cin >> N >> M >> L;
    vector<vector<lint>> A(N, vector<lint>(M)), B(M, vector<lint>(L));
    for (auto &v : A) {
        for (auto &x : v) cin >> x;
    }
    for (auto &v : B) {
        for (auto &x : v) cin >> x;
    }
    auto C = matmul(A, B, lint(1e13));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < L - 1; j++) printf("%lld ", C[i][j]);
        printf("%lld\n", C[i].back());
    }
}
