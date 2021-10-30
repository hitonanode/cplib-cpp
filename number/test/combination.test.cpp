#define PROBLEM "https://judge.yosupo.jp/problem/binomial_coefficient"
#include "../combination.hpp"
#include "../sieve.hpp"
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int T, m;
    cin >> T >> m;
    combination nCr(Sieve(1 << 15).factorize(m));
    while (T--) {
        long long n, r;
        cin >> n >> r;
        cout << nCr(n, r) << '\n';
    }
}
