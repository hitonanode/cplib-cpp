#include "string/suffix_array.hpp"
#define PROBLEM "https://judge.yosupo.jp/problem/number_of_substrings"
#include <iostream>
#include <string>

int main()
{
    std::string S;
    std::cin >> S;
    SuffixArray<decltype(S)> sa(S, true);

    int N = S.length();
    long long int ret = 0;
    for (int i = 0; i < N; i++) ret += N - sa.SA[i + 1] - sa.lcp[i];
    std::cout << ret << std::endl;
}
