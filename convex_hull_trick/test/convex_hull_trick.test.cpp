#include "convex_hull_trick/convex_hull_trick.hpp"
#include <cassert>
#include <iostream>
#define PROBLEM "https://judge.yosupo.jp/problem/line_add_get_min"

ConvexHullTrick<__int128> cht_min(true), cht_max(false);

void add_line() {
    long long int a, b;
    std::cin >> a >> b;
    cht_min.add_line(a, b);
    cht_max.add_line(-a, -b);
}

int main() {
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int N, Q;
    std::cin >> N >> Q;
    while (N--) add_line();
    while (Q--) {
        int q;
        std::cin >> q;
        if (q) {
            int p;
            std::cin >> p;
            auto ret1 = cht_min.get(p);
            auto ret2 = cht_max.get(p);
            assert(ret1.first == -ret2.first);
            std::cout << ret1.first << '\n';
        } else {
            add_line();
        }
    }
}
