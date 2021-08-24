#include "../maxflow_pushrelabel.hpp"
#include <cassert>
#include <iostream>
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A"
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int V, E;
    cin >> V >> E;
    mf_pushrelabel<int> graph(V);
    while (E--) {
        int u, v, c;
        cin >> u >> v >> c;
        graph.add_edge(u, v, c);
    }
    cout << graph.flow(0, V - 1) << '\n';
}
