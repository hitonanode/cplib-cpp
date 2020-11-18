#pragma once
#include "other_data_structures/persistent_array.hpp"
#include <vector>

// Fully persistent UnionFind
// - find(t, x) : find the root of DSU tree x belongs to, when unite() is called t times.
// Complexity: O(logN) for each query
// Reference: <https://ei1333.github.io/library/structure/union-find/persistent-union-find.cpp>
struct PersistentUnionFind {
    int N;
    using Array = persistent_array<int, 4>;
    Array par;
    std::vector<Array::node*> savepoints; // Tree structure is saved after every `unite()` operation
    PersistentUnionFind(int N) : N(N), par(-1) { savepoints.emplace_back(nullptr); }
    int find(int t, int x) const {
        const int p = par.get(savepoints[t], x);
        return p < 0 ? x : find(t, p);
    }
    bool unite(int t, int x, int y) {
        x = find(t, x), y = find(t, y);
        auto ptr = savepoints[t];
        if (x != y) {
            int sz_x = -par.get(savepoints[t], x), sz_y = -par.get(savepoints[t], y);
            if (sz_x > sz_y) {
                par.ch(ptr, x, -sz_x - sz_y), par.ch(ptr, y, x);
            } else {
                par.ch(ptr, y, -sz_x - sz_y), par.ch(ptr, x, y);
            }
        }
        return savepoints.emplace_back(ptr), x != y;
    }
    int count(int t, int x) const { return -par.get(savepoints[t], find(t, x)); }
    bool same(int t, int x, int y) const { return find(t, x) == find(t, y); }
};
