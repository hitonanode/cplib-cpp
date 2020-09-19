#include <iostream>
#include "graph/flow_mincost.hpp"
#define PROBLEM "https://judge.yosupo.jp/problem/min_cost_b_flow"

#include <algorithm>
template <>
struct std::numeric_limits<__int128>
{
    static __int128 max() noexcept { return ((__int128(1) << 126) - 1) * 2 + 1; }
    static __int128 min() noexcept { return -max() - 1; }
    static __int128 lowest() noexcept { return min(); }
};

std::ostream &operator<<(std::ostream &os, const __int128& x)
{
    __int128 tmp = x;
    if (tmp == 0) return os << 0;
    std::vector<int> ds;
    if (tmp < 0)
    {
        os << '-';
        while (tmp)
        {
            int d = tmp % 10;
            if (d > 0) d -= 10;
            ds.emplace_back(-d), tmp = (tmp - d) / 10;
        }
    }
    else
    {
        while (tmp) ds.emplace_back(tmp % 10), tmp /= 10;
    }
    std::reverse(ds.begin(), ds.end());
    for (auto i : ds) os << i;
    return os;
}

using namespace std;

int main()
{
    int N, M;
    cin >> N >> M;
    B_Flow<__int128, __int128> bflow(N);

    constexpr __int128 plim = 1000000000000000;
    for (int i = 0; i < N; i++)
    {
        int b;
        cin >> b;
        bflow.add_supply(i, b);
    }
    for (int i = 0; i < M; i++)
    {
        int s, t, l, u, c;
        cin >> s >> t >> l >> u >> c;
        bflow.add_edge(s, t, l, u, c);
    }
    auto ret = bflow.solve();
    if (ret.first)
    {
        cout << ret.second << '\n';
        for (int i = 0; i < N; i++)
        {
            cout << clamp(bflow.mcf.h[i], -plim, plim) << '\n';
        }
        for (int i = 0; i < M; i++)
        {
            cout << bflow.f[i] << '\n';
        }
    }
    else
    {
        cout << "infeasible\n";
    }
}
