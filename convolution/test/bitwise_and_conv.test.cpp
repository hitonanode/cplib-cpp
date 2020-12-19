#define PROBLEM "https://judge.yosupo.jp/problem/bitwise_and_convolution"
#include "../../modint.hpp"
#include "../hadamard.hpp"
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N;
    cin >> N;
    vector<ModInt<998244353>> A(1 << N), B(1 << N);
    for (auto &x : A) cin >> x;
    for (auto &x : B) cin >> x;

    for (auto x : andconv(A, B)) cout << x << ' ';
}
