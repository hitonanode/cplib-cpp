#define PROBLEM "https://judge.yosupo.jp/problem/discrete_logarithm_mod"
#include "../discrete_logarithm.hpp"

#include <iostream>
using namespace std;

int X, Y, M;

int mp(int x, int y) { return (long long)x * y % M; }

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        cin >> X >> Y >> M;
        cout << DiscreteLogarithmMod<long long>(X, Y, M) << '\n';
    }
}
