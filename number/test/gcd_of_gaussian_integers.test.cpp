#define PROBLEM "https://judge.yosupo.jp/problem/gcd_of_gaussian_integers"

#include "../gaussian_integer.hpp"

#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int T;
    cin >> T;
    while (T--) {
        long long a, b, c, d;
        cin >> a >> b >> c >> d;
        GaussianInteger g1(a, b), g2(c, d);
        const auto g = gcd(g1, g2);
        cout << g.x << " " << g.y << "\n";
    }
}
