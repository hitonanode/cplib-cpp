#include "number/factorize.hpp"
#include <iostream>
#define PROBLEM "https://judge.yosupo.jp/problem/factorize"

int main()
{
    int Q;
    std::cin >> Q;
    while (Q--)
    {
        long long a;
        std::cin >> a;
        auto ret = FactorizeLonglong(a);
        std::cout << ret.size();
        for (auto p : ret) std::cout << ' ' << p;
        std::cout << '\n';
    }
}
