#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det_mod_2"
#include "../linalg_bitset.hpp"

#include <bitset>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    constexpr int dim = 1 << 12;
    using BS = bitset<dim>;

    int N;
    cin >> N;
    vector<BS> mat(N);
    for (auto &v : mat) {
        string s;
        cin >> s;
        v = BS(s);
    }

    cout << f2_determinant<dim>(mat) << '\n';
}
