#define PROBLEM "https://judge.yosupo.jp/problem/subset_convolution"
#include "convolution/subset_convolution.hpp"
#include "modulus/modint_fixed.hpp"
#include <iostream>

int main()
{
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int N;
    std::cin >> N;
    std::vector<ModInt<998244353>> A(1 << N), B(1 << N);
    for (auto &x : A) std::cin >> x;
    for (auto &x : B) std::cin >> x;

    for (auto x : subset_convolution(A, B)) std::cout << x << ' ';
}
