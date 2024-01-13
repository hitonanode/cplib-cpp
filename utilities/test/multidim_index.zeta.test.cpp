#define PROBLEM "https://judge.yosupo.jp/problem/bitwise_and_convolution"
#include "../../modint.hpp"
#include "../multidim_index.hpp"

#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N;
    cin >> N;

    multidim_index mi(std::vector<int>(N, 2));
    vector<ModInt<998244353>> A(1 << N), B(1 << N);

    for (auto &x : A) cin >> x;
    for (auto &x : B) cin >> x;
    mi.superset_sum(A);
    mi.superset_sum(B);
    for (int i = 0; i < 1 << N; ++i) A.at(i) *= B.at(i);
    mi.superset_sum_inv(A);

    for (auto x : A) cout << x << ' ';
}
