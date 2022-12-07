---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: combinatorics/test/hook_length_formulat.yuki2149.test.cpp
    title: combinatorics/test/hook_length_formulat.yuki2149.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://yukicoder.me/problems/no/2149
  bundledCode: "#line 1 \"combinatorics/hook_length_formula.hpp\"\n#include <algorithm>\n\
    #include <vector>\n\n// Hook length formula\n// Complexity: O(sum(hook))\n// Verify:\
    \ https://yukicoder.me/problems/no/2149\ntemplate <class T> T hook_length_formula(std::vector<int>\
    \ hook) {\n    if (hook.empty()) return T(1);\n    std::sort(hook.begin(), hook.end());\n\
    \    std::vector<int> len(hook.back());\n    T num(1), den(1);\n    int sum =\
    \ 0;\n    for (int l : hook) {\n        for (int j = 0; j < l; ++j) num *= ++sum,\
    \ den *= (++len.at(j)) + l - 1 - j;\n    }\n    return num / den;\n}\n"
  code: "#include <algorithm>\n#include <vector>\n\n// Hook length formula\n// Complexity:\
    \ O(sum(hook))\n// Verify: https://yukicoder.me/problems/no/2149\ntemplate <class\
    \ T> T hook_length_formula(std::vector<int> hook) {\n    if (hook.empty()) return\
    \ T(1);\n    std::sort(hook.begin(), hook.end());\n    std::vector<int> len(hook.back());\n\
    \    T num(1), den(1);\n    int sum = 0;\n    for (int l : hook) {\n        for\
    \ (int j = 0; j < l; ++j) num *= ++sum, den *= (++len.at(j)) + l - 1 - j;\n  \
    \  }\n    return num / den;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: combinatorics/hook_length_formula.hpp
  requiredBy: []
  timestamp: '2022-12-07 22:57:01+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - combinatorics/test/hook_length_formulat.yuki2149.test.cpp
documentation_of: combinatorics/hook_length_formula.hpp
layout: document
title: "Hook length formula (\u30D5\u30C3\u30AF\u9577\u516C\u5F0F)"
---

ヤング盤に対するフック長公式．

## 使用方法

```cpp
vector<int> a;

mint ret = hook_length_formula<mint>(a);
```

計算量は $n = \mathrm{len}(a)$ として $O(n \log n + \mathrm{sum}(a))$．

## 問題例

- [C - Numbering Blocks](https://atcoder.jp/contests/judge-update-202004/tasks/judge_update_202004_c)
- [No.2149 Vanitas Vanitatum - yukicoder](https://yukicoder.me/problems/no/2149)

## Links

- [フック長の公式 - Wikipedia](https://ja.wikipedia.org/wiki/%E3%83%95%E3%83%83%E3%82%AF%E9%95%B7%E3%81%AE%E5%85%AC%E5%BC%8F)
