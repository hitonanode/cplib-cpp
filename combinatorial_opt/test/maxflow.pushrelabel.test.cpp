#include "../maxflow_pushrelabel.hpp"
#include <cassert>
#include <iostream>
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A"
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int V, E;
    cin >> V >> E;
    mf_pushrelabel<int, 1 << 29, false, false> g00(V);
    mf_pushrelabel<int, 1 << 29, false, true> g01(V);
    mf_pushrelabel<int, 1 << 29, true, false> g10(V);
    mf_pushrelabel<int, 1 << 29, true, true> g11(V);
    while (E--) {
        int u, v, c;
        cin >> u >> v >> c;
        g00.add_edge(u, v, c);
        g01.add_edge(u, v, c);
        g10.add_edge(u, v, c);
        g11.add_edge(u, v, c);
    }
    auto f00 = g00.flow(0, V - 1);
    auto f01 = g01.flow(0, V - 1);
    auto f10 = g10.flow(0, V - 1);
    auto f11 = g11.flow(0, V - 1);
    assert(f00 == f01);
    assert(f00 == f10);
    assert(f00 == f11);
    cout << f00 << '\n';
}
