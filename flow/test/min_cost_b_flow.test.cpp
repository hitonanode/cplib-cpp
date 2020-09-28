#include "flow/mincostflow.hpp"
#include "utilities/int128.hpp"
#define PROBLEM "https://judge.yosupo.jp/problem/min_cost_b_flow"

using namespace std;

int main()
{
    int N, M;
    cin >> N >> M;
    B_Flow<long long, __int128> bflow(N);

    constexpr __int128 plim = 1000000000000000;
    for (int i = 0; i < N; i++)
    {
        int b;
        cin >> b;
        bflow.add_supply(i, b);
    }
    for (int i = 0; i < M; i++)
    {
        int s, t, l, u;
        __int128 c;
        cin >> s >> t >> l >> u >> c;
        bflow.add_edge(s, t, l, u, c);
    }
    auto ret = bflow.solve();
    if (ret.first)
    {
        cout << ret.second << '\n';
        for (int i = 0; i < N; i++)
        {
            cout << clamp(bflow.potential[i], -plim, plim) << '\n';
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
