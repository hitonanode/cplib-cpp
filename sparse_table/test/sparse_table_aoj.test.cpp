#include "sparse_table/sparse_table.hpp"
#include "sparse_table/rmq_sparse_table.hpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_D"

#include <cstdio>
int main()
{
    int N, L;
    scanf("%d %d", &N, &L);
    std::vector<int> A(N);
    for (auto &a : A) scanf("%d", &a);
    auto f = [](int l, int r) { return std::min(l, r); };
    SparseTable<int, decltype(f)> sp1(A, 1e9, f);
    StaticRMQ<int> sp2(A, 1e9);
    for (int l = 0; l + L <= N; l++) {
        int a = sp1.get(l, l + L);
        int b = sp2.get(l, l + L);
        assert(a == b);
        printf("%d ", a);
    }
}
