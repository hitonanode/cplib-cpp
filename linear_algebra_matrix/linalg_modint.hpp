#pragma once
#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <vector>

// CUT begin
template <typename T> struct matrix {
    int H, W;
    std::vector<T> elem;
    typename std::vector<T>::iterator operator[](int i) { return elem.begin() + i * W; }
    inline T &at(int i, int j) { return elem[i * W + j]; }
    inline T get(int i, int j) const { return elem[i * W + j]; }
    operator std::vector<std::vector<T>>() const {
        std::vector<std::vector<T>> ret(H);
        for (int i = 0; i < H; i++) {
            std::copy(elem.begin() + i * W, elem.begin() + (i + 1) * W, std::back_inserter(ret[i]));
        }
        return ret;
    }

    matrix() = default;
    matrix(int H, int W) : H(H), W(W), elem(H * W) {}
    matrix(const std::vector<std::vector<T>> &d) : H(d.size()), W(d.size() ? d[0].size() : 0) {
        for (auto &raw : d) std::copy(raw.begin(), raw.end(), std::back_inserter(elem));
    }

    static matrix Identity(int N) {
        matrix ret(N, N);
        for (int i = 0; i < N; i++) ret.at(i, i) = 1;
        return ret;
    }

    matrix operator-() const {
        matrix ret(H, W);
        for (int i = 0; i < H * W; i++) ret.elem[i] = -elem[i];
        return ret;
    }
    matrix operator*(const T &v) const {
        matrix ret = *this;
        for (auto &x : ret.elem) x *= v;
        return ret;
    }
    matrix operator/(const T &v) const {
        matrix ret = *this;
        const T vinv = v.inv();
        for (auto &x : ret.elem) x *= vinv;
        return ret;
    }
    matrix operator+(const matrix &r) const {
        matrix ret = *this;
        for (int i = 0; i < H * W; i++) ret.elem[i] += r.elem[i];
        return ret;
    }
    matrix operator-(const matrix &r) const {
        matrix ret = *this;
        for (int i = 0; i < H * W; i++) ret.elem[i] -= r.elem[i];
        return ret;
    }
    matrix operator*(const matrix &r) const {
        matrix ret(H, r.W);
        for (int i = 0; i < H; i++) {
            for (int k = 0; k < W; k++) {
                for (int j = 0; j < r.W; j++) ret.at(i, j) += this->get(i, k) * r.get(k, j);
            }
        }
        return ret;
    }
    matrix &operator*=(const T &v) { return *this = *this * v; }
    matrix &operator/=(const T &v) { return *this = *this / v; }
    matrix &operator+=(const matrix &r) { return *this = *this + r; }
    matrix &operator-=(const matrix &r) { return *this = *this - r; }
    matrix &operator*=(const matrix &r) { return *this = *this * r; }
    bool operator==(const matrix &r) const { return H == r.H and W == r.W and elem == r.elem; }
    bool operator!=(const matrix &r) const { return H != r.H or W != r.W or elem != r.elem; }
    bool operator<(const matrix &r) const { return elem < r.elem; }
    matrix pow(int64_t n) const {
        matrix ret = Identity(H);
        bool ret_is_id = true;
        if (n == 0) return ret;
        for (int i = 63 - __builtin_clzll(n); i >= 0; i--) {
            if (!ret_is_id) ret *= ret;
            if ((n >> i) & 1) ret *= (*this), ret_is_id = false;
        }
        return ret;
    }
    std::vector<T> pow_vec(int64_t n, std::vector<T> vec) const {
        matrix x = *this;
        while (n) {
            if (n & 1) vec = x * vec;
            x *= x;
            n >>= 1;
        }
        return vec;
    };
    matrix transpose() const {
        matrix ret(W, H);
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) ret.at(j, i) = this->get(i, j);
        }
        return ret;
    }
    // Gauss-Jordan elimination
    // - Require inverse for every non-zero element
    // - Complexity: O(H^2 W)
    matrix gauss_jordan() const {
        int c = 0;
        matrix mtr(*this);
        std::vector<int> ws;
        ws.reserve(W);
        for (int h = 0; h < H; h++) {
            if (c == W) break;
            int piv = -1;
            for (int j = h; j < H; j++)
                if (mtr.get(j, c)) {
                    piv = j;
                    break;
                }
            if (piv == -1) {
                c++;
                h--;
                continue;
            }
            if (h != piv) {
                for (int w = 0; w < W; w++) {
                    std::swap(mtr[piv][w], mtr[h][w]);
                    mtr.at(piv, w) *= -1; // To preserve sign of determinant
                }
            }
            ws.clear();
            for (int w = c; w < W; w++) {
                if (mtr.at(h, w) != 0) ws.emplace_back(w);
            }
            const T hcinv = mtr.at(h, c).inv();
            for (int hh = 0; hh < H; hh++)
                if (hh != h) {
                    const T coeff = mtr.at(hh, c) * hcinv;
                    for (auto w : ws) mtr.at(hh, w) -= mtr.at(h, w) * coeff;
                }
            c++;
        }
        return mtr;
    }
    int rank_of_gauss_jordan() const {
        for (int i = H * W - 1; i >= 0; i--) {
            if (elem[i]) return i / W + 1;
        }
        return 0;
    }
    T determinant_of_upper_triangle() const {
        T ret = 1;
        for (int i = 0; i < H; i++) ret *= get(i, i);
        return ret;
    }
    int inverse() {
        assert(H == W);
        std::vector<std::vector<T>> ret = Identity(H), tmp = *this;
        int rank = 0;
        for (int i = 0; i < H; i++) {
            int ti = i;
            while (ti < H and tmp[ti][i] == 0) ti++;
            if (ti == H) {
                continue;
            } else {
                rank++;
            }
            ret[i].swap(ret[ti]), tmp[i].swap(tmp[ti]);
            T inv = tmp[i][i].inv();
            for (int j = 0; j < W; j++) ret[i][j] *= inv;
            for (int j = i + 1; j < W; j++) tmp[i][j] *= inv;
            for (int h = 0; h < H; h++) {
                if (i == h) continue;
                const T c = -tmp[h][i];
                for (int j = 0; j < W; j++) ret[h][j] += ret[i][j] * c;
                for (int j = i + 1; j < W; j++) tmp[h][j] += tmp[i][j] * c;
            }
        }
        *this = ret;
        return rank;
    }
    friend std::vector<T> operator*(const matrix &m, const std::vector<T> &v) {
        assert(m.W == int(v.size()));
        std::vector<T> ret(m.H);
        for (int i = 0; i < m.H; i++) {
            for (int j = 0; j < m.W; j++) ret[i] += m.get(i, j) * v[j];
        }
        return ret;
    }
    friend std::vector<T> operator*(const std::vector<T> &v, const matrix &m) {
        assert(int(v.size()) == m.H);
        std::vector<T> ret(m.W);
        for (int i = 0; i < m.H; i++) {
            for (int j = 0; j < m.W; j++) ret[j] += v[i] * m.get(i, j);
        }
        return ret;
    }
    friend std::ostream &operator<<(std::ostream &os, const matrix &x) {
        os << "[(" << x.H << " * " << x.W << " matrix)";
        os << "\n[column sums: ";
        for (int j = 0; j < x.W; j++) {
            T s = 0;
            for (int i = 0; i < x.H; i++) s += x.get(i, j);
            os << s << ",";
        }
        os << "]";
        for (int i = 0; i < x.H; i++) {
            os << "\n[";
            for (int j = 0; j < x.W; j++) os << x.get(i, j) << ",";
            os << "]";
        }
        os << "]\n";
        return os;
    }
    friend std::istream &operator>>(std::istream &is, matrix &x) {
        for (auto &v : x.elem) is >> v;
        return is;
    }
};
// Fibonacci numbers f(n) = af(n - 1) + bf(n - 2)
// Example (a = b = 1): 0=>1, 1=>1, 2=>2, 3=>3, 4=>5, ...
template <typename T> T Fibonacci(long long int k, int a = 1, int b = 1) {
    matrix<T> mat(2, 2);
    mat[0][1] = 1;
    mat[1][0] = b;
    mat[1][1] = a;
    return mat.pow(k + 1)[0][1];
}
