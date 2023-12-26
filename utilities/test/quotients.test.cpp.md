---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: utilities/quotients.hpp
    title: "Quotients of integer \uFF08\u5546\u5217\u6319\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/enumerate_quotients
    links:
    - https://judge.yosupo.jp/problem/enumerate_quotients
  bundledCode: "#line 1 \"utilities/test/quotients.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/enumerate_quotients\"\n#line 2 \"utilities/quotients.hpp\"\
    \n#include <algorithm>\n#include <vector>\n\n// Generate all quotients of n\n\
    // return: n/1, n/2, ..., n\n// Complexity: O(sqrt(n))\ntemplate <class T = long\
    \ long> std::vector<T> get_quotients(T n) {\n    std::vector<T> res;\n    for\
    \ (T x = 1;; ++x) {\n        if (x * x >= n) {\n            const int sz = res.size();\n\
    \            if (x * x == n) res.push_back(x);\n            res.reserve(res.size()\
    \ + sz);\n            for (int i = sz - 1; i >= 0; --i) {\n                T tmp\
    \ = n / res.at(i);\n                if (tmp < x) continue;\n                if\
    \ (tmp == x and tmp * tmp == n) continue;\n                res.push_back(tmp);\n\
    \            }\n            return res;\n        } else {\n            res.push_back(x);\n\
    \        }\n    }\n}\n#line 3 \"utilities/test/quotients.test.cpp\"\n\n#include\
    \ <iostream>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr);\n  \
    \  ios::sync_with_stdio(false);\n\n    long long N;\n    cin >> N;\n\n    auto\
    \ ret = get_quotients(N);\n    cout << ret.size() << '\\n';\n    for (auto x :\
    \ ret) cout << x << ' ';\n    cout << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/enumerate_quotients\"\n\
    #include \"../quotients.hpp\"\n\n#include <iostream>\nusing namespace std;\n\n\
    int main() {\n    cin.tie(nullptr);\n    ios::sync_with_stdio(false);\n\n    long\
    \ long N;\n    cin >> N;\n\n    auto ret = get_quotients(N);\n    cout << ret.size()\
    \ << '\\n';\n    for (auto x : ret) cout << x << ' ';\n    cout << '\\n';\n}\n"
  dependsOn:
  - utilities/quotients.hpp
  isVerificationFile: true
  path: utilities/test/quotients.test.cpp
  requiredBy: []
  timestamp: '2023-12-26 22:24:23+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: utilities/test/quotients.test.cpp
layout: document
redirect_from:
- /verify/utilities/test/quotients.test.cpp
- /verify/utilities/test/quotients.test.cpp.html
title: utilities/test/quotients.test.cpp
---
