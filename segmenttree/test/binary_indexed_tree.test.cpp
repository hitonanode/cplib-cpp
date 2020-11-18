#include "segmenttree/binary_indexed_tree.hpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B"
#include <cstdio>

int main() {
    int N, Q;
    scanf("%d %d", &N, &Q);
    BIT<int> bit(N);
    while (Q--) {
        int c, x, y;
        scanf("%d %d %d", &c, &x, &y);
        if (c)
            printf("%d\n", bit.sum(y) - bit.sum(x - 1));
        else
            bit.add(x, y);
    }
}
