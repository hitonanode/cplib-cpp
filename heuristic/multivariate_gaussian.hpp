#ifndef MULTIVARIATE_GAUSSIAN_HPP
#define MULTIVARIATE_GAUSSIAN_HPP

#include <cassert>
#include <vector>

// #include "linear_algebra_matrix/matrix.hpp"

// Multivariate Gausssian distribution / Kalman filter
// 多変量正規分布の数値計算・カルマンフィルタ
template <class Matrix> struct MultivariateGaussian {

    // 正規分布 N(x, P)
    std::vector<double> x; // 期待値
    Matrix P;              // 分散共分散行列

    void set(const std::vector<double> &x0, const Matrix &P0) {
        const int dim = x0.size();
        assert(P0.height() == dim and P0.width() == dim);

        x = x0;
        P = P0;
    }

    // 加算
    // すなわち x <- x + dx
    void shift(const std::vector<double> &dx) {
        const int n = x.size();
        assert(dx.size() == n);

        for (int i = 0; i < n; ++i) x.at(i) += dx.at(i);
    }

    // F: 状態遷移行列 正方行列を想定
    // すなわち x <- Fx
    void linear_transform(const Matrix &F) {
        x = F * x;
        P = F * P * F.transpose();
    }

    // Q: ゼロ平均ガウシアンノイズの分散共分散行列
    // すなわち x <- x + w, w ~ N(0, Q)
    void add_noise(const Matrix &Q) { P = P + Q; }

    // 現在の x の分布を P(x | *) として、条件付き確率 P(x | *, z) で更新する
    // H: 観測行列, R: 観測ノイズの分散共分散行列, z: 観測値
    // すなわち z = Hx + v, v ~ N(0, R)
    void measure(const Matrix &H, const Matrix &R, const std::vector<double> &z,
                 double regularlize = 1e-9) {
        const int nobs = z.size();

        // 残差 e = z - Hx
        const auto Hx = H * x;
        std::vector<double> e(nobs);
        for (int i = 0; i < nobs; ++i) e.at(i) = z.at(i) - Hx.at(i);

        // 残差共分散 S = R + H P H^T
        Matrix Sinv = R + H * P * H.transpose();
        Sinv = Sinv + Matrix::Identity(nobs) * regularlize; // 不安定かも？
        Sinv.inverse();

        // カルマンゲイン K = P H^T S^-1
        Matrix K = P * H.transpose() * Sinv;

        // Update x
        const auto dx = K * e;
        for (int i = 0; i < (int)x.size(); ++i) x.at(i) += dx.at(i);

        P = P - K * H * P;
    }
};

#endif
