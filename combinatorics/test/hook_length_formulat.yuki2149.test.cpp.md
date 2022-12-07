---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: combinatorics/hook_length_formula.hpp
    title: "Hook length formula (\u30D5\u30C3\u30AF\u9577\u516C\u5F0F)"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/2149
    links:
    - https://yukicoder.me/problems/no/2149
  bundledCode: "#line 1 \"combinatorics/test/hook_length_formulat.yuki2149.test.cpp\"\
    \n#define PROBLEM \"https://yukicoder.me/problems/no/2149\"\n#line 1 \"combinatorics/hook_length_formula.hpp\"\
    \n#include <algorithm>\n#include <vector>\n\n// Hook length formula\n// Complexity:\
    \ O(sum(hook))\n// Verify: https://yukicoder.me/problems/no/2149\ntemplate <class\
    \ T> T hook_length_formula(std::vector<int> hook) {\n    if (hook.empty()) return\
    \ T(1);\n    std::sort(hook.begin(), hook.end());\n    std::vector<int> len(hook.back());\n\
    \    T num(1), den(1);\n    int sum = 0;\n    for (int l : hook) {\n        for\
    \ (int j = 0; j < l; ++j) num *= ++sum, den *= (++len.at(j)) + l - 1 - j;\n  \
    \  }\n    return num / den;\n}\n#line 3 \"combinatorics/test/hook_length_formulat.yuki2149.test.cpp\"\
    \n\n#line 5 \"combinatorics/test/hook_length_formulat.yuki2149.test.cpp\"\n#include\
    \ <iostream>\n#include <utility>\n#line 8 \"combinatorics/test/hook_length_formulat.yuki2149.test.cpp\"\
    \nusing namespace std;\n\n#include <atcoder/modint>\nusing mint = atcoder::modint998244353;\n\
    \npair<int, mint> solve(const vector<int> &v) {\n    vector<int> hook;\n    int\
    \ n0 = 0;\n    int total_move = 0;\n    for (auto x : v) {\n        if (x == 0)\
    \ {\n            ++n0;\n        } else if (n0) {\n            total_move += n0;\n\
    \            hook.push_back(n0);\n        }\n    }\n    mint ret = hook_length_formula<mint>(hook);\n\
    \    return {total_move, ret};\n}\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    int N;\n    cin >> N;\n\n    vector<int> seq;\n    int lasta = 0;\n    while\
    \ (N--) {\n        int a;\n        cin >> a;\n        seq.resize(seq.size() +\
    \ a - lasta, 0);\n        seq.push_back(1);\n        lasta = a;\n    }\n\n   \
    \ vector<int> v0, v1;\n    for (int i = 0; i < int(seq.size()); ++i) { (i % 2\
    \ ? v1 : v0).push_back(seq.at(i)); }\n    const int n0 = count(v0.cbegin(), v0.cend(),\
    \ 1);\n    const int n1 = count(v1.cbegin(), v1.cend(), 1);\n    if (n0 < n1 or\
    \ n1 + 1 < n0) {\n        puts(\"0\");\n        return 0;\n    }\n    auto [len0,\
    \ sol0] = solve(v0);\n    auto [len1, sol1] = solve(v1);\n    mint ret = sol0\
    \ * sol1;\n    mint den = 1;\n    for (int i = 0; i < len0; ++i) ret *= len0 +\
    \ len1 - i, den *= i + 1;\n    cout << (ret / den).val() << endl;\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/2149\"\n#include \"../hook_length_formula.hpp\"\
    \n\n#include <algorithm>\n#include <iostream>\n#include <utility>\n#include <vector>\n\
    using namespace std;\n\n#include <atcoder/modint>\nusing mint = atcoder::modint998244353;\n\
    \npair<int, mint> solve(const vector<int> &v) {\n    vector<int> hook;\n    int\
    \ n0 = 0;\n    int total_move = 0;\n    for (auto x : v) {\n        if (x == 0)\
    \ {\n            ++n0;\n        } else if (n0) {\n            total_move += n0;\n\
    \            hook.push_back(n0);\n        }\n    }\n    mint ret = hook_length_formula<mint>(hook);\n\
    \    return {total_move, ret};\n}\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    int N;\n    cin >> N;\n\n    vector<int> seq;\n    int lasta = 0;\n    while\
    \ (N--) {\n        int a;\n        cin >> a;\n        seq.resize(seq.size() +\
    \ a - lasta, 0);\n        seq.push_back(1);\n        lasta = a;\n    }\n\n   \
    \ vector<int> v0, v1;\n    for (int i = 0; i < int(seq.size()); ++i) { (i % 2\
    \ ? v1 : v0).push_back(seq.at(i)); }\n    const int n0 = count(v0.cbegin(), v0.cend(),\
    \ 1);\n    const int n1 = count(v1.cbegin(), v1.cend(), 1);\n    if (n0 < n1 or\
    \ n1 + 1 < n0) {\n        puts(\"0\");\n        return 0;\n    }\n    auto [len0,\
    \ sol0] = solve(v0);\n    auto [len1, sol1] = solve(v1);\n    mint ret = sol0\
    \ * sol1;\n    mint den = 1;\n    for (int i = 0; i < len0; ++i) ret *= len0 +\
    \ len1 - i, den *= i + 1;\n    cout << (ret / den).val() << endl;\n}\n"
  dependsOn:
  - combinatorics/hook_length_formula.hpp
  isVerificationFile: true
  path: combinatorics/test/hook_length_formulat.yuki2149.test.cpp
  requiredBy: []
  timestamp: '2022-12-07 22:57:01+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: combinatorics/test/hook_length_formulat.yuki2149.test.cpp
layout: document
redirect_from:
- /verify/combinatorics/test/hook_length_formulat.yuki2149.test.cpp
- /verify/combinatorics/test/hook_length_formulat.yuki2149.test.cpp.html
title: combinatorics/test/hook_length_formulat.yuki2149.test.cpp
---
