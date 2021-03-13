#pragma once
#include <string>
#include <vector>

// CUT begin
// Lyndon factorization based on Duval's algorithm
// **NOT VERIFIED YET**
// Reference:
// [1] K. T. Chen, R. H. Fox, R. C. Lyndon,
//     "Free Differential Calculus, IV. The Quotient Groups of the Lower Central Series,"
//     Annals of Mathematics, 81-95, 1958.
// [2] J. P. Duval, "Factorizing words over an ordered alphabet,"
//     Journal of Algorithms, 4(4), 363-381, 1983.
// - https://cp-algorithms.com/string/lyndon_factorization.html
// - https://qiita.com/nakashi18/items/66882bd6e0127174267a
template <typename T> std::vector<std::pair<int, int>> lyndon_factorization(const std::vector<T> &S) {
    const int N = S.size();
    std::vector<std::pair<int, int>> ret;
    for (int l = 0; l < N;) {
        int i = l, j = i + 1;
        while (j < N and S[i] <= S[j]) i = (S[i] == S[j] ? i + 1 : l), j++;
        ret.emplace_back(l, j - i), l += j - i;
    }
    return ret;
}

std::vector<std::pair<int, int>> lyndon_factorization(const std::string &s) {
    const int N = int(s.size());
    std::vector<int> v(N);
    for (int i = 0; i < N; i++) v[i] = s[i];
    return lyndon_factorization<int>(v);
}
