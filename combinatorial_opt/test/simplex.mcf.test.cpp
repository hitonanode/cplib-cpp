#include "../simplex.hpp"
#include <iostream>
#include <vector>
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B"
using namespace std;

int main() {
    int V, E, F;
    cin >> V >> E >> F;
    using Float = double;
    vector<vector<Float>> A(V * 2, vector<Float>(E, 0));
    vector<Float> b(V * 2);
    vector<Float> c;
    b[0] = b[2 * V - 1] = F, b[V - 1] = b[V] = -F;

    for (int e = 0; e < E; e++) {
        int u, v, cap, cost;
        cin >> u >> v >> cap >> cost;
        A[u][e] += 1, A[u + V][e] -= 1;
        A[v][e] -= 1, A[v + V][e] += 1;
        vector<Float> vec(E);
        vec[e]++;
        A.push_back(vec);
        b.push_back(cap);
        c.push_back(-cost);
    }
    Simplex<Float, 20> simplex(A, b, c);
    cout << (simplex.infeasible ? -1 : -llround(simplex.ans)) << '\n';
}
