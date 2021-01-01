#include "../segment_tree_2d.hpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1068"

#include <iostream>
using namespace std;

int main() {
    auto f = [](int l, int r) { return min(l, r); };
    auto g = [](int x, int q) { return x; };
    while (true) {
        int H, W, Q;
        cin >> H >> W >> Q;
        vector<vector<int>> mat(H, vector<int>(W));
        if (!H) break;
        for (auto &vec : mat)
            for (auto &x : vec) cin >> x;
        int INF = (1LL << 31) - 1;
        SegmentTree2D<int, int, int, decltype(f), decltype(g), decltype(f)> rmq(mat, INF, f, g, f);
        while (Q--) {
            int xl, yl, xr, yr;
            cin >> xl >> yl >> xr >> yr;
            printf("%d\n", rmq.get(xl, xr + 1, yl, yr + 1, -1));
        }
    }
}
