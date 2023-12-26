#define PROBLEM "https://judge.yosupo.jp/problem/lyndon_factorization"
#include "../lyndon.hpp"

#include <iostream>
#include <string>
using namespace std;

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    string S;
    cin >> S;
    auto ret = lyndon_factorization(S);
    for (auto [l, len] : ret) cout << l << ' ';
    cout << S.size() << '\n';
}
