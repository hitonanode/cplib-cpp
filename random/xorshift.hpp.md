---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: number/factorize.hpp
    title: "Integer factorization \uFF08\u7D20\u56E0\u6570\u5206\u89E3\uFF09"
  - icon: ':heavy_check_mark:'
    path: number/primitive_root.hpp
    title: "Primitive root modulo $n$ \uFF08\u539F\u59CB\u6839\u306E\u767A\u898B\uFF09"
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
    path: formal_power_series/test/pow_of_sparse_fps.stress.test.cpp
    title: formal_power_series/test/pow_of_sparse_fps.stress.test.cpp
  - icon: ':heavy_check_mark:'
    path: graph/test/chromatic_number.test.cpp
    title: graph/test/chromatic_number.test.cpp
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/test/hessenberg_system.stress.test.cpp
    title: linear_algebra_matrix/test/hessenberg_system.stress.test.cpp
  - icon: ':heavy_check_mark:'
    path: number/test/factorize_aoj.test.cpp
    title: number/test/factorize_aoj.test.cpp
  - icon: ':heavy_check_mark:'
    path: number/test/factorize_longlong.test.cpp
    title: number/test/factorize_longlong.test.cpp
  - icon: ':heavy_check_mark:'
    path: number/test/is_prime.test.cpp
    title: number/test/is_prime.test.cpp
  - icon: ':heavy_check_mark:'
    path: number/test/miller-rabin-5e7.test.cpp
    title: number/test/miller-rabin-5e7.test.cpp
  - icon: ':heavy_check_mark:'
    path: number/test/miller-rabin.test.cpp
    title: number/test/miller-rabin.test.cpp
  - icon: ':heavy_check_mark:'
    path: number/test/primitive_root.test.cpp
    title: number/test/primitive_root.test.cpp
  - icon: ':heavy_check_mark:'
    path: number/test/primitive_root_1e18.test.cpp
    title: number/test/primitive_root_1e18.test.cpp
  - icon: ':heavy_check_mark:'
    path: segmenttree/test/beats_random_test.test.cpp
    title: segmenttree/test/beats_random_test.test.cpp
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
  requiredBy:
  - number/primitive_root.hpp
  - number/factorize.hpp
  timestamp: '2020-03-07 22:54:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - data_structure/test/link_cut_tree.noncommutative2.stress.test.cpp
  - data_structure/test/lazy_rbst.stress.test.cpp
  - data_structure/test/link_cut_tree.pathadd.stress.test.cpp
  - data_structure/test/link_cut_tree.noncommutative.stress.test.cpp
  - graph/test/chromatic_number.test.cpp
  - number/test/is_prime.test.cpp
  - number/test/factorize_longlong.test.cpp
  - number/test/primitive_root.test.cpp
  - number/test/primitive_root_1e18.test.cpp
  - number/test/miller-rabin.test.cpp
  - number/test/factorize_aoj.test.cpp
  - number/test/miller-rabin-5e7.test.cpp
  - tree/test/frequency_table_of_tree_distance.stress.test.cpp
  - linear_algebra_matrix/test/hessenberg_system.stress.test.cpp
  - segmenttree/test/beats_random_test.test.cpp
  - formal_power_series/test/pow_of_sparse_fps.stress.test.cpp
  - set_power_series/test/subset_pow.stress.test.cpp
  - set_power_series/test/subset_exp.stress.test.cpp
documentation_of: random/xorshift.hpp
layout: document
redirect_from:
- /library/random/xorshift.hpp
- /library/random/xorshift.hpp.html
title: random/xorshift.hpp
---
