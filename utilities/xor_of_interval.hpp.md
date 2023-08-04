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
    - https://codeforces.com/contest/1849/problem/F
  bundledCode: "#line 2 \"utilities/xor_of_interval.hpp\"\n#include <cassert>\n\n\
    // lo <= (x xor v) < hi \u306A\u308B x \u306E\u534A\u958B\u533A\u9593\u3092\u5217\
    \u6319\n// \uFF08lo \u4EE5\u4E0A hi \u672A\u6E80\u306E\u5404\u6574\u6570 \u3068\
    \ v \u306E xor \u3092\u3068\u308B\u3068\u3067\u304D\u308B O(log(hi - lo)) \u500B\
    \u306E\u534A\u958B\u533A\u9593\u3092\u5168\u5217\u6319\uFF09\n// Verify: https://codeforces.com/contest/1849/problem/F\n\
    template <class Int, class F> void xor_of_interval(Int v, Int lo, Int hi, F f)\
    \ {\n    assert(0 <= lo);\n    assert(0 <= v);\n\n    for (int d = 0; lo < hi;\
    \ lo /= 2, hi /= 2, v /= 2, ++d) {\n        if (lo & 1) {\n            f((lo ^\
    \ v) << d, ((lo ^ v) + 1) << d);\n            ++lo;\n        }\n        if (hi\
    \ & 1) {\n            --hi;\n            f((hi ^ v) << d, ((hi ^ v) + 1) << d);\n\
    \        }\n    }\n}\n"
  code: "#pragma once\n#include <cassert>\n\n// lo <= (x xor v) < hi \u306A\u308B\
    \ x \u306E\u534A\u958B\u533A\u9593\u3092\u5217\u6319\n// \uFF08lo \u4EE5\u4E0A\
    \ hi \u672A\u6E80\u306E\u5404\u6574\u6570 \u3068 v \u306E xor \u3092\u3068\u308B\
    \u3068\u3067\u304D\u308B O(log(hi - lo)) \u500B\u306E\u534A\u958B\u533A\u9593\u3092\
    \u5168\u5217\u6319\uFF09\n// Verify: https://codeforces.com/contest/1849/problem/F\n\
    template <class Int, class F> void xor_of_interval(Int v, Int lo, Int hi, F f)\
    \ {\n    assert(0 <= lo);\n    assert(0 <= v);\n\n    for (int d = 0; lo < hi;\
    \ lo /= 2, hi /= 2, v /= 2, ++d) {\n        if (lo & 1) {\n            f((lo ^\
    \ v) << d, ((lo ^ v) + 1) << d);\n            ++lo;\n        }\n        if (hi\
    \ & 1) {\n            --hi;\n            f((hi ^ v) << d, ((hi ^ v) + 1) << d);\n\
    \        }\n    }\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/xor_of_interval.hpp
  requiredBy: []
  timestamp: '2023-08-05 00:31:24+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utilities/xor_of_interval.hpp
layout: document
title: XOR of interval
---

非負整数の半開区間 $[\mathrm{lo}, \mathrm{hi})$ に含まれるそれぞれの整数と $v$ の排他的論理和 (XOR) をとった値の集合はたかだか $O(\log ( \mathrm{hi} - \mathrm{lo}))$ 個の半開区間となる．本関数はその全ての半開区間を列挙する．全ての半開区間の長さは 2 べきである．

## 使用方法

```cpp

int lo, hi;

int v;

xor_of_interval(v, lo, hi, [&](int l, int r) {
    // Do something for [l, r).
    // This function is called O(log(hi - lo)) times.
});

```

## 問題例

- [Educational Codeforces Round 152 (Rated for Div. 2) F. XOR Partition - Codeforces](https://codeforces.com/contest/1849/problem/F)
