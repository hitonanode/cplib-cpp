#include <algorithm>
#include <iostream>
#include <vector>
#include "prime/prime.hpp"
#define PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_1_C
using namespace std;

int main()
{
    vector<int> primes = gen_primes(10000);
    int N;
    cin >> N;
    int ret = 0;
    for (int i = 0; i < N; i++)
    {
        int x;
        cin >> x;
        ret += binary_search(primes.begin(), primes.end(), x);
    }
    cout << ret << endl;
}
