#include "linear_algebra_matrix/linear_recurrence.hpp"
#include "modint.hpp"
#define PROBLEM "https://judge.yosupo.jp/problem/find_linear_recurrence"
#include <iostream>

using mint = ModInt<998244353>;
int main()
{
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);
    int N;
    std::cin >> N;
    std::vector<mint> A(N);
    for (auto &a : A)
    {
        std::cin >> a;
    }
    auto [L, poly] = linear_recurrence(A);
    std::cout << L << '\n';
    for (int i = 1; i <= L; i++) std::cout << -poly[i] << ' ';
    std::cout << '\n';
}
