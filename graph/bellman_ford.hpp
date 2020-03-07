#pragma once
#include <utility>
#include <vector>
using namespace std;

// CUT begin
using wedges = vector<vector<pair<long long int, long long int>>>; // (to, weight)
constexpr long long int INF = 1e17;
vector<long long int> bellman_ford(int s, const wedges &w, int T)
{
    int N = w.size();
    vector<long long int> d(N, INF);
    d[s] = 0;
    for(int l = 0; l < T; l++) {
        bool upd = false;
        for (int i = 0; i < N; i++)
        {
            if (d[i] >= INF) continue;
            for (auto pa : w[i]) {
                if (d[pa.first] > d[i] + pa.second) {
                    d[pa.first] = d[i] + pa.second;
                    upd = true;
                }
            }
        }
        if (!upd) break;
    }
    return d;
}
