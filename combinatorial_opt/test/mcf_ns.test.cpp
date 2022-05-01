#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B"
#include "../networksimplex.hpp"
#include <iostream>
using namespace std;

int main() {
    int V, E, F;
    cin >> V >> E >> F;
    mcf_graph_ns<int, int> mcf(V);
    while (E--) {
        int u, v, c, d;
        cin >> u >> v >> c >> d;
        mcf.add_edge(u, v, 0, c, d);
    }

    mcf.add_supply(0, F), mcf.add_supply(V - 1, -F);
    auto ret = mcf.solve<int>();
    cout << (mcf.infeasible ? -1 : ret) << '\n';
}
