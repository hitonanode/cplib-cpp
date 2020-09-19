---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other_data_structures/persistent_queue.hpp
    title: other_data_structures/persistent_queue.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/persistent_queue
    links:
    - https://judge.yosupo.jp/problem/persistent_queue
  bundledCode: "#line 2 \"other_data_structures/persistent_queue.hpp\"\n#include <cassert>\n\
    #include <utility>\n#include <vector>\n\n// CUT begin\n// Fully persistent queue\n\
    template<typename T, int D>\nstruct pqueue\n{\n    int now;\n\n    std::vector<T>\
    \ data;               // Elements on each node of tree\n    std::vector<std::vector<int>>\
    \ par; // binary-lifted parents\n\n    std::vector<int> back_id; // back_id[t]\
    \ = leaf id of the tree at time t\n    std::vector<int> size;    // size[t] =\
    \ size of the queue at time t\n\n    pqueue() : now(0), data(1), par(1, std::vector<int>(D)),\
    \ back_id(1, 0), size(1, 0) {}\n\n    // Complexity: O(lgD)\n    // return: (curret_time,\
    \ popped element)\n    std::pair<int, T> pop(int t)\n    {\n        now++;\n \
    \       assert(now < 1 << (D + 1));\n        int r = back_id[t], len = size[t]\
    \ - 1;\n        back_id.emplace_back(r), size.emplace_back(len);\n        for\
    \ (int d = 0; d < D; d++) if ((len >> d) & 1) r = par[r][d];\n        return std::make_pair(now,\
    \ data[r]);\n    }\n\n    // Complexity: O(lgD)\n    // return: curret_time\n\
    \    int push(int t, const T &dat)\n    {\n        now++;\n        assert(now\
    \ < 1 << (D + 1));\n        int newid = data.size();\n        data.emplace_back(dat);\n\
    \        par.emplace_back(std::vector<int>(D, back_id[t]));\n        back_id.emplace_back(newid),\
    \ size.emplace_back(size[t] + 1);\n        for (int d = 1; d < D; d++) par[newid][d]\
    \ = par[par[newid][d - 1]][d - 1];\n        return now;\n    }\n};\n#line 2 \"\
    other_data_structures/test/persistent_queue.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/persistent_queue\"\
    \n#include <iostream>\n\nint main()\n{\n    std::cin.tie(NULL);\n    std::ios::sync_with_stdio(false);\n\
    \n    pqueue<int, 18> pq;\n    int Q;\n    std::cin >> Q;\n    while (Q--) {\n\
    \        int q, t;\n        std::cin >> q >> t;\n        if (q == 0) {\n     \
    \       int x;\n            std::cin >> x;\n            pq.push(t + 1, x);\n \
    \       }\n        else {\n            std::cout << pq.pop(t + 1).second << '\\\
    n';\n        }\n    }\n}\n"
  code: "#include \"other_data_structures/persistent_queue.hpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/persistent_queue\"\n#include <iostream>\n\n\
    int main()\n{\n    std::cin.tie(NULL);\n    std::ios::sync_with_stdio(false);\n\
    \n    pqueue<int, 18> pq;\n    int Q;\n    std::cin >> Q;\n    while (Q--) {\n\
    \        int q, t;\n        std::cin >> q >> t;\n        if (q == 0) {\n     \
    \       int x;\n            std::cin >> x;\n            pq.push(t + 1, x);\n \
    \       }\n        else {\n            std::cout << pq.pop(t + 1).second << '\\\
    n';\n        }\n    }\n}\n"
  dependsOn:
  - other_data_structures/persistent_queue.hpp
  isVerificationFile: true
  path: other_data_structures/test/persistent_queue.test.cpp
  requiredBy: []
  timestamp: '2020-04-18 22:56:40+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: other_data_structures/test/persistent_queue.test.cpp
layout: document
redirect_from:
- /verify/other_data_structures/test/persistent_queue.test.cpp
- /verify/other_data_structures/test/persistent_queue.test.cpp.html
title: other_data_structures/test/persistent_queue.test.cpp
---
