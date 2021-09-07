#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"
#include "../radix_heap_array.hpp"
#include "../../utilities/reader.hpp"
#include <iostream>
#include <limits>
#include <utility>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N = rdi(), M = rdi(), s = rdi(), t = rdi();

    vector<vector<pair<int, unsigned>>> to(N);
    while (M--) {
        int a = rdi(), b = rdi(), c = rdi();
        to[b].emplace_back(a, c);
    }
    vector<unsigned long long> dist(N, numeric_limits<unsigned long long>::max());
    vector<int> prv(N, -1);
    dist[t] = 0;
    radix_heap_array<unsigned long long> pq;
    pq.chmin(0, t);
    while (!pq.empty()) {
        int now = pq.argmin_pop();
        if (now == s) break;
        for (const auto &nx : to[now]) {
            int nxt = nx.first;
            if (dist[nxt] > dist[now] + nx.second) {
                dist[nxt] = dist[now] + nx.second;
                prv[nxt] = now;
                pq.chmin(dist[nxt], nxt);
            }
        }
    }
    if (dist[s] == numeric_limits<unsigned long long>::max()) {
        cout << "-1\n";
        return 0;
    }

    std::vector<int> path;
    for (int now = s; now != -1; now = prv[now]) path.push_back(now);

    cout << dist[s] << ' ' << path.size() - 1 << '\n';
    for (int i = 1; i < int(path.size()); i++) cout << path[i - 1] << ' ' << path[i] << '\n';
}
