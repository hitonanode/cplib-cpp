#pragma once
#include <algorithm>
#include <unordered_map>
#include <utility>

// Calculate log_A B (MOD M) (baby-step gian-step)
// DiscreteLogarithm dl(M, A);
// lint ans = dl.log(B);
// Complexity: O(M^(3/2)) for each query
// Verified: <https://judge.yosupo.jp/problem/discrete_logarithm_mod>
// Constraints: 0 <= A < M, B < M, 1 <= M <= 1e9  (M is not limited to prime)
struct DiscreteLogarithm
{
    using lint = long long int;
    int M, stepsize;
    lint baby_a, giant_a, g;
    std::unordered_map<lint, int> baby_log_dict;

    lint inverse(lint a) {
        lint b = M / g, u = 1, v = 0;
        while (b) {
            lint t = a / b;
            a -= t * b; std::swap(a, b);
            u -= t * v; std::swap(u, v);
        }
        u %= M / g;
        return u >= 0 ? u : u + M / g;
    }

    DiscreteLogarithm(int mod, int a_new) : M(mod), baby_a(a_new % mod), giant_a(1) {
        g = 1;
        while (std::__gcd(baby_a, M / g) > 1) g *= std::__gcd(baby_a, M / g);
        stepsize = 32;  // lg(MAX_M)
        while (stepsize * stepsize < M / g) stepsize++;

        lint now = 1 % (M / g), inv_g = inverse(baby_a);
        for (int n = 0; n < stepsize; n++) {
            if (!baby_log_dict.count(now)) baby_log_dict[now] = n;
            (now *= baby_a) %= M / g;
            (giant_a *= inv_g) %= M / g;
        }
    }

    // log(): returns the smallest nonnegative x that satisfies a^x = b mod M, or -1 if there's no solution
    lint log(lint b) {
        b %= M;
        lint acc = 1 % M;
        for (int i = 0; i < stepsize; i++) {
            if (acc == b) return i;
            (acc *= baby_a) %= M;
        }
        if (b % g) return -1;  // No solution
        lint now = b * giant_a % (M / g);
        for (lint q = 1; q <= M / stepsize + 1; q++) {
            if (baby_log_dict.count(now)) return q * stepsize + baby_log_dict[now];
            (now *= giant_a) %= M / g;
        }
        return -1;
    }
};
