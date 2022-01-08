#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1613"
#include "../tree_isomorphism.hpp"
#include "../../modint.hpp"
#include "../../unionfind/grid_unionfind.hpp"
#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

using mint = ModInt<998244353>;

pair<mint, mint> tree_hash(vector<string> S) {
    for (auto &s : S) s = "." + s + ".";
    const int W = S[0].size();
    S.insert(S.begin(), string(W, '.'));
    S.push_back(string(W, '.'));
    const int H = S.size();
    GridUnionFind uf(H, W);
    vector<pair<int, int>> dx4{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    vector<pair<int, int>> dx8{
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    auto is_inner = [&](int i, int j) { return i >= 0 and i < H and j >= 0 and j < W; };
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            vector<pair<int, int>> *ptr = S[i][j] == '#' ? &dx8 : &dx4;
            for (auto p : *ptr) {
                int nx = i + p.first, ny = j + p.second;
                if (is_inner(nx, ny) and S[i][j] == S[nx][ny]) uf.unite(i, j, nx, ny);
            }
        }
    }
    std::vector<int> roots;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) roots.push_back(uf.find(i, j));
    }
    sort(roots.begin(), roots.end());
    roots.erase(unique(roots.begin(), roots.end()), roots.end());
    tree_isomorphism<mint> iso(roots.size());
    vector<int> seen(H * W);
    seen[uf.find(0, 0)] = 1;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            int r = uf.find(i, j);
            if (seen[r]) continue;
            seen[r] = 1;
            int outer = -1;
            int cur = i;
            while (cur >= 0) {
                if (uf.find(cur, j) == r) {
                    outer = -1;
                } else if (outer < 0) {
                    outer = uf.find(cur, j);
                }
                cur--;
            }
            int u = lower_bound(roots.begin(), roots.end(), r) - roots.begin();
            int v = lower_bound(roots.begin(), roots.end(), outer) - roots.begin();
            iso.add_edge(u, v);
        }
    }
    int rid = lower_bound(roots.begin(), roots.end(), uf.find(0, 0)) - roots.begin();
    iso.build_hash(0, 141598, 181263479);
    return iso.hash[rid];
}

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int H, W;
    while (true) {
        cin >> H >> W;
        if (!H) break;
        vector<string> S(H);
        for (auto &s : S) cin >> s;
        int H2, W2;
        cin >> H2 >> W2;
        vector<string> T(H2);
        for (auto &s : T) cin >> s;
        cout << (tree_hash(S) == tree_hash(T) ? "yes" : "no") << '\n';
    }
}
