---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: utilities/floor_sum.hpp
    title: utilities/floor_sum.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/sum_of_floor_of_linear
    links:
    - https://judge.yosupo.jp/problem/sum_of_floor_of_linear
  bundledCode: "#line 1 \"utilities/test/floor_sum.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/sum_of_floor_of_linear\"\n#line 2 \"utilities/floor_sum.hpp\"\
    \n\n// CUT begin\n// \\sum_{i=0}^{n-1} floor((ai + b) / m)\n// 0 <= n <= 1e9\n\
    // 1 <= m <= 1e9\n// 0 <= a, b < m\n// Complexity: O(lg(n + m + a + b))\nlong\
    \ long floor_sum(long long n, long long m, long long a, long long b) {\n    long\
    \ long ans = 0;\n    if (a >= m) {\n        ans += (n - 1) * n * (a / m) / 2;\n\
    \        a %= m;\n    }\n    if (b >= m) {\n        ans += n * (b / m);\n    \
    \    b %= m;\n    }\n\n    long long y_max = (a * n + b) / m, x_max = (y_max *\
    \ m - b);\n    if (y_max == 0) return ans;\n    ans += (n - (x_max + a - 1) /\
    \ a) * y_max;\n    ans += floor_sum(y_max, a, m, (a - x_max % a) % a);\n    return\
    \ ans;\n}\n#line 3 \"utilities/test/floor_sum.test.cpp\"\n#include <iostream>\n\
    using namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \    int T;\n    cin >> T;\n    while (T--) {\n        int N, M, A, B;\n     \
    \   cin >> N >> M >> A >> B;\n        cout << floor_sum(N, M, A, B) << '\\n';\n\
    \    }\n}\n"
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
  timestamp: '2021-01-01 16:52:32+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: utilities/test/floor_sum.test.cpp
layout: document
redirect_from:
- /verify/utilities/test/floor_sum.test.cpp
- /verify/utilities/test/floor_sum.test.cpp.html
title: utilities/test/floor_sum.test.cpp
---
