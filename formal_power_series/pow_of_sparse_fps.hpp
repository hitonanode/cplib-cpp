#pragma once
#include <algorithm>
#include <cassert>
#include <tuple>
#include <utility>
#include <vector>

// Calculate f(x)^k up to x^N
// Requirement: k > 0
// Complexity: O(NM) (M : num. of nonzero coefficients of f(x))
template <class T> std::vector<T> pow_of_sparse_fps(const std::vector<T> &f, int N, long long k) {
    assert(k > 0);
    std::vector<std::pair<int, T>> nonzero_terms;
    int d0 = 0;
    while (d0 < int(f.size()) and d0 <= N and f[d0] == T()) ++d0;
    if (d0 == int(f.size()) or d0 > N) return std::vector<T>(N + 1);

    if (d0 and N / d0 < k) return std::vector<T>(N + 1);

    for (int d = d0; d < std::min<int>(N + 1, f.size()); ++d) {
        if (f[d] != T()) nonzero_terms.emplace_back(d - d0, f[d]);
    }

    int Ncalc = N - d0 * k;

    std::vector<T> ret(Ncalc + 1);
    ret[0] = f[d0].pow(k);
    for (int d = 0; d + 1 < int(ret.size()); ++d) {
        // Compare [x^d](k f'g - fg')
        T tmp = T();
        int i, j;
        T fi;
        for (auto i_fi : nonzero_terms) {
            std::tie(i, fi) = i_fi;
            if (!i) continue;
            j = d - i;
            if (0 <= j) tmp -= fi * ret[j + 1] * (j + 1);
            j = d - (i - 1);
            if (0 <= j) tmp += fi * i * ret[j] * T(k);
        }
        ret[d + 1] = tmp / (f[d0] * (d + 1));
    }

    ret.resize(N + 1, T());
    std::rotate(ret.begin(), ret.end() - d0 * k, ret.end());
    return ret;
}
