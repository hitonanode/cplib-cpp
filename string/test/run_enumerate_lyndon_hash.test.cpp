#include "../lyndon_factorization.hpp"
#include "../rolling_hash_1d.hpp"
#include <iostream>
#include <string>
#define PROBLEM "https://judge.yosupo.jp/problem/runenumerate"
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    string S;
    cin >> S;
    auto ret = run_enumerate<rolling_hash<DoubleHash>>(S);
    cout << ret.size() << '\n';
    for (auto p : ret) cout << get<0>(p) << ' ' << get<1>(p) << ' ' << get<2>(p) << '\n';
}
