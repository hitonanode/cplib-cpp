#pragma once
#include <queue>
#include <utility>
#include <vector>
using namespace std;

using wedges = vector<vector<pair<long long, long long>>>; // (to, weight)

constexpr long long int INF = 1e17;
pair<vector<long long int>, vector<int>> dijkstra(int N, int s, const wedges &w) {
    using lint = long long;
    using plint = pair<long long, long long>;
    vector<lint> dist(N, INF);
    dist[s] = 0;
    vector<int> prev(N, -1);
    priority_queue<plint, vector<plint>, greater<plint>> pq;
    pq.emplace(0, s);
    while (!pq.empty()) {
        plint p = pq.top();
        pq.pop();
        int v = p.second;
        if (dist[v] < p.first) continue;
        for (auto nx : w[v]) {
            lint dnx = p.first + nx.second;
            if (dist[nx.first] > dnx) {
                dist[nx.first] = dnx, prev[nx.first] = v;
                pq.emplace(dnx, nx.first);
            }
        }
    }
    return make_pair(dist, prev); // (distance, previous_node)
}
