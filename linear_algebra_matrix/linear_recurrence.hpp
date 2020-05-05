#pragma once
#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

// CUT begin
// Berlekamp–Massey algorithm
// <https://en.wikipedia.org/wiki/Berlekamp%E2%80%93Massey_algorithm>
// Complexity: O(N^2)
// input: S = sequence from field K
// return: L          = degree of minimal polynomial,
//         C_reversed = monic min. polynomial (size = L + 1, reversed order, C_reversed[0] = 1))
// Formula: convolve(S, C_reversed)[i] = 0 for i >= L
// Example:
// - [1, 2, 4, 8, 16]   -> (1, [1, -2])
// - [1, 1, 2, 3, 5, 8] -> (2, [1, -1, -1])
// - [0, 0, 0, 0, 1]    -> (5, [1, 0, 0, 0, 0, 998244352]) (mod 998244353)
// - []                 -> (0, [1])
// - [0, 0, 0]          -> (0, [1])
// - [-2]               -> (1, [1, 2])
template <typename _Tfield>
std::pair<int, std::vector<_Tfield>> linear_recurrence(const std::vector<_Tfield> &S)
{
    int N = S.size();
    using poly = std::vector<_Tfield>;
    poly C_reversed{1}, B{1};
    int L = 0, m = 1;
    _Tfield b = 1;

    // adjust: C(x) <- C(x) - (d / b) x^m B(x)
    auto adjust = [](poly C, const poly &B, _Tfield d, _Tfield b, int m) -> poly {
        C.resize(std::max(C.size(), B.size() + m));
        _Tfield a = d / b;
        for (unsigned i = 0; i < B.size(); i++) C[i + m] -= a * B[i];
        return C;
    };

    for (int n = 0; n < N; n++) {
        _Tfield d = S[n];
        for (int i = 1; i <= L; i++) d += C_reversed[i] * S[n - i];

        if (d == 0) m++;
        else if (2 * L <= n) {
            poly T = C_reversed;
            C_reversed = adjust(C_reversed, B, d, b, m);
            L = n + 1 - L;
            B = T;
            b = d;
            m = 1;
        }
        else C_reversed = adjust(C_reversed, B, d, b, m++);
    }
    return std::make_pair(L, C_reversed);
}


// Calculate x^N mod f(x)
// Known as `Kitamasa method`
// Input: f_reversed: monic, reversed (f_reversed[0] = 1)
// Complexity: O(K^2 lgN) (K: deg. of f)
// Example: (4, [1, -1, -1]) -> [2, 3]
//          ( x^4 = (x^2 + x + 2)(x^2 - x - 1) + 3x + 2 )
// Reference: <http://misawa.github.io/others/fast_kitamasa_method.html>
//            <http://sugarknri.hatenablog.com/entry/2017/11/18/233936>
template <typename _Tfield>
std::vector<_Tfield> monomial_mod_polynomial(long long N, const std::vector<_Tfield> &f_reversed)
{
    assert(!f_reversed.empty() and f_reversed[0] == 1);
    int K = f_reversed.size() - 1;
    if (!K) return {};
    int D = 64 - __builtin_clzll(N);
    std::vector<_Tfield> ret(K, 0);
    ret[0] = 1;
    auto self_conv = [](std::vector<_Tfield> x) -> std::vector<_Tfield> {
        int d = x.size();
        std::vector<_Tfield> ret(d * 2 - 1);
        for (int i = 0; i < d; i++)
        {
            ret[i * 2] += x[i] * x[i];
            for (int j = 0; j < i; j++) ret[i + j] += x[i] * x[j] * 2;
        }
        return ret;
    };
    for (int d = D; d--;)
    {
        ret = self_conv(ret);
        for (int i = 2 * K - 2; i >= K; i--)
        {
            for (int j = 1; j <= K; j++) ret[i - j] -= ret[i] * f_reversed[j];
        }
        ret.resize(K);
        if ((N >> d) & 1)
        {
            std::vector<_Tfield> c(K);
            c[0] = -ret[K - 1] * f_reversed[K];
            for (int i = 1; i < K; i++)
            {
                c[i] = ret[i - 1] - ret[K - 1] * f_reversed[K - i];
            }
            ret = c;
        }
    }
    return ret;
}
