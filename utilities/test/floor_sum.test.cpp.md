---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: utilities/floor_sum.hpp
    title: floor sum
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/sum_of_floor_of_linear
    links:
    - https://judge.yosupo.jp/problem/sum_of_floor_of_linear
  bundledCode: "#line 1 \"utilities/test/floor_sum.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/sum_of_floor_of_linear\"\n#line 2 \"utilities/floor_sum.hpp\"\
    \n#include <utility>\n\n// CUT begin\n// \\sum_{i=0}^{n-1} floor((ai + b) / m)\n\
    // 0 <= n < 2e32\n// 1 <= m < 2e32\n// 0 <= a, b < m\n// Complexity: O(lg(m))\n\
    long long floor_sum(long long n, long long m, long long a, long long b) {\n  \
    \  auto safe_mod = [](long long x, long long m) -> long long {\n        x %= m;\n\
    \        if (x < 0) x += m;\n        return x;\n    };\n    auto floor_sum_unsigned\
    \ = [](unsigned long long n, unsigned long long m, unsigned long long a,\n   \
    \                              unsigned long long b) -> unsigned long long {\n\
    \        unsigned long long ans = 0;\n        while (true) {\n            if (a\
    \ >= m) {\n                ans += n * (n - 1) / 2 * (a / m);\n               \
    \ a %= m;\n            }\n            if (b >= m) {\n                ans += n\
    \ * (b / m);\n                b %= m;\n            }\n\n            unsigned long\
    \ long y_max = a * n + b;\n            if (y_max < m) break;\n            // y_max\
    \ < m * (n + 1)\n            // floor(y_max / m) <= n\n            n = (unsigned\
    \ long long)(y_max / m);\n            b = (unsigned long long)(y_max % m);\n \
    \           std::swap(m, a);\n        }\n        return ans;\n    };\n\n    unsigned\
    \ long long ans = 0;\n    if (a < 0) {\n        unsigned long long a2 = safe_mod(a,\
    \ m);\n        ans -= 1ULL * n * (n - 1) / 2 * ((a2 - a) / m);\n        a = a2;\n\
    \    }\n    if (b < 0) {\n        unsigned long long b2 = safe_mod(b, m);\n  \
    \      ans -= 1ULL * n * ((b2 - b) / m);\n        b = b2;\n    }\n    return ans\
    \ + floor_sum_unsigned(n, m, a, b);\n}\n#line 3 \"utilities/test/floor_sum.test.cpp\"\
    \n#include <iostream>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n    int T;\n    cin >> T;\n    while (T--) {\n\
    \        int N, M, A, B;\n        cin >> N >> M >> A >> B;\n        cout << floor_sum(N,\
    \ M, A, B) << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/sum_of_floor_of_linear\"\
    \n#include \"../floor_sum.hpp\"\n#include <iostream>\nusing namespace std;\n\n\
    int main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n    int T;\n\
    \    cin >> T;\n    while (T--) {\n        int N, M, A, B;\n        cin >> N >>\
    \ M >> A >> B;\n        cout << floor_sum(N, M, A, B) << '\\n';\n    }\n}\n"
  dependsOn:
  - utilities/floor_sum.hpp
  isVerificationFile: true
  path: utilities/test/floor_sum.test.cpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: utilities/test/floor_sum.test.cpp
layout: document
redirect_from:
- /verify/utilities/test/floor_sum.test.cpp
- /verify/utilities/test/floor_sum.test.cpp.html
title: utilities/test/floor_sum.test.cpp
---
