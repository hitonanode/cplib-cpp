#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2842"
#include "segmenttree/segment_tree_2d.hpp"

#include <cstdio>
#include <iostream>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

int main() {
    int H, W, T, Q;
    cin >> H >> W >> T >> Q;

    // Point add, range sum (like binary-indexed-tree)
    vector<vector<int>> mat(H, vector<int>(W));
    auto f = [](int l, int r) { return l + r; };
    auto g = [](int x, int q) { return x; };
    SegmentTree2D<int, int, int, decltype(f), decltype(g), decltype(f)> s1(mat, 0, f, g, f), s2(mat, 0, f, g, f);

    queue<pair<int, pair<int, int>>> q;
    while (Q--) {
        int t, c, h, w;
        cin >> t >> c >> h >> w;
        h--, w--;
        while (q.size() and q.front().first <= t) {
            int x, y;
            tie(x, y) = q.front().second;
            mat[x][y] = 2;
            s1.update(x, y, 0);
            s2.update(x, y, 1);
            q.pop();
        }
        if (c == 0) {
            mat[h][w] = 1;
            s1.update(h, w, 1);
            q.emplace(t + T, make_pair(h, w));
        }
        if (c == 1) {
            if (mat[h][w] == 2) {
                mat[h][w] = 0;
                s2.update(h, w, 0);
            }
        }
        if (c == 2) {
            int h2, w2;
            cin >> h2 >> w2;
            int m = s2.get(h, h2, w, w2, -1);
            int n = s1.get(h, h2, w, w2, -1);
            printf("%d %d\n", m, n);
        }
    }
}
