---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other_data_structures/light_forward_list.hpp
    title: other_data_structures/light_forward_list.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: string/test/incremental_matching.test.cpp
    title: string/test/incremental_matching.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"other_data_structures/light_forward_list.hpp\"\n#include\
    \ <vector>\n\n// CUT begin\n// Simple forward_list for MLE-sensitive situations\n\
    // Verify: <http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D>\n\
    template <typename T> struct light_forward_list {\n    static std::vector<unsigned>\
    \ ptr;\n    static std::vector<T> val;\n    unsigned head;\n    light_forward_list()\
    \ : head(0) {}\n    void push_front(T x) {\n        ptr.push_back(head), val.push_back(x);\n\
    \        head = ptr.size() - 1;\n    }\n    struct iterator {\n        unsigned\
    \ p;\n        iterator operator++() { return {p = ptr[p]}; }\n        T &operator*()\
    \ { return val[p]; }\n        bool operator!=(const iterator &rhs) { return p\
    \ != rhs.p; }\n    };\n    iterator begin() { return {head}; }\n    iterator end()\
    \ { return {0}; }\n};\ntemplate <typename T> std::vector<unsigned> light_forward_list<T>::ptr\
    \ = {0};\ntemplate <typename T> std::vector<T> light_forward_list<T>::val = {0};\n\
    #line 3 \"string/incremental_matching.hpp\"\n#include <cassert>\n#include <iostream>\n\
    #include <string>\n#include <unordered_set>\n#line 8 \"string/incremental_matching.hpp\"\
    \n\n// CUT begin\n// [1] B. Meyer, \"Incremental String Matching,\" Information\
    \ Processing Letters, 21(5), 1985.\n//\n// (Dynamic version of Aho-Corasick algorithm)\n\
    // Complexity:\n// - add(): O(|keyword_i|)\n// - match() : O(\\sum_i |keyword_i|\
    \ + |str|)\ntemplate <class T, int (*char2int)(char)> struct IncrementalMatching\
    \ {\n    const int D;\n    std::vector<T> node;\n    IncrementalMatching(int D_)\
    \ : D(D_), node(1, D) {}\n\n    void enter_child(int n, int nn, int c) {\n   \
    \     complete_failure(n, nn, c);\n        node[n].setch(c, nn);\n        int\
    \ fnn = node[nn].fail;\n        node[fnn].inv_fail.insert(nn);\n        complete_inverse(n,\
    \ nn, c);\n    }\n\n    void complete_inverse(const int y, const int nn, const\
    \ int c) {\n        for (auto x : node[y].inv_fail) {\n            const int xx\
    \ = node[x].Goto(c);\n            if (xx) {\n                const int fxx = node[xx].fail;\n\
    \                node[fxx].inv_fail.erase(xx);\n                node[xx].fail\
    \ = nn, node[nn].inv_fail.insert(xx);\n            } else {\n                complete_inverse(x,\
    \ nn, c);\n            }\n        }\n    }\n\n    std::vector<int> endpos;\n \
    \   int add(const std::string &keyword) { // Enter_in_tree() in [1]\n        assert(keyword.length()\
    \ > 0);\n        int n = 0;\n        for (const auto &cc : keyword) {\n      \
    \      int c = char2int(cc), nn = node[n].Goto(c);\n            if (!nn) {\n \
    \               nn = node.size();\n                node.emplace_back(D), enter_child(n,\
    \ nn, c);\n            }\n            n = nn;\n        }\n        return endpos.push_back(n),\
    \ n;\n    }\n\n    void complete_failure(int n, int nn, int c) {\n        int\
    \ m = n, Tmc = node[m].Goto(c);\n        while (m and !Tmc) m = node[m].fail,\
    \ Tmc = node[m].Goto(c);\n        node[nn].fail = Tmc;\n    }\n\n    std::vector<int>\
    \ visorder; // BFS order of node ids\n    void build_bfs() {         // Build_failure()\
    \ in [1]\n        visorder.clear();\n        for (int c = 0; c < D; c++) {\n \
    \           int u = node[0].Goto(c);\n            if (u) visorder.push_back(u);\n\
    \        }\n        for (size_t p = 0; p < visorder.size(); p++) {\n         \
    \   int n = visorder[p];\n            for (int c = 0; c < D; c++) {\n        \
    \        const int nn = node[n].Goto(c);\n                if (nn) visorder.push_back(nn);\n\
    \            }\n        }\n    }\n\n    int step(int now, int d) {\n        while\
    \ (now and !node[now].Goto(d)) now = node[now].fail;\n        return node[now].Goto(d);\n\
    \    }\n\n    // Count occurences of each added keyword in `str`\n    std::vector<int>\
    \ match(const std::string &str) {\n        std::vector<int> freq(node.size());\n\
    \        int now = 0;\n        for (const auto &c : str) freq[now = step(now,\
    \ char2int(c))]++;\n\n        for (auto i = visorder.rbegin(); i != visorder.rend();\
    \ i++) freq[node[*i].fail] += freq[*i];\n        std::vector<int> ret;\n     \
    \   for (auto x : endpos) ret.push_back(freq[x]);\n        return ret;\n    }\n\
    };\n\nstruct TrieNodeFL {\n    static const int B = 8, mask = (1 << B) - 1;\n\
    \    light_forward_list<unsigned> chlist; // \u4E0B\u4F4D B bits \u304C\u6587\u5B57\
    \u7A2E\uFF0C\u4E0A\u4F4D bit \u304C\u884C\u304D\u5148\n    std::unordered_set<int>\
    \ inv_fail;\n    int fail;\n    TrieNodeFL(int = 0) : fail(0) {}\n    int Goto(int\
    \ c) {\n        for (const auto x : chlist) {\n            if ((x & mask) == c)\
    \ return x >> B;\n        }\n        return 0;\n    }\n    void setch(int c, int\
    \ i) { chlist.push_front(c + (i << B)); }\n    friend std::ostream &operator<<(std::ostream\
    \ &os, TrieNodeFL &x) {\n        os << '[' << x.fail << '/';\n        for (const\
    \ auto c : x.chlist) os << '(' << (c & mask) << ',' << (c >> B) << \"),\";\n \
    \       return os << ']';\n    }\n\n    struct iterator {\n        light_forward_list<unsigned>::iterator\
    \ iter;\n        iterator operator++() { return {++iter}; }\n        std::pair<int,\
    \ int> operator*() {\n            unsigned val = *iter;\n            return std::make_pair(val\
    \ & mask, val >> B); // (char, next_pos)\n        }\n        bool operator!=(const\
    \ iterator &rhs) { return iter != rhs.iter; }\n    };\n    iterator begin() {\
    \ return {chlist.begin()}; }\n    iterator end() { return {chlist.end()}; }\n\
    };\n\nint c2i_0aA(char c) { return isdigit(c) ? c - '0' : islower(c) ? c - 'a'\
    \ + 10 : c - 'A' + 36; }\n"
  code: "#pragma once\n#include \"../other_data_structures/light_forward_list.hpp\"\
    \n#include <cassert>\n#include <iostream>\n#include <string>\n#include <unordered_set>\n\
    #include <vector>\n\n// CUT begin\n// [1] B. Meyer, \"Incremental String Matching,\"\
    \ Information Processing Letters, 21(5), 1985.\n//\n// (Dynamic version of Aho-Corasick\
    \ algorithm)\n// Complexity:\n// - add(): O(|keyword_i|)\n// - match() : O(\\\
    sum_i |keyword_i| + |str|)\ntemplate <class T, int (*char2int)(char)> struct IncrementalMatching\
    \ {\n    const int D;\n    std::vector<T> node;\n    IncrementalMatching(int D_)\
    \ : D(D_), node(1, D) {}\n\n    void enter_child(int n, int nn, int c) {\n   \
    \     complete_failure(n, nn, c);\n        node[n].setch(c, nn);\n        int\
    \ fnn = node[nn].fail;\n        node[fnn].inv_fail.insert(nn);\n        complete_inverse(n,\
    \ nn, c);\n    }\n\n    void complete_inverse(const int y, const int nn, const\
    \ int c) {\n        for (auto x : node[y].inv_fail) {\n            const int xx\
    \ = node[x].Goto(c);\n            if (xx) {\n                const int fxx = node[xx].fail;\n\
    \                node[fxx].inv_fail.erase(xx);\n                node[xx].fail\
    \ = nn, node[nn].inv_fail.insert(xx);\n            } else {\n                complete_inverse(x,\
    \ nn, c);\n            }\n        }\n    }\n\n    std::vector<int> endpos;\n \
    \   int add(const std::string &keyword) { // Enter_in_tree() in [1]\n        assert(keyword.length()\
    \ > 0);\n        int n = 0;\n        for (const auto &cc : keyword) {\n      \
    \      int c = char2int(cc), nn = node[n].Goto(c);\n            if (!nn) {\n \
    \               nn = node.size();\n                node.emplace_back(D), enter_child(n,\
    \ nn, c);\n            }\n            n = nn;\n        }\n        return endpos.push_back(n),\
    \ n;\n    }\n\n    void complete_failure(int n, int nn, int c) {\n        int\
    \ m = n, Tmc = node[m].Goto(c);\n        while (m and !Tmc) m = node[m].fail,\
    \ Tmc = node[m].Goto(c);\n        node[nn].fail = Tmc;\n    }\n\n    std::vector<int>\
    \ visorder; // BFS order of node ids\n    void build_bfs() {         // Build_failure()\
    \ in [1]\n        visorder.clear();\n        for (int c = 0; c < D; c++) {\n \
    \           int u = node[0].Goto(c);\n            if (u) visorder.push_back(u);\n\
    \        }\n        for (size_t p = 0; p < visorder.size(); p++) {\n         \
    \   int n = visorder[p];\n            for (int c = 0; c < D; c++) {\n        \
    \        const int nn = node[n].Goto(c);\n                if (nn) visorder.push_back(nn);\n\
    \            }\n        }\n    }\n\n    int step(int now, int d) {\n        while\
    \ (now and !node[now].Goto(d)) now = node[now].fail;\n        return node[now].Goto(d);\n\
    \    }\n\n    // Count occurences of each added keyword in `str`\n    std::vector<int>\
    \ match(const std::string &str) {\n        std::vector<int> freq(node.size());\n\
    \        int now = 0;\n        for (const auto &c : str) freq[now = step(now,\
    \ char2int(c))]++;\n\n        for (auto i = visorder.rbegin(); i != visorder.rend();\
    \ i++) freq[node[*i].fail] += freq[*i];\n        std::vector<int> ret;\n     \
    \   for (auto x : endpos) ret.push_back(freq[x]);\n        return ret;\n    }\n\
    };\n\nstruct TrieNodeFL {\n    static const int B = 8, mask = (1 << B) - 1;\n\
    \    light_forward_list<unsigned> chlist; // \u4E0B\u4F4D B bits \u304C\u6587\u5B57\
    \u7A2E\uFF0C\u4E0A\u4F4D bit \u304C\u884C\u304D\u5148\n    std::unordered_set<int>\
    \ inv_fail;\n    int fail;\n    TrieNodeFL(int = 0) : fail(0) {}\n    int Goto(int\
    \ c) {\n        for (const auto x : chlist) {\n            if ((x & mask) == c)\
    \ return x >> B;\n        }\n        return 0;\n    }\n    void setch(int c, int\
    \ i) { chlist.push_front(c + (i << B)); }\n    friend std::ostream &operator<<(std::ostream\
    \ &os, TrieNodeFL &x) {\n        os << '[' << x.fail << '/';\n        for (const\
    \ auto c : x.chlist) os << '(' << (c & mask) << ',' << (c >> B) << \"),\";\n \
    \       return os << ']';\n    }\n\n    struct iterator {\n        light_forward_list<unsigned>::iterator\
    \ iter;\n        iterator operator++() { return {++iter}; }\n        std::pair<int,\
    \ int> operator*() {\n            unsigned val = *iter;\n            return std::make_pair(val\
    \ & mask, val >> B); // (char, next_pos)\n        }\n        bool operator!=(const\
    \ iterator &rhs) { return iter != rhs.iter; }\n    };\n    iterator begin() {\
    \ return {chlist.begin()}; }\n    iterator end() { return {chlist.end()}; }\n\
    };\n\nint c2i_0aA(char c) { return isdigit(c) ? c - '0' : islower(c) ? c - 'a'\
    \ + 10 : c - 'A' + 36; }\n"
  dependsOn:
  - other_data_structures/light_forward_list.hpp
  isVerificationFile: false
  path: string/incremental_matching.hpp
  requiredBy: []
  timestamp: '2021-01-01 02:53:25+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - string/test/incremental_matching.test.cpp
documentation_of: string/incremental_matching.hpp
layout: document
redirect_from:
- /library/string/incremental_matching.hpp
- /library/string/incremental_matching.hpp.html
title: string/incremental_matching.hpp
---
