#include "../simplex.hpp"
#include <iostream>
#include <vector>
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A"
using namespace std;

int main() {
    int V, E;
    cin >> V >> E;
    using Float = double;
    vector<Float> C(E);
    vector<vector<Float>> A((V - 2) * 2, vector<Float>(E, 0));
    vector<Float> b((V - 2) * 2);
    for (int e = 0; e < E; e++) {
        int u, v, c;
        cin >> u >> v >> c;
        if (u == 0) {
            C[e] += 0.5;
        } else if (u == V - 1) {
            C[e] -= 0.5;
        } else {
            A[u - 1][e]++, A[u - 1 + V - 2][e]--;
        }
        if (v == 0) {
            C[e] -= 0.5;
        } else if (v == V - 1) {
            C[e] += 0.5;
        } else {
            A[v - 1][e]--, A[v - 1 + V - 2][e]++;
        }
        vector<Float> vec(E);
        vec[e]++;
        A.push_back(vec);
        b.push_back(c);
    }
    Simplex<> simplex(A, b, C);
    cout << llround(simplex.ans) << '\n';
}
