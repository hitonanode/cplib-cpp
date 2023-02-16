---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"tsp/dense_distance_matrix.hpp\"\n\n#include <vector>\n\n\
    template <class T> class dense_distance_matrix {\n    int _n;\n    std::vector<T>\
    \ _d;\n\npublic:\n    dense_distance_matrix(const std::vector<std::vector<T>>\
    \ &distance_vecvec)\n        : _n(distance_vecvec.size()) {\n        _d.reserve(n()\
    \ * n());\n        for (const auto &vec : distance_vecvec) _d.insert(end(_d),\
    \ begin(vec), end(vec));\n    }\n\n    template <class U> void apply_pi(const\
    \ std::vector<U> &pi) {\n        for (int i = 0; i < n(); ++i) {\n           \
    \ for (int j = 0; j < n(); ++j) _d.at(i * n() + j) += pi.at(i) + pi.at(j);\n \
    \       }\n    }\n\n    int n() const noexcept { return _n; }\n\n    T dist(int\
    \ s, int t) const { return _d.at(s * n() + t); }\n    T operator()(int s, int\
    \ t) const { return dist(s, t); }\n\n    struct adjacents_sequence {\n       \
    \ const dense_distance_matrix *ptr;\n        int from;\n        struct iterator\
    \ {\n            const dense_distance_matrix *ptr;\n            int from;\n  \
    \          int to;\n            iterator operator++() { return {ptr, from, to++};\
    \ }\n            std::pair<int, T> operator*() const { return {to, ptr->dist(from,\
    \ to)}; }\n            bool operator!=(const iterator &rhs) const {\n        \
    \        return to != rhs.to or ptr != rhs.ptr or from != rhs.from;\n        \
    \    }\n        };\n        iterator begin() const { return iterator{ptr, from,\
    \ 0}; }\n        iterator end() const { return iterator{ptr, from, ptr->n()};\
    \ }\n    };\n\n    adjacents_sequence adjacents(int from) const { return {this,\
    \ from}; }\n};\n"
  code: "#pragma once\n\n#include <vector>\n\ntemplate <class T> class dense_distance_matrix\
    \ {\n    int _n;\n    std::vector<T> _d;\n\npublic:\n    dense_distance_matrix(const\
    \ std::vector<std::vector<T>> &distance_vecvec)\n        : _n(distance_vecvec.size())\
    \ {\n        _d.reserve(n() * n());\n        for (const auto &vec : distance_vecvec)\
    \ _d.insert(end(_d), begin(vec), end(vec));\n    }\n\n    template <class U> void\
    \ apply_pi(const std::vector<U> &pi) {\n        for (int i = 0; i < n(); ++i)\
    \ {\n            for (int j = 0; j < n(); ++j) _d.at(i * n() + j) += pi.at(i)\
    \ + pi.at(j);\n        }\n    }\n\n    int n() const noexcept { return _n; }\n\
    \n    T dist(int s, int t) const { return _d.at(s * n() + t); }\n    T operator()(int\
    \ s, int t) const { return dist(s, t); }\n\n    struct adjacents_sequence {\n\
    \        const dense_distance_matrix *ptr;\n        int from;\n        struct\
    \ iterator {\n            const dense_distance_matrix *ptr;\n            int from;\n\
    \            int to;\n            iterator operator++() { return {ptr, from, to++};\
    \ }\n            std::pair<int, T> operator*() const { return {to, ptr->dist(from,\
    \ to)}; }\n            bool operator!=(const iterator &rhs) const {\n        \
    \        return to != rhs.to or ptr != rhs.ptr or from != rhs.from;\n        \
    \    }\n        };\n        iterator begin() const { return iterator{ptr, from,\
    \ 0}; }\n        iterator end() const { return iterator{ptr, from, ptr->n()};\
    \ }\n    };\n\n    adjacents_sequence adjacents(int from) const { return {this,\
    \ from}; }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: tsp/dense_distance_matrix.hpp
  requiredBy: []
  timestamp: '2023-02-16 23:07:28+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: tsp/dense_distance_matrix.hpp
layout: document
redirect_from:
- /library/tsp/dense_distance_matrix.hpp
- /library/tsp/dense_distance_matrix.hpp.html
title: tsp/dense_distance_matrix.hpp
---
