---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/radix_heap.hpp
    title: "Radix heap \uFF08\u57FA\u6570\u30D2\u30FC\u30D7\uFF09"
  - icon: ':heavy_check_mark:'
    path: utilities/reader.hpp
    title: "\u9AD8\u901F\u6A19\u6E96\u5165\u529B"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/shortest_path
    links:
    - https://judge.yosupo.jp/problem/shortest_path
  bundledCode: "#line 1 \"data_structure/test/radix_heap.dijkstra.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/shortest_path\"\n#line 2 \"data_structure/radix_heap.hpp\"\
    \n#include <array>\n#include <cstddef>\n#include <limits>\n#include <tuple>\n\
    #include <type_traits>\n#include <utility>\n#include <vector>\n\n// Radix heap\
    \ for unsigned integer\n// https://github.com/iwiwi/radix-heap\ntemplate <class\
    \ Uint, class Label, typename std::enable_if<std::is_unsigned<Uint>::value>::type\
    \ * = nullptr>\nclass radix_heap {\n    int sz;\n    Uint last;\n    std::array<std::vector<std::pair<Uint,\
    \ Label>>, std::numeric_limits<Uint>::digits + 1> v;\n\n    template <class U,\
    \ typename std::enable_if<sizeof(U) == 4>::type * = nullptr>\n    static inline\
    \ int bucket(U x) noexcept {\n        return x ? 32 - __builtin_clz(x) : 0;\n\
    \    }\n    template <class U, typename std::enable_if<sizeof(U) == 8>::type *\
    \ = nullptr>\n    static inline int bucket(U x) noexcept {\n        return x ?\
    \ 64 - __builtin_clzll(x) : 0;\n    }\n\n    void pull() {\n        if (!v[0].empty())\
    \ return;\n        int i = 1;\n        while (v[i].empty()) ++i;\n        last\
    \ = v[i].back().first;\n        for (int j = 0; j < int(v[i].size()); j++) last\
    \ = std::min(last, v[i][j].first);\n        for (int j = 0; j < int(v[i].size());\
    \ j++) {\n            v[bucket(v[i][j].first ^ last)].emplace_back(std::move(v[i][j]));\n\
    \        }\n        v[i].clear();\n    }\n\npublic:\n    radix_heap() : sz(0),\
    \ last(0) {\n        static_assert(std::numeric_limits<Uint>::digits > 0, \"Invalid\
    \ type.\");\n    }\n    std::size_t size() const noexcept { return sz; }\n   \
    \ bool empty() const noexcept { return sz == 0; }\n    void push(Uint x, const\
    \ Label &val) { ++sz, v[bucket(x ^ last)].emplace_back(x, val); }\n    void push(Uint\
    \ x, Label &&val) { ++sz, v[bucket(x ^ last)].emplace_back(x, std::move(val));\
    \ }\n    template <class... Args> void emplace(Uint x, Args &&...args) {\n   \
    \     ++sz, v[bucket(x ^ last)].emplace_back(std::piecewise_construct, std::forward_as_tuple(x),\n\
    \                                               std::forward_as_tuple(args...));\n\
    \    }\n    void pop() { pull(), --sz, v[0].pop_back(); }\n    std::pair<Uint,\
    \ Label> top() { return pull(), v[0].back(); }\n    Uint top_key() { return pull(),\
    \ last; }\n    Label &top_label() { return pull(), v[0].back().second; }\n   \
    \ void clear() noexcept {\n        sz = 0, last = 0;\n        for (auto &vec :\
    \ v) vec.clear();\n    }\n    void swap(radix_heap<Uint, Label> &a) {\n      \
    \  std::swap(sz, a.sz), std::swap(last, a.last), v.swap(a.v);\n    }\n};\n#line\
    \ 2 \"utilities/reader.hpp\"\n#include <cstdio>\n#include <string>\n\n// CUT begin\n\
    template <typename T> T rd_integer() {\n    T ret = 0;\n    bool minus = false;\n\
    \n    char c = getchar_unlocked();\n    while (!isdigit(c)) minus |= (c == '-'),\
    \ c = getchar_unlocked();\n    while (isdigit(c)) ret = (ret << 1) + (ret << 3)\
    \ + (c ^ 48), c = getchar_unlocked();\n\n    return minus ? -ret : ret;\n}\nint\
    \ rdi() { return rd_integer<int>(); }\nlong long rdll() { return rd_integer<long\
    \ long>(); }\nstd::string rdstr() {\n    std::string ret;\n    char c = getchar_unlocked();\n\
    \    while (!isgraph(c)) c = getchar_unlocked();\n    while (isgraph(c)) ret +=\
    \ c, c = getchar_unlocked();\n    return ret;\n}\n#line 4 \"data_structure/test/radix_heap.dijkstra.test.cpp\"\
    \n#include <iostream>\n#line 8 \"data_structure/test/radix_heap.dijkstra.test.cpp\"\
    \nusing namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \    int N = rdi(), M = rdi(), s = rdi(), t = rdi();\n\n    vector<vector<pair<int,\
    \ unsigned>>> to(N);\n    while (M--) {\n        int a = rdi(), b = rdi(), c =\
    \ rdi();\n        to[b].emplace_back(a, c);\n    }\n    vector<unsigned long long>\
    \ dist(N, numeric_limits<unsigned long long>::max());\n    vector<int> prv(N,\
    \ -1);\n    dist[t] = 0;\n    radix_heap<unsigned long long, int> pq;\n    pq.push(0,\
    \ t);\n    while (!pq.empty()) {\n        auto p = pq.top();\n        pq.pop();\n\
    \        int now = p.second;\n        if (now == s) break;\n        if (dist[now]\
    \ < p.first) continue;\n        for (const auto &nx : to[now]) {\n           \
    \ int nxt = nx.first;\n            if (dist[nxt] > dist[now] + nx.second) {\n\
    \                dist[nxt] = dist[now] + nx.second;\n                prv[nxt]\
    \ = now;\n                pq.push(dist[nxt], nxt);\n            }\n        }\n\
    \    }\n    if (dist[s] == numeric_limits<unsigned long long>::max()) {\n    \
    \    cout << \"-1\\n\";\n        return 0;\n    }\n\n    std::vector<int> path;\n\
    \    for (int now = s; now != -1; now = prv[now]) path.push_back(now);\n    cout\
    \ << dist[s] << ' ' << path.size() - 1 << '\\n';\n    for (int i = 1; i < int(path.size());\
    \ i++) cout << path[i - 1] << ' ' << path[i] << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/shortest_path\"\n#include\
    \ \"../radix_heap.hpp\"\n#include \"../../utilities/reader.hpp\"\n#include <iostream>\n\
    #include <limits>\n#include <utility>\n#include <vector>\nusing namespace std;\n\
    \nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n    int N\
    \ = rdi(), M = rdi(), s = rdi(), t = rdi();\n\n    vector<vector<pair<int, unsigned>>>\
    \ to(N);\n    while (M--) {\n        int a = rdi(), b = rdi(), c = rdi();\n  \
    \      to[b].emplace_back(a, c);\n    }\n    vector<unsigned long long> dist(N,\
    \ numeric_limits<unsigned long long>::max());\n    vector<int> prv(N, -1);\n \
    \   dist[t] = 0;\n    radix_heap<unsigned long long, int> pq;\n    pq.push(0,\
    \ t);\n    while (!pq.empty()) {\n        auto p = pq.top();\n        pq.pop();\n\
    \        int now = p.second;\n        if (now == s) break;\n        if (dist[now]\
    \ < p.first) continue;\n        for (const auto &nx : to[now]) {\n           \
    \ int nxt = nx.first;\n            if (dist[nxt] > dist[now] + nx.second) {\n\
    \                dist[nxt] = dist[now] + nx.second;\n                prv[nxt]\
    \ = now;\n                pq.push(dist[nxt], nxt);\n            }\n        }\n\
    \    }\n    if (dist[s] == numeric_limits<unsigned long long>::max()) {\n    \
    \    cout << \"-1\\n\";\n        return 0;\n    }\n\n    std::vector<int> path;\n\
    \    for (int now = s; now != -1; now = prv[now]) path.push_back(now);\n    cout\
    \ << dist[s] << ' ' << path.size() - 1 << '\\n';\n    for (int i = 1; i < int(path.size());\
    \ i++) cout << path[i - 1] << ' ' << path[i] << '\\n';\n}\n"
  dependsOn:
  - data_structure/radix_heap.hpp
  - utilities/reader.hpp
  isVerificationFile: true
  path: data_structure/test/radix_heap.dijkstra.test.cpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: data_structure/test/radix_heap.dijkstra.test.cpp
layout: document
redirect_from:
- /verify/data_structure/test/radix_heap.dijkstra.test.cpp
- /verify/data_structure/test/radix_heap.dijkstra.test.cpp.html
title: data_structure/test/radix_heap.dijkstra.test.cpp
---
