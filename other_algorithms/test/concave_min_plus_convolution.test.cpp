#define PROBLEM "https://judge.yosupo.jp/problem/min_plus_convolution_concave_arbitrary"

#include "../smawk.hpp"

#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, M;
    cin >> N >> M;
    vector<int> A(N), B(M);
    for (auto &a : A) cin >> a;
    for (auto &b : B) cin >> b;

    vector<int> ret = concave_min_plus_convolution<int>(B, A);

    for (int i = 0; i < N + M - 1; ++i) cout << ret[i] << " \n"[i + 1 == N + M - 1];
}
