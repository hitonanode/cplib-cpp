#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_mod"
#include "../sqrt_mod.hpp"

#include <iostream>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int Y, P;
        cin >> Y >> P;
        cout << sqrt_mod<int>(Y, P) << '\n';
    }
}
