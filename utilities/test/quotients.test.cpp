#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_quotients"
#include "../quotients.hpp"

#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    long long N;
    cin >> N;

    auto ret = get_quotients(N);
    cout << ret.size() << '\n';
    for (auto x : ret) cout << x << ' ';
    cout << '\n';
}
