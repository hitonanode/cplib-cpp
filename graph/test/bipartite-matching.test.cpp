#include <iostream>
#include "graph/bipartite-matching.hpp"
#define PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_7_A

int main()
{
    int X, Y, E;
    cin >> X >> Y >> E;
    BipartiteMatching graph(X + Y);
    for (int i = 0; i < E; i++)
    {
        int s, t;
        cin >> s >> t;
        graph.add_edge(s, X + t);
    }
    cout << graph.solve() << endl;
}
