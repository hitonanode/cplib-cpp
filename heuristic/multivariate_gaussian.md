---
title: Multivariate Gaussian Distribution, Kalman filter / 多変量正規分布・カルマンフィルタ
documentation_of: ./multivariate_gaussian.hpp
---

多変量正規分布のパラメータを管理するクラス．線形変換・ノイズの加算・観測による事後確率の更新が行える．カルマンフィルタの実装に利用可能．

## 使用方法

線形システムのカルマンフィルタの実装例を以下に示す．

```cpp
#include "linear_algebra_matrix/matrix.hpp"

// 初期化
MultivariateGaussian<matrix<double>> kf;
vector<double> mu(dim);
matrix<double> Sigma(dim, dim);
kf.set(mu, Sigma);  // N(mu, Sigma) で初期化

// 以下の「時間発展」「雑音の付与」「制御信号の注入」「推定」を任意の順序で任意の回数行ってよい。

// 時間発展
matrix<double> F(dim, dim);  // 時間発展行列
kf.linear_transform(F);

// 雑音の付与
matrix<double> Q(dim, dim);  // 正規雑音の分散・共分散行列
kf.add_noise(Q);

// 制御信号の注入
vector<double> u(dim);  // 制御入力
kf.shift(u);

// 観測
matrix<double> H(o, dim);  // 観測行列
matrix<double> R(o, o);  // 観測に重畳される正規雑音の分散・共分散行列
vector<double> z(o);  // 観測行列による観測結果
double regularize = 1e-9;  // 逆行列数値計算の安定のためのパラメータ
kf.measure(H, R, z, regularize);

// 推定
vector<double> est = kf.x;
```

- 現在の MAP 推定量が知りたい -> mu を見ればよい
- 周辺分布が欲しい -> mu と Sigma のうち特定の次元だけ取り出せばよい
- 一部の次元だけ観測できた場合の残りの次元の条件付き分布が欲しい → 未実装です
- サンプリングしたい → 未実装です

## 問題例

- [第一回マスターズ選手権 -決勝- A - Windy Drone Control (A)](https://atcoder.jp/contests/masters2024-final/tasks/masters2024_final_a)
