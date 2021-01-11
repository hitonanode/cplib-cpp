#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_primes"
#include "../bs_sieve.hpp"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N, A, B;
    cin >> N >> A >> B;
    BitsetSieve<500000001> sieve(N);
    vector<int> ret;
    for (unsigned i = 0; A * i + B < sieve.primes.size(); i++) ret.push_back(sieve.primes[A * i + B]);
    cout << sieve.primes.size() << ' ' << ret.size() << '\n';
    for (auto p : ret) cout << p << ' ';
    cout << '\n';
}
