---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: data_structure/test/lazy_rbst.stress.test.cpp
    title: data_structure/test/lazy_rbst.stress.test.cpp
  - icon: ':heavy_check_mark:'
    path: data_structure/test/link_cut_tree.noncommutative.stress.test.cpp
    title: data_structure/test/link_cut_tree.noncommutative.stress.test.cpp
  - icon: ':heavy_check_mark:'
    path: data_structure/test/link_cut_tree.noncommutative2.stress.test.cpp
    title: data_structure/test/link_cut_tree.noncommutative2.stress.test.cpp
  - icon: ':heavy_check_mark:'
    path: data_structure/test/link_cut_tree.pathadd.stress.test.cpp
    title: data_structure/test/link_cut_tree.pathadd.stress.test.cpp
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/test/hessenberg_system.stress.test.cpp
    title: linear_algebra_matrix/test/hessenberg_system.stress.test.cpp
  - icon: ':heavy_check_mark:'
    path: set_power_series/test/subset_exp.stress.test.cpp
    title: set_power_series/test/subset_exp.stress.test.cpp
  - icon: ':heavy_check_mark:'
    path: set_power_series/test/subset_pow.stress.test.cpp
    title: set_power_series/test/subset_pow.stress.test.cpp
  - icon: ':heavy_check_mark:'
    path: tree/test/frequency_table_of_tree_distance.stress.test.cpp
    title: tree/test/frequency_table_of_tree_distance.stress.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"random/xorshift.hpp\"\n#include <cstdint>\n\n// CUT begin\n\
    uint32_t rand_int() // XorShift random integer generator\n{\n    static uint32_t\
    \ x = 123456789, y = 362436069, z = 521288629, w = 88675123;\n    uint32_t t =\
    \ x ^ (x << 11);\n    x = y;\n    y = z;\n    z = w;\n    return w = (w ^ (w >>\
    \ 19)) ^ (t ^ (t >> 8));\n}\ndouble rand_double() { return (double)rand_int()\
    \ / UINT32_MAX; }\n"
  code: "#pragma once\n#include <cstdint>\n\n// CUT begin\nuint32_t rand_int() //\
    \ XorShift random integer generator\n{\n    static uint32_t x = 123456789, y =\
    \ 362436069, z = 521288629, w = 88675123;\n    uint32_t t = x ^ (x << 11);\n \
    \   x = y;\n    y = z;\n    z = w;\n    return w = (w ^ (w >> 19)) ^ (t ^ (t >>\
    \ 8));\n}\ndouble rand_double() { return (double)rand_int() / UINT32_MAX; }\n"
  dependsOn: []
  isVerificationFile: false
  path: random/xorshift.hpp
  requiredBy: []
  timestamp: '2020-03-07 22:54:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - linear_algebra_matrix/test/hessenberg_system.stress.test.cpp
  - data_structure/test/link_cut_tree.pathadd.stress.test.cpp
  - data_structure/test/link_cut_tree.noncommutative.stress.test.cpp
  - data_structure/test/link_cut_tree.noncommutative2.stress.test.cpp
  - data_structure/test/lazy_rbst.stress.test.cpp
  - tree/test/frequency_table_of_tree_distance.stress.test.cpp
  - set_power_series/test/subset_exp.stress.test.cpp
  - set_power_series/test/subset_pow.stress.test.cpp
documentation_of: random/xorshift.hpp
layout: document
redirect_from:
- /library/random/xorshift.hpp
- /library/random/xorshift.hpp.html
title: random/xorshift.hpp
---
