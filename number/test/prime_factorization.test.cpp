#include "../sieve.hpp"
#include <iostream>
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_A"
using namespace std;

int main() {
    Sieve sieve(1 << 15);
    int N;
    cin >> N;
    map<long long int, int> factors = sieve.factorize<long long>(N);
    cout << N << ':';
    for (auto p : factors) {
        while (p.second--) cout << ' ' << p.first;
    }
    cout << '\n';
}
