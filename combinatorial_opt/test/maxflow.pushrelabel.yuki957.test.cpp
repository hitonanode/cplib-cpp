#define PROBLEM "https://yukicoder.me/problems/no/957"
#include "../../utilities/reader.hpp"
#include "../maxflow_pushrelabel.hpp"
#include <algorithm>
#include <iostream>
#include <numeric>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int H = rdi(), W = rdi();
    vector<vector<int>> G(H, vector<int>(W));
    for (auto &v : G) {
        for (auto &x : v) x = rdi();
    }
    vector<int> R(H), C(W);
    long long tot = 0;
    for (auto &x : R) x = rdi(), tot += x;
    for (auto &x : C) x = rdi(), tot += x;

    int Z = 1 + H + W;
    mf_pushrelabel<long long> g(Z + 1);

    for (int i = 0; i < H; i++) {
        auto gtot = accumulate(G[i].begin(), G[i].end(), 0LL);
        auto f0 = min<long long>(gtot, R[i]);
        tot -= f0;
        if (gtot > f0) g.add_edge(0, i + 1, gtot - f0);
        for (int j = 0; j < W; j++) g.add_edge(i + 1, H + 1 + j, G[i][j]);
    }
    for (int j = 0; j < W; j++) g.add_edge(H + 1 + j, Z, C[j]);
    cout << tot - g.flow(0, Z) << '\n';
}
