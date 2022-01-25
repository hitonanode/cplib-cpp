#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A" // DUMMY
#include "../min_max_semiring.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>

template <class T> void test_min_max_semiring() {
    using R = min_max_semiring<T>;
    for (int x = -100; x <= 100; ++x) {
        for (int y = -100; y <= 100; ++y) {
            T Tx = x, Ty = y;
            assert(R(Tx) + R(Ty) == std::min(Tx, Ty));
            assert(!(R(Tx) + R(Ty) != std::min(Tx, Ty)));
            assert(R(Tx) * R(Ty) == std::max(Tx, Ty));
            assert(!(R(Tx) * R(Ty) != std::max(Tx, Ty)));

            R A = R(Tx), B = R(Tx);
            A += R(Ty);
            B *= R(Ty);
            assert(A == R(std::min(Tx, Ty)));
            assert(B == R(std::max(Tx, Ty)));
        }
    }
}

int main() {
    test_min_max_semiring<int>();
    test_min_max_semiring<long long>();
    test_min_max_semiring<double>();
    test_min_max_semiring<long double>();
    std::cout << "Hello World\n";
}
