---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: utilities/int_kth_root.hpp
    title: utilities/int_kth_root.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/kth_root_integer
    links:
    - https://judge.yosupo.jp/problem/kth_root_integer
  bundledCode: "#line 1 \"utilities/test/kth_root_integer.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/kth_root_integer\"\n#line 2 \"utilities/int_kth_root.hpp\"\
    \n\n// floor(a^(1/k)) (the largest x s.t. x^k doesn't exceed a)\n// Constraints:\
    \ a >= 0, k > 0\nunsigned long long int_kth_root(unsigned long long a, int k)\
    \ {\n    using Int = __int128;\n    if (a == 0) {\n        return 0;\n    } else\
    \ if (k == 1) {\n        return a;\n    } else {\n        Int ok = 1, ng = Int(a)\
    \ + 1;\n        while (ng - ok > 1) {\n            Int c = (ok + ng) / 2, p =\
    \ c;\n            for (int t = 0; t < k - 1; t++) {\n                p *= c;\n\
    \                if (p > a) break;\n            }\n            (p > a ? ng : ok)\
    \ = c;\n        }\n        return ok;\n    }\n}\n#line 3 \"utilities/test/kth_root_integer.test.cpp\"\
    \n#include <iostream>\nusing namespace std;\n\nint main()\n{\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n\n    int T;\n    cin >> T;\n    while (T--) {\n\
    \        unsigned long long a;\n        int k;\n        cin >> a >> k;\n     \
    \   cout << int_kth_root(a, k) << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/kth_root_integer\"\n#include\
    \ \"utilities/int_kth_root.hpp\"\n#include <iostream>\nusing namespace std;\n\n\
    int main()\n{\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\n    int T;\n\
    \    cin >> T;\n    while (T--) {\n        unsigned long long a;\n        int\
    \ k;\n        cin >> a >> k;\n        cout << int_kth_root(a, k) << '\\n';\n \
    \   }\n}\n"
  dependsOn:
  - utilities/int_kth_root.hpp
  isVerificationFile: true
  path: utilities/test/kth_root_integer.test.cpp
  requiredBy: []
  timestamp: '2020-11-15 01:44:41+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: utilities/test/kth_root_integer.test.cpp
layout: document
redirect_from:
- /verify/utilities/test/kth_root_integer.test.cpp
- /verify/utilities/test/kth_root_integer.test.cpp.html
title: utilities/test/kth_root_integer.test.cpp
---
