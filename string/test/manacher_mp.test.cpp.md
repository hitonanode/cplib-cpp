---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/manacher.hpp
    title: "Longest palindromic substring enumeration (Manacher's algorithm) \uFF08\
      \u56DE\u6587\u9577\u914D\u5217\u69CB\u7BC9\uFF09"
  - icon: ':heavy_check_mark:'
    path: string/mp_algorithm.hpp
    title: string/mp_algorithm.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2934
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2934
  bundledCode: "#line 2 \"string/manacher.hpp\"\n#include <string>\n#include <utility>\n\
    #include <vector>\n\n// CUT begin\n// Manacher's Algorithm: radius of palindromes\n\
    // Input: std::string or std::vector<T> of length N\n// Output: std::vector<int>\
    \ of size N\n// Complexity: O(N)\n// Sample:\n// - `sakanakanandaka` -> [1, 1,\
    \ 2, 1, 4, 1, 4, 1, 2, 2, 1, 1, 1, 2, 1]\n// Reference: https://snuke.hatenablog.com/entry/2014/12/02/235837\n\
    template <typename T> std::vector<int> manacher(const std::vector<T> &S) {\n \
    \   std::vector<int> res(S.size());\n    int i = 0, j = 0;\n    while (i < int(S.size()))\
    \ {\n        while (i - j >= 0 and i + j < int(S.size()) and S[i - j] == S[i +\
    \ j]) j++;\n        res[i] = j;\n        int k = 1;\n        while (i - k >= 0\
    \ and i + k < int(S.size()) and k + res[i - k] < j)\n            res[i + k] =\
    \ res[i - k], k++;\n        i += k, j -= k;\n    }\n    return res;\n}\nstd::vector<int>\
    \ manacher(const std::string &S) {\n    std::vector<char> v(S.size());\n    for\
    \ (int i = 0; i < int(S.size()); i++) v[i] = S[i];\n    return manacher(v);\n\
    }\n\ntemplate <typename T>\nstd::vector<std::pair<int, int>> enumerate_palindromes(const\
    \ std::vector<T> &vec) {\n    std::vector<T> v;\n    const int N = vec.size();\n\
    \    for (int i = 0; i < N - 1; i++) {\n        v.push_back(vec[i]);\n       \
    \ v.push_back(-1);\n    }\n    v.push_back(vec.back());\n    const auto man =\
    \ manacher(v);\n    std::vector<std::pair<int, int>> ret;\n    for (int i = 0;\
    \ i < N * 2 - 1; i++) {\n        if (i & 1) {\n            int w = man[i] / 2;\n\
    \            ret.emplace_back((i + 1) / 2 - w, (i + 1) / 2 + w);\n        } else\
    \ {\n            int w = (man[i] - 1) / 2;\n            ret.emplace_back(i / 2\
    \ - w, i / 2 + w + 1);\n        }\n    }\n    return ret;\n}\n\nstd::vector<std::pair<int,\
    \ int>> enumerate_palindromes(const std::string &S) {\n    std::vector<char> v(S.size());\n\
    \    for (int i = 0; i < int(S.size()); i++) v[i] = S[i];\n    return enumerate_palindromes<char>(v);\n\
    }\n#line 4 \"string/mp_algorithm.hpp\"\n\n// CUT begin\n// MP (Morris-Pratt) algorithm\
    \ (length of longest nontrivial matching for\n// prefix & suffix of s[0:i] for\
    \ each i)\n// Input: std::string of length N\n// Output: std::vector<int> of size\
    \ N + 1\n// Complexity: O(N)\n// Sample:\n// - `teletelepathy` -> [-1, 0, 0, 0,\
    \ 0, 1, 2, 3, 4, 0, 0, 1, 0, 0]\n// Reference: <https://snuke.hatenablog.com/entry/2014/12/01/235807>\n\
    std::vector<int> mp_algorithm(std::string s) {\n    int N = s.length();\n    std::vector<int>\
    \ ret(N + 1, -1);\n    int j = -1;\n    for (int i = 0; i < N; i++) {\n      \
    \  while (j >= 0 and s[i] != s[j]) j = ret[j];\n        ret[i + 1] = ++j;\n  \
    \  }\n    return ret;\n}\n#line 3 \"string/test/manacher_mp.test.cpp\"\n#include\
    \ <iostream>\n#line 6 \"string/test/manacher_mp.test.cpp\"\n#define PROBLEM \"\
    http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2934\"\nusing namespace\
    \ std;\n\nint main() {\n    int N;\n    string T;\n    cin >> N >> T;\n\n    vector<int>\
    \ mp = mp_algorithm(T);\n    vector<int> mana = manacher(T);\n\n    int rep =\
    \ N - mp[N];\n    for (int i = 2; i <= N; i++) {\n        if (i + mana[i - 1]\
    \ - 1 == N) {\n            cout << i << '\\n';\n            return 0;\n      \
    \  }\n        if (mana[i - 1] < i) continue;\n        if ((2 * i - 2) % rep ==\
    \ 0) {\n            cout << i << '\\n';\n            return 0;\n        }\n  \
    \  }\n}\n"
  code: "#include \"../manacher.hpp\"\n#include \"../mp_algorithm.hpp\"\n#include\
    \ <iostream>\n#include <string>\n#include <vector>\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2934\"\
    \nusing namespace std;\n\nint main() {\n    int N;\n    string T;\n    cin >>\
    \ N >> T;\n\n    vector<int> mp = mp_algorithm(T);\n    vector<int> mana = manacher(T);\n\
    \n    int rep = N - mp[N];\n    for (int i = 2; i <= N; i++) {\n        if (i\
    \ + mana[i - 1] - 1 == N) {\n            cout << i << '\\n';\n            return\
    \ 0;\n        }\n        if (mana[i - 1] < i) continue;\n        if ((2 * i -\
    \ 2) % rep == 0) {\n            cout << i << '\\n';\n            return 0;\n \
    \       }\n    }\n}\n"
  dependsOn:
  - string/manacher.hpp
  - string/mp_algorithm.hpp
  isVerificationFile: true
  path: string/test/manacher_mp.test.cpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: string/test/manacher_mp.test.cpp
layout: document
redirect_from:
- /verify/string/test/manacher_mp.test.cpp
- /verify/string/test/manacher_mp.test.cpp.html
title: string/test/manacher_mp.test.cpp
---
