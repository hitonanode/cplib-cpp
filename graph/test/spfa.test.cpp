#include "../shortest_path.hpp"
#include <cassert>
#include <iostream>
#include <vector>
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A"
using namespace std;

int main() {
    int V, E, r;
    cin >> V >> E >> r;
    constexpr int INF = 1 << 30;
    shortest_path<int, INF> graph(V);
    for (int i = 0; i < E; i++) {
        int s, t, d;
        cin >> s >> t >> d;
        graph.add_edge(s, t, d);
    }

    graph.SPFA(r);
    for (auto d : graph.dist) {
        if (d < INF) {
            cout << d << '\n';
        } else {
            cout << "INF\n";
        }
    }
}
