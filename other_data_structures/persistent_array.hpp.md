---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: unionfind/fully_persistent_uf.hpp
    title: unionfind/fully_persistent_uf.hpp
  - icon: ':warning:'
    path: unionfind/test/fully_persistent_uf.cpp
    title: unionfind/test/fully_persistent_uf.cpp
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://codeforces.com/contest/707/problem/D>
    - https://ei1333.github.io/luzhiled/snippets/structure/persistent-array.html>
    - https://qiita.com/hotman78/items/9c643feae1de087e6fc5>
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
    \ i, vec[i]);\n        }\n        return root;\n    }\n};\n"
  code: "#pragma once\n#include <algorithm>\n#include <array>\n#include <vector>\n\
    \n// CUT begin\n// Persistent Array\n// Reference: <https://qiita.com/hotman78/items/9c643feae1de087e6fc5>\n\
    //            <https://ei1333.github.io/luzhiled/snippets/structure/persistent-array.html>\n\
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
    \ i, vec[i]);\n        }\n        return root;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: other_data_structures/persistent_array.hpp
  requiredBy:
  - unionfind/fully_persistent_uf.hpp
  - unionfind/test/fully_persistent_uf.cpp
  timestamp: '2020-11-14 20:14:03+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: other_data_structures/persistent_array.hpp
layout: document
redirect_from:
- /library/other_data_structures/persistent_array.hpp
- /library/other_data_structures/persistent_array.hpp.html
title: other_data_structures/persistent_array.hpp
---
