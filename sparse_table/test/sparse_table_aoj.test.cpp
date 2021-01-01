#include "../rmq_sparse_table.hpp"
#include "../sparse_table.hpp"
#include <iostream>
#include <vector>
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_D"
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, L;
    cin >> N >> L;
    vector<int> A(N);
    for (auto &a : A) cin >> a;
    auto f = [](int l, int r) { return min(l, r); };
    SparseTable<int, decltype(f)> sp1(A, 1e9, f);
    StaticRMQ<int> sp2(A, 1e9);
    for (int l = 0; l + L <= N; l++) {
        int a = sp1.get(l, l + L);
        int b = sp2.get(l, l + L);
        assert(a == b);
        cout << a << (l + L == N ? '\n' : ' ');
    }
}
