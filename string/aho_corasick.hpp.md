---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: string/test/aho_corasick.deprecated.cpp
    title: string/test/aho_corasick.deprecated.cpp
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"string/aho_corasick.hpp\"\n#include <map>\n#include <queue>\n\
    #include <string>\n#include <vector>\nusing namespace std;\n\n// CUT begin\ntemplate<typename\
    \ T>\nstruct Trie\n{\n    vector<map<char, int>> child;\n    vector<int> fail;\n\
    \    vector<T> node_info;\n    int root;\n    Trie() : child(1), fail(1), node_info(1),\
    \ root(0) {}\n    void add_keyword(string str, T info)\n    {\n        int now\
    \ = 0;\n        for (auto c : str)\n        {\n            if (child[now].count(c)\
    \ == 0)\n            {\n                child[now][c] = fail.size();\n       \
    \         child.emplace_back(map<char, int>());\n                fail.emplace_back(root);\n\
    \                node_info.emplace_back(0);\n            }\n            now =\
    \ child[now][c];\n        }\n        node_info[now] += info;\n    }\n\n    void\
    \ build_aho_corasick()\n    {\n        queue<int> q;\n        for (auto pa : child[root])\
    \ q.push(pa.second);\n        while (!q.empty())\n        {\n            int s\
    \ = q.front();\n            q.pop();\n            for (auto pa : child[s])\n \
    \           {\n                int t = fail[s];\n                while (t and\
    \ child[t].count(pa.first) == 0) t = fail[t];\n                int u = (child[t].count(pa.first)\
    \ ? child[t][pa.first] : root);\n                fail[pa.second] = u;\n      \
    \          node_info[pa.second] += node_info[u];\n                q.push(pa.second);\n\
    \            }\n        }\n    }\n};\n"
  code: "#pragma once\n#include <map>\n#include <queue>\n#include <string>\n#include\
    \ <vector>\nusing namespace std;\n\n// CUT begin\ntemplate<typename T>\nstruct\
    \ Trie\n{\n    vector<map<char, int>> child;\n    vector<int> fail;\n    vector<T>\
    \ node_info;\n    int root;\n    Trie() : child(1), fail(1), node_info(1), root(0)\
    \ {}\n    void add_keyword(string str, T info)\n    {\n        int now = 0;\n\
    \        for (auto c : str)\n        {\n            if (child[now].count(c) ==\
    \ 0)\n            {\n                child[now][c] = fail.size();\n          \
    \      child.emplace_back(map<char, int>());\n                fail.emplace_back(root);\n\
    \                node_info.emplace_back(0);\n            }\n            now =\
    \ child[now][c];\n        }\n        node_info[now] += info;\n    }\n\n    void\
    \ build_aho_corasick()\n    {\n        queue<int> q;\n        for (auto pa : child[root])\
    \ q.push(pa.second);\n        while (!q.empty())\n        {\n            int s\
    \ = q.front();\n            q.pop();\n            for (auto pa : child[s])\n \
    \           {\n                int t = fail[s];\n                while (t and\
    \ child[t].count(pa.first) == 0) t = fail[t];\n                int u = (child[t].count(pa.first)\
    \ ? child[t][pa.first] : root);\n                fail[pa.second] = u;\n      \
    \          node_info[pa.second] += node_info[u];\n                q.push(pa.second);\n\
    \            }\n        }\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: string/aho_corasick.hpp
  requiredBy:
  - string/test/aho_corasick.deprecated.cpp
  timestamp: '2020-03-07 22:54:47+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: string/aho_corasick.hpp
layout: document
redirect_from:
- /library/string/aho_corasick.hpp
- /library/string/aho_corasick.hpp.html
title: string/aho_corasick.hpp
---
