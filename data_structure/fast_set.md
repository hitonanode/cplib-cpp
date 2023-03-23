---
title: Fast set of integers （64分木で整数集合を高速に処理するデータ構造）
documentation_of: ./fast_set.hpp
---

`std::set<int>` のように使えるが $0$ 以上 $N$ 未満の整数の集合に特化したデータ構造．各種クエリに対して非常に高速に動作するので， Mo's algorithm などと組み合わせると非常に有効．空間計算量 $N + O(\log N)$ bit.

## 使用方法

```cpp
int N;
fast_set fs(N);  // [0, N)

int a;

// Almost same as std::set<int>
fs.insert(a);
fs.erase(a);
bool has_a = fs.contains(a);
int sz = fs.size();
bool is_empty = fs.empty();
fs.clear();

// Additional methods
int nxt = fs.next(a);  // a 以上の最小の要素の取得（存在しなければ N を返す）
int prv = fs.prev(a);  // a 以下の最大の要素の取得（存在しなければ -1 を返す）
int lo = fs.min();     // 最小値
int hi = fs.max();     // 最大値
```

## 問題例

- [Library Checker: Predecessor Problem](https://judge.yosupo.jp/problem/predecessor_problem)
