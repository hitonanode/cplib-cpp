---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: string/aho_corasick.hpp
    title: string/aho_corasick.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D
  bundledCode: "#line 1 \"string/test/aho_corasick.deprecated.cpp\"\n#include <bitset>\n\
    #include <iostream>\n#line 2 \"string/aho_corasick.hpp\"\n#include <map>\n#include\
    \ <queue>\n#include <string>\n#include <vector>\nusing namespace std;\n\n// CUT\
    \ begin\ntemplate<typename T>\nstruct Trie\n{\n    vector<map<char, int>> child;\n\
    \    vector<int> fail;\n    vector<T> node_info;\n    int root;\n    Trie() :\
    \ child(1), fail(1), node_info(1), root(0) {}\n    void add_keyword(string str,\
    \ T info)\n    {\n        int now = 0;\n        for (auto c : str)\n        {\n\
    \            if (child[now].count(c) == 0)\n            {\n                child[now][c]\
    \ = fail.size();\n                child.emplace_back(map<char, int>());\n    \
    \            fail.emplace_back(root);\n                node_info.emplace_back(0);\n\
    \            }\n            now = child[now][c];\n        }\n        node_info[now]\
    \ += info;\n    }\n\n    void build_aho_corasick()\n    {\n        queue<int>\
    \ q;\n        for (auto pa : child[root]) q.push(pa.second);\n        while (!q.empty())\n\
    \        {\n            int s = q.front();\n            q.pop();\n           \
    \ for (auto pa : child[s])\n            {\n                int t = fail[s];\n\
    \                while (t and child[t].count(pa.first) == 0) t = fail[t];\n  \
    \              int u = (child[t].count(pa.first) ? child[t][pa.first] : root);\n\
    \                fail[pa.second] = u;\n                node_info[pa.second] +=\
    \ node_info[u];\n                q.push(pa.second);\n            }\n        }\n\
    \    }\n};\n#line 4 \"string/test/aho_corasick.deprecated.cpp\"\nusing namespace\
    \ std;\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D\"\
    \n\nvoid operator+=(bitset<10000> &l, const bitset<10000> &r) { l |= r; }\n\n\
    int main()\n{\n    Trie<bitset<10000>> trie;\n    string T;\n    cin >> T;\n \
    \   int N;\n    cin >> N;\n    for (int i = 0; i < N; i++)\n    {\n        string\
    \ P;\n        cin >> P;\n        bitset<10000> bs;\n        bs.set(i);\n     \
    \   trie.add_keyword(P, bs);\n    }\n    trie.build_aho_corasick();\n\n    int\
    \ now = 0;\n    bitset<10000> ans;\n    for (auto c : T)\n    {\n        while\
    \ (now and trie.child[now][c] == 0) now = trie.fail[now];\n        now = trie.child[now][c];\n\
    \        ans |= trie.node_info[now];\n    }\n    for (int i = 0; i < N; i++) cout\
    \ << ans[i] << endl;\n}\n"
  code: "#include <bitset>\n#include <iostream>\n#include \"string/aho_corasick.hpp\"\
    \nusing namespace std;\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D\"\
    \n\nvoid operator+=(bitset<10000> &l, const bitset<10000> &r) { l |= r; }\n\n\
    int main()\n{\n    Trie<bitset<10000>> trie;\n    string T;\n    cin >> T;\n \
    \   int N;\n    cin >> N;\n    for (int i = 0; i < N; i++)\n    {\n        string\
    \ P;\n        cin >> P;\n        bitset<10000> bs;\n        bs.set(i);\n     \
    \   trie.add_keyword(P, bs);\n    }\n    trie.build_aho_corasick();\n\n    int\
    \ now = 0;\n    bitset<10000> ans;\n    for (auto c : T)\n    {\n        while\
    \ (now and trie.child[now][c] == 0) now = trie.fail[now];\n        now = trie.child[now][c];\n\
    \        ans |= trie.node_info[now];\n    }\n    for (int i = 0; i < N; i++) cout\
    \ << ans[i] << endl;\n}\n"
  dependsOn:
  - string/aho_corasick.hpp
  isVerificationFile: false
  path: string/test/aho_corasick.deprecated.cpp
  requiredBy: []
  timestamp: '2020-03-07 22:54:47+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: string/test/aho_corasick.deprecated.cpp
layout: document
redirect_from:
- /library/string/test/aho_corasick.deprecated.cpp
- /library/string/test/aho_corasick.deprecated.cpp.html
title: string/test/aho_corasick.deprecated.cpp
---
