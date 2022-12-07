#include "../networksimplex.hpp"
#include <iostream>
#define PROBLEM "https://judge.yosupo.jp/problem/min_cost_b_flow"

std::ostream &operator<<(std::ostream &os, const __int128 &x) {
    __int128 tmp = x;
    if (tmp == 0) return os << 0;
    std::vector<int> ds;
    if (tmp < 0) {
        os << '-';
        while (tmp) {
            int d = tmp % 10;
            if (d > 0) d -= 10;
            ds.emplace_back(-d), tmp = (tmp - d) / 10;
        }
    } else {
        while (tmp) ds.emplace_back(tmp % 10), tmp /= 10;
    }
    std::reverse(ds.begin(), ds.end());
    for (auto i : ds) os << i;
    return os;
}

using std::cin;
using std::cout;

int main() {
    int N, M;
    cin >> N >> M;
    mcf_graph_ns<long long, long long> bflow(N);

    for (int i = 0; i < N; i++) {
        int b;
        cin >> b;
        bflow.add_supply(i, b);
    }
    while (M--) {
        int s, t, l, u;
        long long c;
        cin >> s >> t >> l >> u >> c;
        bflow.add_edge(s, t, l, u, c);
    }
    __int128 ret = bflow.solve<__int128>();
    if (!bflow.infeasible) {
        cout << ret << '\n';
        for (auto p : bflow.potential) cout << p << '\n';
        for (auto f : bflow.flow) cout << f << '\n';
    } else {
        cout << "infeasible\n";
    }
}
