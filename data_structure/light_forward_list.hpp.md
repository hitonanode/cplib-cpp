---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: graph/paths_of_length_two_decomposition.hpp
    title: "\u7121\u5411\u30B0\u30E9\u30D5\u306E\u9577\u3055 2 \u306E\u30D1\u30B9\u3078\
      \u306E\u5206\u89E3"
  - icon: ':heavy_check_mark:'
    path: string/aho_corasick.hpp
    title: string/aho_corasick.hpp
  - icon: ':heavy_check_mark:'
    path: string/aho_corasick_online.hpp
    title: string/aho_corasick_online.hpp
  - icon: ':heavy_check_mark:'
    path: string/incremental_matching.hpp
    title: string/incremental_matching.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: string/test/aho_corasick_forwardlist.test.cpp
    title: string/test/aho_corasick_forwardlist.test.cpp
  - icon: ':heavy_check_mark:'
    path: string/test/aho_corasick_online.test.cpp
    title: string/test/aho_corasick_online.test.cpp
  - icon: ':heavy_check_mark:'
    path: string/test/aho_corasick_unorderedmap.test.cpp
    title: string/test/aho_corasick_unorderedmap.test.cpp
  - icon: ':heavy_check_mark:'
    path: string/test/aho_corasick_vector.test.cpp
    title: string/test/aho_corasick_vector.test.cpp
  - icon: ':heavy_check_mark:'
    path: string/test/incremental_matching.test.cpp
    title: string/test/incremental_matching.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D>
  bundledCode: "#line 2 \"data_structure/light_forward_list.hpp\"\n#include <vector>\n\
    \n// CUT begin\n// Simple forward_list for MLE-sensitive situations\n// Verify:\
    \ <http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D>\ntemplate\
    \ <typename T> struct light_forward_list {\n    static std::vector<unsigned> ptr;\n\
    \    static std::vector<T> val;\n    unsigned head;\n    light_forward_list()\
    \ : head(0) {}\n    void push_front(T x) {\n        ptr.push_back(head), val.push_back(x);\n\
    \        head = ptr.size() - 1;\n    }\n    struct iterator {\n        unsigned\
    \ p;\n        iterator operator++() { return {p = ptr[p]}; }\n        T &operator*()\
    \ { return val[p]; }\n        bool operator!=(const iterator &rhs) { return p\
    \ != rhs.p; }\n    };\n    iterator begin() { return {head}; }\n    iterator end()\
    \ { return {0}; }\n};\ntemplate <typename T> std::vector<unsigned> light_forward_list<T>::ptr\
    \ = {0};\ntemplate <typename T> std::vector<T> light_forward_list<T>::val = {T()};\n"
  code: "#pragma once\n#include <vector>\n\n// CUT begin\n// Simple forward_list for\
    \ MLE-sensitive situations\n// Verify: <http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D>\n\
    template <typename T> struct light_forward_list {\n    static std::vector<unsigned>\
    \ ptr;\n    static std::vector<T> val;\n    unsigned head;\n    light_forward_list()\
    \ : head(0) {}\n    void push_front(T x) {\n        ptr.push_back(head), val.push_back(x);\n\
    \        head = ptr.size() - 1;\n    }\n    struct iterator {\n        unsigned\
    \ p;\n        iterator operator++() { return {p = ptr[p]}; }\n        T &operator*()\
    \ { return val[p]; }\n        bool operator!=(const iterator &rhs) { return p\
    \ != rhs.p; }\n    };\n    iterator begin() { return {head}; }\n    iterator end()\
    \ { return {0}; }\n};\ntemplate <typename T> std::vector<unsigned> light_forward_list<T>::ptr\
    \ = {0};\ntemplate <typename T> std::vector<T> light_forward_list<T>::val = {T()};\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/light_forward_list.hpp
  requiredBy:
  - string/aho_corasick.hpp
  - string/incremental_matching.hpp
  - string/aho_corasick_online.hpp
  - graph/paths_of_length_two_decomposition.hpp
  timestamp: '2021-02-26 23:47:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - string/test/aho_corasick_online.test.cpp
  - string/test/aho_corasick_unorderedmap.test.cpp
  - string/test/incremental_matching.test.cpp
  - string/test/aho_corasick_vector.test.cpp
  - string/test/aho_corasick_forwardlist.test.cpp
documentation_of: data_structure/light_forward_list.hpp
layout: document
redirect_from:
- /library/data_structure/light_forward_list.hpp
- /library/data_structure/light_forward_list.hpp.html
title: data_structure/light_forward_list.hpp
---
