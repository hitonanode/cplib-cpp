#include "../sparse_table_2d.hpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1068"
// Very slow (worst case: 6sec, memory 3GB)

#include <iostream>
using namespace std;

int main() {
    auto f = [](int l, int r) { return min(l, r); };
    while (true) {
        int H, W, Q;
        cin >> H >> W >> Q;
        if (!H) break;
        vector<vector<int>> mat(H, vector<int>(W));
        for (auto &vec : mat)
            for (auto &x : vec) cin >> x;
        SparseTable2D<int, decltype(f)> rmq(mat, (1LL << 31) - 1, f);
        while (Q--) {
            int xl, yl, xr, yr;
            cin >> xl >> yl >> xr >> yr;
            printf("%d\n", rmq.get(xl, xr + 1, yl, yr + 1));
        }
    }
}
