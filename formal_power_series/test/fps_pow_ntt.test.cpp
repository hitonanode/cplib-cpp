#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_formal_power_series"
#include "formal_power_series/fps_nttmodint.hpp"
#include "modint.hpp"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int N;
    cin >> N;
    long long M;
    cin >> M;

    vector<ModInt<998244353>> A(N);
    for (auto &x : A) cin >> x;

    for (auto x : fps_nttmod::pow(A, M)) cout << x << ' ';
    cout << '\n';
}
