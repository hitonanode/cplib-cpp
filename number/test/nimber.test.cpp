#define PROBLEM "https://judge.yosupo.jp/problem/nim_product_64"
#include "../nimber.hpp"
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        Nimber A, B;
        cin >> A >> B;
        cout << A * B << '\n';
    }
}
