#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_B"
#include "../pow.hpp"
#include "../../modint.hpp"
#include "../pow_sum.hpp"
#include <cassert>
#include <iostream>
using namespace std;

int main() {
    ModInt<1000000007> M;
    int N;
    cin >> M >> N;
    auto ret = pow(M, N);
    assert(pow_sum(M, N).first == ret);
    assert((pow_sum(M, N).second) * (M - 1) + 1 == ret);

    cout << ret << '\n';
}
