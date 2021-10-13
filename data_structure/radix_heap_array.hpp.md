---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/test/mincostflow.radixheaparray.yuki1288.test.cpp
    title: combinatorial_opt/test/mincostflow.radixheaparray.yuki1288.test.cpp
  - icon: ':heavy_check_mark:'
    path: data_structure/test/radix_heap_array.dijkstra.test.cpp
    title: data_structure/test/radix_heap_array.dijkstra.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"data_structure/radix_heap_array.hpp\"\n#include <array>\n\
    #include <limits>\n#include <type_traits>\n#include <utility>\n#include <vector>\n\
    \ntemplate <class Uint> class radix_heap_array {\n    int sz;\n    Uint last;\n\
    \    std::array<std::vector<std::pair<Uint, int>>, std::numeric_limits<Uint>::digits\
    \ + 1> v;\n\n    struct smallpii {\n        unsigned b : 7;\n        int j : 25;\n\
    \    };\n    std::vector<smallpii> i2bj;\n\n    template <class U, typename std::enable_if<sizeof(U)\
    \ == 4>::type* = nullptr>\n    static inline unsigned bucket(U x) noexcept {\n\
    \        return x ? 32 - __builtin_clz(x) : 0;\n    }\n    template <class U,\
    \ typename std::enable_if<sizeof(U) == 8>::type* = nullptr>\n    static inline\
    \ unsigned bucket(U x) noexcept {\n        return x ? 64 - __builtin_clzll(x)\
    \ : 0;\n    }\n\n    void pull() {\n        if (!v[0].empty()) return;\n     \
    \   int b = 1;\n        while (v[b].empty()) ++b;\n        last = v[b].back().first;\n\
    \        for (int j = 0; j < int(v[b].size()); j++) last = std::min(last, v[b][j].first);\n\
    \        for (int j = 0; j < int(v[b].size()); j++) {\n            int i = v[b][j].second;\n\
    \            auto bnxt = bucket(v[b][j].first ^ last);\n            i2bj[i] =\
    \ {bnxt, int(v[bnxt].size())}, v[bnxt].emplace_back(std::move(v[b][j]));\n   \
    \     }\n        v[b].clear();\n    }\n\npublic:\n    radix_heap_array() : sz(0),\
    \ last(0) {}\n    bool empty() const noexcept { return sz == 0; }\n    int argmin_pop()\
    \ {\n        pull(), --sz;\n        int i = v[0].back().second;\n        i2bj[i].j\
    \ = -1;\n        v[0].pop_back();\n        return i;\n    }\n    void chmin(Uint\
    \ vnew, int i) {\n        if (i >= int(i2bj.size())) i2bj.resize(i + 1, {0, -1});\n\
    \        if (i2bj[i].j < 0) {\n            auto b = bucket(vnew ^ last);\n   \
    \         ++sz, i2bj[i] = {b, int(v[b].size())}, v[b].emplace_back(vnew, i);\n\
    \        } else if (v[i2bj[i].b][i2bj[i].j].first > vnew) {\n            auto\
    \ bold = i2bj[i].b, bnew = bucket(vnew ^ last);\n            if (bnew < bold)\
    \ {\n                int ilast = v[bold].back().second, j = i2bj[i].j;\n     \
    \           std::swap(v[bold][j], v[bold].back());\n                i2bj[ilast].j\
    \ = j, i2bj[i] = {bnew, int(v[bnew].size())};\n                v[bnew].emplace_back(vnew,\
    \ i), v[bold].pop_back();\n            } else {\n                v[bold][i2bj[i].j].first\
    \ = vnew;\n            }\n        }\n    }\n\n    void pop() { argmin_pop(); }\n\
    \    std::pair<Uint, int> top() { return pull(), v[0].back(); }\n    [[deprecated(\"\
    NOT usual emplace() opeation!\")]] void emplace(Uint vnew, int i) { chmin(vnew,\
    \ i); }\n\n    void clear() noexcept { sz = 0, last = 0, i2bj.clear(); }\n};\n"
  code: "#pragma once\n#include <array>\n#include <limits>\n#include <type_traits>\n\
    #include <utility>\n#include <vector>\n\ntemplate <class Uint> class radix_heap_array\
    \ {\n    int sz;\n    Uint last;\n    std::array<std::vector<std::pair<Uint, int>>,\
    \ std::numeric_limits<Uint>::digits + 1> v;\n\n    struct smallpii {\n       \
    \ unsigned b : 7;\n        int j : 25;\n    };\n    std::vector<smallpii> i2bj;\n\
    \n    template <class U, typename std::enable_if<sizeof(U) == 4>::type* = nullptr>\n\
    \    static inline unsigned bucket(U x) noexcept {\n        return x ? 32 - __builtin_clz(x)\
    \ : 0;\n    }\n    template <class U, typename std::enable_if<sizeof(U) == 8>::type*\
    \ = nullptr>\n    static inline unsigned bucket(U x) noexcept {\n        return\
    \ x ? 64 - __builtin_clzll(x) : 0;\n    }\n\n    void pull() {\n        if (!v[0].empty())\
    \ return;\n        int b = 1;\n        while (v[b].empty()) ++b;\n        last\
    \ = v[b].back().first;\n        for (int j = 0; j < int(v[b].size()); j++) last\
    \ = std::min(last, v[b][j].first);\n        for (int j = 0; j < int(v[b].size());\
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
    NOT usual emplace() opeation!\")]] void emplace(Uint vnew, int i) { chmin(vnew,\
    \ i); }\n\n    void clear() noexcept { sz = 0, last = 0, i2bj.clear(); }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/radix_heap_array.hpp
  requiredBy: []
  timestamp: '2021-09-09 22:48:03+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - data_structure/test/radix_heap_array.dijkstra.test.cpp
  - combinatorial_opt/test/mincostflow.radixheaparray.yuki1288.test.cpp
documentation_of: data_structure/radix_heap_array.hpp
layout: document
title: "Array-like radix heap with decrease query\uFF08`chmin()` \u64CD\u4F5C\u304C\
  \u53EF\u80FD\u306A\u57FA\u6570\u30D2\u30FC\u30D7\uFF09"
---

`radix_heap.hpp` におけるラベルを非負整数に限り，更にラベル $i$ に対応したキーに対する decrease 操作（いわゆる `chmin`）を $O(1)$ で行えるもの．

## 使用方法

以下のように，Dijkstra 法を効率的に実行可能なクエリが揃っている．以下，$D$ を `UnsignedInt` 型のビット数とする．

- `radix_heap_array<UnsignedInt>()`: Radix heap の初期化．各 $i \ge 0$ について $A_i = \infty$ と初期化．計算量は $O(D)$．
- `bool empty()`: $A\_i < \infty$ である $i$ が存在しないとき，及びそのときに限り `true` を返す．$O(1)$
- `int argmin_pop()`: $A\_i$ が最小値をとる $i$ を一つとって $A\_i = \infty$ と更新し，$i$ を返す．償却 $O(D)$
- `void chmin(UnsignedInt x, int i)`: $A\_i$ を $\min(A\_i, x)$ で更新する．$x$ の値はこれまで `pop()` や `top()` の対象となった最大の値以上でなければならない．$O(1)$

以下は既存のライブラリとの互換性のために実装されている．

- `void pop()`: $A\_i$ が最小の $i$ の一つについて，$A_i = \infty$ と更新する．償却 $O(D)$
- `pair<UnsignedInt, int> top()`: $A\_i$ が最小の $i$ の一つについて，$(A\_i, i)$ の組を返す．償却 $O(D)$
- `void emplace(Uint vnew, int i)` （非推奨）: `chmin()` と同じ効果で，STL における同名の関数とは意味が大きく異なる．既存のライブラリに含まれる `priority_queue` をコンテスト中に素早くこのライブラリに置き換えることを可能にするためにのみ存在している．$O(1)$

Dijkstra 法による最短 $s$ - $t$ パスの計算は次のように書ける：
```cpp
vector<unsigned long long> dist(N, numeric_limits<unsigned long long>::max());
vector<int> prv(N, -1);
dist[s] = 0;
radix_heap_array<unsigned long long> pq;
pq.chmin(0, s);
while (!pq.empty()) {
    int now = pq.argmin_pop();
    if (now == t) break;
    for (const auto &nx : to[now]) {
        int nxt = nx.first;
        if (dist[nxt] > dist[now] + nx.second) {
            dist[nxt] = dist[now] + nx.second;
            prv[nxt] = now;
            pq.chmin(dist[nxt], nxt);
        }
    }
}
```
