---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: other_data_structures/test/queue_operate_all_composite.test.cpp
    title: other_data_structures/test/queue_operate_all_composite.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links:
    - https://github.com/NiMiLib/NoshiMochiLibrary/blob/queue_aggregation/lib/data_structure/sequence/queue_aggregation.hpp>
    - https://www.hackerrank.com/contests/tsg-live-4-programming-contest/challenges/tsg-live-4-procon-lcm-interval/submissions/code/1317888077>
  bundledCode: "#line 2 \"other_data_structures/sliding_window_aggregation.hpp\"\n\
    #include <stack>\n#include <utility>\nusing namespace std;\n\n// CUT begin\n//\
    \ Sliding-Window Aggregation based queue\n// - `std::queue`-like data structure\
    \ with monoid operation\n// - Each operation is amortized O(1)\n// - Verification:\
    \ <https://www.hackerrank.com/contests/tsg-live-4-programming-contest/challenges/tsg-live-4-procon-lcm-interval/submissions/code/1317888077>\n\
    // - Reference: <https://github.com/NiMiLib/NoshiMochiLibrary/blob/queue_aggregation/lib/data_structure/sequence/queue_aggregation.hpp>\n\
    template<typename T_VAL, typename T_PROD, typename VAL2PROD, typename MERGE>\n\
    struct SlidingWindowAggregation\n{\n    stack<pair<T_VAL, T_PROD>> front_stack,\
    \ back_stack;\n    VAL2PROD val2prod;\n    MERGE merge;\n    T_PROD ID_;\n\n \
    \   SlidingWindowAggregation(VAL2PROD v2p, MERGE pp2p, T_PROD id_prod)\n     \
    \   : val2prod(v2p), merge(pp2p), ID_(id_prod) {}\n    bool empty() const { return\
    \ front_stack.empty() and back_stack.empty(); }\n    int size() const { return\
    \ front_stack.size() + back_stack.size(); }\n    T_PROD fold_all() const {\n \
    \       if (empty()) return ID_;\n        else if (front_stack.empty()) return\
    \ back_stack.top().second;\n        else if (back_stack.empty()) return front_stack.top().second;\n\
    \        else return merge(front_stack.top().second, back_stack.top().second);\n\
    \    }\n    void push(const T_VAL &x) {\n        if (back_stack.empty()) back_stack.emplace(x,\
    \ val2prod(x));\n        else back_stack.emplace(x, merge(back_stack.top().second,\
    \ val2prod(x)));\n    }\n    T_VAL pop() {\n        if (front_stack.empty()) {\n\
    \            front_stack.emplace(back_stack.top().first, val2prod(back_stack.top().first));\n\
    \            back_stack.pop();\n            while (!back_stack.empty()) {\n  \
    \              T_VAL t = back_stack.top().first;\n                front_stack.emplace(t,\
    \ merge(val2prod(t), front_stack.top().second));\n                back_stack.pop();\n\
    \            }\n        }\n        T_VAL t = front_stack.top().first;\n      \
    \  front_stack.pop();\n        return t;\n    }\n};\n\nauto swag_op_id = [](auto\
    \ x) { return x; };\nauto swag_op_linear_merge = [](auto l, auto r) { return make_pair(l.first\
    \ * r.first, l.second * r.first + r.second); };\n\n// Linear function composition\n\
    // `f(x) = first * x + second`, operate most recently added function first\ntemplate\
    \ <typename T>\nstruct LinearFunctionQueue : public SlidingWindowAggregation<pair<T,\
    \ T>, pair<T, T>, decltype(swag_op_id), decltype(swag_op_linear_merge)>\n{\n \
    \   LinearFunctionQueue() : SlidingWindowAggregation<pair<T, T>, pair<T, T>, decltype(swag_op_id),\
    \ decltype(swag_op_linear_merge)>::SlidingWindowAggregation(swag_op_id, swag_op_linear_merge,\
    \ pair<T, T>(1, 0)) {}\n};\n"
  code: "#pragma once\n#include <stack>\n#include <utility>\nusing namespace std;\n\
    \n// CUT begin\n// Sliding-Window Aggregation based queue\n// - `std::queue`-like\
    \ data structure with monoid operation\n// - Each operation is amortized O(1)\n\
    // - Verification: <https://www.hackerrank.com/contests/tsg-live-4-programming-contest/challenges/tsg-live-4-procon-lcm-interval/submissions/code/1317888077>\n\
    // - Reference: <https://github.com/NiMiLib/NoshiMochiLibrary/blob/queue_aggregation/lib/data_structure/sequence/queue_aggregation.hpp>\n\
    template<typename T_VAL, typename T_PROD, typename VAL2PROD, typename MERGE>\n\
    struct SlidingWindowAggregation\n{\n    stack<pair<T_VAL, T_PROD>> front_stack,\
    \ back_stack;\n    VAL2PROD val2prod;\n    MERGE merge;\n    T_PROD ID_;\n\n \
    \   SlidingWindowAggregation(VAL2PROD v2p, MERGE pp2p, T_PROD id_prod)\n     \
    \   : val2prod(v2p), merge(pp2p), ID_(id_prod) {}\n    bool empty() const { return\
    \ front_stack.empty() and back_stack.empty(); }\n    int size() const { return\
    \ front_stack.size() + back_stack.size(); }\n    T_PROD fold_all() const {\n \
    \       if (empty()) return ID_;\n        else if (front_stack.empty()) return\
    \ back_stack.top().second;\n        else if (back_stack.empty()) return front_stack.top().second;\n\
    \        else return merge(front_stack.top().second, back_stack.top().second);\n\
    \    }\n    void push(const T_VAL &x) {\n        if (back_stack.empty()) back_stack.emplace(x,\
    \ val2prod(x));\n        else back_stack.emplace(x, merge(back_stack.top().second,\
    \ val2prod(x)));\n    }\n    T_VAL pop() {\n        if (front_stack.empty()) {\n\
    \            front_stack.emplace(back_stack.top().first, val2prod(back_stack.top().first));\n\
    \            back_stack.pop();\n            while (!back_stack.empty()) {\n  \
    \              T_VAL t = back_stack.top().first;\n                front_stack.emplace(t,\
    \ merge(val2prod(t), front_stack.top().second));\n                back_stack.pop();\n\
    \            }\n        }\n        T_VAL t = front_stack.top().first;\n      \
    \  front_stack.pop();\n        return t;\n    }\n};\n\nauto swag_op_id = [](auto\
    \ x) { return x; };\nauto swag_op_linear_merge = [](auto l, auto r) { return make_pair(l.first\
    \ * r.first, l.second * r.first + r.second); };\n\n// Linear function composition\n\
    // `f(x) = first * x + second`, operate most recently added function first\ntemplate\
    \ <typename T>\nstruct LinearFunctionQueue : public SlidingWindowAggregation<pair<T,\
    \ T>, pair<T, T>, decltype(swag_op_id), decltype(swag_op_linear_merge)>\n{\n \
    \   LinearFunctionQueue() : SlidingWindowAggregation<pair<T, T>, pair<T, T>, decltype(swag_op_id),\
    \ decltype(swag_op_linear_merge)>::SlidingWindowAggregation(swag_op_id, swag_op_linear_merge,\
    \ pair<T, T>(1, 0)) {}\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: other_data_structures/sliding_window_aggregation.hpp
  requiredBy: []
  timestamp: '2020-03-07 22:54:47+09:00'
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
