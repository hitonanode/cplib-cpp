#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "../../modint.hpp"
#include "../relaxed_multiplication.hpp"

#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, M;
    cin >> N >> M;
    vector<ModInt998244353> A(N), B(M);
    for (auto &x : A) cin >> x;
    for (auto &x : B) cin >> x;

    relaxed_multiplication<ModInt998244353> f;
    for (int i = 0; i < N + M - 1; ++i) {
        cout << f.add(i < N ? A.at(i) : 0, i < M ? B.at(i) : 0) << ' ';
    }
    cout << endl;
}
