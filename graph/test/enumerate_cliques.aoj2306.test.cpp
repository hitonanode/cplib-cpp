#include "../enumerate_cliques.hpp"
#include <iostream>
#include <vector>
using namespace std;

#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2306"

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, M;
    cin >> N >> M;
    vector F(N, vector<int>(N));
    enumerate_cliques ec(N);
    while (M--) {
        int u, v, f;
        cin >> u >> v >> f;

        --u, --v;
        ec.add_bi_edge(u, v);

        F[u][v] = max(F[u][v], f);
        F[v][u] = max(F[v][u], f);
    }
    int ret = 0;

    auto op = [&](const std::vector<int> &clique) -> void {
        if (clique.size() <= 1) return;
        int tmp = 0;
        for (int s : clique) {
            int a = 1 << 30;
            for (int t : clique) {
                if (s != t) a = min(a, F[s][t]);
            }
            tmp += a;
        }
        ret = max(ret, tmp);
    };
    ec.run(op);

    cout << ret << endl;
}
