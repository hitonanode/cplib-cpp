#define PROBLEM "https://yukicoder.me/problems/no/957"
#include "../maxflow_pushrelabel.hpp"
#include <algorithm>
#include <iostream>
#include <numeric>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int H, W;
    cin >> H >> W;
    vector<vector<int>> G(H, vector<int>(W));
    for (auto &v : G) {
        for (auto &x : v) cin >> x;
    }
    vector<int> R(H), C(W);
    for (auto &x : R) cin >> x;
    for (auto &x : C) cin >> x;
    long long tot = accumulate(R.begin(), R.end(), 0LL) + accumulate(C.begin(), C.end(), 0LL);

    long long f1 = 0;

    int Z = 1 + H + W;
    mf_pushrelabel<long long> g(Z + 1);

    for (int i = 0; i < H; i++) {
        auto gtot = accumulate(G[i].begin(), G[i].end(), 0LL);
        auto f0 = min<long long>(gtot, R[i]);
        f1 += f0;
        g.add_edge(0, i + 1, gtot - f0);
        for (int j = 0; j < W; j++) g.add_edge(i + 1, H + 1 + j, G[i][j]);
    }
    for (int j = 0; j < W; j++) g.add_edge(H + 1 + j, Z, C[j]);
    cout << tot - f1 - g.flow(0, Z) << '\n';
}
