---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: other_data_structures/test/binary_trie.test.cpp
    title: other_data_structures/test/binary_trie.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"other_data_structures/binary_trie.hpp\"\n#include <vector>\n\
    \n// CUT begin\nstruct BinaryTrie\n{\n    using Int = int;\n    int maxD;\n  \
    \  std::vector<int> deg, sz;\n    std::vector<int> ch0, ch1, par;\n\n    int _new_node(int\
    \ id_par)\n    {\n        deg.emplace_back(0);\n        sz.emplace_back(0);\n\
    \        ch0.emplace_back(-1);\n        ch1.emplace_back(-1);\n        par.emplace_back(id_par);\n\
    \        return ch0.size() - 1;\n    }\n\n    BinaryTrie(int maxD = 0) : maxD(maxD)\n\
    \    {\n        _new_node(-1);\n    }\n    int _goto(Int x)\n    {\n        int\
    \ now = 0;\n        for (int d = maxD - 1; d >= 0; d--)\n        {\n         \
    \   int nxt = ((x >> d) & 1) ? ch1[now] : ch0[now];\n            if (nxt == -1)\n\
    \            {\n                nxt = _new_node(now);\n                (((x >>\
    \ d) & 1) ? ch1[now] : ch0[now]) = nxt;\n            }\n            now = nxt;\n\
    \        }\n        return now;\n    }\n\n    void insert(Int x)\n    {\n    \
    \    int now = _goto(x);\n        if (deg[now] == 0)\n        {\n            deg[now]\
    \ = 1;\n            while (now >= 0)\n            {\n                sz[now]++,\
    \ now = par[now];\n            }\n        }\n    }\n\n    void erase(Int x)\n\
    \    {\n        int now = _goto(x);\n        if (deg[now] > 0)\n        {\n  \
    \          deg[now] = 0;\n            while (now >= 0)\n            {\n      \
    \          sz[now]--, now = par[now];\n            }\n        }\n    }\n\n   \
    \ Int xor_min(Int x)\n    {\n        Int ret = 0;\n        int now = 0;\n    \
    \    if (!sz[now]) return -1;\n        for (int d = maxD - 1; d >= 0; d--)\n \
    \       {\n            int y = ((x >> d) & 1) ? ch1[now] : ch0[now];\n       \
    \     if (y != -1 and sz[y])\n            {\n                now = y;\n      \
    \      }\n            else\n            {\n                ret += Int(1) << d,\
    \ now = ch0[now] ^ ch1[now] ^ y;\n            }\n        }\n        return ret;\n\
    \    }\n};\n"
  code: "#pragma once\n#include <vector>\n\n// CUT begin\nstruct BinaryTrie\n{\n \
    \   using Int = int;\n    int maxD;\n    std::vector<int> deg, sz;\n    std::vector<int>\
    \ ch0, ch1, par;\n\n    int _new_node(int id_par)\n    {\n        deg.emplace_back(0);\n\
    \        sz.emplace_back(0);\n        ch0.emplace_back(-1);\n        ch1.emplace_back(-1);\n\
    \        par.emplace_back(id_par);\n        return ch0.size() - 1;\n    }\n\n\
    \    BinaryTrie(int maxD = 0) : maxD(maxD)\n    {\n        _new_node(-1);\n  \
    \  }\n    int _goto(Int x)\n    {\n        int now = 0;\n        for (int d =\
    \ maxD - 1; d >= 0; d--)\n        {\n            int nxt = ((x >> d) & 1) ? ch1[now]\
    \ : ch0[now];\n            if (nxt == -1)\n            {\n                nxt\
    \ = _new_node(now);\n                (((x >> d) & 1) ? ch1[now] : ch0[now]) =\
    \ nxt;\n            }\n            now = nxt;\n        }\n        return now;\n\
    \    }\n\n    void insert(Int x)\n    {\n        int now = _goto(x);\n       \
    \ if (deg[now] == 0)\n        {\n            deg[now] = 1;\n            while\
    \ (now >= 0)\n            {\n                sz[now]++, now = par[now];\n    \
    \        }\n        }\n    }\n\n    void erase(Int x)\n    {\n        int now\
    \ = _goto(x);\n        if (deg[now] > 0)\n        {\n            deg[now] = 0;\n\
    \            while (now >= 0)\n            {\n                sz[now]--, now =\
    \ par[now];\n            }\n        }\n    }\n\n    Int xor_min(Int x)\n    {\n\
    \        Int ret = 0;\n        int now = 0;\n        if (!sz[now]) return -1;\n\
    \        for (int d = maxD - 1; d >= 0; d--)\n        {\n            int y = ((x\
    \ >> d) & 1) ? ch1[now] : ch0[now];\n            if (y != -1 and sz[y])\n    \
    \        {\n                now = y;\n            }\n            else\n      \
    \      {\n                ret += Int(1) << d, now = ch0[now] ^ ch1[now] ^ y;\n\
    \            }\n        }\n        return ret;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: other_data_structures/binary_trie.hpp
  requiredBy: []
  timestamp: '2020-10-06 01:41:58+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - other_data_structures/test/binary_trie.test.cpp
documentation_of: other_data_structures/binary_trie.hpp
layout: document
redirect_from:
- /library/other_data_structures/binary_trie.hpp
- /library/other_data_structures/binary_trie.hpp.html
title: other_data_structures/binary_trie.hpp
---
