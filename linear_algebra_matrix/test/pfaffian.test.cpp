#define PROBLEM "https://judge.yosupo.jp/problem/pfaffian_of_matrix"

#include "../pfaffian.hpp"

#include <iostream>
#include <vector>

#include <atcoder/modint>

using namespace std;
using mint = atcoder::modint998244353;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N;
    cin >> N;
    vector A(N * 2, vector<mint>(N * 2));
    for (auto &v : A) {
        for (auto &x : v) {
            int tmp;
            cin >> tmp;
            x = tmp;
        }
    }

    cout << Pfaffian(A).val() << '\n';
}
