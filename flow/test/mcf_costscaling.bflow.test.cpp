#define PROBLEM "https://judge.yosupo.jp/problem/min_cost_b_flow"
#include "../maxflow_lowerbound.hpp"
#include "../mcf_costscaling.hpp"
#include <algorithm>
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
    MaxFlowLowerBound<long long> mf(N + 2);
    long long amount = 0, amount2 = 0;
    mcf_costscaling<long long, long long, 3, 10> mcf(N);
    for (int i = 0; i < N; i++) {
        int b;
        cin >> b;
        mcf.add_supply(i, b);
        if (b > 0) mf.add_edge(N, i, 0, b), amount += b;
        if (b < 0) mf.add_edge(i, N + 1, 0, -b), amount2 -= b;
    }
    __int128 ret_bias = 0;
    vector<long long> flow_bias;
    while (M--) {
        int s, t, l, u;
        long long c;
        cin >> s >> t >> l >> u >> c;
        if (u < 0) {
            mf.add_edge(t, s, -u, -l);
        } else if (l > 0) {
            mf.add_edge(s, t, l, u);
        } else {
            if (l < 0) mf.add_edge(t, s, 0, -l);
            if (u > 0) mf.add_edge(s, t, 0, u);
        }
        ret_bias += __int128(l) * c;
        flow_bias.push_back(l);
        mcf.add_edge(s, t, u - l, c);
        mcf.add_demand(s, l);
        mcf.add_supply(t, l);
    }
    if (amount != amount2 or mf.flow(N, N + 1) < amount) {
        cout << "infeasible\n";
    } else {
        cout << mcf.solve<__int128>() + ret_bias << '\n';
        for (auto x : mcf.potential()) cout << x << '\n';
        auto edges = mcf.edges();
        for (int e = 0; e < int(edges.size()); e++) cout << edges[e].flow + flow_bias[e] << '\n';
    }
}
