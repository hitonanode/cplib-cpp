#include "geometry/geometry2d.hpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_A"
#include <cmath>
#include <cstdio>
#include <iostream>

int main()
{
    int N;
    std::cin >> N;
    std::vector<P<double>> P(N);
    P[0].set_eps(1e-9);

    for (auto &p : P) std::cin >> p;
    std::vector<std::pair<int, int>> ps;
    for (auto idx : convex_hull(P, true)) ps.emplace_back(std::llround(P[idx].y), std::llround(P[idx].x));
    int init = std::min_element(ps.begin(), ps.end()) - ps.begin();
    
    printf("%lu\n", ps.size());
    for (size_t i = 0; i < ps.size(); i++) {
        printf("%d %d\n", ps[(i + init) % ps.size()].second, ps[(i + init) % ps.size()].first);
    }
}
