#define PROBLEM "https://judge.yosupo.jp/problem/system_of_linear_equations"
#include "../../modint.hpp"
#include "../system_of_linear_equations.hpp"
#include <iostream>
using mint = ModInt<998244353>;

int main() {
    int N, M;
    std::cin >> N >> M;
    matrix<mint> A(N, M);
    std::cin >> A;
    std::vector<mint> b(N);
    for (auto &x : b) std::cin >> x;
    auto ret = system_of_linear_equations(A, b);
    if (ret.first.empty())
        std::cout << -1 << "\n";
    else {
        std::cout << ret.second.size() << "\n";
        for (auto x : ret.first) std::cout << x << " ";
        std::cout << "\n";

        for (auto vec : ret.second) {
            for (auto e : vec) std::cout << e << " ";
            std::cout << "\n";
        }
    }
}
