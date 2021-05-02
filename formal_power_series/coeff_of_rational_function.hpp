#pragma once
#include "../convolution/ntt.hpp"
#include <cassert>
#include <vector>

// CUT begin
// Calculate [x^N](num(x) / den(x))
// - Coplexity: O(LlgLlgN) ( L = size(num) + size(den) )
// - Reference: `Bostan–Mori algorithm` <https://qiita.com/ryuhe1/items/da5acbcce4ac1911f47a>
template <typename Tp> Tp coefficient_of_rational_function(long long N, std::vector<Tp> num, std::vector<Tp> den) {
    assert(N >= 0);
    while (den.size() and den.back() == 0) den.pop_back();
    assert(den.size());
    int h = 0;
    while (den[h] == 0) h++;
    N += h;
    den.erase(den.begin(), den.begin() + h);

    if (den.size() == 1) {
        assert(N < int(num.size()));
        return num[N] / den[0];
    }

    while (N) {
        std::vector<Tp> g = den;
        for (size_t i = 1; i < g.size(); i += 2) { g[i] = -g[i]; }
        auto conv_num_g = nttconv(num, g);
        num.resize((conv_num_g.size() + 1 - (N & 1)) / 2);
        for (size_t i = 0; i < num.size(); i++) { num[i] = conv_num_g[i * 2 + (N & 1)]; }
        auto conv_den_g = nttconv(den, g);
        for (size_t i = 0; i < den.size(); i++) { den[i] = conv_den_g[i * 2]; }
        N >>= 1;
    }
    return num[0] / den[0];
}

// Find the n-th term of the sequence (0-ORIGIN)
// Complexity: O(K lg K \log N)
// ainit = [a_0, a_1,..., ]
// c[0] = 1, \sum_j a_{i - j} * c_j = 0
template <typename Tp> Tp find_kth_term(std::vector<Tp> ainit, const std::vector<Tp> c, long long n) {
    assert(ainit.size() + 1 == c.size());
    auto a = nttconv(ainit, c);
    a.resize(ainit.size());
    return coefficient_of_rational_function(n, a, c);
}
