---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: other_data_structures/test/queue_operate_all_composite.test.cpp
    title: other_data_structures/test/queue_operate_all_composite.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://github.com/NiMiLib/NoshiMochiLibrary/blob/queue_aggregation/lib/data_structure/sequence/queue_aggregation.hpp>
    - https://www.hackerrank.com/contests/tsg-live-4-programming-contest/challenges/tsg-live-4-procon-lcm-interval/submissions/code/1317888077>
  bundledCode: "#line 2 \"other_data_structures/sliding_window_aggregation.hpp\"\n\
    #include <stack>\n#include <utility>\nusing namespace std;\n\n// CUT begin\n//\
    \ Sliding-Window Aggregation based queue\n// - `std::queue`-like data structure\
    \ with monoid operation\n// - Each operation is amortized O(1)\n// - Verification:\
    \ <https://www.hackerrank.com/contests/tsg-live-4-programming-contest/challenges/tsg-live-4-procon-lcm-interval/submissions/code/1317888077>\n\
    // - Reference: <https://github.com/NiMiLib/NoshiMochiLibrary/blob/queue_aggregation/lib/data_structure/sequence/queue_aggregation.hpp>\n\
    template <typename T_VAL, typename T_PROD, T_PROD (*val2prod)(T_VAL), T_PROD (*merge)(T_PROD,\
    \ T_PROD)> struct SlidingWindowAggregation {\n    std::stack<std::pair<T_VAL,\
    \ T_PROD>> front_stack, back_stack;\n    T_PROD ID_;\n\n    SlidingWindowAggregation(T_PROD\
    \ id_prod) : ID_(id_prod) {}\n    bool empty() const { return front_stack.empty()\
    \ and back_stack.empty(); }\n    int size() const { return front_stack.size()\
    \ + back_stack.size(); }\n    T_PROD fold_all() const {\n        if (empty())\n\
    \            return ID_;\n        else if (front_stack.empty())\n            return\
    \ back_stack.top().second;\n        else if (back_stack.empty())\n           \
    \ return front_stack.top().second;\n        else\n            return merge(front_stack.top().second,\
    \ back_stack.top().second);\n    }\n    void push(const T_VAL &x) {\n        if\
    \ (back_stack.empty())\n            back_stack.emplace(x, val2prod(x));\n    \
    \    else\n            back_stack.emplace(x, merge(back_stack.top().second, val2prod(x)));\n\
    \    }\n    T_VAL pop() {\n        if (front_stack.empty()) {\n            front_stack.emplace(back_stack.top().first,\
    \ val2prod(back_stack.top().first));\n            back_stack.pop();\n        \
    \    while (!back_stack.empty()) {\n                T_VAL t = back_stack.top().first;\n\
    \                front_stack.emplace(t, merge(val2prod(t), front_stack.top().second));\n\
    \                back_stack.pop();\n            }\n        }\n        T_VAL t\
    \ = front_stack.top().first;\n        front_stack.pop();\n        return t;\n\
    \    }\n};\n\ntemplate <typename T> T swag_op_id(T x) { return x; };\ntemplate\
    \ <typename T> T swag_op_linear_merge(T l, T r) { return make_pair(l.first * r.first,\
    \ l.second * r.first + r.second); };\n\n// Linear function composition\n// `f(x)\
    \ = first * x + second`, operate most recently added function first\ntemplate\
    \ <typename T> struct LinearFunctionQueue : public SlidingWindowAggregation<pair<T,\
    \ T>, pair<T, T>, swag_op_id, swag_op_linear_merge> {\n    LinearFunctionQueue()\
    \ : SlidingWindowAggregation<pair<T, T>, pair<T, T>, swag_op_id, swag_op_linear_merge>::SlidingWindowAggregation(pair<T,\
    \ T>(1, 0)) {}\n};\n"
  code: "#pragma once\n#include <stack>\n#include <utility>\nusing namespace std;\n\
    \n// CUT begin\n// Sliding-Window Aggregation based queue\n// - `std::queue`-like\
    \ data structure with monoid operation\n// - Each operation is amortized O(1)\n\
    // - Verification: <https://www.hackerrank.com/contests/tsg-live-4-programming-contest/challenges/tsg-live-4-procon-lcm-interval/submissions/code/1317888077>\n\
    // - Reference: <https://github.com/NiMiLib/NoshiMochiLibrary/blob/queue_aggregation/lib/data_structure/sequence/queue_aggregation.hpp>\n\
    template <typename T_VAL, typename T_PROD, T_PROD (*val2prod)(T_VAL), T_PROD (*merge)(T_PROD,\
    \ T_PROD)> struct SlidingWindowAggregation {\n    std::stack<std::pair<T_VAL,\
    \ T_PROD>> front_stack, back_stack;\n    T_PROD ID_;\n\n    SlidingWindowAggregation(T_PROD\
    \ id_prod) : ID_(id_prod) {}\n    bool empty() const { return front_stack.empty()\
    \ and back_stack.empty(); }\n    int size() const { return front_stack.size()\
    \ + back_stack.size(); }\n    T_PROD fold_all() const {\n        if (empty())\n\
    \            return ID_;\n        else if (front_stack.empty())\n            return\
    \ back_stack.top().second;\n        else if (back_stack.empty())\n           \
    \ return front_stack.top().second;\n        else\n            return merge(front_stack.top().second,\
    \ back_stack.top().second);\n    }\n    void push(const T_VAL &x) {\n        if\
    \ (back_stack.empty())\n            back_stack.emplace(x, val2prod(x));\n    \
    \    else\n            back_stack.emplace(x, merge(back_stack.top().second, val2prod(x)));\n\
    \    }\n    T_VAL pop() {\n        if (front_stack.empty()) {\n            front_stack.emplace(back_stack.top().first,\
    \ val2prod(back_stack.top().first));\n            back_stack.pop();\n        \
    \    while (!back_stack.empty()) {\n                T_VAL t = back_stack.top().first;\n\
    \                front_stack.emplace(t, merge(val2prod(t), front_stack.top().second));\n\
    \                back_stack.pop();\n            }\n        }\n        T_VAL t\
    \ = front_stack.top().first;\n        front_stack.pop();\n        return t;\n\
    \    }\n};\n\ntemplate <typename T> T swag_op_id(T x) { return x; };\ntemplate\
    \ <typename T> T swag_op_linear_merge(T l, T r) { return make_pair(l.first * r.first,\
    \ l.second * r.first + r.second); };\n\n// Linear function composition\n// `f(x)\
    \ = first * x + second`, operate most recently added function first\ntemplate\
    \ <typename T> struct LinearFunctionQueue : public SlidingWindowAggregation<pair<T,\
    \ T>, pair<T, T>, swag_op_id, swag_op_linear_merge> {\n    LinearFunctionQueue()\
    \ : SlidingWindowAggregation<pair<T, T>, pair<T, T>, swag_op_id, swag_op_linear_merge>::SlidingWindowAggregation(pair<T,\
    \ T>(1, 0)) {}\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: other_data_structures/sliding_window_aggregation.hpp
  requiredBy: []
  timestamp: '2021-01-01 16:38:37+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - other_data_structures/test/queue_operate_all_composite.test.cpp
documentation_of: other_data_structures/sliding_window_aggregation.hpp
layout: document
redirect_from:
- /library/other_data_structures/sliding_window_aggregation.hpp
- /library/other_data_structures/sliding_window_aggregation.hpp.html
title: other_data_structures/sliding_window_aggregation.hpp
---
