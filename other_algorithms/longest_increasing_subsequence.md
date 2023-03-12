---
title: Longest increasing subsequence （LIS, 最長増加部分列）
documentation_of: ./longest_increasing_subsequence.hpp
---

列の最長増加部分列 (LIS)・最長非減少部分列の長さや，これらの部分列を構成する要素の添字列を得る．

## 使用方法

```cpp
vector<long long> A(N);

// LIS の長さ O(N log len(lis))
int lis_len = lis_length(A, LisType::StrictlyIncreasing);
// 最長非減少部分列の長さ O(N log len(lis))
int lnds_len = lis_length(A, LisType::Nondecreasing);

// LIS を構成する要素の添字列を取得 O(N log len(lis))
vector<int> lis_idxs = longest_increasing_subsequence(A, LisType::StrictlyIncreasing).get_lis_indices();
```

## 問題例

- [Library Checker: Longest Increasing Subsequence](https://judge.yosupo.jp/problem/longest_increasing_subsequence)
