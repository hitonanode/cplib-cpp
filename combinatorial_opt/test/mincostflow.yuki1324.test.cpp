#define PROBLEM "https://yukicoder.me/problems/no/1324"
#include "../mincostflow_nonegativeloop.hpp"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N, K;
    cin >> N >> K;
    vector<int> A(N), B(N);
    vector<vector<int>> P(N, vector<int>(N));
    for (auto &x : A) cin >> x;
    for (auto &x : B) cin >> x;
    for (auto &v : P) {
        for (auto &x : v) cin >> x;
    }

    const int gs = N * 2, gt = gs + 1;
    MinCostFlow<int, long long> graph(gt + 1);
    long long ret = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            ret += P[i][j] * P[i][j];
            for (int a = 0; a < A[i]; a++) graph.add_edge(i, j + N, 1, 2 * (a - P[i][j]) + 1);
        }
        graph.add_edge(gs, i, A[i], 0);
        graph.add_edge(i + N, gt, B[i], 0);
    }
    cout << ret + graph.flow(gs, gt, K).second << '\n';
}
