---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"string/trie_light.hpp\"\n#include <string>\n#include <vector>\n\
    \nstruct Trie {\n    char a_init;\n    int D;\n    int INVALID = -1;\n    std::vector<std::vector<int>>\
    \ child;\n    std::vector<int> par;\n\n    using T_NODE = int;\n    std::vector<T_NODE>\
    \ v_info;\n\n    Trie(char a_init = 'a', int D = 26)\n        : a_init(a_init),\
    \ D(D), child(1, std::vector<int>(D, INVALID)), par(1, -1), v_info(1) {}\n\n \
    \   int step(int now, char c) const {\n        if (now == INVALID) return INVALID;\n\
    \        return child.at(now).at(c - a_init);\n    }\n\n    int add_word(const\
    \ std::string &str, T_NODE info) {\n        int now = 0;\n        for (auto &c\
    \ : str) {\n            if (child[now][c - a_init] == INVALID) {\n           \
    \     par.push_back(now);\n                child[now][c - a_init] = child.size();\n\
    \                child.emplace_back(D, INVALID);\n                v_info.resize(child.size());\n\
    \            }\n            now = child[now][c - a_init];\n        }\n       \
    \ v_info[now] += info;\n        return now;\n    }\n};\n"
  code: "#include <string>\n#include <vector>\n\nstruct Trie {\n    char a_init;\n\
    \    int D;\n    int INVALID = -1;\n    std::vector<std::vector<int>> child;\n\
    \    std::vector<int> par;\n\n    using T_NODE = int;\n    std::vector<T_NODE>\
    \ v_info;\n\n    Trie(char a_init = 'a', int D = 26)\n        : a_init(a_init),\
    \ D(D), child(1, std::vector<int>(D, INVALID)), par(1, -1), v_info(1) {}\n\n \
    \   int step(int now, char c) const {\n        if (now == INVALID) return INVALID;\n\
    \        return child.at(now).at(c - a_init);\n    }\n\n    int add_word(const\
    \ std::string &str, T_NODE info) {\n        int now = 0;\n        for (auto &c\
    \ : str) {\n            if (child[now][c - a_init] == INVALID) {\n           \
    \     par.push_back(now);\n                child[now][c - a_init] = child.size();\n\
    \                child.emplace_back(D, INVALID);\n                v_info.resize(child.size());\n\
    \            }\n            now = child[now][c - a_init];\n        }\n       \
    \ v_info[now] += info;\n        return now;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: string/trie_light.hpp
  requiredBy: []
  timestamp: '2023-12-09 22:52:11+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: string/trie_light.hpp
layout: document
redirect_from:
- /library/string/trie_light.hpp
- /library/string/trie_light.hpp.html
title: string/trie_light.hpp
---
