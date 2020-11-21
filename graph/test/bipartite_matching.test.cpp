#include "../bipartite_matching.hpp"
#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"

#include <algorithm>
#include <numeric>
#include <random>

int main() {
    std::cin.tie(nullptr), std::ios::sync_with_stdio(false);

    int L, R, M;
    std::cin >> L >> R >> M;

    std::vector<int> perm(L + R), perm_inv(L + R);
    std::iota(perm.begin(), perm.end(), 0);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(perm.begin(), perm.end(), g);
    for (int i = 0; i < L + R; i++) { perm_inv[perm[i]] = i; }

    BipartiteMatching bm(L + R);
    while (M--) {
        int a, b;
        std::cin >> a >> b;
        bm.add_edge(perm[a], perm[L + b]);
    }

    std::cout << bm.solve() << '\n';
    for (int j = 0; j < L + R; j++)
        if (bm.match[j] > j) {
            int a = perm_inv[j], b = perm_inv[bm.match[j]];
            if (a > b)
                std::cout << b << ' ' << a - L << '\n';
            else
                std::cout << a << ' ' << b - L << '\n';
        }
}
