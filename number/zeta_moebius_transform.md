---
title: Zeta transform / Moebius transform （約数包除）
documentation_of: ./zeta_moebius_transform.hpp
---

整除関係に基づくゼータ変換・メビウス変換．またこれらを使用した添字 GCD・添字 LCM 畳み込み．計算量は $O(N \log \log N)$．なお，引数の `vector<>` について第 0 要素（`f[0]`）の値は無視される．

## 実装されている関数

### `void multiple_zeta(vector<T> &f)`

`f[x]` を `f[x * j]` ($j = 1, 2, \dots$) の総和で置き換える．

### `void multiple_moebius(vector<T> &f)`

`multiple_zeta()` の逆関数．

### `void divisor_zeta(vector<T> &f)`

`f[x]` を `f[y]` ($y$ は $x$ の約数) の総和で置き換える．

### `void divisor_moebius(vector<T> &f)`

`divisor_zeta()` の逆関数．
### `vector<T> gcdconv(vector<T> f, vector<T> g)`

添字 GCD 畳み込み．

$$
\mathrm{ret}[k] = \sum_{k = \mathrm{GCD}(i, j)} f[i] * g[j]
$$

### `vector<T> lcmconv(vector<T> f, vector<T> g)`

添字 LCM 畳み込み（もとの配列長をはみ出す部分は無視）．

$$
\mathrm{ret}[k] = \sum_{k = \mathrm{LCM}(i, j)} f[i] * g[j]
$$

## 使用例

```cpp
int N;
vector<unsigned long long> dp(N + 1);
multiple_moebius(dp);

vector<mint> f(N + 1), g(N + 1);
vector<mint> h = gcdconv(f, g);
```

## 問題例

- [No.886 Direct - yukicoder](https://yukicoder.me/problems/no/886)
- [No.1627 三角形の成立 - yukicoder](https://yukicoder.me/problems/no/1627)

## 文献・リンク

- [添え字 gcd での畳み込みで AGC038-C を解く - noshi91のメモ](https://noshi91.hatenablog.com/entry/2019/09/23/002445?_ga=2.226724693.934348036.1570274035-8397580.1533805090)
- [高速ゼータ変換の約数版 O(N log(log(N))) - noshi91のメモ](https://noshi91.hatenablog.com/entry/2018/12/27/121649)
