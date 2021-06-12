#pragma once
#include "../convolution/ntt.hpp"
#include "../formal_power_series/linear_recurrence.hpp"
#include <algorithm>
#include <cassert>
#include <chrono>
#include <numeric>
#include <random>
#include <utility>
#include <vector>

template <typename ModInt> std::vector<ModInt> gen_random_vector(int len) {
    static std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());
    static std::uniform_int_distribution<int> rnd(1, ModInt::mod() - 1);
    std::vector<ModInt> ret(len);
    for (auto &x : ret) x = rnd(mt);
    return ret;
};

// Sparse matrix
template <typename Tp> struct sparse_matrix {
    int H, W;
    std::vector<std::vector<std::pair<int, Tp>>> vals;
    sparse_matrix(int H = 0, int W = 0) : H(H), W(W), vals(H) {}
    int height() const { return H; }
    int width() const { return W; }
    void add_element(int i, int j, Tp val) {
        assert(i >= 0 and i < H);
        assert(j >= 0 and i < W);
        vals[i].emplace_back(j, val);
    }
    std::vector<Tp> prod(const std::vector<Tp> &vec) const {
        assert(W == int(vec.size()));
        std::vector<Tp> ret(H);
        for (int i = 0; i < H; i++) {
            for (const auto &p : vals[i]) ret[i] += p.second * vec[p.first];
        }
        return ret;
    }
    std::vector<Tp> prod_left(const std::vector<Tp> &vec) const {
        assert(H == int(vec.size()));
        std::vector<Tp> ret(W);
        for (int i = 0; i < H; i++) {
            for (const auto &p : vals[i]) ret[p.first] += p.second * vec[i];
        }
        return ret;
    }
    std::vector<std::vector<Tp>> dense() const {
        std::vector<std::vector<Tp>> ret(H, std::vector<Tp>(W));
        for (int i = 0; i < H; i++) {
            for (auto p : vals[i]) ret[i][p.first] += p.second;
        }
        return ret;
    }
};

// Toeplitz matrix
// M = [
// [ vw_0 vw_1 vw_2 ... ]
// [ vh_1 ...           ]
// [ vh_2 ...           ]
// [ ...                ] (vw_0 == vh_0)
// prod() / prod_left() : O((H + W) log (H + W))
template <typename NTTModInt> struct toeplitz {
    int _h, _w;
    int _len_pow2;
    std::vector<NTTModInt> ts, ntt_ts;
    toeplitz(const std::vector<NTTModInt> &vh, const std::vector<NTTModInt> &vw)
        : _h(vh.size()), _w(vw.size()) {
        assert(vh.size() and vw.size() and vh[0] == vw[0]);
        ts.resize(_h + _w - 1);
        for (int i = 0; i < _w; i++) ts[i] = vw[_w - 1 - i];
        for (int j = 0; j < _h; j++) ts[_w - 1 + j] = vh[j];
        _len_pow2 = 1;
        while (_len_pow2 < int(ts.size()) + std::max(_h, _w) - 1) _len_pow2 *= 2;
        ntt_ts = ts;
        ntt_ts.resize(_len_pow2);
        ntt(ntt_ts, false);
    }
    int height() const { return _h; }
    int width() const { return _w; }
    std::vector<NTTModInt> prod(std::vector<NTTModInt> b) const {
        assert(int(b.size()) == _w);
        b.resize(_len_pow2);
        ntt(b, false);
        for (int i = 0; i < _len_pow2; i++) b[i] *= ntt_ts[i];
        ntt(b, true);
        b.erase(b.begin(), b.begin() + _w - 1);
        b.resize(_h);
        return b;
    }
    std::vector<NTTModInt> prod_left(std::vector<NTTModInt> b) const {
        assert(int(b.size()) == _h);
        std::reverse(b.begin(), b.end());
        b.resize(_len_pow2);
        ntt(b, false);
        for (int i = 0; i < _len_pow2; i++) b[i] *= ntt_ts[i];
        ntt(b, true);
        b.erase(b.begin(), b.begin() + _h - 1);
        b.resize(_w);
        std::reverse(b.begin(), b.end());
        return b;
    }
    std::vector<std::vector<NTTModInt>> dense() const {
        std::vector<std::vector<NTTModInt>> ret(_h, std::vector<NTTModInt>(_w));
        for (int i = 0; i < _h; i++) {
            for (int j = 0; j < _w; j++) ret[i][j] = ts[i - j + _w - 1];
        }
        return ret;
    }
};

// Square Toeplitz matrix
// M = [
// [ t_(N-1) t_(N-2) ... t_1 t_0     ]
// [ t_N     t_(N-1) ... t_2 t_1     ]
// [ ...                             ]
// [ t_(N*2-2)       ...     t_(N-1) ]]
// prod() / prod_left() : O(N log N)
template <typename NTTModInt> struct square_toeplitz {
    int _dim;
    int _len_pow2;
    std::vector<NTTModInt> ts;
    std::vector<NTTModInt> ntt_ts;
    square_toeplitz(const std::vector<NTTModInt> &t) : _dim(t.size() / 2 + 1), ts(t) {
        assert(t.size() % 2);
        _len_pow2 = 1;
        while (_len_pow2 < int(ts.size()) + _dim - 1) _len_pow2 *= 2;
        ntt_ts = ts;
        ntt_ts.resize(_len_pow2);
        ntt(ntt_ts, false);
    }
    int height() const { return _dim; }
    int width() const { return _dim; }

    // Calculate A * b
    std::vector<NTTModInt> prod(std::vector<NTTModInt> b) const {
        assert(int(b.size()) == _dim);
        b.resize(_len_pow2);
        ntt(b, false);
        for (int i = 0; i < _len_pow2; i++) b[i] *= ntt_ts[i];
        ntt(b, true);
        b.erase(b.begin(), b.begin() + _dim - 1);
        b.resize(_dim);
        return b;
    }
    // Calculate bT * A
    std::vector<NTTModInt> prod_left(std::vector<NTTModInt> b) const {
        std::reverse(b.begin(), b.end());
        b = prod(b);
        std::reverse(b.begin(), b.end());
        return b;
    }
    std::vector<std::vector<NTTModInt>> dense() const {
        std::vector<std::vector<NTTModInt>> ret(_dim, std::vector<NTTModInt>(_dim));
        for (int i = 0; i < _dim; i++) {
            for (int j = 0; j < _dim; j++) ret[i][j] = ts[i - j + _dim - 1];
        }
        return ret;
    }
};

// Probabilistic algorithm to find a solution of linear equation Ax = b if exists.
// Complexity: O(n T(n) + n^2)
// Reference:
// [1] W. Eberly, E. Kaltofen, "On randomized Lanczos algorithms," Proc. of international symposium on
//     Symbolic and algebraic computation, 176-183, 1997.
template <typename Matrix, typename T>
std::vector<T> linear_system_solver_lanczos(const Matrix &A, const std::vector<T> &b) {
    assert(A.height() == int(b.size()));
    const int M = A.height(), N = A.width();

    const std::vector<T> D1 = gen_random_vector<T>(N), D2 = gen_random_vector<T>(M), v = gen_random_vector<T>(N);
    auto applyD1 = [&D1](std::vector<T> v) {
        for (int i = 0; i < int(v.size()); i++) v[i] *= D1[i];
        return v;
    };
    auto applyD2 = [&D2](std::vector<T> v) {
        for (int i = 0; i < int(v.size()); i++) v[i] *= D2[i];
        return v;
    };
    auto applyAtilde = [&](std::vector<T> v) -> std::vector<T> {
        v = applyD1(v);
        v = A.prod(v);
        v = applyD2(v);
        v = A.prod_left(v);
        v = applyD1(v);
        return v;
    };
    auto dot = [&](const std::vector<T> &vl, const std::vector<T> &vr) -> T {
        return std::inner_product(vl.begin(), vl.end(), vr.begin(), T(0));
    };
    auto scalar_vec = [&](const T &x, std::vector<T> vec) -> std::vector<T> {
        for (auto &v : vec) v *= x;
        return vec;
    };

    auto btilde1 = applyD1(A.prod_left(applyD2(b))), btilde2 = applyAtilde(v);
    std::vector<T> btilde(N);
    for (int i = 0; i < N; i++) btilde[i] = btilde1[i] + btilde2[i];

    std::vector<T> w0 = btilde, v1 = applyAtilde(w0);
    std::vector<T> wm1(w0.size()), v0(v1.size());
    T t0 = dot(v1, w0), gamma = dot(btilde, w0) / t0, tm1 = 1;
    std::vector<T> x = scalar_vec(gamma, w0);
    while (true) {
        if (!t0 or !std::count_if(w0.begin(), w0.end(), [](T x) { return x != T(0); })) break;
        T alpha = dot(v1, v1) / t0, beta = dot(v1, v0) / tm1;
        std::vector<T> w1(N);
        for (int i = 0; i < N; i++) w1[i] = v1[i] - alpha * w0[i] - beta * wm1[i];
        std::vector<T> v2 = applyAtilde(w1);
        T t1 = dot(w1, v2);
        gamma = dot(btilde, w1) / t1;
        for (int i = 0; i < N; i++) x[i] += gamma * w1[i];

        wm1 = w0, w0 = w1;
        v0 = v1, v1 = v2;
        tm1 = t0, t0 = t1;
    }
    for (int i = 0; i < N; i++) x[i] -= v[i];
    return applyD1(x);
}

// Probabilistic algorithm to calculate determinant of matrices
// Complexity: O(n T(n) + n^2)
// Reference:
// [1] D. H. Wiedmann, "Solving sparse linear equations over finite fields,"
//     IEEE Trans. on Information Theory, 32(1), 54-62, 1986.
template <class Matrix, class Tp> Tp blackbox_determinant(const Matrix &M) {
    assert(M.height() == M.width());
    const int N = M.height();
    std::vector<Tp> b = gen_random_vector<Tp>(N), u = gen_random_vector<Tp>(N), D = gen_random_vector<Tp>(N);
    std::vector<Tp> uMDib(2 * N);
    for (int i = 0; i < 2 * N; i++) {
        uMDib[i] = std::inner_product(u.begin(), u.end(), b.begin(), Tp(0));
        for (int j = 0; j < N; j++) b[j] *= D[j];
        b = M.prod(b);
    }
    auto ret = find_linear_recurrence<Tp>(uMDib);
    Tp det = ret.second.back() * (N % 2 ? -1 : 1);
    Tp ddet = 1;
    for (auto d : D) ddet *= d;
    return det / ddet;
}
