---
title: Binary search （二分探索）
documentation_of: ./bisect.hpp
---

二分探索を行う．
探索範囲が浮動小数点数で与えられた場合は， IEEE 754 の binary64 形式を 64 bit 整数だと思って上の桁から順に値を定めていくような挙動を示す（よって必ず 64 回以下のループで実行が完了する）．

## 使用方法

### `double bisect_mid_fp(double a, double b)`

64 bit 浮動小数点数の区間に対する二分探索で，現在の探索範囲の両端の値をもとに次に探索すべき値を返す．
引数 `a` や `b` は NaN でなければよい（非正規化数や無限でもよい）．
動作のイメージとして `ok` と `ng` がともに正の場合は幾何平均くらいのオーダーの値を返す．

### `template <class T> auto bisect(T ok, T ng, const std::function<bool(T)> &f, T abs_tol = T())`

二分探索を行い，条件を満たす値を求める関数．

- `ok` : `f(x) == true` を満たすことがわかっている `x` の値．
- `ng` : `f(x) == false` を満たすことがわかっている `x` の値．
- `f` : `T` 型の引数をとり，条件を満たす場合 `true` を返す判定関数．
- `abs_tol` : 許容絶対誤差． `ok` と `ng` の差がこの値以下になったら探索を打ち切る（デフォルトは `T()` ）．
- 戻り値 : `ok` および `ng` の最終値を含む `Result` 構造体．

## 問題例

- [No.2352 Sharpened Knife in Fall - yukicoder](https://yukicoder.me/problems/no/2352)
