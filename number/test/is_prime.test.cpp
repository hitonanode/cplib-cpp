#define PROBLEM "https://judge.yosupo.jp/problem/primality_test"
#include "../factorize.hpp"

#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int Q;
    cin >> Q;
    while (Q--) {
        unsigned long long N;
        cin >> N;
        cout << (is_prime(N) ? "Yes" : "No") << '\n';
    }
}
