#include "../shortest_path.hpp"
#include <iostream>
#include <string>
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_C"
using namespace std;

int main() {
    int V, E;
    cin >> V >> E;
    constexpr int INF = 2000000000;
    shortest_path<int, INF> graph(V);
    while (E--) {
        int s, t, d;
        cin >> s >> t >> d;
        graph.add_edge(s, t, d);
    }

    auto dist2d = graph.WarshallFloyd();
    for (int i = 0; i < V; i++) {
        if (dist2d[i][i] < 0) {
            cout << "NEGATIVE CYCLE\n";
            return 0;
        }
    }

    for (auto vec : dist2d) {
        for (int i = 0; i < V; i++)
            cout << (vec[i] < INF ? to_string(vec[i]) : "INF") << (i + 1 == V ? '\n' : ' ');
    }
}
