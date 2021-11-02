#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1068"
#include "../sparse_table_2d.hpp"
// Very slow (worst case: 6sec, memory 3GB)

#include <iostream>
using namespace std;

int op(int l, int r) { return l < r ? l : r; }
int e() { return (1LL << 31) - 1; }

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    while (true) {
        int H, W, Q;
        cin >> H >> W >> Q;
        if (!H) break;
        vector<vector<int>> mat(H, vector<int>(W));
        for (auto &vec : mat) {
            for (auto &x : vec) cin >> x;
        }
        SparseTable2D<int, op, e> rmq(mat);
        while (Q--) {
            int xl, yl, xr, yr;
            cin >> xl >> yl >> xr >> yr;
            cout << rmq.prod(xl, xr + 1, yl, yr + 1) << '\n';
        }
    }
}
