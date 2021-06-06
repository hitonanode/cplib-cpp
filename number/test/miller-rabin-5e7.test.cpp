#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A" // DUMMY
#include "../factorize.hpp"
#include "../sieve.hpp"
#include <cassert>
#include <cstdio>

int main() {
    int lim = 5e7;
    Sieve sieve(lim);
    for (int x = 1; x <= lim; x++) {
        bool is_prime_1 = (sieve.min_factor[x] == x);
        bool is_prime_2 = is_prime(x);
        assert(is_prime_1 == is_prime_2);
    }
    puts("Hello World");
}
