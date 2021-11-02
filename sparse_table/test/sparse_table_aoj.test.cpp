#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_D"
#include "../rmq_sparse_table.hpp"
#include "../sparse_table.hpp"
#include <iostream>
#include <vector>
using namespace std;

int op(int l, int r) { return l < r ? l : r; }
int e() { return 1e9; }

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, L;
    cin >> N >> L;
    vector<int> A(N);
    for (auto &a : A) cin >> a;
    sparse_table<int, op, e> sp1(A);
    StaticRMQ<int> sp2(A, 1e9);
    for (int l = 0; l + L <= N; l++) {
        int a = sp1.prod(l, l + L);
        int b = sp2.get(l, l + L);
        assert(a == b);
        cout << a << (l + L == N ? '\n' : ' ');
    }
}
