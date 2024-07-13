#define PROBLEM "https://judge.yosupo.jp/problem/rational_approximation"
#include "../rational_approximation.hpp"

#include <cassert>
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int T;
    cin >> T;
    while (T--) {
        int N, x, y;
        cin >> N >> x >> y;
        const auto [l, r] = rational_approximation<int>(N, x, y);
        const auto [lnum, lden] = l;
        const auto [rnum, rden] = r;
        cout << lnum << ' ' << lden << ' ' << rnum << ' ' << rden << '\n';
    }
}
