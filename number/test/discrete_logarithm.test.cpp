#define PROBLEM "https://judge.yosupo.jp/problem/discrete_logarithm_mod"
#include "number/discrete_logarithm.hpp"
#include <iostream>

int main() {
    int T;
    std::cin >> T;
    while (T--) {
        int X, Y, M;
        std::cin >> X >> Y >> M;
        DiscreteLogarithm dl(M, X);
        std::cout << dl.log(Y) << std::endl;
    }
}
