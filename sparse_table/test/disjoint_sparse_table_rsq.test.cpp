#include "../disjoint_sparse_table.hpp"
#include <cassert>
#include <cstdio>
#define PROBLEM "https://judge.yosupo.jp/problem/static_range_sum"

int main() {
    int N, Q;
    scanf("%d %d", &N, &Q);
    std::vector<long long> A(N);
    for (int i = 0; i < N; i++) { scanf("%lld", &A[i]); }
    auto f = [](long long l, long long r) { return l + r; };
    DisjointSparseTable<long long, decltype(f)> st(A, f);
    while (Q--) {
        int l, r;
        scanf("%d %d", &l, &r);
        long long a = st.get(l, r);
        printf("%lld\n", a);
    }
}
