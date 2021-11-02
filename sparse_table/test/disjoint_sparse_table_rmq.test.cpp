#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"
#include "../disjoint_sparse_table.hpp"
#include <iostream>
#include <vector>
using namespace std;

int f(int l, int r) { return l < r ? l : r; };

int main() {
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N);
    for (auto &x : A) cin >> x;
    disj_sparse_table<int, f> rmq(A);
    while (Q--) {
        int l, r;
        cin >> l >> r;
        cout << rmq.prod(l, r) << '\n';
    }
}
