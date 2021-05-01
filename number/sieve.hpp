#pragma once
#include <cassert>
#include <map>
#include <vector>

// CUT begin
// Linear sieve algorithm for fast prime factorization
// Complexity: O(N) time, O(N) space:
// - MAXN = 10^7:  ~44 MB,  80~100 ms (Codeforces / AtCoder GCC, C++17)
// - MAXN = 10^8: ~435 MB, 810~980 ms (Codeforces / AtCoder GCC, C++17)
// Reference:
// [1] D. Gries, J. Misra, "A Linear Sieve Algorithm for Finding Prime Numbers,"
//     Communications of the ACM, 21(12), 999-1003, 1978.
// - https://cp-algorithms.com/algebra/prime-sieve-linear.html
// - https://37zigen.com/linear-sieve/
struct Sieve {
    std::vector<int> min_factor;
    std::vector<int> primes;
    Sieve(int MAXN) : min_factor(MAXN + 1) {
        for (int d = 2; d <= MAXN; d++) {
            if (!min_factor[d]) {
                min_factor[d] = d;
                primes.emplace_back(d);
            }
            for (const auto &p : primes) {
                if (p > min_factor[d] or d * p > MAXN) break;
                min_factor[d * p] = p;
            }
        }
    }
    // Prime factorization for 1 <= x <= MAXN^2
    // Complexity: O(log x)           (x <= MAXN)
    //             O(MAXN / log MAXN) (MAXN < x <= MAXN^2)
    template <typename T> std::map<T, int> factorize(T x) {
        std::map<T, int> ret;
        assert(x > 0 and x <= ((long long)min_factor.size() - 1) * ((long long)min_factor.size() - 1));
        for (const auto &p : primes) {
            if (x < T(min_factor.size())) break;
            while (!(x % p)) x /= p, ret[p]++;
        }
        if (x >= T(min_factor.size())) ret[x]++, x = 1;
        while (x > 1) ret[min_factor[x]]++, x /= min_factor[x];
        return ret;
    }
    // Enumerate divisors of 1 <= x <= MAXN^2
    // Be careful of highly composite numbers <https://oeis.org/A002182/list> <https://gist.github.com/dario2994/fb4713f252ca86c1254d#file-list-txt>:
    // (n, (# of div. of n)): 45360->100, 735134400(<1e9)->1344, 963761198400(<1e12)->6720
    template <typename T> std::vector<T> divisors(T x) {
        std::vector<T> ret{1};
        for (const auto p : factorize(x)) {
            int n = ret.size();
            for (int i = 0; i < n; i++) {
                for (T a = 1, d = 1; d <= p.second; d++) {
                    a *= p.first;
                    ret.push_back(ret[i] * a);
                }
            }
        }
        return ret; // NOT sorted
    }
    // Moebius function Table, (-1)^{# of different prime factors} for square-free x
    // return: [0=>0, 1=>1, 2=>-1, 3=>-1, 4=>0, 5=>-1, 6=>1, 7=>-1, 8=>0, ...] <https://oeis.org/A008683>
    std::vector<int> GenerateMoebiusFunctionTable() {
        std::vector<int> ret(min_factor.size());
        for (unsigned i = 1; i < min_factor.size(); i++) {
            if (i == 1)
                ret[i] = 1;
            else if ((i / min_factor[i]) % min_factor[i] == 0)
                ret[i] = 0;
            else
                ret[i] = -ret[i / min_factor[i]];
        }
        return ret;
    }
    // Calculate [0^K, 1^K, ..., nmax^K] in O(nmax)
    template <typename MODINT> std::vector<MODINT> enumerate_kth_pows(long long K, int nmax) {
        assert(nmax < int(min_factor.size()));
        std::vector<MODINT> ret(nmax + 1);
        ret[0] = 0, ret[1] = 1;
        for (int n = 2; n <= nmax; n++) {
            if (min_factor[n] == n) {
                ret[n] = MODINT(n).pow(K);
            } else {
                ret[n] = ret[n / min_factor[n]] * ret[min_factor[n]];
            }
        }
        return ret;
    }
};
// Sieve sieve(1 << 15);  // (can factorize n <= 10^9)
