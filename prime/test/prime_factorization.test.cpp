#include <iostream>
#include <vector>
#include "prime/prime.hpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_A"
using namespace std;

int main()
{
    vector<int> primes = gen_primes(40000);
    int N;
    cin >> N;
    map<lint, int> factors = prime_factorization(N, primes);
    cout << N << ":";
    for (auto factor : factors)
    {
        for (int i = 0; i < factor.second; i++)
        {
            cout << " " << factor.first;
        }
    }
    cout << endl;
}
