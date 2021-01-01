#include "../factorize.hpp"
#define PROBLEM "https://yukicoder.me/problems/1967"
#include <iostream>

int main() {
    int Q;
    std::cin >> Q;
    while (Q--) {
        long long n;
        std::cin >> n;
        std::cout << n << ' ' << is_prime(n) << '\n';
    }
}
