#define PROBLEM "https://judge.yosupo.jp/problem/min_cost_b_flow"
#include "../b-flow.hpp"
#include <iostream>

using namespace std;

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

int main() {
    int N, M;
    cin >> N >> M;
    B_Flow<long long, __int128> bflow(N);

    for (int i = 0; i < N; i++) {
        int b;
        cin >> b;
        bflow.add_supply(i, b);
    }
    for (int i = 0; i < M; i++) {
        int s, t, l, u;
        long long c;
        cin >> s >> t >> l >> u >> c;
        bflow.add_edge(s, t, l, u, c);
    }
    auto ret = bflow.solve();
    if (ret.first) {
        cout << ret.second << '\n';
        for (auto p : bflow.potential) {
            assert(p >= -1e15 and p <= 1e15);
            cout << p << '\n';
        }
        for (auto f : bflow.f) cout << f << '\n';
    } else {
        cout << "infeasible\n";
    }
}
