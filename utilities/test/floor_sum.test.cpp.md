---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: utilities/floor_sum.hpp
    title: floor sum
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
    \n#include <utility>\n\n// \\sum_{i=0}^{n-1} floor((ai + b) / m)\n// 0 <= n <\
    \ 2e32 (if Int is long long)\n// 1 <= m < 2e32 (if Int is long long)\n// 0 <=\
    \ a, b < m\n// Complexity: O(lg(m))\ntemplate <class Int, class Unsigned> Int\
    \ floor_sum(Int n, Int m, Int a, Int b) {\n    static_assert(-Int(1) < 0, \"Int\
    \ must be signed\");\n    static_assert(-Unsigned(1) > 0, \"Unsigned must be unsigned\"\
    );\n    static_assert(sizeof(Unsigned) >= sizeof(Int), \"Unsigned must be larger\
    \ than Int\");\n\n    auto safe_mod = [](Int x, Int m) -> Int {\n        x %=\
    \ m;\n        if (x < 0) x += m;\n        return x;\n    };\n    auto floor_sum_unsigned\
    \ = [](Unsigned n, Unsigned m, Unsigned a, Unsigned b) -> Unsigned {\n       \
    \ Unsigned ans = 0;\n        while (true) {\n            if (a >= m) {\n     \
    \           ans += n * (n - 1) / 2 * (a / m);\n                a %= m;\n     \
    \       }\n            if (b >= m) {\n                ans += n * (b / m);\n  \
    \              b %= m;\n            }\n\n            Unsigned y_max = a * n +\
    \ b;\n            if (y_max < m) break;\n            // y_max < m * (n + 1)\n\
    \            // floor(y_max / m) <= n\n            n = (Unsigned)(y_max / m);\n\
    \            b = (Unsigned)(y_max % m);\n            std::swap(m, a);\n      \
    \  }\n        return ans;\n    };\n\n    Unsigned ans = 0;\n    if (a < 0) {\n\
    \        Unsigned a2 = safe_mod(a, m);\n        ans -= Unsigned(1) * n * (n -\
    \ 1) / 2 * ((a2 - a) / m);\n        a = a2;\n    }\n    if (b < 0) {\n       \
    \ Unsigned b2 = safe_mod(b, m);\n        ans -= Unsigned(1) * n * ((b2 - b) /\
    \ m);\n        b = b2;\n    }\n    return ans + floor_sum_unsigned(n, m, a, b);\n\
    }\n#line 3 \"utilities/test/floor_sum.test.cpp\"\n#include <iostream>\nusing namespace\
    \ std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n \
    \   int T;\n    cin >> T;\n    while (T--) {\n        int N, M, A, B;\n      \
    \  cin >> N >> M >> A >> B;\n        cout << floor_sum<long long, unsigned long\
    \ long>(N, M, A, B) << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/sum_of_floor_of_linear\"\
    \n#include \"../floor_sum.hpp\"\n#include <iostream>\nusing namespace std;\n\n\
    int main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n    int T;\n\
    \    cin >> T;\n    while (T--) {\n        int N, M, A, B;\n        cin >> N >>\
    \ M >> A >> B;\n        cout << floor_sum<long long, unsigned long long>(N, M,\
    \ A, B) << '\\n';\n    }\n}\n"
  dependsOn:
  - utilities/floor_sum.hpp
  isVerificationFile: true
  path: utilities/test/floor_sum.test.cpp
  requiredBy: []
  timestamp: '2024-09-22 10:23:03+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: utilities/test/floor_sum.test.cpp
layout: document
redirect_from:
- /verify/utilities/test/floor_sum.test.cpp
- /verify/utilities/test/floor_sum.test.cpp.html
title: utilities/test/floor_sum.test.cpp
---
