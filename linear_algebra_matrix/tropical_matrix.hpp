#include <cassert>
#include <iostream>
#include <limits>
#include <vector>

// CUT begin
// Tropical matrix
// Verify: <https://atcoder.jp/contests/ddcc2020-final/submissions/16941701>
// A[j][i] = "length of shortest parh i -> j of graph A"
// (B * A)[k][i] = min_j (B[k][j] + A[j][i])
template <typename T> struct tropical_matrix {
    constexpr static T INF = std::numeric_limits<T>::max() / 2;
    static bool _chmin(T &m, const T q) {
        if (m > q) {
            m = q;
            return true;
        }
        return false;
    }
    int H, W;
    std::vector<T> elem;
    typename std::vector<T>::iterator operator[](int i) { return elem.begin() + i * W; }
    inline T &at(int i, int j) { return elem[i * W + j]; }
    inline T get(int i, int j) const { return elem[i * W + j]; }
    operator std::vector<std::vector<T>>() const {
        std::vector<std::vector<T>> ret(H);
        for (int i = 0; i < H; i++)
            std::copy(elem.begin() + i * W, elem.begin() + (i + 1) * W, std::back_inserter(ret[i]));
        return ret;
    }

    tropical_matrix(int H = 0, int W = 0) : H(H), W(W), elem(H * W, INF) {}
    tropical_matrix(const std::vector<std::vector<T>> &d)
        : H(d.size()), W(d.size() ? d[0].size() : 0) {
        for (auto &raw : d) std::copy(raw.begin(), raw.end(), std::back_inserter(elem));
    }

    static tropical_matrix Identity(int N) {
        tropical_matrix ret(N, N);
        for (int i = 0; i < N; i++) ret.at(i, i) = 0;
        return ret;
    }

    tropical_matrix operator+(const tropical_matrix &r) const {
        tropical_matrix ret(H, W);
        for (int i = 0; i < H * W; i++) _chmin(ret.elem[i], r.elem[i]);
        return ret;
    }
    tropical_matrix operator*(const tropical_matrix &r) const {
        tropical_matrix ret(H, r.W);
        for (int i = 0; i < H; i++) {
            for (int k = 0; k < W; k++) {
                for (int j = 0; j < r.W; j++) {
                    _chmin(ret.at(i, j), this->get(i, k) + r.get(k, j));
                }
            }
        }
        return ret;
    }
    tropical_matrix &operator+=(const tropical_matrix &r) { return *this = *this + r; }
    tropical_matrix &operator*=(const tropical_matrix &r) { return *this = *this * r; }
    bool operator==(const tropical_matrix &r) const {
        return H == r.H and W == r.W and elem == r.elem;
    }
    bool operator!=(const tropical_matrix &r) const {
        return H != r.H or W != r.W or elem != r.elem;
    }
    bool operator<(const tropical_matrix &r) const { return elem < r.elem; }
    tropical_matrix pow(int64_t n) const {
        tropical_matrix ret = Identity(H);
        if (n == 0) return ret;
        for (int i = 63 - __builtin_clzll(n); i >= 0; i--) {
            ret *= ret;
            if ((n >> i) & 1) ret *= (*this);
        }
        return ret;
    }
    tropical_matrix transpose() const {
        tropical_matrix ret(W, H);
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++) ret.at(j, i) = this->get(i, j);
        return ret;
    }
    friend std::vector<T> operator*(const tropical_matrix &m, const std::vector<T> &v) {
        assert(m.W == int(v.size()));
        std::vector<T> ret(m.H, m.INF);
        for (int i = 0; i < m.H; i++) {
            for (int j = 0; j < m.W; j++) { _chmin(ret[i], m.get(i, j) + v[j]); }
        }
        return ret;
    }
    friend std::vector<T> operator*(const std::vector<T> &v, const tropical_matrix &m) {
        assert(int(v.size()) == m.H);
        std::vector<T> ret(m.W, m.INF);
        for (int i = 0; i < m.H; i++) {
            for (int j = 0; j < m.W; j++) { _chmin(ret[j], v[i] + m.get(i, j)); }
        }
        return ret;
    }
    friend std::ostream &operator<<(std::ostream &os, const tropical_matrix &x) {
        os << "[(" << x.H << " * " << x.W << " matrix)";
        for (int i = 0; i < x.H; i++) {
            os << "\n[";
            for (int j = 0; j < x.W; j++) os << x.get(i, j) << ",";
            os << "]";
        }
        os << "]\n";
        return os;
    }
    friend std::istream &operator>>(std::istream &is, tropical_matrix &x) {
        for (auto &v : x.elem) is >> v;
        return is;
    }
};
