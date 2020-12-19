#define PROBLEM "https://judge.yosupo.jp/problem/counting_primes"
#include "../count_primes.hpp"
#include <iostream>

int main() {
    long long N;
    std::cout << CountPrimes((std::cin >> N, N)).pi[0] << '\n';
}
