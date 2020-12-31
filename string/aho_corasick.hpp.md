---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=5101653>
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.1/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.1/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 193, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.1/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.1/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: ../other_data_structures/light_forward_list.hpp:\
    \ line -1: no such header\n"
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
  dependsOn: []
  isVerificationFile: false
  path: string/aho_corasick.hpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: string/aho_corasick.hpp
layout: document
redirect_from:
- /library/string/aho_corasick.hpp
- /library/string/aho_corasick.hpp.html
title: string/aho_corasick.hpp
---
