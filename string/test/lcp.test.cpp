#include "../suffix_array_doubling.hpp"
#define PROBLEM "https://judge.yosupo.jp/problem/number_of_substrings"
#include <iostream>
#include <string>

int main() {
    std::string S;
    std::cin >> S;
    SuffixArray<decltype(S)> sa(S, true);

    long long ret = (long long)S.length() * (S.length() + 1) / 2;
    std::cout << ret - std::accumulate(sa.lcp.begin(), sa.lcp.end(), 0LL) << '\n';
}
