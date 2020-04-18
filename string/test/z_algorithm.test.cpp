#include "string/z_algorithm.hpp"
#include <cstdio>
#include <iostream>
#include <string>
#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

int main()
{
    std::string S;
    std::cin >> S;
    for (auto x : z_algorithm(S))
    {
        printf("%d ", x);
    }
}
