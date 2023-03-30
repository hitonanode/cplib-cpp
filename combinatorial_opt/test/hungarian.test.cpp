#define PROBLEM "https://judge.yosupo.jp/problem/assignment"
#include "../hungarian.hpp"

#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int n;
    cin >> n;
    vector<vector<long long>> a(n, vector<long long>(n));
    for (auto &vec : a) {
        for (auto &x : vec) cin >> x;
    }
    auto [val, sol] = hungarian<long long>(a);
    cout << val << '\n';
    for (auto x : sol) cout << x << ' ';
    cout << '\n';
}
