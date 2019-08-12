#pragma once
#include <utility>
#include <vector>
using namespace std;
using lint = long long;

using wedges = vector<vector<pair<lint, lint>>>; // (to, weight)
constexpr lint INF = 1e17;
vector<lint> bellman_ford(int s, const wedges &w, int T)
{
    int N = w.size();
    vector<lint> d(N, INF);
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