---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/light_forward_list.hpp
    title: data_structure/light_forward_list.hpp
  - icon: ':heavy_check_mark:'
    path: string/incremental_matching.hpp
    title: string/incremental_matching.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D
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
    #line 3 \"string/incremental_matching.hpp\"\n#include <iostream>\n#include <list>\n\
    #include <string>\n#line 7 \"string/incremental_matching.hpp\"\n\n// CUT begin\n\
    // [1] B. Meyer, \"Incremental String Matching,\" Information Processing Letters,\
    \ 21(5), 1985.\n//\n// (Dynamic version of Aho-Corasick algorithm)\n// Overall\
    \ complexity: O(K * (\\sum_i |keyword_i|) * (\\max_i |keyword_i|))\ntemplate <class\
    \ T, int (*char2int)(char)> struct IncrementalMatching {\n    bool built;\n  \
    \  const int D;\n    std::vector<T> node;\n    IncrementalMatching(int D_) : built(false),\
    \ D(D_), node(1, D) {}\n\n    void enter_child(int n, int nn, int c) {\n     \
    \   complete_failure(n, nn, c);\n        node[n].setch(c, nn);\n        int fnn\
    \ = node[nn].fail;\n        node[fnn].inv_fail.push_back(nn);\n        complete_inverse(n,\
    \ nn, c);\n    }\n\n    void complete_inverse(const int y, const int nn, const\
    \ int c) {\n        for (auto it = node[y].inv_fail.begin();; it++) {\n      \
    \      while (it != node[y].inv_fail.end() and node[*it].fail != y) it = node[y].inv_fail.erase(it);\n\
    \            if (it == node[y].inv_fail.end()) return;\n            const int\
    \ x = *it, xx = node[x].Goto(c);\n            if (xx) {\n                node[xx].fail\
    \ = nn, node[nn].inv_fail.push_back(xx);\n            } else {\n             \
    \   complete_inverse(x, nn, c);\n            }\n        }\n    }\n\n    std::vector<int>\
    \ endpos;\n    int add(const std::string &keyword) { // Enter_in_tree() in [1]\n\
    \        built = false;\n        int n = 0;\n        for (const auto &cc : keyword)\
    \ {\n            int c = char2int(cc), nn = node[n].Goto(c);\n            if (!nn)\
    \ {\n                nn = node.size();\n                node.emplace_back(D),\
    \ enter_child(n, nn, c);\n            }\n            n = nn;\n        }\n    \
    \    return endpos.push_back(n), n;\n    }\n\n    void complete_failure(int n,\
    \ int nn, int c) {\n        int m = n, Tmc = node[m].Goto(c);\n        while (m\
    \ and !Tmc) m = node[m].fail, Tmc = node[m].Goto(c);\n        node[nn].fail =\
    \ Tmc;\n    }\n\n    std::vector<int> visorder; // BFS order of node ids\n   \
    \ void build() {             // Build_failure() in [1]\n        built = true;\n\
    \        visorder = {0};\n        for (size_t p = 0; p < visorder.size(); p++)\
    \ {\n            for (auto p : node[visorder[p]]) {\n                if (p.second)\
    \ visorder.push_back(p.second);\n            }\n        }\n    }\n\n    int step(int\
    \ now, int d) {\n        while (now and !node[now].Goto(d)) now = node[now].fail;\n\
    \        return node[now].Goto(d);\n    }\n\n    // Count occurences of each added\
    \ keyword in `str`\n    std::vector<int> match(const std::string &str) {\n   \
    \     if (!built) build();\n        std::vector<int> freq(node.size());\n    \
    \    int now = 0;\n        for (const auto &c : str) freq[now = step(now, char2int(c))]++;\n\
    \n        for (auto i = visorder.rbegin(); i != visorder.rend(); i++) freq[node[*i].fail]\
    \ += freq[*i];\n        std::vector<int> ret;\n        for (auto x : endpos) ret.push_back(freq[x]);\n\
    \        return ret;\n    }\n};\n\nstruct TrieNodeFL {\n    static const int B\
    \ = 8, mask = (1 << B) - 1;\n    light_forward_list<unsigned> chlist; // \u4E0B\
    \u4F4D B bits \u304C\u6587\u5B57\u7A2E\uFF0C\u4E0A\u4F4D bit \u304C\u884C\u304D\
    \u5148\n    std::list<int> inv_fail;\n    int fail;\n    TrieNodeFL(int = 0) :\
    \ fail(0) {}\n    int Goto(int c) {\n        for (const auto x : chlist) {\n \
    \           if ((x & mask) == c) return x >> B;\n        }\n        return 0;\n\
    \    }\n    void setch(int c, int i) { chlist.push_front(c + (i << B)); }\n  \
    \  friend std::ostream &operator<<(std::ostream &os, TrieNodeFL &x) {\n      \
    \  os << '[' << x.fail << '/';\n        for (const auto c : x.chlist) os << '('\
    \ << (c & mask) << ',' << (c >> B) << \"),\";\n        return os << ']';\n   \
    \ }\n\n    struct iterator {\n        light_forward_list<unsigned>::iterator iter;\n\
    \        iterator operator++() { return {++iter}; }\n        std::pair<int, int>\
    \ operator*() {\n            unsigned val = *iter;\n            return std::make_pair(val\
    \ & mask, val >> B); // (char, next_pos)\n        }\n        bool operator!=(const\
    \ iterator &rhs) { return iter != rhs.iter; }\n    };\n    iterator begin() {\
    \ return {chlist.begin()}; }\n    iterator end() { return {chlist.end()}; }\n\
    };\n\nint c2i_0aA(char c) { return isdigit(c) ? c - '0' : islower(c) ? c - 'a'\
    \ + 10 : c - 'A' + 36; }\n#line 3 \"string/test/incremental_matching.test.cpp\"\
    \nusing namespace std;\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D\"\
    \n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n    IncrementalMatching<TrieNodeFL,\
    \ c2i_0aA> trie(62);\n    string T, P;\n    int Q;\n    cin >> T >> Q;\n    while\
    \ (Q--) cin >> P, trie.add(P);\n\n    for (auto n : trie.match(T)) cout << !!n\
    \ << '\\n';\n}\n"
  code: "#include \"../incremental_matching.hpp\"\n#include <iostream>\nusing namespace\
    \ std;\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D\"\
    \n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n    IncrementalMatching<TrieNodeFL,\
    \ c2i_0aA> trie(62);\n    string T, P;\n    int Q;\n    cin >> T >> Q;\n    while\
    \ (Q--) cin >> P, trie.add(P);\n\n    for (auto n : trie.match(T)) cout << !!n\
    \ << '\\n';\n}\n"
  dependsOn:
  - string/incremental_matching.hpp
  - data_structure/light_forward_list.hpp
  isVerificationFile: true
  path: string/test/incremental_matching.test.cpp
  requiredBy: []
  timestamp: '2021-02-26 23:47:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: string/test/incremental_matching.test.cpp
layout: document
redirect_from:
- /verify/string/test/incremental_matching.test.cpp
- /verify/string/test/incremental_matching.test.cpp.html
title: string/test/incremental_matching.test.cpp
---
