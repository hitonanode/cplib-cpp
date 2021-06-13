#pragma once
#include "../convolution/ntt.hpp"
#include <algorithm>
#include <cassert>
#include <numeric>
#include <utility>
#include <vector>

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
    std::vector<std::vector<Tp>> vecvec() const {
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
template <typename NTTModInt> struct toeplitz_ntt {
    int _h, _w;
    int _len_pow2;
    std::vector<NTTModInt> ts, ntt_ts;
    toeplitz_ntt(const std::vector<NTTModInt> &vh, const std::vector<NTTModInt> &vw)
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
    std::vector<std::vector<NTTModInt>> vecvec() const {
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
template <typename NTTModInt> struct square_toeplitz_ntt {
    int _dim;
    int _len_pow2;
    std::vector<NTTModInt> ts;
    std::vector<NTTModInt> ntt_ts;
    square_toeplitz_ntt(const std::vector<NTTModInt> &t) : _dim(t.size() / 2 + 1), ts(t) {
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
    std::vector<std::vector<NTTModInt>> vecvec() const {
        std::vector<std::vector<NTTModInt>> ret(_dim, std::vector<NTTModInt>(_dim));
        for (int i = 0; i < _dim; i++) {
            for (int j = 0; j < _dim; j++) ret[i][j] = ts[i - j + _dim - 1];
        }
        return ret;
    }
};
