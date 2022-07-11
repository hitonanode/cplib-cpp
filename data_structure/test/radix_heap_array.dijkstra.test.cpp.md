---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/radix_heap_array.hpp
    title: "Array-like radix heap with decrease query\uFF08`chmin()` \u64CD\u4F5C\u304C\
      \u53EF\u80FD\u306A\u57FA\u6570\u30D2\u30FC\u30D7\uFF09"
  - icon: ':question:'
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
  bundledCode: "#line 1 \"data_structure/test/radix_heap_array.dijkstra.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/shortest_path\"\n#line 2 \"\
    data_structure/radix_heap_array.hpp\"\n#include <array>\n#include <limits>\n#include\
    \ <type_traits>\n#include <utility>\n#include <vector>\n\ntemplate <class Uint>\
    \ class radix_heap_array {\n    int sz;\n    Uint last;\n    std::array<std::vector<std::pair<Uint,\
    \ int>>, std::numeric_limits<Uint>::digits + 1> v;\n\n    struct smallpii {\n\
    \        unsigned b : 7;\n        int j : 25;\n    };\n    std::vector<smallpii>\
    \ i2bj;\n\n    template <class U, typename std::enable_if<sizeof(U) == 4>::type\
    \ * = nullptr>\n    static inline unsigned bucket(U x) noexcept {\n        return\
    \ x ? 32 - __builtin_clz(x) : 0;\n    }\n    template <class U, typename std::enable_if<sizeof(U)\
    \ == 8>::type * = nullptr>\n    static inline unsigned bucket(U x) noexcept {\n\
    \        return x ? 64 - __builtin_clzll(x) : 0;\n    }\n\n    void pull() {\n\
    \        if (!v[0].empty()) return;\n        int b = 1;\n        while (v[b].empty())\
    \ ++b;\n        last = v[b].back().first;\n        for (int j = 0; j < int(v[b].size());\
    \ j++) last = std::min(last, v[b][j].first);\n        for (int j = 0; j < int(v[b].size());\
    \ j++) {\n            int i = v[b][j].second;\n            auto bnxt = bucket(v[b][j].first\
    \ ^ last);\n            i2bj[i] = {bnxt, int(v[bnxt].size())}, v[bnxt].emplace_back(std::move(v[b][j]));\n\
    \        }\n        v[b].clear();\n    }\n\npublic:\n    radix_heap_array() :\
    \ sz(0), last(0) {}\n    bool empty() const noexcept { return sz == 0; }\n   \
    \ int argmin_pop() {\n        pull(), --sz;\n        int i = v[0].back().second;\n\
    \        i2bj[i].j = -1;\n        v[0].pop_back();\n        return i;\n    }\n\
    \    void chmin(Uint vnew, int i) {\n        if (i >= int(i2bj.size())) i2bj.resize(i\
    \ + 1, {0, -1});\n        if (i2bj[i].j < 0) {\n            auto b = bucket(vnew\
    \ ^ last);\n            ++sz, i2bj[i] = {b, int(v[b].size())}, v[b].emplace_back(vnew,\
    \ i);\n        } else if (v[i2bj[i].b][i2bj[i].j].first > vnew) {\n          \
    \  auto bold = i2bj[i].b, bnew = bucket(vnew ^ last);\n            if (bnew <\
    \ bold) {\n                int ilast = v[bold].back().second, j = i2bj[i].j;\n\
    \                std::swap(v[bold][j], v[bold].back());\n                i2bj[ilast].j\
    \ = j, i2bj[i] = {bnew, int(v[bnew].size())};\n                v[bnew].emplace_back(vnew,\
    \ i), v[bold].pop_back();\n            } else {\n                v[bold][i2bj[i].j].first\
    \ = vnew;\n            }\n        }\n    }\n\n    void pop() { argmin_pop(); }\n\
    \    std::pair<Uint, int> top() { return pull(), v[0].back(); }\n    [[deprecated(\"\
    NOT usual emplace() opeation!\")]] void emplace(Uint vnew, int i) {\n        chmin(vnew,\
    \ i);\n    }\n\n    void clear() noexcept { sz = 0, last = 0, i2bj.clear(); }\n\
    };\n#line 2 \"utilities/reader.hpp\"\n#include <cstdio>\n#include <string>\n\n\
    // CUT begin\ntemplate <typename T> T rd_integer() {\n    T ret = 0;\n    bool\
    \ minus = false;\n\n    char c = getchar_unlocked();\n    while (!isdigit(c))\
    \ minus |= (c == '-'), c = getchar_unlocked();\n    while (isdigit(c)) ret = (ret\
    \ << 1) + (ret << 3) + (c ^ 48), c = getchar_unlocked();\n\n    return minus ?\
    \ -ret : ret;\n}\nint rdi() { return rd_integer<int>(); }\nlong long rdll() {\
    \ return rd_integer<long long>(); }\nstd::string rdstr() {\n    std::string ret;\n\
    \    char c = getchar_unlocked();\n    while (!isgraph(c)) c = getchar_unlocked();\n\
    \    while (isgraph(c)) ret += c, c = getchar_unlocked();\n    return ret;\n}\n\
    #line 4 \"data_structure/test/radix_heap_array.dijkstra.test.cpp\"\n#include <iostream>\n\
    #line 8 \"data_structure/test/radix_heap_array.dijkstra.test.cpp\"\nusing namespace\
    \ std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n \
    \   int N = rdi(), M = rdi(), s = rdi(), t = rdi();\n\n    vector<vector<pair<int,\
    \ unsigned>>> to(N);\n    while (M--) {\n        int a = rdi(), b = rdi(), c =\
    \ rdi();\n        to[b].emplace_back(a, c);\n    }\n    vector<unsigned long long>\
    \ dist(N, numeric_limits<unsigned long long>::max());\n    vector<int> prv(N,\
    \ -1);\n    dist[t] = 0;\n    radix_heap_array<unsigned long long> pq;\n    pq.chmin(0,\
    \ t);\n    while (!pq.empty()) {\n        int now = pq.argmin_pop();\n       \
    \ if (now == s) break;\n        for (const auto &nx : to[now]) {\n           \
    \ int nxt = nx.first;\n            if (dist[nxt] > dist[now] + nx.second) {\n\
    \                dist[nxt] = dist[now] + nx.second;\n                prv[nxt]\
    \ = now;\n                pq.chmin(dist[nxt], nxt);\n            }\n        }\n\
    \    }\n    if (dist[s] == numeric_limits<unsigned long long>::max()) {\n    \
    \    cout << \"-1\\n\";\n        return 0;\n    }\n\n    std::vector<int> path;\n\
    \    for (int now = s; now != -1; now = prv[now]) path.push_back(now);\n\n   \
    \ cout << dist[s] << ' ' << path.size() - 1 << '\\n';\n    for (int i = 1; i <\
    \ int(path.size()); i++) cout << path[i - 1] << ' ' << path[i] << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/shortest_path\"\n#include\
    \ \"../radix_heap_array.hpp\"\n#include \"../../utilities/reader.hpp\"\n#include\
    \ <iostream>\n#include <limits>\n#include <utility>\n#include <vector>\nusing\
    \ namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \    int N = rdi(), M = rdi(), s = rdi(), t = rdi();\n\n    vector<vector<pair<int,\
    \ unsigned>>> to(N);\n    while (M--) {\n        int a = rdi(), b = rdi(), c =\
    \ rdi();\n        to[b].emplace_back(a, c);\n    }\n    vector<unsigned long long>\
    \ dist(N, numeric_limits<unsigned long long>::max());\n    vector<int> prv(N,\
    \ -1);\n    dist[t] = 0;\n    radix_heap_array<unsigned long long> pq;\n    pq.chmin(0,\
    \ t);\n    while (!pq.empty()) {\n        int now = pq.argmin_pop();\n       \
    \ if (now == s) break;\n        for (const auto &nx : to[now]) {\n           \
    \ int nxt = nx.first;\n            if (dist[nxt] > dist[now] + nx.second) {\n\
    \                dist[nxt] = dist[now] + nx.second;\n                prv[nxt]\
    \ = now;\n                pq.chmin(dist[nxt], nxt);\n            }\n        }\n\
    \    }\n    if (dist[s] == numeric_limits<unsigned long long>::max()) {\n    \
    \    cout << \"-1\\n\";\n        return 0;\n    }\n\n    std::vector<int> path;\n\
    \    for (int now = s; now != -1; now = prv[now]) path.push_back(now);\n\n   \
    \ cout << dist[s] << ' ' << path.size() - 1 << '\\n';\n    for (int i = 1; i <\
    \ int(path.size()); i++) cout << path[i - 1] << ' ' << path[i] << '\\n';\n}\n"
  dependsOn:
  - data_structure/radix_heap_array.hpp
  - utilities/reader.hpp
  isVerificationFile: true
  path: data_structure/test/radix_heap_array.dijkstra.test.cpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: data_structure/test/radix_heap_array.dijkstra.test.cpp
layout: document
redirect_from:
- /verify/data_structure/test/radix_heap_array.dijkstra.test.cpp
- /verify/data_structure/test/radix_heap_array.dijkstra.test.cpp.html
title: data_structure/test/radix_heap_array.dijkstra.test.cpp
---
