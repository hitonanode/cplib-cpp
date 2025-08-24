#define PROBLEM "https://yukicoder.me/problems/no/1773"

#include "../matrix.hpp"

#include <iostream>
#include <random>
#include <tuple>
#include <vector>
using namespace std;

#include <atcoder/modint>
using mint = atcoder::modint1000000007;

mt19937 mt(530629);
uniform_int_distribution<int> rndgen(0, mint::mod() - 1);

int solve(int N, const vector<tuple<int, int, int>> &uvws) {
    matrix<mint> M(N, N);
    for (auto [u, v, w] : uvws) {
        mint x = rndgen(mt);
        M[u][v] += x;
        M[v][w] += x;
        M[w][u] += x;
        M[v][u] -= x;
        M[w][v] -= x;
        M[u][w] -= x;
    }
    return M.gauss_jordan().rank_of_gauss_jordan() / 2;
}

int main() {
    int N, M;
    cin >> N >> M;
    vector<tuple<int, int, int>> uvws;
    while (M--) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--, w--;
        uvws.emplace_back(u, v, w);
    }
    cout << max(solve(N, uvws), solve(N, uvws)) << '\n';
}
