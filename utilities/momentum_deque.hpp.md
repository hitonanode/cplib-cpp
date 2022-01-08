---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://atcoder.jp/contests/otemae2019/submissions/17097802>
  bundledCode: "#line 2 \"utilities/momentum_deque.hpp\"\n#include <deque>\n\n// CUT\
    \ begin\n// Deque keeping (up to 2nd order) moment\n// m0 = \\sum_i ai, m1 = \\\
    sum_i (i * ai), m2 = \\sum_i (i^2 * ai)\n// Verify: <https://atcoder.jp/contests/otemae2019/submissions/17097802>\n\
    // Be careful for overflow\ntemplate <typename DTYPE_DEQUE> struct deque_momentum\
    \ {\n    std::deque<DTYPE_DEQUE> deq;\n    DTYPE_DEQUE m0, m1, m2;\n    deque_momentum()\
    \ : m0(0), m1(0), m2(0) {}\n\n    int size() const { return int(deq.size()); }\n\
    \    DTYPE_DEQUE front() const {\n        return deq.front();\n    } // `front()\
    \ const` => `&front()` makes faster, but unsafe.\n    DTYPE_DEQUE back() const\
    \ { return deq.back(); }\n    void push_back(DTYPE_DEQUE x) noexcept {\n     \
    \   m0 += x;\n        long long i = size();\n        m1 += x * i;\n        m2\
    \ += x * i * i; // be careful for overflow\n        deq.push_back(x);\n    }\n\
    \    void pop_back() {\n        DTYPE_DEQUE x = back();\n        deq.pop_back();\n\
    \        long long i = size();\n        m0 -= x;\n        m1 -= x * i;\n     \
    \   m2 -= x * i * i; // be careful for overflow\n    }\n    void push_front(DTYPE_DEQUE\
    \ x) noexcept {\n        m2 += m1 * 2 + m0;\n        m1 += m0;\n        m0 +=\
    \ x;\n        deq.push_front(x);\n    }\n    void pop_front() {\n        DTYPE_DEQUE\
    \ x0 = front();\n        m2 -= m1 * 2 - m0 + x0;\n        m1 -= m0 - x0;\n   \
    \     m0 -= x0;\n        deq.pop_front();\n    }\n};\n"
  code: "#pragma once\n#include <deque>\n\n// CUT begin\n// Deque keeping (up to 2nd\
    \ order) moment\n// m0 = \\sum_i ai, m1 = \\sum_i (i * ai), m2 = \\sum_i (i^2\
    \ * ai)\n// Verify: <https://atcoder.jp/contests/otemae2019/submissions/17097802>\n\
    // Be careful for overflow\ntemplate <typename DTYPE_DEQUE> struct deque_momentum\
    \ {\n    std::deque<DTYPE_DEQUE> deq;\n    DTYPE_DEQUE m0, m1, m2;\n    deque_momentum()\
    \ : m0(0), m1(0), m2(0) {}\n\n    int size() const { return int(deq.size()); }\n\
    \    DTYPE_DEQUE front() const {\n        return deq.front();\n    } // `front()\
    \ const` => `&front()` makes faster, but unsafe.\n    DTYPE_DEQUE back() const\
    \ { return deq.back(); }\n    void push_back(DTYPE_DEQUE x) noexcept {\n     \
    \   m0 += x;\n        long long i = size();\n        m1 += x * i;\n        m2\
    \ += x * i * i; // be careful for overflow\n        deq.push_back(x);\n    }\n\
    \    void pop_back() {\n        DTYPE_DEQUE x = back();\n        deq.pop_back();\n\
    \        long long i = size();\n        m0 -= x;\n        m1 -= x * i;\n     \
    \   m2 -= x * i * i; // be careful for overflow\n    }\n    void push_front(DTYPE_DEQUE\
    \ x) noexcept {\n        m2 += m1 * 2 + m0;\n        m1 += m0;\n        m0 +=\
    \ x;\n        deq.push_front(x);\n    }\n    void pop_front() {\n        DTYPE_DEQUE\
    \ x0 = front();\n        m2 -= m1 * 2 - m0 + x0;\n        m1 -= m0 - x0;\n   \
    \     m0 -= x0;\n        deq.pop_front();\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/momentum_deque.hpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utilities/momentum_deque.hpp
layout: document
redirect_from:
- /library/utilities/momentum_deque.hpp
- /library/utilities/momentum_deque.hpp.html
title: utilities/momentum_deque.hpp
---
