#include "../geometry.hpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_A"
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<Point2d<double>> P(N);
    P[0].set_eps(1e-9);
    for (auto &p : P) cin >> p;

    vector<pair<int, int>> ps;
    for (auto idx : convex_hull(P, true)) ps.emplace_back(llround(P[idx].y), llround(P[idx].x));
    int init = min_element(ps.begin(), ps.end()) - ps.begin();

    printf("%lu\n", ps.size());
    for (size_t i = 0; i < ps.size(); i++) {
        printf("%d %d\n", ps[(i + init) % ps.size()].second, ps[(i + init) % ps.size()].first);
    }
}
