#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_totient_function"
#include "../../modint.hpp"
#include "../arithmetic_cumsum.hpp"
#include <iostream>
using namespace std;

int main() {
    long long N;
    cin >> N;
    cout << euler_phi_cumsum<ModInt<998244353>>(N).sum(N) << '\n';
}
