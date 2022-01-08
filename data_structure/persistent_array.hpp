#pragma once
#include <algorithm>
#include <array>
#include <vector>

// CUT begin
// Persistent Array
// Reference: <https://qiita.com/hotman78/items/9c643feae1de087e6fc5>
//            <https://ei1333.github.io/luzhiled/snippets/structure/persistent-array.html>
// - (2^LOG)-ary tree-based
// - Fully persistent
// - `get(root, k)`:  get k-th element
// - `set(root, k, data)`: make new array whose k-th element is updated to data
// - `ch(root, k, data)` : change k-th element and implicitly update root
// Verify: Codeforces 707D <https://codeforces.com/contest/707/problem/D>
template <typename T, int LOG> struct persistent_array {
    T zero;
    struct node {
        T data;
        std::array<node *, 1 << LOG> child;
        node(const T &d) : data(d) { std::fill(child.begin(), child.end(), nullptr); }
        node(const node &n) : data(n.data) {
            std::copy(n.child.begin(), n.child.end(), child.begin());
        }
    };
    persistent_array(T zero) : zero(zero) {}

    T get(node *t, int k) const {
        if (t == nullptr) { return zero; }
        return k ? get(t->child[k & ((1 << LOG) - 1)], k >> LOG) : t->data;
    }

    [[nodiscard]] node *set(node *t, int k, const T &data) {
        t = (t == nullptr) ? new node(zero) : new node(*t);
        if (k == 0) {
            t->data = data;
        } else {
            auto ptr = set(t->child[k & ((1 << LOG) - 1)], k >> LOG, data);
            t->child[k & ((1 << LOG) - 1)] = ptr;
        }
        return t;
    }

    void ch(node *&t, int k, const T &data) { t = set(t, k, data); }

    [[nodiscard]] node *build(const std::vector<T> &vec) {
        node *root = nullptr;
        for (size_t i = 0; i < vec.size(); i++) { root = set(root, i, vec[i]); }
        return root;
    }
};
