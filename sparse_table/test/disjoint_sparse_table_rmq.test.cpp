#include "../disjoint_sparse_table.hpp"
#include <cassert>
#include <cstdio>
#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

int main() {
    int N, Q;
    scanf("%d %d", &N, &Q);
    std::vector<int> A(N);
    for (int i = 0; i < N; i++) { scanf("%d", &A[i]); }
    auto f = [](int l, int r) { return std::min(l, r); };
    DisjointSparseTable<int, decltype(f)> rmq(A, f);
    while (Q--) {
        int l, r;
        scanf("%d %d", &l, &r);
        int a = rmq.get(l, r);
        printf("%d\n", a);
    }
}
