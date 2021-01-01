#include "../binary_indexed_tree.hpp"
#include <iostream>
#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

// PointAddRangeSum (BIT based) 0-indexed
// Complexity: O(lg N) for each query
template <typename T> struct PointAddRangeSum {
    BIT<T> bit;
    PointAddRangeSum(const std::vector<T> &A) : bit(A.size()) {
        for (unsigned i = 0; i < A.size(); i++) bit.add(i, A[i]);
    }
    void add(int i, T val) { bit.add(i, val); }
    // sum [l, r)
    T get(int l, int r) const { return bit.sum(l, r); }
};

int main() {
    std::cin.tie(nullptr), std::ios::sync_with_stdio(false);

    int N, Q;
    std::cin >> N >> Q;
    std::vector<long long> A(N);
    for (auto &a : A) std::cin >> a;
    PointAddRangeSum<long long> s(A);
    while (Q--) {
        int q, l, r;
        std::cin >> q >> l >> r;
        if (q) {
            std::cout << s.get(l, r) << '\n';
        } else {
            s.add(l, r);
        }
    }
}
