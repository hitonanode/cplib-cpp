#include "../sieve.hpp"
#include <iostream>
#include <vector>
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_1_C"
using namespace std;

int main() {
    Sieve sieve(10000);
    int N;
    cin >> N;
    int ret = 0;
    while (N--) {
        int x;
        cin >> x;
        bool flg = true;
        for (auto p : sieve.primes)
            if (x % p == 0 and x != p) {
                flg = false;
                break;
            }
        ret += flg;
    }
    cout << ret << '\n';
}
