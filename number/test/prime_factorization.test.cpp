#include "number/eratosthenes.hpp"
#include <iostream>
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_A"
using namespace std;

int main()
{
    SieveOfEratosthenes sieve(40000);
    int N;
    cin >> N;
    map<long long int, int> factors = sieve.Factorize(N);
    cout << N << ":";
    for (auto p : factors) {
        while (p.second--) cout << " " << p.first;
    }
    cout << endl;
}
