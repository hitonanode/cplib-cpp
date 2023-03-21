#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "../../modint.hpp"
#include "../semirelaxed_multiplication.hpp"

#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, M;
    cin >> N >> M;
    vector<ModInt998244353> A(N);
    for (auto &x : A) cin >> x;

    semirelaxed_multiplication f(A);
    ModInt998244353 b;
    for (int i = 0; i < N + M - 1; ++i) cout << f.add(i < M ? (cin >> b, b) : 0) << ' ';
    cout << endl;
}
