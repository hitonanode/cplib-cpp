#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B"
#include "../maxflow.hpp"
#include "../mcf_costscaling.hpp"
#include <iostream>
using namespace std;

int main() {
    int V, E, F;
    cin >> V >> E >> F;
    mcf_costscaling<int, long long> mcf(V);
    mf_graph<int> mf(V);
    while (E--) {
        int u, v, c, d;
        cin >> u >> v >> c >> d;
        mcf.add_edge(u, v, c, d);
        mf.add_edge(u, v, c);
    }

    mcf.add_supply(0, F), mcf.add_supply(V - 1, -F);
    if (mf.flow(0, V - 1) < F) {
        cout << "-1" << '\n';
    } else {
        cout << mcf.solve() << '\n';
    }
}
