#define PROBLEM "https://judge.yosupo.jp/problem/static_range_sum"
#include "../disjoint_sparse_table.hpp"
#include <iostream>
#include <vector>
using namespace std;

long long f(long long l, long long r) { return l + r; }

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, Q;
    cin >> N >> Q;
    vector<long long> A(N);
    for (auto &x : A) cin >> x;
    disj_sparse_table<long long, f> st(A);

    while (Q--) {
        int l, r;
        cin >> l >> r;
        cout << st.prod(l, r) << '\n';
    }
}
