---
title: Min-plus semiring / tropical semiring（(min, +) 半環・トロピカル半環）
documentation_of: ./min_plus_semiring.hpp
---

加法を `min`，乗法を `+` で定義した半環．零元は `std::numeric_limits<T>::max() / 2` （オーバーフロー回避），単位元は `0` となっていることに注意．例えば距離行列に載せて行列積をとることで，パス長最小化等に使用できる．

なお，（当たり前ではあるが）零元と任意の値（正負に関わらず）との乗算の結果は零元になることに注意．
## 使用例

```cpp
using R = min_plus_semiring<int>;
matrix<R> mat(N, N);

while (M--) {
    int a, b;
    cin >> a >> b;
    mat[b][a] = 0;
}

std::vector<R> initvec(N, R()); // R() == INF
initvec[0] = R::id(); // R::id() == 0
auto vec = mat.pow_vec(T, initvec);
cout << count(vec.begin(), vec.end(), R(0)) << '\n';
```

## 問題例

- [No.1340 おーじ君をさがせ - yukicoder](https://yukicoder.me/problems/no/1340)
- [No.1780 [Cherry Anniversary] 真冬に咲く26の櫻の木 - yukicoder](https://yukicoder.me/problems/no/1780)
