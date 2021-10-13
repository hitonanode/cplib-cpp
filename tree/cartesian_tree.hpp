#pragma once
#include <functional>
#include <vector>

// Cartesian tree
// Complexity: O(n)
// By default, the smaller node is nearer to the root
// Return : -1 (root), parent_idx (otherwise)
// Example: [1, 0, 2] => [1, -1, 1]
// Verified: https://judge.yosupo.jp/problem/cartesian_tree
template <class T, class Cmp = std::less<T>>
std::vector<int> cartesian_tree(const std::vector<T> &X) {
    const int n = X.size();
    Cmp comp;
    std::vector<int> st(n);
    int sz = 0;

    std::vector<int> par(n, -1);

    for (int i = 0; i < n; ++i) {
        while (sz >= 2 and comp(X[i], X[st[sz - 1]])) {
            par[st[sz - 1]] = comp(X[i], X[st[sz - 2]]) ? st[sz - 2] : i;
            --sz;
        }
        if (sz == 1 and comp(X[i], X[st[sz - 1]])) par[st[--sz]] = i;
        st[sz++] = i;
    }
    for (; sz > 1; --sz) par[st[sz - 1]] = st[sz - 2];
    return par;
};
