#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"
#include "../range_kth_smallest_offline.hpp"
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, Q;
    cin >> N >> Q;
    std::vector<int> A(N);
    for (auto &x : A) cin >> x;
    range_kth_smallest solver(A);
    while (Q--) {
        int l, r, k;
        cin >> l >> r >> k;
        solver.add_query(l, r, k);
    }
    solver.solve();
    for (auto i : solver.solve()) cout << A[i] << '\n';
}
