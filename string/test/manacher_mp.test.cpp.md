---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/manacher.hpp
    title: string/manacher.hpp
  - icon: ':heavy_check_mark:'
    path: string/mp_algorithm.hpp
    title: string/mp_algorithm.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2934
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2934
  bundledCode: "#line 1 \"string/test/manacher_mp.test.cpp\"\n#include <iostream>\n\
    #include <string>\n#include <vector>\n#line 4 \"string/manacher.hpp\"\n\n// CUT\
    \ begin\n// Manacher's Algorithm: radius of palindromes\n// Input: std::string\
    \ of length N\n// Output: std::vector<int> of size N\n// Complexity: O(N)\n//\
    \ Sample:\n// - `sakanakanandaka` -> [1, 1, 2, 1, 4, 1, 4, 1, 2, 2, 1, 1, 1, 2,\
    \ 1]\n// Reference: <https://snuke.hatenablog.com/entry/2014/12/02/235837>\nstd::vector<int>\
    \ manacher(std::string S)\n{\n    std::vector<int> res(S.length());\n    int i\
    \ = 0, j = 0;\n    while (i < (int)S.size()) {\n        while (i - j >= 0 and\
    \ i + j < (int)S.size() and S[i - j] == S[i + j]) j++;\n        res[i] = j;\n\
    \        int k = 1;\n        while (i - k >= 0 and i + k < (int)S.size() and k\
    \ + res[i - k] < j) res[i + k] = res[i - k], k++;\n        i += k, j -= k;\n \
    \   }\n    return res;\n}\n#line 4 \"string/mp_algorithm.hpp\"\n\n// CUT begin\n\
    std::vector<int> mp_algorithm(std::string s) {\n    int N = s.length();\n    std::vector<int>\
    \ ret(N + 1, -1);\n    int j = -1;\n    for (int i = 0; i < N;  i++) {\n     \
    \   while (j >= 0 and s[i] != s[j]) j = ret[j];\n        ret[i + 1] = ++j;\n \
    \   }\n    return ret;\n}\n#line 6 \"string/test/manacher_mp.test.cpp\"\n#define\
    \ PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2934\"\n\
    using namespace std;\n\nint main()\n{\n    int N;\n    string T;\n    cin >> N\
    \ >> T;\n\n    vector<int> mp = mp_algorithm(T);\n    vector<int> mana = manacher(T);\n\
    \n    int rep = N - mp[N];\n    for (int i = 2; i <= N; i++)\n    {\n        if\
    \ (i + mana[i - 1] - 1 == N)\n        {\n            cout << i << endl;\n    \
    \        return 0;\n        }\n        if (mana[i - 1] < i) continue;\n      \
    \  if ((2 * i - 2) % rep == 0) {\n            cout << i << endl;\n           \
    \ return 0;\n        }\n    }\n}\n"
  code: "#include <iostream>\n#include <string>\n#include <vector>\n#include \"string/manacher.hpp\"\
    \n#include \"string/mp_algorithm.hpp\"\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2934\"\
    \nusing namespace std;\n\nint main()\n{\n    int N;\n    string T;\n    cin >>\
    \ N >> T;\n\n    vector<int> mp = mp_algorithm(T);\n    vector<int> mana = manacher(T);\n\
    \n    int rep = N - mp[N];\n    for (int i = 2; i <= N; i++)\n    {\n        if\
    \ (i + mana[i - 1] - 1 == N)\n        {\n            cout << i << endl;\n    \
    \        return 0;\n        }\n        if (mana[i - 1] < i) continue;\n      \
    \  if ((2 * i - 2) % rep == 0) {\n            cout << i << endl;\n           \
    \ return 0;\n        }\n    }\n}\n"
  dependsOn:
  - string/manacher.hpp
  - string/mp_algorithm.hpp
  isVerificationFile: true
  path: string/test/manacher_mp.test.cpp
  requiredBy: []
  timestamp: '2020-03-07 22:54:47+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: string/test/manacher_mp.test.cpp
layout: document
redirect_from:
- /verify/string/test/manacher_mp.test.cpp
- /verify/string/test/manacher_mp.test.cpp.html
title: string/test/manacher_mp.test.cpp
---
