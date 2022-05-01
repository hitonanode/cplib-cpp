#define PROBLEM "https://yukicoder.me/problems/no/160"
#include "../shortest_path.hpp"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N, M, S, G;
    cin >> N >> M >> S >> G;
    shortest_path<int> graph(N);
    vector<vector<pair<int, int>>> to(N);
    while (M--) {
        int a, b, c;
        cin >> a >> b >> c;
        graph.add_bi_edge(a, b, c);
        to[a].emplace_back(b, c);
        to[b].emplace_back(a, c);
    }
    graph.dial(S);
    auto dS = graph.dist;
    graph.dial(G);
    auto dG = graph.dist;
    cout << S;
    while (S != G) {
        int best = N;
        for (auto p : to[S]) {
            int nxt = p.first, w = p.second;
            if (dS[nxt] + dG[nxt] == dS[G] and dS[nxt] == dS[S] + w) best = min(best, nxt);
        }
        S = best;
        cout << ' ' << S;
    }
    cout << '\n';
}
