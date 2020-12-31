---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other_data_structures/light_forward_list.hpp
    title: other_data_structures/light_forward_list.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: string/test/aho_corasick_forwardlist.test.cpp
    title: string/test/aho_corasick_forwardlist.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=5101653>
  bundledCode: "#line 2 \"other_data_structures/light_forward_list.hpp\"\n#include\
    \ <vector>\n\n// Simple forward_list for MLE-sensitive situations\n// Verify:\
    \ <http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D>\ntemplate\
    \ <typename T> struct light_forward_list {\n    static std::vector<unsigned> ptr;\n\
    \    static std::vector<T> val;\n    unsigned head;\n    light_forward_list()\
    \ : head(0) {}\n    void push_front(T x) {\n        ptr.push_back(head), val.push_back(x);\n\
    \        head = ptr.size() - 1;\n    }\n    struct iterator {\n        unsigned\
    \ p;\n        iterator operator++() { return {p = ptr[p]}; }\n        T &operator*()\
    \ { return val[p]; }\n        bool operator!=(const iterator &rhs) { return p\
    \ != rhs.p; }\n    };\n    iterator begin() { return {head}; }\n    iterator end()\
    \ { return {0}; }\n};\ntemplate <typename T> std::vector<unsigned> light_forward_list<T>::ptr\
    \ = {0};\ntemplate <typename T> std::vector<T> light_forward_list<T>::val = {0};\n\
    #line 3 \"string/aho_corasick.hpp\"\n#include <cassert>\n#include <map>\n#include\
    \ <queue>\n#include <string>\n#include <unordered_map>\n#line 9 \"string/aho_corasick.hpp\"\
    \n\n// CUT begin\n// Aho-Corasick algorithm\n// Verify: <http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=5101653>\n\
    // Complexity:\n// - add(): O(|str_i|)\n// - build_aho_corasick(): O(\\sum_i |str_i|)\n\
    // - match() : O(\\sum_i |str_i| + |str|)\ntemplate <class T, int (*char2int)(char)>\
    \ struct AhoCorasick {\n    const int D;\n    std::vector<T> node;\n    AhoCorasick(int\
    \ D_) : D(D_), node(1, D) {}\n\n    std::vector<int> endpos;\n    int add(const\
    \ std::string &str) {\n        assert(str.length() > 0);\n        int now = 0;\n\
    \        for (const auto &c : str) {\n            const int i = char2int(c);\n\
    \            if (!get_child(now, i)) {\n                node[now].set(i, node.size());\n\
    \                node.emplace_back(D);\n            }\n            now = get_child(now,\
    \ i);\n        }\n        return endpos.push_back(now), now;\n    }\n\n    std::vector<int>\
    \ visorder; // BFS order of node ids\n    void build_aho_corasick() {\n      \
    \  visorder.clear();\n        for (int i = 0; i < D; i++) {\n            int u\
    \ = get_child(0, i);\n            if (u) visorder.push_back(u);\n        }\n \
    \       for (size_t p = 0; p < visorder.size(); p++) {\n            int s = visorder[p];\n\
    \            for (int i = 0; i < D; i++) {\n                const int u = get_child(s,\
    \ i);\n                if (!u) continue;\n                visorder.push_back(u);\n\
    \                int t = node[s].fail, c = get_child(t, i);\n                while\
    \ (t and !c) t = node[t].fail, c = get_child(t, i);\n                node[u].fail\
    \ = c;\n            }\n        }\n    }\n\n    int get_child(int now, int d) {\
    \ return node[now].child(d); }\n\n    int step(int now, int d) {\n        while\
    \ (now and !get_child(now, d)) now = node[now].fail;\n        return get_child(now,\
    \ d);\n    }\n\n    // Count occurences of each added strings in `str`\n    std::vector<int>\
    \ match(const std::string &str) {\n        std::vector<int> freq(node.size());\n\
    \        int now = 0;\n        for (const auto &c : str) freq[now = step(now,\
    \ char2int(c))]++;\n\n        for (auto i = visorder.rbegin(); i != visorder.rend();\
    \ i++) freq[node[*i].fail] += freq[*i];\n        std::vector<int> ret;\n     \
    \   for (auto x : endpos) ret.push_back(freq[x]);\n        return ret;\n    }\n\
    };\n\nstruct TrieNodeFL {\n    static const int B = 8, mask = (1 << B) - 1;\n\
    \    light_forward_list<unsigned> chlist; // \u4E0B\u4F4D B bits \u304C\u6587\u5B57\
    \u7A2E\uFF0C\u4E0A\u4F4D bit \u304C\u884C\u304D\u5148\n    unsigned fail;\n  \
    \  TrieNodeFL(int = 0) : fail(0) {}\n    int child(int d) {\n        for (const\
    \ auto x : chlist)\n            if ((x & mask) == d) return x >> B;\n        return\
    \ 0;\n    }\n    void set(int d, unsigned i) { chlist.push_front(d + (i << B));\
    \ }\n};\n\nstruct TrieNodeV {\n    std::vector<unsigned> ch; // \u5168 bit \u304C\
    \u884C\u304D\u5148\n    unsigned fail;\n    TrieNodeV(int D = 0) : ch(D), fail(0)\
    \ {}\n    int child(int d) { return ch[d]; }\n    void set(int d, unsigned i)\
    \ { ch[d] = i; }\n};\n\nstruct TrieNodeUM {\n    std::unordered_map<int, unsigned>\
    \ mp;\n    unsigned fail;\n    TrieNodeUM(int = 0) : fail(0) {}\n    int child(int\
    \ d) { return mp.count(d) ? mp[d] : 0; }\n    void set(int d, unsigned i) { mp[d]\
    \ = i; }\n};\n\nint c2i0aA(char c) { return isdigit(c) ? c - '0' : islower(c)\
    \ ? c - 'a' + 10 : c - 'A' + 36; }\n\n/* Usage:\nAhoCorasick<TrieNodeFL, c2i0aA>\
    \ trie(62);\ntrie.add(P);\ntrie.build_aho_corasick();\nvector<int> ret = trie.match();\n\
    */\n"
  code: "#pragma once\n#include \"../other_data_structures/light_forward_list.hpp\"\
    \n#include <cassert>\n#include <map>\n#include <queue>\n#include <string>\n#include\
    \ <unordered_map>\n#include <vector>\n\n// CUT begin\n// Aho-Corasick algorithm\n\
    // Verify: <http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=5101653>\n//\
    \ Complexity:\n// - add(): O(|str_i|)\n// - build_aho_corasick(): O(\\sum_i |str_i|)\n\
    // - match() : O(\\sum_i |str_i| + |str|)\ntemplate <class T, int (*char2int)(char)>\
    \ struct AhoCorasick {\n    const int D;\n    std::vector<T> node;\n    AhoCorasick(int\
    \ D_) : D(D_), node(1, D) {}\n\n    std::vector<int> endpos;\n    int add(const\
    \ std::string &str) {\n        assert(str.length() > 0);\n        int now = 0;\n\
    \        for (const auto &c : str) {\n            const int i = char2int(c);\n\
    \            if (!get_child(now, i)) {\n                node[now].set(i, node.size());\n\
    \                node.emplace_back(D);\n            }\n            now = get_child(now,\
    \ i);\n        }\n        return endpos.push_back(now), now;\n    }\n\n    std::vector<int>\
    \ visorder; // BFS order of node ids\n    void build_aho_corasick() {\n      \
    \  visorder.clear();\n        for (int i = 0; i < D; i++) {\n            int u\
    \ = get_child(0, i);\n            if (u) visorder.push_back(u);\n        }\n \
    \       for (size_t p = 0; p < visorder.size(); p++) {\n            int s = visorder[p];\n\
    \            for (int i = 0; i < D; i++) {\n                const int u = get_child(s,\
    \ i);\n                if (!u) continue;\n                visorder.push_back(u);\n\
    \                int t = node[s].fail, c = get_child(t, i);\n                while\
    \ (t and !c) t = node[t].fail, c = get_child(t, i);\n                node[u].fail\
    \ = c;\n            }\n        }\n    }\n\n    int get_child(int now, int d) {\
    \ return node[now].child(d); }\n\n    int step(int now, int d) {\n        while\
    \ (now and !get_child(now, d)) now = node[now].fail;\n        return get_child(now,\
    \ d);\n    }\n\n    // Count occurences of each added strings in `str`\n    std::vector<int>\
    \ match(const std::string &str) {\n        std::vector<int> freq(node.size());\n\
    \        int now = 0;\n        for (const auto &c : str) freq[now = step(now,\
    \ char2int(c))]++;\n\n        for (auto i = visorder.rbegin(); i != visorder.rend();\
    \ i++) freq[node[*i].fail] += freq[*i];\n        std::vector<int> ret;\n     \
    \   for (auto x : endpos) ret.push_back(freq[x]);\n        return ret;\n    }\n\
    };\n\nstruct TrieNodeFL {\n    static const int B = 8, mask = (1 << B) - 1;\n\
    \    light_forward_list<unsigned> chlist; // \u4E0B\u4F4D B bits \u304C\u6587\u5B57\
    \u7A2E\uFF0C\u4E0A\u4F4D bit \u304C\u884C\u304D\u5148\n    unsigned fail;\n  \
    \  TrieNodeFL(int = 0) : fail(0) {}\n    int child(int d) {\n        for (const\
    \ auto x : chlist)\n            if ((x & mask) == d) return x >> B;\n        return\
    \ 0;\n    }\n    void set(int d, unsigned i) { chlist.push_front(d + (i << B));\
    \ }\n};\n\nstruct TrieNodeV {\n    std::vector<unsigned> ch; // \u5168 bit \u304C\
    \u884C\u304D\u5148\n    unsigned fail;\n    TrieNodeV(int D = 0) : ch(D), fail(0)\
    \ {}\n    int child(int d) { return ch[d]; }\n    void set(int d, unsigned i)\
    \ { ch[d] = i; }\n};\n\nstruct TrieNodeUM {\n    std::unordered_map<int, unsigned>\
    \ mp;\n    unsigned fail;\n    TrieNodeUM(int = 0) : fail(0) {}\n    int child(int\
    \ d) { return mp.count(d) ? mp[d] : 0; }\n    void set(int d, unsigned i) { mp[d]\
    \ = i; }\n};\n\nint c2i0aA(char c) { return isdigit(c) ? c - '0' : islower(c)\
    \ ? c - 'a' + 10 : c - 'A' + 36; }\n\n/* Usage:\nAhoCorasick<TrieNodeFL, c2i0aA>\
    \ trie(62);\ntrie.add(P);\ntrie.build_aho_corasick();\nvector<int> ret = trie.match();\n\
    */\n"
  dependsOn:
  - other_data_structures/light_forward_list.hpp
  isVerificationFile: false
  path: string/aho_corasick.hpp
  requiredBy: []
  timestamp: '2020-12-31 18:21:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - string/test/aho_corasick_forwardlist.test.cpp
documentation_of: string/aho_corasick.hpp
layout: document
redirect_from:
- /library/string/aho_corasick.hpp
- /library/string/aho_corasick.hpp.html
title: string/aho_corasick.hpp
---
