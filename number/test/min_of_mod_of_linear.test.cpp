#define PROBLEM "https://judge.yosupo.jp/problem/min_of_mod_of_linear"

#include "../min_of_mod_of_linear.hpp"
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int T;
    cin >> T;
    while (T--) {
        int n, m, a, b;
        cin >> n >> m >> a >> b;
        cout << min_of_mod_of_linear<int, long long>(n, m, a, b).back().min() << '\n';
    }
}
