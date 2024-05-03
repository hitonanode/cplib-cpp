#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product_mod_2"
#include "../linalg_bitset.hpp"

#include <algorithm>
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

    int N, M, K;
    cin >> N >> M >> K;

    vector<BS> A(N), B(M);
    for (auto &v : A) {
        string s;
        cin >> s;
        std::reverse(s.begin(), s.end()); // bitset に文字列 s を与えると s[0] が最高位になるので反転
        v = BS(s);
    }

    for (auto &v : B) {
        string s;
        cin >> s;
        std::reverse(s.begin(), s.end());
        v = BS(s);
    }

    auto C = f2_matmul<dim, dim>(A, B);
    for (const auto &v : C) {
        auto tmp = v.to_string();
        std::reverse(tmp.begin(), tmp.end());
        cout << tmp.substr(0, K) << '\n';
    }
}
