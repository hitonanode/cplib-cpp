---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other_data_structures/binary_trie.hpp
    title: other_data_structures/binary_trie.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/set_xor_min
    links:
    - https://judge.yosupo.jp/problem/set_xor_min
  bundledCode: "#line 2 \"other_data_structures/binary_trie.hpp\"\n#include <vector>\n\
    \n// CUT begin\nstruct BinaryTrie {\n    using Int = int;\n    int maxD;\n   \
    \ std::vector<int> deg, sz;\n    std::vector<int> ch0, ch1, par;\n\n    int _new_node(int\
    \ id_par) {\n        deg.emplace_back(0);\n        sz.emplace_back(0);\n     \
    \   ch0.emplace_back(-1);\n        ch1.emplace_back(-1);\n        par.emplace_back(id_par);\n\
    \        return ch0.size() - 1;\n    }\n\n    BinaryTrie(int maxD = 0) : maxD(maxD)\
    \ { _new_node(-1); }\n    int _goto(Int x) {\n        int now = 0;\n        for\
    \ (int d = maxD - 1; d >= 0; d--) {\n            int nxt = ((x >> d) & 1) ? ch1[now]\
    \ : ch0[now];\n            if (nxt == -1) {\n                nxt = _new_node(now);\n\
    \                (((x >> d) & 1) ? ch1[now] : ch0[now]) = nxt;\n            }\n\
    \            now = nxt;\n        }\n        return now;\n    }\n\n    void insert(Int\
    \ x) {\n        int now = _goto(x);\n        if (deg[now] == 0) {\n          \
    \  deg[now] = 1;\n            while (now >= 0) { sz[now]++, now = par[now]; }\n\
    \        }\n    }\n\n    void erase(Int x) {\n        int now = _goto(x);\n  \
    \      if (deg[now] > 0) {\n            deg[now] = 0;\n            while (now\
    \ >= 0) { sz[now]--, now = par[now]; }\n        }\n    }\n\n    Int xor_min(Int\
    \ x) {\n        Int ret = 0;\n        int now = 0;\n        if (!sz[now]) return\
    \ -1;\n        for (int d = maxD - 1; d >= 0; d--) {\n            int y = ((x\
    \ >> d) & 1) ? ch1[now] : ch0[now];\n            if (y != -1 and sz[y]) {\n  \
    \              now = y;\n            } else {\n                ret += Int(1) <<\
    \ d, now = ch0[now] ^ ch1[now] ^ y;\n            }\n        }\n        return\
    \ ret;\n    }\n};\n#line 2 \"other_data_structures/test/binary_trie.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/set_xor_min\"\n\n#include\
    \ <iostream>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    int Q;\n    cin >> Q;\n    BinaryTrie bt(30);\n    while (Q--) {\n     \
    \   int q, x;\n        cin >> q >> x;\n        if (q == 0)\n            bt.insert(x);\n\
    \        else if (q == 1)\n            bt.erase(x);\n        else\n          \
    \  cout << bt.xor_min(x) << '\\n';\n    }\n}\n"
  code: "#include \"../binary_trie.hpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/set_xor_min\"\
    \n\n#include <iostream>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n\n    int Q;\n    cin >> Q;\n    BinaryTrie bt(30);\n\
    \    while (Q--) {\n        int q, x;\n        cin >> q >> x;\n        if (q ==\
    \ 0)\n            bt.insert(x);\n        else if (q == 1)\n            bt.erase(x);\n\
    \        else\n            cout << bt.xor_min(x) << '\\n';\n    }\n}\n"
  dependsOn:
  - other_data_structures/binary_trie.hpp
  isVerificationFile: true
  path: other_data_structures/test/binary_trie.test.cpp
  requiredBy: []
  timestamp: '2021-01-01 16:52:32+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: other_data_structures/test/binary_trie.test.cpp
layout: document
redirect_from:
- /verify/other_data_structures/test/binary_trie.test.cpp
- /verify/other_data_structures/test/binary_trie.test.cpp.html
title: other_data_structures/test/binary_trie.test.cpp
---
