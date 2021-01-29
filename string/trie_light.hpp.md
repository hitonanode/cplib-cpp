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
    \n// CUT begin\nstruct Trie {\n    char a_init;\n    int D;\n    int INVALID =\
    \ -1;\n    std::vector<std::vector<int>> child;\n    using T_NODE = int;\n   \
    \ std::vector<T_NODE> v_info;\n    Trie(char a_init = 'a', int D = 26) : a_init(a_init),\
    \ D(D), child(1, std::vector<int>(D, INVALID)), v_info(1) {}\n    void add_word(const\
    \ std::string &str, T_NODE info) {\n        int now = 0;\n        for (auto &c\
    \ : str) {\n            if (child[now][c - a_init] == INVALID) {\n           \
    \     child[now][c - a_init] = child.size();\n                child.emplace_back(std::vector<int>(D,\
    \ INVALID));\n                v_info.resize(child.size());\n            }\n  \
    \          now = child[now][c - a_init];\n        }\n        v_info[now] += info;\n\
    \    }\n};\n"
  code: "#include <string>\n#include <vector>\n\n// CUT begin\nstruct Trie {\n   \
    \ char a_init;\n    int D;\n    int INVALID = -1;\n    std::vector<std::vector<int>>\
    \ child;\n    using T_NODE = int;\n    std::vector<T_NODE> v_info;\n    Trie(char\
    \ a_init = 'a', int D = 26) : a_init(a_init), D(D), child(1, std::vector<int>(D,\
    \ INVALID)), v_info(1) {}\n    void add_word(const std::string &str, T_NODE info)\
    \ {\n        int now = 0;\n        for (auto &c : str) {\n            if (child[now][c\
    \ - a_init] == INVALID) {\n                child[now][c - a_init] = child.size();\n\
    \                child.emplace_back(std::vector<int>(D, INVALID));\n         \
    \       v_info.resize(child.size());\n            }\n            now = child[now][c\
    \ - a_init];\n        }\n        v_info[now] += info;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: string/trie_light.hpp
  requiredBy: []
  timestamp: '2020-11-18 20:25:12+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: string/trie_light.hpp
layout: document
redirect_from:
- /library/string/trie_light.hpp
- /library/string/trie_light.hpp.html
title: string/trie_light.hpp
---
