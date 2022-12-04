---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/light_forward_list.hpp
    title: data_structure/light_forward_list.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: string/aho_corasick_online.hpp
    title: string/aho_corasick_online.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: string/test/aho_corasick_forwardlist.test.cpp
    title: string/test/aho_corasick_forwardlist.test.cpp
  - icon: ':heavy_check_mark:'
    path: string/test/aho_corasick_online.test.cpp
    title: string/test/aho_corasick_online.test.cpp
  - icon: ':heavy_check_mark:'
    path: string/test/aho_corasick_unorderedmap.test.cpp
    title: string/test/aho_corasick_unorderedmap.test.cpp
  - icon: ':heavy_check_mark:'
    path: string/test/aho_corasick_vector.test.cpp
    title: string/test/aho_corasick_vector.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=5101653>
    - https://yukicoder.me/submissions/598606>
  bundledCode: "#line 2 \"data_structure/light_forward_list.hpp\"\n#include <vector>\n\
    \n// CUT begin\n// Simple forward_list for MLE-sensitive situations\n// Verify:\
    \ <http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D>\ntemplate\
    \ <typename T> struct light_forward_list {\n    static std::vector<unsigned> ptr;\n\
    \    static std::vector<T> val;\n    unsigned head;\n    light_forward_list()\
    \ : head(0) {}\n    void push_front(T x) {\n        ptr.push_back(head), val.push_back(x);\n\
    \        head = ptr.size() - 1;\n    }\n    struct iterator {\n        unsigned\
    \ p;\n        iterator operator++() { return {p = ptr[p]}; }\n        T &operator*()\
    \ { return val[p]; }\n        bool operator!=(const iterator &rhs) { return p\
    \ != rhs.p; }\n    };\n    iterator begin() { return {head}; }\n    iterator end()\
    \ { return {0}; }\n};\ntemplate <typename T> std::vector<unsigned> light_forward_list<T>::ptr\
    \ = {0};\ntemplate <typename T> std::vector<T> light_forward_list<T>::val = {T()};\n\
    #line 3 \"string/aho_corasick.hpp\"\n#include <cassert>\n#include <string>\n#include\
    \ <unordered_map>\n#line 7 \"string/aho_corasick.hpp\"\n\n// CUT begin\n// Aho-Corasick\
    \ algorithm\n// Verify: <http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=5101653>\n\
    //         <https://yukicoder.me/submissions/598606>\n// Complexity:\n// - add():\
    \ O(|keyword_i|)\n// - build_aho_corasick(): O(\\sum_i |keyword_i|)\n// - match()\
    \ : O(\\sum_i |keyword_i| + |str|)\ntemplate <class T, int (*char2int)(char)>\
    \ struct AhoCorasick {\n    bool built;\n    const int D;\n    std::vector<T>\
    \ node;\n    AhoCorasick(int D_) : built(false), D(D_), node(1, D) {}\n    AhoCorasick\
    \ operator=(const AhoCorasick &rhs) { return AhoCorasick(rhs.D); }\n\n    void\
    \ enter_child(int n, int nn, int c) { node[n].setch(c, nn); }\n\n    std::vector<int>\
    \ endpos;\n    int add(const std::string &keyword) { // Enter_in_tree() in [1]\n\
    \        built = false;\n        int n = 0;\n        for (const auto &cc : keyword)\
    \ {\n            int c = char2int(cc), nn = node[n].Goto(c);\n            if (!nn)\
    \ {\n                nn = node.size();\n                enter_child(n, nn, c),\
    \ node.emplace_back(D);\n            }\n            n = nn;\n        }\n     \
    \   return endpos.push_back(n), n;\n    }\n\n    void complete_failure(int n,\
    \ int nn, int c) {\n        int m = node[n].fail, mm = node[m].Goto(c);\n    \
    \    while (m and !mm) m = node[m].fail, mm = node[m].Goto(c);\n        node[nn].fail\
    \ = mm;\n    }\n\n    std::vector<int> visorder; // BFS order of node ids\n  \
    \  void build() {             // Build_failure() in [1]\n        visorder.clear();\n\
    \        for (auto p : node[0]) {\n            if (p.second) visorder.push_back(p.second);\n\
    \        }\n        for (size_t p = 0; p < visorder.size(); p++) {\n         \
    \   int n = visorder[p];\n            for (auto p : node[n]) {\n             \
    \   int c = p.first, nn = p.second;\n                if (nn) visorder.push_back(nn),\
    \ complete_failure(n, nn, c);\n            }\n        }\n        built = true;\n\
    \    }\n\n    int step(int now, int d) {\n        while (now and !node[now].Goto(d))\
    \ now = node[now].fail;\n        return node[now].Goto(d);\n    }\n\n    // Count\
    \ occurences of each added keywords in `str`\n    std::vector<int> match(const\
    \ std::string &str) {\n        if (!built) build();\n        std::vector<int>\
    \ freq(node.size());\n        int now = 0;\n        for (const auto &c : str)\
    \ freq[now = step(now, char2int(c))]++;\n\n        for (auto i = visorder.rbegin();\
    \ i != visorder.rend(); i++)\n            freq[node[*i].fail] += freq[*i];\n \
    \       std::vector<int> ret;\n        for (auto x : endpos) ret.push_back(freq[x]);\n\
    \        return ret;\n    }\n};\n\nstruct TrieNodeFL {\n    struct smallpii {\n\
    \        int first : 8;\n        int second : 24;\n    };\n    light_forward_list<smallpii>\
    \ chlist;\n    int fail;\n    TrieNodeFL(int = 0) : fail(0) {}\n    int Goto(int\
    \ c) {\n        for (const auto x : chlist) {\n            if (x.first == c) return\
    \ x.second;\n        }\n        return 0;\n    }\n    void setch(int c, int i)\
    \ { chlist.push_front({c, i}); }\n\n    struct iterator {\n        light_forward_list<smallpii>::iterator\
    \ iter;\n        iterator operator++() { return {++iter}; }\n        smallpii\
    \ operator*() { return *iter; }\n        bool operator!=(const iterator &rhs)\
    \ { return iter != rhs.iter; }\n    };\n    iterator begin() { return {chlist.begin()};\
    \ }\n    iterator end() { return {chlist.end()}; }\n};\n\nstruct TrieNodeV {\n\
    \    std::vector<int> ch; // \u5168 bit \u304C\u884C\u304D\u5148\n    int fail;\n\
    \    TrieNodeV(int D = 0) : ch(D), fail(0) {}\n    int Goto(int d) { return ch[d];\
    \ }\n    void setch(int d, int i) { ch[d] = i; }\n\n    struct iterator {\n  \
    \      int i;\n        std::vector<int>::iterator iter;\n        iterator operator++()\
    \ { return {++i, ++iter}; }\n        std::pair<int, int> operator*() { return\
    \ std::make_pair(i, *iter); }\n        bool operator!=(const iterator &rhs) {\
    \ return iter != rhs.iter; }\n    };\n    iterator begin() { return {0, ch.begin()};\
    \ }\n    iterator end() { return {int(ch.size()), ch.end()}; }\n};\n\nstruct TrieNodeUM\
    \ : std::unordered_map<int, int> {\n    int fail;\n    TrieNodeUM(int = 0) : fail(0)\
    \ {}\n    int Goto(int d) { return count(d) ? (*this)[d] : 0; }\n    void setch(int\
    \ d, int i) { (*this)[d] = i; }\n};\n\nint c2i0aA(char c) { return isdigit(c)\
    \ ? c - '0' : islower(c) ? c - 'a' + 10 : c - 'A' + 36; }\n\n/* Usage:\nAhoCorasick<TrieNodeFL,\
    \ c2i0aA> trie(62);\ntrie.add(P);\ntrie.build();\nvector<int> ret = trie.match();\n\
    */\n"
  code: "#pragma once\n#include \"../data_structure/light_forward_list.hpp\"\n#include\
    \ <cassert>\n#include <string>\n#include <unordered_map>\n#include <vector>\n\n\
    // CUT begin\n// Aho-Corasick algorithm\n// Verify: <http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=5101653>\n\
    //         <https://yukicoder.me/submissions/598606>\n// Complexity:\n// - add():\
    \ O(|keyword_i|)\n// - build_aho_corasick(): O(\\sum_i |keyword_i|)\n// - match()\
    \ : O(\\sum_i |keyword_i| + |str|)\ntemplate <class T, int (*char2int)(char)>\
    \ struct AhoCorasick {\n    bool built;\n    const int D;\n    std::vector<T>\
    \ node;\n    AhoCorasick(int D_) : built(false), D(D_), node(1, D) {}\n    AhoCorasick\
    \ operator=(const AhoCorasick &rhs) { return AhoCorasick(rhs.D); }\n\n    void\
    \ enter_child(int n, int nn, int c) { node[n].setch(c, nn); }\n\n    std::vector<int>\
    \ endpos;\n    int add(const std::string &keyword) { // Enter_in_tree() in [1]\n\
    \        built = false;\n        int n = 0;\n        for (const auto &cc : keyword)\
    \ {\n            int c = char2int(cc), nn = node[n].Goto(c);\n            if (!nn)\
    \ {\n                nn = node.size();\n                enter_child(n, nn, c),\
    \ node.emplace_back(D);\n            }\n            n = nn;\n        }\n     \
    \   return endpos.push_back(n), n;\n    }\n\n    void complete_failure(int n,\
    \ int nn, int c) {\n        int m = node[n].fail, mm = node[m].Goto(c);\n    \
    \    while (m and !mm) m = node[m].fail, mm = node[m].Goto(c);\n        node[nn].fail\
    \ = mm;\n    }\n\n    std::vector<int> visorder; // BFS order of node ids\n  \
    \  void build() {             // Build_failure() in [1]\n        visorder.clear();\n\
    \        for (auto p : node[0]) {\n            if (p.second) visorder.push_back(p.second);\n\
    \        }\n        for (size_t p = 0; p < visorder.size(); p++) {\n         \
    \   int n = visorder[p];\n            for (auto p : node[n]) {\n             \
    \   int c = p.first, nn = p.second;\n                if (nn) visorder.push_back(nn),\
    \ complete_failure(n, nn, c);\n            }\n        }\n        built = true;\n\
    \    }\n\n    int step(int now, int d) {\n        while (now and !node[now].Goto(d))\
    \ now = node[now].fail;\n        return node[now].Goto(d);\n    }\n\n    // Count\
    \ occurences of each added keywords in `str`\n    std::vector<int> match(const\
    \ std::string &str) {\n        if (!built) build();\n        std::vector<int>\
    \ freq(node.size());\n        int now = 0;\n        for (const auto &c : str)\
    \ freq[now = step(now, char2int(c))]++;\n\n        for (auto i = visorder.rbegin();\
    \ i != visorder.rend(); i++)\n            freq[node[*i].fail] += freq[*i];\n \
    \       std::vector<int> ret;\n        for (auto x : endpos) ret.push_back(freq[x]);\n\
    \        return ret;\n    }\n};\n\nstruct TrieNodeFL {\n    struct smallpii {\n\
    \        int first : 8;\n        int second : 24;\n    };\n    light_forward_list<smallpii>\
    \ chlist;\n    int fail;\n    TrieNodeFL(int = 0) : fail(0) {}\n    int Goto(int\
    \ c) {\n        for (const auto x : chlist) {\n            if (x.first == c) return\
    \ x.second;\n        }\n        return 0;\n    }\n    void setch(int c, int i)\
    \ { chlist.push_front({c, i}); }\n\n    struct iterator {\n        light_forward_list<smallpii>::iterator\
    \ iter;\n        iterator operator++() { return {++iter}; }\n        smallpii\
    \ operator*() { return *iter; }\n        bool operator!=(const iterator &rhs)\
    \ { return iter != rhs.iter; }\n    };\n    iterator begin() { return {chlist.begin()};\
    \ }\n    iterator end() { return {chlist.end()}; }\n};\n\nstruct TrieNodeV {\n\
    \    std::vector<int> ch; // \u5168 bit \u304C\u884C\u304D\u5148\n    int fail;\n\
    \    TrieNodeV(int D = 0) : ch(D), fail(0) {}\n    int Goto(int d) { return ch[d];\
    \ }\n    void setch(int d, int i) { ch[d] = i; }\n\n    struct iterator {\n  \
    \      int i;\n        std::vector<int>::iterator iter;\n        iterator operator++()\
    \ { return {++i, ++iter}; }\n        std::pair<int, int> operator*() { return\
    \ std::make_pair(i, *iter); }\n        bool operator!=(const iterator &rhs) {\
    \ return iter != rhs.iter; }\n    };\n    iterator begin() { return {0, ch.begin()};\
    \ }\n    iterator end() { return {int(ch.size()), ch.end()}; }\n};\n\nstruct TrieNodeUM\
    \ : std::unordered_map<int, int> {\n    int fail;\n    TrieNodeUM(int = 0) : fail(0)\
    \ {}\n    int Goto(int d) { return count(d) ? (*this)[d] : 0; }\n    void setch(int\
    \ d, int i) { (*this)[d] = i; }\n};\n\nint c2i0aA(char c) { return isdigit(c)\
    \ ? c - '0' : islower(c) ? c - 'a' + 10 : c - 'A' + 36; }\n\n/* Usage:\nAhoCorasick<TrieNodeFL,\
    \ c2i0aA> trie(62);\ntrie.add(P);\ntrie.build();\nvector<int> ret = trie.match();\n\
    */\n"
  dependsOn:
  - data_structure/light_forward_list.hpp
  isVerificationFile: false
  path: string/aho_corasick.hpp
  requiredBy:
  - string/aho_corasick_online.hpp
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - string/test/aho_corasick_vector.test.cpp
  - string/test/aho_corasick_forwardlist.test.cpp
  - string/test/aho_corasick_online.test.cpp
  - string/test/aho_corasick_unorderedmap.test.cpp
documentation_of: string/aho_corasick.hpp
layout: document
redirect_from:
- /library/string/aho_corasick.hpp
- /library/string/aho_corasick.hpp.html
title: string/aho_corasick.hpp
---
