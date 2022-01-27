#define PROBLEM "https://yukicoder.me/problems/no/1303"
#include "../../modint.hpp"
#include "../../number/dual_number.hpp"
#include "../../unionfind/unionfind.hpp"
#include "../matrix.hpp"

#include <iostream>
#include <utility>
#include <vector>
using namespace std;

using mint = ModInt<998244353>;
using dual = DualNumber<mint>;

mint solve1(int N, const vector<pair<int, int>> &edges) {
    vector<vector<dual>> d(N, vector<dual>(N));
    for (auto p : edges) {
        int u = p.first, v = p.second;
        d[u][u] += dual::id();
        d[v][v] += dual::id();
        d[u][v] -= dual::id();
        d[v][u] -= dual::id();
    }
    const dual x = dual(0, 1);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < i; ++j) {
            if (d[i][j] == dual()) {
                d[i][i] += x;
                d[j][j] += x;
                d[i][j] -= x;
                d[j][i] -= x;
            }
        }
    }
    d.resize(N - 1);
    for (auto &v : d) v.resize(N - 1);
    auto ret = matrix<dual>(d).gauss_jordan().determinant_of_upper_triangle();
    return ret.a + ret.b;
}

mint solve2(const vector<int> &vs, const vector<pair<int, int>> &edges) {
    int D = vs.size();
    matrix<mint> mat(D - 1, D - 1);
    for (auto p : edges) {
        int i = lower_bound(vs.begin(), vs.end(), p.first) - vs.begin();
        int j = lower_bound(vs.begin(), vs.end(), p.second) - vs.begin();
        if (i < D - 1) mat[i][i] += 1;
        if (j < D - 1) mat[j][j] += 1;
        if (i + 1 < D and j + 1 < D) mat[i][j] -= 1, mat[j][i] -= 1;
    }
    return mat.gauss_jordan().determinant_of_upper_triangle();
}

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N, M;
    cin >> N >> M;
    vector<pair<int, int>> edges;
    UnionFind uf1(N);
    while (M--) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        edges.emplace_back(u, v);
        uf1.unite(u, v);
    }

    if (uf1.count(0) == N) {
        cout << "0\n" << solve1(N, edges) << '\n';
        return 0;
    }

    int max_red = 0, cntmaxi = 0, fuben = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) fuben += !uf1.same(i, j);
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < i; ++j) {
            if (!uf1.same(i, j)) {
                int s = uf1.count(i) * uf1.count(j);
                if (s > max_red) {
                    max_red = s, cntmaxi = 1;
                } else {
                    if (max_red == s) cntmaxi++;
                }
            }
        }
    }
    mint ret = cntmaxi;
    vector<vector<int>> r2is(N);
    vector<vector<pair<int, int>>> r2edges(N);
    for (int i = 0; i < N; ++i) r2is[uf1.find(i)].push_back(i);
    for (auto p : edges) r2edges[uf1.find(p.first)].push_back(p);

    for (int r = 0; r < N; ++r) {
        if (r2is[r].size()) ret *= solve2(r2is[r], r2edges[r]);
    }
    cout << fuben - max_red * 2 << '\n' << ret << '\n';
}
