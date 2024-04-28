---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"heuristic/multivariate_gaussian.hpp\"\n\n\n\n#include <cassert>\n\
    #include <vector>\n\n// #include \"linear_algebra_matrix/matrix.hpp\"\n\n// Multivariate\
    \ Gausssian distribution / Kalman filter\n// \u591A\u5909\u91CF\u6B63\u898F\u5206\
    \u5E03\u306E\u6570\u5024\u8A08\u7B97\u30FB\u30AB\u30EB\u30DE\u30F3\u30D5\u30A3\
    \u30EB\u30BF\ntemplate <class Matrix> struct MultivariateGaussian {\n\n    //\
    \ \u6B63\u898F\u5206\u5E03 N(x, P)\n    std::vector<double> x; // \u671F\u5F85\
    \u5024\n    Matrix P;              // \u5206\u6563\u5171\u5206\u6563\u884C\u5217\
    \n\n    void set(const std::vector<double> &x0, const Matrix &P0) {\n        const\
    \ int dim = x0.size();\n        assert(P0.height() == dim and P0.width() == dim);\n\
    \n        x = x0;\n        P = P0;\n    }\n\n    // \u52A0\u7B97\n    // \u3059\
    \u306A\u308F\u3061 x <- x + dx\n    void shift(const std::vector<double> &dx)\
    \ {\n        const int n = x.size();\n        assert(dx.size() == n);\n\n    \
    \    for (int i = 0; i < n; ++i) x.at(i) += dx.at(i);\n    }\n\n    // F: \u72B6\
    \u614B\u9077\u79FB\u884C\u5217 \u6B63\u65B9\u884C\u5217\u3092\u60F3\u5B9A\n  \
    \  // \u3059\u306A\u308F\u3061 x <- Fx\n    void linear_transform(const Matrix\
    \ &F) {\n        x = F * x;\n        P = F * P * F.transpose();\n    }\n\n   \
    \ // Q: \u30BC\u30ED\u5E73\u5747\u30AC\u30A6\u30B7\u30A2\u30F3\u30CE\u30A4\u30BA\
    \u306E\u5206\u6563\u5171\u5206\u6563\u884C\u5217\n    // \u3059\u306A\u308F\u3061\
    \ x <- x + w, w ~ N(0, Q)\n    void add_noise(const Matrix &Q) { P = P + Q; }\n\
    \n    // \u73FE\u5728\u306E x \u306E\u5206\u5E03\u3092 P(x | *) \u3068\u3057\u3066\
    \u3001\u6761\u4EF6\u4ED8\u304D\u78BA\u7387 P(x | *, z) \u3067\u66F4\u65B0\u3059\
    \u308B\n    // H: \u89B3\u6E2C\u884C\u5217, R: \u89B3\u6E2C\u30CE\u30A4\u30BA\u306E\
    \u5206\u6563\u5171\u5206\u6563\u884C\u5217, z: \u89B3\u6E2C\u5024\n    // \u3059\
    \u306A\u308F\u3061 z = Hx + v, v ~ N(0, R)\n    void measure(const Matrix &H,\
    \ const Matrix &R, const std::vector<double> &z,\n                 double regularlize\
    \ = 1e-9) {\n        const int nobs = z.size();\n\n        // \u6B8B\u5DEE e =\
    \ z - Hx\n        const auto Hx = H * x;\n        std::vector<double> e(nobs);\n\
    \        for (int i = 0; i < nobs; ++i) e.at(i) = z.at(i) - Hx.at(i);\n\n    \
    \    // \u6B8B\u5DEE\u5171\u5206\u6563 S = R + H P H^T\n        Matrix Sinv =\
    \ R + H * P * H.transpose();\n        Sinv = Sinv + Matrix::Identity(nobs) * regularlize;\
    \ // \u4E0D\u5B89\u5B9A\u304B\u3082\uFF1F\n        Sinv.inverse();\n\n       \
    \ // \u30AB\u30EB\u30DE\u30F3\u30B2\u30A4\u30F3 K = P H^T S^-1\n        Matrix\
    \ K = P * H.transpose() * Sinv;\n\n        // Update x\n        const auto dx\
    \ = K * e;\n        for (int i = 0; i < (int)x.size(); ++i) x.at(i) += dx.at(i);\n\
    \n        P = P - K * H * P;\n    }\n};\n\n\n"
  code: "#ifndef MULTIVARIATE_GAUSSIAN_HPP\n#define MULTIVARIATE_GAUSSIAN_HPP\n\n\
    #include <cassert>\n#include <vector>\n\n// #include \"linear_algebra_matrix/matrix.hpp\"\
    \n\n// Multivariate Gausssian distribution / Kalman filter\n// \u591A\u5909\u91CF\
    \u6B63\u898F\u5206\u5E03\u306E\u6570\u5024\u8A08\u7B97\u30FB\u30AB\u30EB\u30DE\
    \u30F3\u30D5\u30A3\u30EB\u30BF\ntemplate <class Matrix> struct MultivariateGaussian\
    \ {\n\n    // \u6B63\u898F\u5206\u5E03 N(x, P)\n    std::vector<double> x; //\
    \ \u671F\u5F85\u5024\n    Matrix P;              // \u5206\u6563\u5171\u5206\u6563\
    \u884C\u5217\n\n    void set(const std::vector<double> &x0, const Matrix &P0)\
    \ {\n        const int dim = x0.size();\n        assert(P0.height() == dim and\
    \ P0.width() == dim);\n\n        x = x0;\n        P = P0;\n    }\n\n    // \u52A0\
    \u7B97\n    // \u3059\u306A\u308F\u3061 x <- x + dx\n    void shift(const std::vector<double>\
    \ &dx) {\n        const int n = x.size();\n        assert(dx.size() == n);\n\n\
    \        for (int i = 0; i < n; ++i) x.at(i) += dx.at(i);\n    }\n\n    // F:\
    \ \u72B6\u614B\u9077\u79FB\u884C\u5217 \u6B63\u65B9\u884C\u5217\u3092\u60F3\u5B9A\
    \n    // \u3059\u306A\u308F\u3061 x <- Fx\n    void linear_transform(const Matrix\
    \ &F) {\n        x = F * x;\n        P = F * P * F.transpose();\n    }\n\n   \
    \ // Q: \u30BC\u30ED\u5E73\u5747\u30AC\u30A6\u30B7\u30A2\u30F3\u30CE\u30A4\u30BA\
    \u306E\u5206\u6563\u5171\u5206\u6563\u884C\u5217\n    // \u3059\u306A\u308F\u3061\
    \ x <- x + w, w ~ N(0, Q)\n    void add_noise(const Matrix &Q) { P = P + Q; }\n\
    \n    // \u73FE\u5728\u306E x \u306E\u5206\u5E03\u3092 P(x | *) \u3068\u3057\u3066\
    \u3001\u6761\u4EF6\u4ED8\u304D\u78BA\u7387 P(x | *, z) \u3067\u66F4\u65B0\u3059\
    \u308B\n    // H: \u89B3\u6E2C\u884C\u5217, R: \u89B3\u6E2C\u30CE\u30A4\u30BA\u306E\
    \u5206\u6563\u5171\u5206\u6563\u884C\u5217, z: \u89B3\u6E2C\u5024\n    // \u3059\
    \u306A\u308F\u3061 z = Hx + v, v ~ N(0, R)\n    void measure(const Matrix &H,\
    \ const Matrix &R, const std::vector<double> &z,\n                 double regularlize\
    \ = 1e-9) {\n        const int nobs = z.size();\n\n        // \u6B8B\u5DEE e =\
    \ z - Hx\n        const auto Hx = H * x;\n        std::vector<double> e(nobs);\n\
    \        for (int i = 0; i < nobs; ++i) e.at(i) = z.at(i) - Hx.at(i);\n\n    \
    \    // \u6B8B\u5DEE\u5171\u5206\u6563 S = R + H P H^T\n        Matrix Sinv =\
    \ R + H * P * H.transpose();\n        Sinv = Sinv + Matrix::Identity(nobs) * regularlize;\
    \ // \u4E0D\u5B89\u5B9A\u304B\u3082\uFF1F\n        Sinv.inverse();\n\n       \
    \ // \u30AB\u30EB\u30DE\u30F3\u30B2\u30A4\u30F3 K = P H^T S^-1\n        Matrix\
    \ K = P * H.transpose() * Sinv;\n\n        // Update x\n        const auto dx\
    \ = K * e;\n        for (int i = 0; i < (int)x.size(); ++i) x.at(i) += dx.at(i);\n\
    \n        P = P - K * H * P;\n    }\n};\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: heuristic/multivariate_gaussian.hpp
  requiredBy: []
  timestamp: '2024-04-28 14:03:51+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: heuristic/multivariate_gaussian.hpp
layout: document
title: "Multivariate Gaussian Distribution, Kalman filter / \u591A\u5909\u91CF\u6B63\
  \u898F\u5206\u5E03\u30FB\u30AB\u30EB\u30DE\u30F3\u30D5\u30A3\u30EB\u30BF"
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
