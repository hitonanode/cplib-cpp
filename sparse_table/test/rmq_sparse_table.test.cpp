#include "sparse_table/rmq_sparse_table.hpp"
#include <cstdio>
#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

int main()
{
    int N, Q;
    scanf("%d %d", &N, &Q);
    std::vector<int> A(N);
    for (int i = 0; i < N; i++) scanf("%d", &A[i]);
    StaticRMQ<int> rmq(A, 2e9);
    while (Q--) {
        int l, r;
        scanf("%d %d", &l, &r);
        printf("%d\n", rmq.get(l, r));
    }
}
