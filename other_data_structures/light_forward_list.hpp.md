---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: string/aho_corasick.hpp
    title: string/aho_corasick.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: string/test/aho_corasick_forwardlist.test.cpp
    title: string/test/aho_corasick_forwardlist.test.cpp
  - icon: ':heavy_check_mark:'
    path: string/test/aho_corasick_unorderedmap.test.cpp
    title: string/test/aho_corasick_unorderedmap.test.cpp
  - icon: ':heavy_check_mark:'
    path: string/test/aho_corasick_vector.test.cpp
    title: string/test/aho_corasick_vector.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D>
  bundledCode: "#line 2 \"other_data_structures/light_forward_list.hpp\"\n#include\
    \ <vector>\n\n// Simple forward_list for MLE-sensitive situations\n// Verify:\
    \ <http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D>\ntemplate\
    \ <typename T> struct light_forward_list {\n    static std::vector<unsigned> ptr;\n\
    \    static std::vector<T> val;\n    unsigned head;\n    light_forward_list()\
    \ : head(0) {}\n    void push_front(T x) {\n        ptr.push_back(head), val.push_back(x);\n\
    \        head = ptr.size() - 1;\n    }\n    struct iterator {\n        unsigned\
    \ p;\n        iterator operator++() { return {p = ptr[p]}; }\n        T &operator*()\
    \ { return val[p]; }\n        bool operator!=(const iterator &rhs) { return p\
    \ != rhs.p; }\n    };\n    iterator begin() { return {head}; }\n    iterator end()\
    \ { return {0}; }\n};\ntemplate <typename T> std::vector<unsigned> light_forward_list<T>::ptr\
    \ = {0};\ntemplate <typename T> std::vector<T> light_forward_list<T>::val = {0};\n"
  code: "#pragma once\n#include <vector>\n\n// Simple forward_list for MLE-sensitive\
    \ situations\n// Verify: <http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D>\n\
    template <typename T> struct light_forward_list {\n    static std::vector<unsigned>\
    \ ptr;\n    static std::vector<T> val;\n    unsigned head;\n    light_forward_list()\
    \ : head(0) {}\n    void push_front(T x) {\n        ptr.push_back(head), val.push_back(x);\n\
    \        head = ptr.size() - 1;\n    }\n    struct iterator {\n        unsigned\
    \ p;\n        iterator operator++() { return {p = ptr[p]}; }\n        T &operator*()\
    \ { return val[p]; }\n        bool operator!=(const iterator &rhs) { return p\
    \ != rhs.p; }\n    };\n    iterator begin() { return {head}; }\n    iterator end()\
    \ { return {0}; }\n};\ntemplate <typename T> std::vector<unsigned> light_forward_list<T>::ptr\
    \ = {0};\ntemplate <typename T> std::vector<T> light_forward_list<T>::val = {0};\n"
  dependsOn: []
  isVerificationFile: false
  path: other_data_structures/light_forward_list.hpp
  requiredBy:
  - string/aho_corasick.hpp
  timestamp: '2020-12-31 18:21:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - string/test/aho_corasick_vector.test.cpp
  - string/test/aho_corasick_forwardlist.test.cpp
  - string/test/aho_corasick_unorderedmap.test.cpp
documentation_of: other_data_structures/light_forward_list.hpp
layout: document
redirect_from:
- /library/other_data_structures/light_forward_list.hpp
- /library/other_data_structures/light_forward_list.hpp.html
title: other_data_structures/light_forward_list.hpp
---
