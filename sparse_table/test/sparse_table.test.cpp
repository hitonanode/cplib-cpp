#include "sparse_table/rmq_sparse_table.hpp"
#include "sparse_table/sparse_table.hpp"
#include <cassert>
#include <cstdio>
#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

int main() {
    int N, Q;
    scanf("%d %d", &N, &Q);
    std::vector<int> A(N);
    for (int i = 0; i < N; i++) scanf("%d", &A[i]);
    auto f = [](int l, int r) { return std::min(l, r); };
    SparseTable<int, decltype(f)> rmq1(A, 2e9, f);
    StaticRMQ<int> rmq2(A, 2e9);
    while (Q--) {
        int l, r;
        scanf("%d %d", &l, &r);
        int a = rmq1.get(l, r), b = rmq2.get(l, r);
        assert(a == b);
        printf("%d\n", a);
    }
}
