#include "segmenttree/binary_indexed_tree.hpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B"
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, Q;
    cin >> N >> Q;
    BIT<int> bit(N);
    while (Q--) {
        int c, x, y;
        cin >> c >> x >> y;
        if (c) {
            cout << bit.sum(x - 1, y) << '\n';
        } else {
            bit.add(x - 1, y);
        }
    }
}
