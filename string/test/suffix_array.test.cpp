#include "../suffix_array_doubling.hpp"
#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"
#include <iostream>
#include <string>

int main() {
    std::string S;
    std::cin >> S;
    SuffixArray<decltype(S)> sa(S, false);

    for (size_t i = 1; i <= S.length(); i++) std::cout << sa.SA[i] << ' ';
}
