---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/test/mincostflow.radixheap.yuki1288.test.cpp
    title: combinatorial_opt/test/mincostflow.radixheap.yuki1288.test.cpp
  - icon: ':heavy_check_mark:'
    path: data_structure/test/radix_heap.dijkstra.test.cpp
    title: data_structure/test/radix_heap.dijkstra.test.cpp
  - icon: ':heavy_check_mark:'
    path: graph/test/shortest_path.test.cpp
    title: graph/test/shortest_path.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://github.com/iwiwi/radix-heap
  bundledCode: "#line 2 \"data_structure/radix_heap.hpp\"\n#include <array>\n#include\
    \ <cstddef>\n#include <limits>\n#include <tuple>\n#include <type_traits>\n#include\
    \ <utility>\n#include <vector>\n\n// Radix heap for unsigned integer\n// https://github.com/iwiwi/radix-heap\n\
    template <class Uint, class Label, typename std::enable_if<std::is_unsigned<Uint>::value>::type\
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
    \ last(0) { static_assert(std::numeric_limits<Uint>::digits > 0, \"Invalid type.\"\
    ); }\n    std::size_t size() const noexcept { return sz; }\n    bool empty() const\
    \ noexcept { return sz == 0; }\n    void push(Uint x, const Label &val) { ++sz,\
    \ v[bucket(x ^ last)].emplace_back(x, val); }\n    void push(Uint x, Label &&val)\
    \ { ++sz, v[bucket(x ^ last)].emplace_back(x, std::move(val)); }\n    template\
    \ <class... Args> void emplace(Uint x, Args &&...args) {\n        ++sz, v[bucket(x\
    \ ^ last)].emplace_back(std::piecewise_construct, std::forward_as_tuple(x), std::forward_as_tuple(args...));\n\
    \    }\n    void pop() { pull(), --sz, v[0].pop_back(); }\n    std::pair<Uint,\
    \ Label> top() { return pull(), v[0].back(); }\n    Uint top_key() { return pull(),\
    \ last; }\n    Label &top_label() { return pull(), v[0].back().second; }\n   \
    \ void clear() noexcept {\n        sz = 0, last = 0;\n        for (auto &vec :\
    \ v) vec.clear();\n    }\n    void swap(radix_heap<Uint, Label> &a) { std::swap(sz,\
    \ a.sz), std::swap(last, a.last), v.swap(a.v); }\n};\n"
  code: "#pragma once\n#include <array>\n#include <cstddef>\n#include <limits>\n#include\
    \ <tuple>\n#include <type_traits>\n#include <utility>\n#include <vector>\n\n//\
    \ Radix heap for unsigned integer\n// https://github.com/iwiwi/radix-heap\ntemplate\
    \ <class Uint, class Label, typename std::enable_if<std::is_unsigned<Uint>::value>::type\
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
    \ last(0) { static_assert(std::numeric_limits<Uint>::digits > 0, \"Invalid type.\"\
    ); }\n    std::size_t size() const noexcept { return sz; }\n    bool empty() const\
    \ noexcept { return sz == 0; }\n    void push(Uint x, const Label &val) { ++sz,\
    \ v[bucket(x ^ last)].emplace_back(x, val); }\n    void push(Uint x, Label &&val)\
    \ { ++sz, v[bucket(x ^ last)].emplace_back(x, std::move(val)); }\n    template\
    \ <class... Args> void emplace(Uint x, Args &&...args) {\n        ++sz, v[bucket(x\
    \ ^ last)].emplace_back(std::piecewise_construct, std::forward_as_tuple(x), std::forward_as_tuple(args...));\n\
    \    }\n    void pop() { pull(), --sz, v[0].pop_back(); }\n    std::pair<Uint,\
    \ Label> top() { return pull(), v[0].back(); }\n    Uint top_key() { return pull(),\
    \ last; }\n    Label &top_label() { return pull(), v[0].back().second; }\n   \
    \ void clear() noexcept {\n        sz = 0, last = 0;\n        for (auto &vec :\
    \ v) vec.clear();\n    }\n    void swap(radix_heap<Uint, Label> &a) { std::swap(sz,\
    \ a.sz), std::swap(last, a.last), v.swap(a.v); }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/radix_heap.hpp
  requiredBy: []
  timestamp: '2021-09-07 01:07:11+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - graph/test/shortest_path.test.cpp
  - combinatorial_opt/test/mincostflow.radixheap.yuki1288.test.cpp
  - data_structure/test/radix_heap.dijkstra.test.cpp
documentation_of: data_structure/radix_heap.hpp
layout: document
title: "Radix heap \uFF08\u57FA\u6570\u30D2\u30FC\u30D7\uFF09"
---

`std::priroity_queue` と同様の機能を提供するヒープだが，「最後に取り出した値以上の値しか追加できない」という制約があり（本実装では更に，`top()` などのクエリで最後に「見た」以上の値しか追加できないという制約も加わる），また本実装では符号なし整数型に使用が限られる．ヒープがキーとして持つ整数型のビット数を $D$ とおくと，一度追加した要素に対しては演算が高々 $O(D)$ 回しか発生しないため，クエリ毎の計算量は償却 $O(D)$ で，定数倍にも優れているとされる．Dijkstra 法や各種フローアルゴリズムの定数倍高速化などに活用できる．

## 使用方法

```cpp
radix_heap<unsigned, string> pq, pq2;

pq.push(5, "a");
pq.emplace(1, "b");
cout << pq.top_key() << ' ' << pq.top_label() << '\n'; // 1 b
cout << pq.top().first << ' ' << pq.top().second << '\n'; // 1 b

pq.push(2, "c");
pq.push(3, "d");

cout << "size=" << pq.size() << '\n'; // size=4

while (pq.size()) {
    cout << pq.top_key() << ' ' << pq.top_label() << '\n';
    // 1 b
    // 2 c
    // 3 d
    // 5 a
    pq.pop();
}

pq.push(50, "heap1");
pq2.push(100, "heap2");
pq.swap(pq2);
cout << pq.top_label() << ' ' << pq2.top_label() << '\n'; // heap2 heap1
```

## 問題例

- [No.1288 yuki collection - yukicoder](https://yukicoder.me/problems/no/1288) 最小費用流の計算中に使用するヒープを `std::priority_queue` から `radix_heap` に変更することで定数倍が改善される（[2,261 ms](https://yukicoder.me/submissions/696945) → [886 ms](https://yukicoder.me/submissions/696946)）．

## リンク

- [1] R. K. Ahuja et al., "Faster algorithms for the shortest path problem,"
      Journal of the ACM 37(2), 213-223, 1990.
- [iwiwi/radix-heap: An implementation of radix heap](https://github.com/iwiwi/radix-heap) 本コードはこちらを参考に実装された．こちらは符号付整数型や浮動小数点数型にも対応する．
- [色々なダイクストラ高速化](https://www.slideshare.net/yosupo/ss-46612984)
