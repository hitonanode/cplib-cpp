---
title: Min-max semiring（(min, max) 半環）
documentation_of: ./min_max_semiring.hpp
---

加法を `min`，乗法を `max` で定義した半環．零元は `std::numeric_limits<T>::max()`、単位元は `std::numeric_limits<T>::min()` となっていることに注意．例えば距離行列に載せて行列積をとることで，パス上の最大重みの最小化等に使用できる．

## 問題例

- [AtCoder Beginner Contest 236 G - Good Vertices](https://atcoder.jp/contests/abc236/tasks/abc236_g)
- - [No.1340 おーじ君をさがせ - yukicoder](https://yukicoder.me/problems/no/1340)
