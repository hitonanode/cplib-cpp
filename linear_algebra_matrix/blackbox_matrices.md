---
title: Black box linear algebra のための行列
documentation_of: ./blackbox_matrices.hpp
---

## 各行列クラスに実装されるべき関数

- `int height()` : 行列 $\mathbf{M}$ の行数を返す．
- `int width()` : 行列 $\mathbf{M}$ の列数を返す．
- `vector<T> prod(vector<T> v)` : 行列 $\mathbf{M}$ に右から列ベクトル $\mathbf{v}$ をかけた結果の列ベクトル $\mathbf{M}\mathbf{v}$ を計算．
- `vector<T> prod_left(vector<T> v)` : 行列 $\mathbf{M}$ に左から行ベクトル $\mathbf{u}^\top$ をかけた結果の行ベクトル $\mathbf{u}^\top \mathbf{M}$ を計算．
- `vector<vector<T>> vecvec()` : 行列 $\mathbf{M}$ を二次元のベクトルとして出力．

## 実装されている具体的な特殊行列

- `sparse_matrix<T>` : 疎行列．$S$ 個の非零の値追加に対し，`prod() / prod_left()` の計算量は $O(W + S), O(H + S)$．
- `toeplitz_ntt<T>` 特に T が $\mathbb{F}_p$ （$p$ は NTT-friendly な素数）の場合の Toeplitz 行列．`prod() / prod_left()` の計算量は $O((H + W) \log (H + W))$．FFTを用いることで乗算を高速化．
- `square_toeplitz_ntt<T>` : $N$ 次正方 Toeplitz 行列（不要かもしれない）．`prod() / prod_left()` の計算量は $O(N \log N)$．
