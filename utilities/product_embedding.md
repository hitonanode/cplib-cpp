---
title: Static range product query with precalculation （前計算埋め込み）
documentation_of: ./product_embedding.hpp
---

$\bmod$ 階乗などの計算を前計算して埋め込み， ${}_n \mathrm{P}_r$ などのクエリに高速で結果を返す．

## できること

（結合法則を満たす）乗法が定義された要素の列 $f(0), f(1), \dots$ を考える．$f(i)$ たちの値は陽には持たないが，$i$ の値を与えると $f(i)$ は十分高速に求められるものとする．バケットサイズとして正の整数 $B$ を定める．$F(k) = f(Bk) f(Bk + 1) \cdots f((B + 1)k - 1)$ の値を各 $k$ について前計算しておけば，任意のクエリ $(l, r)$ について $f(l) f(l + 1) \cdots f(r - 1)$ の値が $O(B + (r - l) / B)$ で求まる．

本コードは前計算した $F(k)$ の値の一覧をテキストファイルに出力する機能，およびこの前計算された結果を元に $f(l) \cdots f(r - 1)$ の値を計算するメソッドを提供する．

## 使用方法

「問題例」に挙げた階乗クエリを高速に処理したいケースで述べる．

まず前計算として，以下のようなコードを書いてコンパイルし実行する．

```cpp
using S = int;
constexpr S md = 1000000007;
S op(S l, S r) { return (long long)l * r % md; }
S e() { return 1; }
S getter(long long i) { return i + 1 >= md ? (i + 1) % md : i + 1; }  // f(i) = i + 1
using PE = product_embedding<S, op, e, getter, 500000>;

int main() {
    PE::prerun("tmp.txt", len);  // 0 <= l <= r <= len までのクエリ (l, r) の実行を保証する．
}
```

すると，`tmp.txt` というテキストファイルが生成されるので，その中身を用いて改めて `PE` クラスのインスタンスを生成し，これを用いて問題を解く．

```cpp
int main() {
    PE pe({154425679,765215884,239137314, ..., 899058414,0}); // 「PE pe」以降は tmp.txt のコピペで OK

    int ret = pe.prod(l, r);  // f(l) * ... * f(r - 1) = (l + 1) * ... * r の計算結果
}
```

## 問題例

- [No.502 階乗を計算するだけ - yukicoder](https://yukicoder.me/problems/no/502)
- [SRM 830 Div.1 1000 RedAndBlueShades](https://community.topcoder.com/stat?c=problem_statement&pm=17600) : 階乗のほか，$f(i) = 2i + 1$ 型の列に関する range product も使用される（考察により省くことも可能）．
