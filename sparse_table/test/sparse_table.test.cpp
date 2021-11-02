#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"
#include "../sparse_table.hpp"
#include "../rmq_sparse_table.hpp"
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

int op(int l, int r) { return l < r ? l : r; }
int e() { return 2e9; }

int main() {
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N);
    for (auto &x : A) cin >> x;
    sparse_table<int, op, e> rmq1(A);
    StaticRMQ<int> rmq2(A, 2e9);
    while (Q--) {
        int l, r;
        cin >> l >> r;
        int a = rmq1.prod(l, r), b = rmq2.get(l, r);
        assert(a == b);
        cout << a << '\n';
    }
}
