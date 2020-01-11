#include "number/eratosthenes.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_1_C"
using namespace std;

int main()
{
    SieveOfEratosthenes sieve(10000);
    int N;
    cin >> N;
    int ret = 0;
    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;
        bool flg = true;
        for (auto p : sieve.primes) if (x % p == 0 and x != p) {
            flg = false;
            break;
        }
        ret += flg;
    }
    cout << ret << endl;
}
