#pragma once
#include <algorithm>
#include <cmath>
#include <vector>

// CUT begin
struct CountPrimes {
    // Count Primes less than or equal to x (\pi(x)) for each x = N / i (i = 1, ..., N) in O(N^(2/3)) time
    // Learned this algorihtm from https://old.yosupo.jp/submission/14650
    // Reference: https://min-25.hatenablog.com/entry/2018/11/11/172216
    using Int = long long;
    Int n, n2, n3, n6;
    std::vector<int> is_prime; // [0, 0, 1, 1, 0, 1, 0, 1, ...]
    std::vector<Int> primes;   // primes up to O(N^(1/2)), [2, 3, 5, 7, ...]

    int s;               // size of vs
    std::vector<Int> vs; // [N, ..., n2, n2 - 1, n2 - 2, ..., 3, 2, 1]
    std::vector<Int> pi; // pi[i] = (# of primes s.t. <= vs[i]) is finally obtained

    std::vector<int> _fenwick;

    int getidx(Int a) const {
        return a <= n2 ? s - a : n / a - 1;
    } // vs[i] >= a を満たす最大の i を返す

    void _fenwick_rec_update(
        int i, Int cur,
        bool first) { // pi[n3:] に対して cur * (primes[i] 以上の素因数) の数の寄与を減じる
        if (!first) {
            for (int x = getidx(cur) - n3; x >= 0; x -= (x + 1) & (-x - 1)) _fenwick[x]--;
        }
        for (int j = i; cur * primes[j] <= vs[n3]; j++)
            _fenwick_rec_update(j, cur * primes[j], false);
    }

    CountPrimes(Int n_) : n(n_), n2((Int)sqrtl(n)), n3((Int)cbrtl(n)), n6((Int)sqrtl(n3)) {
        is_prime.assign(n2 + 300, 1),
            is_prime[0] = is_prime[1] = 0; // `+ 300`: https://en.wikipedia.org/wiki/Prime_gap
        for (size_t p = 2; p < is_prime.size(); p++) {
            if (is_prime[p]) {
                primes.push_back(p);
                for (size_t j = p * 2; j < is_prime.size(); j += p) is_prime[j] = 0;
            }
        }
        for (Int now = n; now; now = n / (n / now + 1))
            vs.push_back(
                now); // [N, N / 2, ..., 1], Relevant integers (decreasing) length ~= 2sqrt(N)
        s = vs.size();

        // pi[i] = (# of integers x s.t. x <= vs[i],  (x is prime or all factors of x >= p))
        // pre = (# of primes less than p)
        // 最小の素因数 p = 2, ..., について篩っていく
        pi.resize(s);
        for (int i = 0; i < s; i++) pi[i] = vs[i] - 1;
        int pre = 0;

        auto trans = [&](int i, Int p) { pi[i] -= pi[getidx(vs[i] / p)] - pre; };

        size_t ip = 0;

        // [Sieve Part 1] For each prime p satisfying p <= N^(1/6) (Only O(N^(1/6) / log N) such primes exist),
        //                O(sqrt(N)) simple operation is conducted.
        // - Complexity of this part: O(N^(2/3) / logN)
        for (; primes[ip] <= n6; ip++, pre++) {
            const auto &p = primes[ip];
            for (int i = 0; p * p <= vs[i]; i++) trans(i, p);
        }

        // [Sieve Part 2] For each prime p satisfying N^(1/6) < p <= N^(1/3),
        //                point-wise & Fenwick tree-based hybrid update is used
        // - first N^(1/3) elements are simply updated by quadratic algorithm.
        // - Updates of latter segments are managed by Fenwick tree.
        // - Complexity of this part: O(N^(2/3)) (O(N^(2/3)/log N) operations for Fenwick tree (O(logN) per query))
        _fenwick.assign(s - n3, 0); // Fenwick tree, inversed order (summation for upper region)
        auto trans2 = [&](int i, Int p) {
            int j = getidx(vs[i] / p);
            auto z = pi[j];
            if (j >= n3) {
                for (j -= n3; j < int(_fenwick.size()); j += (j + 1) & (-j - 1)) z += _fenwick[j];
            }
            pi[i] -= z - pre;
        };
        for (; primes[ip] <= n3; ip++, pre++) {
            const auto &p = primes[ip];
            for (int i = 0; i < n3 and p * p <= vs[i]; i++)
                trans2(i, p); // upto n3, total trans2 times: O(N^(2/3) / logN)
            _fenwick_rec_update(ip, primes[ip], true); // total update times: O(N^(2/3) / logN)
        }
        for (int i = s - n3 - 1; i >= 0; i--) {
            int j = i + ((i + 1) & (-i - 1));
            if (j < s - n3) _fenwick[i] += _fenwick[j];
        }
        for (int i = 0; i < s - n3; i++) pi[i + n3] += _fenwick[i];

        // [Sieve Part 3] For each prime p satisfying N^(1/3) < p <= N^(1/2), use only simple updates.
        // - Complexity of this part: O(N^(2/3) / logN)
        //     \sum_i (# of factors of vs[i] of the form p^2, p >= N^(1/3)) = \sum_{i=1}^{N^(1/3)} \pi(\sqrt(vs[i])))
        //                                                                  = sqrt(N) \sum_i^{N^(1/3)}
        //                                                                  i^{-1/2} / logN = O(N^(2/3) / logN)
        //     (Note: \sum_{i=1}^{N} i^{-1/2} = O(sqrt N)
        //     https://math.stackexchange.com/questions/2600796/finding-summation-of-inverse-of-square-roots )
        for (; primes[ip] <= n2; ip++, pre++) {
            const auto &p = primes[ip];
            for (int i = 0; p * p <= vs[i]; i++) trans(i, p);
        }
    }
};
