#include "geometry/sort_by_argument.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
#define PROBLEM "https://judge.yosupo.jp/problem/sort_points_by_argument"

int main()
{
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int N;
    std::cin >> N;
    std::vector<P> ps;
    while (N--)
    {
        long long x, y;
        std::cin >> x >> y;
        ps.emplace_back(x, y);
    }
    std::sort(ps.begin(), ps.end());
    for (auto p : ps)
    {
        std::cout << p.X << ' ' << p.Y << '\n';
    }
}
