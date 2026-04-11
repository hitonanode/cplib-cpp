#pragma once
#include <algorithm>
#include <cassert>
#include <numeric>
#include <type_traits>
#include <vector>

// Decompose {ax + b mod M (0 <= x < n)}
template <class Int> struct ModOfLinear {
    struct Linear {
        Int f0;
        Int df;
        Int len;
        Int num_repeat;
    };

    using Long =
        std::conditional_t<std::is_same_v<Int, int>, long long,
                           std::conditional_t<std::is_same_v<Int, long long>, __int128, void>>;

    // Decompose multiset {(a * i + b) % m for i = 0, ..., (n - 1)} into multisets.
    // Each decomposed one is arithmetic progression
    // Complexity: O(sqrt(m))
    // https://codeforces.com/blog/entry/141889
    // Verified: https://atcoder.jp/contests/abc429/tasks/abc429_g
    static std::vector<Linear> decompose(Int n, Int a, Int b, Int m) {
        assert(0 <= n);
        assert(0 < m);
        a = (a % m + m) % m;
        b = (b % m + m) % m;

        if (n == 0) return {};
        if (a == 0) return {Linear{b, 0, n, 1}};

        std::vector<Linear> ret;

        if (const Int g = std::gcd(m, a), T = m / g; n >= T) {
            ret.push_back(Linear{b % g, g, T, n / T});
            n %= T;
        }

        auto eval_step = [&](Int step) -> Long {
            const Int s = std::min(Long(m - a) * step % m, Long(a) * step % m);
            const Int t = s ? m / s : n;
            return Long(step) * (((n + step - 1) / step + t - 1) / t);
        };

        Int best_step = 1;
        Long best_eval = eval_step(1);

        for (Int step = 2; step < n; ++step) {
            const auto e = eval_step(step);
            if (e < best_eval) best_eval = e, best_step = step;
            if ((Long)step * step > m) break;
        }

        for (Int head = 0; head < best_step; ++head) {
            for (Int i = head; i < n;) {
                const Int ai = (Long(a) * i + b) % m;
                const Int a_next = (Long(a) * (i + best_step) + b) % m;
                const Int diff = a_next - ai;

                Int len = 1 + (n - 1 - i) / best_step;
                if (diff > 0) len = std::min(len, 1 + (m - 1 - ai) / diff);
                if (diff < 0) len = std::min(len, 1 + ai / (-diff));

                ret.push_back(Linear{ai, diff, len, 1});
                i += len * best_step;
            }
        }

        return ret;
    }
};
