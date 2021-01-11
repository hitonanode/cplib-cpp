#pragma once
#include <algorithm>
#include <bitset>
#include <cassert>
#include <vector>

// CUT begin
// Complexity: O(N log log N):
// - N = 10^7:  8 /  6 MB,   62 /  81 ms (Codeforces / AtCoder, GCC C++17)
// - N = 10^8: 61 / 44 MB, 1481 / 866 ms (Codeforces / AtCoder, GCC C++17)
template <int LIMN> struct BitsetSieve {
    std::vector<int> primes;
    std::bitset<LIMN + 1> is_prime;
    const int maxN;
    BitsetSieve(int MAXN = LIMN) : maxN(MAXN) {
        is_prime.set();
        is_prime.reset(0), is_prime.reset(1);
        for (int p = 2; p <= MAXN; p++) {
            if (is_prime[p]) {
                primes.push_back(p);
                for (int j = p * 2; j <= MAXN; j += p) is_prime[j] = 0;
            }
        }
    }
    // Count primes less than or equal to x
    int prime_counting(int x) {
        assert(x <= maxN);
        return std::distance(primes.begin(), std::upper_bound(primes.begin(), primes.end(), x));
    }
};
