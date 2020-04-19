#pragma once
#include <algorithm>
#include <utility>
#include <vector>

// CUT begin
// Berlekamp–Massey algorithm
// <https://en.wikipedia.org/wiki/Berlekamp%E2%80%93Massey_algorithm>
// Complexity: O(N^2)
// input: S = sequence from field K
// return: (L=degree of minimal polynomial, C=min. poly.(size = L + 1, C[0] = 1))
// Formula: convolve(S, C)[i] = 0 for i >= L
// Example:
// - [1, 2, 4, 8, 16]   -> (1, [1, -2])
// - [1, 1, 2, 3, 5, 8] -> (2, [1, -1, -1])
// - [0, 0, 0, 0, 1]    -> (5, [1, 0, 0, 0, 0, 998244352]) (mod 998244353)
// - []                 -> (0, [1])
// - [0, 0, 0]          -> (0, [1])
// - [-2]               -> (1, [1, 2])
template <typename K>
std::pair<int, std::vector<K>> linear_recurrence(const std::vector<K> &S)
{
    int N = S.size();
    using poly = std::vector<K>;
    poly C{1}, B{1};
    int L = 0, m = 1;
    K b = 1;

    // adjust: C(x) <- C(x) - (d / b) x^m B(x)
    auto adjust = [](poly C, const poly &B, K d, K b, int m) -> poly {
        C.resize(std::max(C.size(), B.size() + m));
        K a = d / b;
        for (unsigned i = 0; i < B.size(); i++) C[i + m] -= a * B[i];
        return C;
    };

    for (int n = 0; n < N; n++) {
        K d = S[n];
        for (int i = 1; i <= L; i++) d += C[i] * S[n - i];

        if (d == 0) m++;
        else if (2 * L <= n) {
            poly T = C;
            C = adjust(C, B, d, b, m);
            L = n + 1 - L;
            B = T;
            b = d;
            m = 1;
        }
        else C = adjust(C, B, d, b, m++);
    }
    return std::make_pair(L, C);
}
