#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_mod"
#include "number/modint_runtime.hpp"
#include <iostream>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int Y, P;
        cin >> Y >> P;
        ModIntRuntime::set_mod(P);
        ModIntRuntime m = Y;
        if (Y) {
            m = m.sqrt();
            cout << (m ? m.val : -1) << endl;
        } else
            cout << 0 << endl;
    }
}
