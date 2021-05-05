#pragma once
#include <numeric>
#include <vector>

// CUT begin
// Euler's totient function
// Complexity: O(NlgN)
std::vector<int> euler_phi_table(int N) {
    std::vector<int> ret(N + 1);
    std::iota(ret.begin(), ret.end(), 0);
    for (int p = 2; p <= N; p++) {
        if (ret[p] == p) {
            ret[p] = p - 1;
            for (int i = p * 2; i <= N; i += p) ret[i] = ret[i] / p * (p - 1);
        }
    }
    return ret;
}

// Euler's totient function
// Complexity: O(sqrtN)
// https://csacademy.com/contest/fii-code-2021-round-2/task/clown-fiesta/
// https://kopricky.github.io/code/Computation_Advanced/tetration.html
template <typename Int> Int euler_phi(Int n) {
    Int ret = n;
    if (n % 2 == 0) {
        ret /= 2;
        do { n /= 2; } while (n % 2 == 0);
    }
    if (n % 3 == 0) {
        ret = ret / 3 * 2;
        do { n /= 3; } while (n % 3 == 0);
    }
    for (Int i = 5; i * i <= n; i += 4) {
        if (n % i == 0) {
            ret = ret / i * (i - 1);
            do { n /= i; } while (n % i == 0);
        }
        i += 2;
        if (n % i == 0) {
            ret = ret / i * (i - 1);
            do { n /= i; } while (n % i == 0);
        }
    }
    if (n != 1) ret = ret / n * (n - 1);
    return ret;
}
