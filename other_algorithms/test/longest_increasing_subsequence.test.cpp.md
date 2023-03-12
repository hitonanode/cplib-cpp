---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other_algorithms/longest_increasing_subsequence.hpp
    title: "Longest increasing subsequence \uFF08LIS, \u6700\u9577\u5897\u52A0\u90E8\
      \u5206\u5217\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/longest_increasing_subsequence
    links:
    - https://judge.yosupo.jp/problem/longest_increasing_subsequence
  bundledCode: "#line 2 \"other_algorithms/longest_increasing_subsequence.hpp\"\n\
    #include <algorithm>\n#include <memory>\n#include <vector>\n\nenum class LisType\
    \ {\n    StrictlyIncreasing,\n    Nondecreasing,\n};\n\n// Calculate (only) length\
    \ of longest increasing subsequence (LIS)\n// Complexity: O(n log n)\ntemplate\
    \ <class T>\nint lis_length(const std::vector<T> &seq, LisType lis_type = LisType::StrictlyIncreasing)\
    \ {\n    std::vector<T> dp;\n    for (const T &x : seq) {\n        if (auto itr\
    \ = (lis_type == LisType::StrictlyIncreasing\n                            ? std::lower_bound(begin(dp),\
    \ end(dp), x)\n                            : std::upper_bound(begin(dp), end(dp),\
    \ x));\n            itr == end(dp)) {\n            dp.push_back(x);\n        }\
    \ else {\n            *itr = x;\n        }\n    }\n    return dp.size();\n}\n\n\
    template <class T> struct longest_increasing_subsequence {\n\n    LisType lis_type_\
    \ = LisType::StrictlyIncreasing;\n    int current_idx = 0;\n\n    struct Node\
    \ {\n        std::shared_ptr<Node> par;\n        int len, idx;\n        T v;\n\
    \    };\n\n    std::vector<T> dp;\n    std::vector<std::shared_ptr<Node>> ptrs;\n\
    \n    // Complexity: O(1)\n    longest_increasing_subsequence(LisType lis_type)\
    \ : lis_type_(lis_type) {}\n\n    // Complexity: O(N log N)\n    longest_increasing_subsequence(const\
    \ std::vector<T> &seq, LisType lis_type)\n        : lis_type_(lis_type) {\n  \
    \      for (const T &x : seq) add(x);\n    }\n\n    // Complexity: O(log N)\n\
    \    std::shared_ptr<Node> add(const T &x) {\n        auto itr =\n           \
    \ (lis_type_ == LisType::StrictlyIncreasing ? std::lower_bound(begin(dp), end(dp),\
    \ x)\n                                                      : std::upper_bound(begin(dp),\
    \ end(dp), x));\n        int cur = std::distance(begin(dp), itr);\n        std::shared_ptr<Node>\
    \ prv = (begin(dp) == itr ? nullptr : ptrs.at(cur - 1));\n\n        std::shared_ptr<Node>\
    \ node(\n            new Node{prv, (prv == nullptr ? 0 : prv->len) + 1, current_idx++,\
    \ x});\n\n        if (itr == end(dp)) {\n            dp.push_back(x), ptrs.push_back(node);\n\
    \        } else {\n            dp.at(cur) = x, ptrs.at(cur) = node;\n        }\n\
    \        return node;\n    }\n\n    std::shared_ptr<Node> head() const { return\
    \ ptrs.empty() ? nullptr : ptrs.back(); }\n\n    // LIS \u3092\u306A\u3059\u6DFB\
    \u5B57\u5217\u3092\u51FA\u529B\n    // Complexity: O(N)\n    std::vector<int>\
    \ get_lis_indices() const {\n        std::vector<int> ret;\n        for (auto\
    \ ptr = head(); ptr != nullptr; ptr = ptr->par) ret.push_back(ptr->idx);\n   \
    \     std::reverse(ret.begin(), ret.end());\n        return ret;\n    }\n};\n\
    #line 2 \"other_algorithms/test/longest_increasing_subsequence.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/longest_increasing_subsequence\"\n\
    \n#include <cassert>\n#include <iostream>\n\nusing namespace std;\n\nint main()\
    \ {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\n    int N;\n    cin\
    \ >> N;\n    std::vector<int> A(N);\n    for (auto &x : A) cin >> x;\n\n    auto\
    \ lis_idxs = longest_increasing_subsequence(A, LisType::StrictlyIncreasing).get_lis_indices();\n\
    \    assert(lis_idxs.size() == lis_length(A, LisType::StrictlyIncreasing));\n\n\
    \    cout << lis_idxs.size() << '\\n';\n    for (auto i : lis_idxs) cout << i\
    \ << ' ';\n    cout << '\\n';\n}\n"
  code: "#include \"../longest_increasing_subsequence.hpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/longest_increasing_subsequence\"\
    \n\n#include <cassert>\n#include <iostream>\n\nusing namespace std;\n\nint main()\
    \ {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\n    int N;\n    cin\
    \ >> N;\n    std::vector<int> A(N);\n    for (auto &x : A) cin >> x;\n\n    auto\
    \ lis_idxs = longest_increasing_subsequence(A, LisType::StrictlyIncreasing).get_lis_indices();\n\
    \    assert(lis_idxs.size() == lis_length(A, LisType::StrictlyIncreasing));\n\n\
    \    cout << lis_idxs.size() << '\\n';\n    for (auto i : lis_idxs) cout << i\
    \ << ' ';\n    cout << '\\n';\n}\n"
  dependsOn:
  - other_algorithms/longest_increasing_subsequence.hpp
  isVerificationFile: true
  path: other_algorithms/test/longest_increasing_subsequence.test.cpp
  requiredBy: []
  timestamp: '2023-03-12 20:19:26+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: other_algorithms/test/longest_increasing_subsequence.test.cpp
layout: document
redirect_from:
- /verify/other_algorithms/test/longest_increasing_subsequence.test.cpp
- /verify/other_algorithms/test/longest_increasing_subsequence.test.cpp.html
title: other_algorithms/test/longest_increasing_subsequence.test.cpp
---
