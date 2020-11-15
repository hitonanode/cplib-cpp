---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other_data_structures/persistent_array.hpp
    title: other_data_structures/persistent_array.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: unionfind/test/fully_persistent_uf.test.cpp
    title: unionfind/test/fully_persistent_uf.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://ei1333.github.io/library/structure/union-find/persistent-union-find.cpp>
  bundledCode: "#line 2 \"other_data_structures/persistent_array.hpp\"\n#include <algorithm>\n\
    #include <array>\n#include <vector>\n\n// CUT begin\n// Persistent Array\n// Reference:\
    \ <https://qiita.com/hotman78/items/9c643feae1de087e6fc5>\n//            <https://ei1333.github.io/luzhiled/snippets/structure/persistent-array.html>\n\
    // - (2^LOG)-ary tree-based\n// - Fully persistent\n// - `get(root, k)`:  get\
    \ k-th element\n// - `set(root, k, data)`: make new array whose k-th element is\
    \ updated to data\n// - `ch(root, k, data)` : change k-th element and implicitly\
    \ update root\n// Verify: Codeforces 707D <https://codeforces.com/contest/707/problem/D>\n\
    template <typename T, int LOG>\nstruct persistent_array {\n    T zero;\n    struct\
    \ node {\n        T data;\n        std::array<node*, 1 << LOG> child;\n      \
    \  node(const T &d) : data(d) {\n            std::fill(child.begin(), child.end(),\
    \ nullptr);\n        }\n        node(const node &n) : data(n.data) {\n       \
    \     std::copy(n.child.begin(), n.child.end(), child.begin());\n        }\n \
    \   };\n    persistent_array(T zero) : zero(zero) {}\n\n    T get(node *t, int\
    \ k) const {\n        if (t == nullptr) {\n            return zero;\n        }\n\
    \        return k ? get(t->child[k & ((1 << LOG) - 1)], k >> LOG) : t->data;\n\
    \    }\n\n    [[nodiscard]] node *set(node *t, int k, const T &data) {\n     \
    \   t = (t == nullptr) ? new node(zero) : new node(*t);\n        if (k == 0) {\n\
    \            t->data = data;\n        } else {\n            auto ptr = set(t->child[k\
    \ & ((1 << LOG) - 1)], k >> LOG, data);\n            t->child[k & ((1 << LOG)\
    \ - 1)] = ptr;\n        }\n        return t;\n    }\n\n    void ch(node *&t, int\
    \ k, const T &data) {\n        t = set(t, k, data);\n    }\n\n    [[nodiscard]]\
    \ node *build(const std::vector<T> &vec) {\n        node* root = nullptr;\n  \
    \      for (size_t i = 0; i < vec.size(); i++) {\n            root = set(root,\
    \ i, vec[i]);\n        }\n        return root;\n    }\n};\n#line 4 \"unionfind/fully_persistent_uf.hpp\"\
    \n\n// Fully persistent UnionFind\n// - find(t, x) : find the root of DSU tree\
    \ x belongs to, when unite() is called t times.\n// Complexity: O(logN) for each\
    \ query\n// Reference: <https://ei1333.github.io/library/structure/union-find/persistent-union-find.cpp>\n\
    struct PersistentUnionFind\n{\n    int N;\n    using Array = persistent_array<int,\
    \ 4>;\n    Array par;\n    std::vector<Array::node*> savepoints; // Tree structure\
    \ is saved after every `unite()` operation\n    PersistentUnionFind(int N) : N(N),\
    \ par(-1) {\n        savepoints.emplace_back(nullptr);\n    }\n    int find(int\
    \ t, int x) const {\n        const int p = par.get(savepoints[t], x);\n      \
    \  return p < 0 ? x : find(t, p);\n    }\n    bool unite(int t, int x, int y)\
    \ {\n        x = find(t, x), y = find(t, y);\n        auto ptr = savepoints[t];\n\
    \        if (x != y) {\n            int sz_x = -par.get(savepoints[t], x), sz_y\
    \ = -par.get(savepoints[t], y);\n            if (sz_x > sz_y) {\n            \
    \    par.ch(ptr, x, -sz_x - sz_y), par.ch(ptr, y, x);\n            } else {\n\
    \                par.ch(ptr, y, -sz_x - sz_y), par.ch(ptr, x, y);\n          \
    \  }\n        }\n        return savepoints.emplace_back(ptr), x != y;\n    }\n\
    \    int count(int t, int x) const {\n        return -par.get(savepoints[t], find(t,\
    \ x));\n    }\n    bool same(int t, int x, int y) const {\n        return find(t,\
    \ x) == find(t, y);\n    }\n};\n"
  code: "#pragma once\n#include \"other_data_structures/persistent_array.hpp\"\n#include\
    \ <vector>\n\n// Fully persistent UnionFind\n// - find(t, x) : find the root of\
    \ DSU tree x belongs to, when unite() is called t times.\n// Complexity: O(logN)\
    \ for each query\n// Reference: <https://ei1333.github.io/library/structure/union-find/persistent-union-find.cpp>\n\
    struct PersistentUnionFind\n{\n    int N;\n    using Array = persistent_array<int,\
    \ 4>;\n    Array par;\n    std::vector<Array::node*> savepoints; // Tree structure\
    \ is saved after every `unite()` operation\n    PersistentUnionFind(int N) : N(N),\
    \ par(-1) {\n        savepoints.emplace_back(nullptr);\n    }\n    int find(int\
    \ t, int x) const {\n        const int p = par.get(savepoints[t], x);\n      \
    \  return p < 0 ? x : find(t, p);\n    }\n    bool unite(int t, int x, int y)\
    \ {\n        x = find(t, x), y = find(t, y);\n        auto ptr = savepoints[t];\n\
    \        if (x != y) {\n            int sz_x = -par.get(savepoints[t], x), sz_y\
    \ = -par.get(savepoints[t], y);\n            if (sz_x > sz_y) {\n            \
    \    par.ch(ptr, x, -sz_x - sz_y), par.ch(ptr, y, x);\n            } else {\n\
    \                par.ch(ptr, y, -sz_x - sz_y), par.ch(ptr, x, y);\n          \
    \  }\n        }\n        return savepoints.emplace_back(ptr), x != y;\n    }\n\
    \    int count(int t, int x) const {\n        return -par.get(savepoints[t], find(t,\
    \ x));\n    }\n    bool same(int t, int x, int y) const {\n        return find(t,\
    \ x) == find(t, y);\n    }\n};\n"
  dependsOn:
  - other_data_structures/persistent_array.hpp
  isVerificationFile: false
  path: unionfind/fully_persistent_uf.hpp
  requiredBy: []
  timestamp: '2020-11-14 20:14:03+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - unionfind/test/fully_persistent_uf.test.cpp
documentation_of: unionfind/fully_persistent_uf.hpp
layout: document
redirect_from:
- /library/unionfind/fully_persistent_uf.hpp
- /library/unionfind/fully_persistent_uf.hpp.html
title: unionfind/fully_persistent_uf.hpp
---
