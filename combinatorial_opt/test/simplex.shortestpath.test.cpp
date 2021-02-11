#include "../simplex.hpp"
#include <iostream>
#include <vector>
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_12_B"
using namespace std;

int main() {
    int N;
    cin >> N;
    using Float = double;
    vector<Float> c(N, 1);
    c[0] = -(N - 1);
    vector<vector<Float>> A;
    vector<Float> b;
    for (int u = 0; u < N; u++) {
        int k;
        cin >> k >> k;
        while (k--) {
            int v, d;
            cin >> v >> d;
            vector<Float> vec(N);
            vec[v] = 1, vec[u] = -1;
            A.push_back(vec);
            b.push_back(d);
        }
    }
    Simplex<> simplex(A, b, c);
    for (int u = 0; u < N; u++) cout << u << ' ' << llround(simplex.x[u] - simplex.x[0]) << '\n';
}
