#include "graph/bipartite_matching.hpp"
#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"

int main()
{
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int L, R, M;
    std::cin >> L >> R >> M;
    BipartiteMatching bm(L, R);
    while (M--)
    {
        int a, b;
        std::cin >> a >> b;
        bm.add_edge(a, b);
    }
    std::cout << bm.solve() << '\n';
    for (int j = 0; j < R; j++) if (bm.match[j] >= 0) {
        std::cout << bm.match[j] << ' ' << j << '\n';
    }
}
