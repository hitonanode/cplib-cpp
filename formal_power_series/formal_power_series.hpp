#pragma once
#include "convolution/ntt.hpp"
#include <algorithm>
#include <cassert>
#include <vector>

// Formal Power Series (形式的冪級数) based on ModInt<mod> / ModIntRuntime
// Reference: https://ei1333.github.io/luzhiled/snippets/math/formal-power-series.html
template <typename T> struct FormalPowerSeries : std::vector<T> {
    using std::vector<T>::vector;
    using P = FormalPowerSeries;

    void shrink() {
        while (this->size() and this->back() == T(0)) this->pop_back();
    }

    P operator+(const P &r) const { return P(*this) += r; }
    P operator+(const T &v) const { return P(*this) += v; }
    P operator-(const P &r) const { return P(*this) -= r; }
    P operator-(const T &v) const { return P(*this) -= v; }
    P operator*(const P &r) const { return P(*this) *= r; }
    P operator*(const T &v) const { return P(*this) *= v; }
    P operator/(const P &r) const { return P(*this) /= r; }
    P operator/(const T &v) const { return P(*this) /= v; }
    P operator%(const P &r) const { return P(*this) %= r; }

    P &operator+=(const P &r) {
        if (r.size() > this->size()) this->resize(r.size());
        for (int i = 0; i < (int)r.size(); i++) (*this)[i] += r[i];
        return *this;
    }
    P &operator+=(const T &v) {
        if (this->empty()) this->resize(1);
        (*this)[0] += v;
        return *this;
    }
    P &operator-=(const P &r) {
        if (r.size() > this->size()) this->resize(r.size());
        for (int i = 0; i < (int)r.size(); i++) (*this)[i] -= r[i];
        return *this;
    }
    P &operator-=(const T &v) {
        if (this->empty()) this->resize(1);
        (*this)[0] -= v;
        return *this;
    }
    P &operator*=(const T &v) {
        for (auto &x : (*this)) x *= v;
        return *this;
    }
    P &operator*=(const P &r) {
        if (this->empty() || r.empty())
            this->clear();
        else {
            auto ret = nttconv(*this, r);
            *this = P(ret.begin(), ret.end());
        }
        return *this;
    }
    P &operator%=(const P &r) {
        *this -= *this / r * r;
        return *this;
    }
    P operator-() const {
        P ret = *this;
        for (auto &v : ret) v = -v;
        return ret;
    }
    P &operator/=(const T &v) {
        assert(v != T(0));
        for (auto &x : (*this)) x /= v;
        return *this;
    }
    P &operator/=(const P &r) {
        if (this->size() < r.size()) {
            this->clear();
            return *this;
        }
        int n = (int)this->size() - r.size() + 1;
        return *this = (reversed().pre(n) * r.reversed().inv(n)).pre(n).reversed(n);
    }
    P pre(int sz) const {
        P ret(this->begin(), this->begin() + std::min((int)this->size(), sz));
        return ret;
    }
    P operator>>(int sz) const {
        if ((int)this->size() <= sz) return {};
        return P(this->begin() + sz, this->end());
    }
    P operator<<(int sz) const {
        if (this->empty()) return {};
        P ret(*this);
        ret.insert(ret.begin(), sz, T(0));
        return ret;
    }

    P reversed(int sz = -1) const {
        assert(sz >= -1);
        P ret(*this);
        if (sz != -1) ret.resize(sz, T());
        std::reverse(ret.begin(), ret.end());
        return ret;
    }

    P differential() const { // formal derivative (differential) of f.p.s.
        const int n = (int)this->size();
        P ret(std::max(0, n - 1));
        for (int i = 1; i < n; i++) ret[i - 1] = (*this)[i] * T(i);
        return ret;
    }

    P integral() const {
        const int n = (int)this->size();
        P ret(n + 1);
        ret[0] = T(0);
        for (int i = 0; i < n; i++) ret[i + 1] = (*this)[i] / T(i + 1);
        return ret;
    }

    /**
     * @brief f(x)g(x) = 1 (mod x^deg)
     *
     * @param deg
     * @return P ret.size() == deg
     */
    P inv(int deg) const {
        assert(deg >= -1);
        if (deg == 0) return {};

        assert(this->size() and this->at(0) != T()); // Requirement: F(0) != 0
        const int n = this->size();
        if (deg == -1) deg = n;

        P ret({T(1) / this->at(0)});
        for (int i = 1; i < deg; i <<= 1) {
            auto h = (pre(i << 1) * ret).pre(i << 1) >> i;
            auto tmp = (-h * ret).pre(i);
            ret.insert(ret.end(), tmp.cbegin(), tmp.cend());
            ret.resize(i << 1);
        }
        return ret.pre(deg);
    }

    P log(int len = -1) const {
        assert(len >= -1);
        if (len == 0) return {};

        assert(this->size() and ((*this)[0]) == T(1)); // Requirement: F(0) = 1

        const int n = (int)this->size();
        if (len == 0) return {};
        if (len == -1) len = n;
        return (this->differential() * this->inv(len)).pre(len - 1).integral();
    }

    P sqrt(int deg = -1) const {
        assert(deg >= -1);
        const int n = (int)this->size();
        if (deg == -1) deg = n;
        if (this->empty()) return {};
        if ((*this)[0] == T(0)) {
            for (int i = 1; i < n; i++)
                if ((*this)[i] != T(0)) {
                    if ((i & 1) or deg - i / 2 <= 0) return {};
                    return (*this >> i).sqrt(deg - i / 2) << (i / 2);
                }
            return {};
        }
        T sqrtf0 = (*this)[0].sqrt();
        if (sqrtf0 == T(0)) return {};

        P y = (*this) / (*this)[0], ret({T(1)});
        T inv2 = T(1) / T(2);
        for (int i = 1; i < deg; i <<= 1) ret = (ret + y.pre(i << 1) * ret.inv(i << 1)) * inv2;
        return ret.pre(deg) * sqrtf0;
    }

    P exp(int deg = -1) const {
        assert(deg >= -1);
        assert(this->empty() or ((*this)[0]) == T(0)); // Requirement: F(0) = 0
        const int n = (int)this->size();
        if (deg == -1) deg = n;
        P ret({T(1)});
        for (int i = 1; i < deg; i <<= 1) {
            ret = (ret * (pre(i << 1) + T(1) - ret.log(i << 1))).pre(i << 1);
        }
        return ret.pre(deg);
    }

    P pow(long long k, int deg = -1) const {
        assert(deg >= -1);
        const int n = (int)this->size();
        if (deg == -1) deg = n;

        if (k == 0) {
            P ret(deg);
            if (deg >= 1) ret[0] = T(1);
            ret.shrink();
            return ret;
        }

        for (int i = 0; i < n; i++) {
            if ((*this)[i] != T(0)) {
                T rev = T(1) / (*this)[i];
                P C = (*this) * rev, D(n - i);
                for (int j = i; j < n; j++) D[j - i] = C.coeff(j);
                D = (D.log(deg) * T(k)).exp(deg) * (*this)[i].pow(k);
                if (__int128(k) * i > deg) return {};
                P E(deg);
                long long S = i * k;
                for (int j = 0; j + S < deg and j < (int)D.size(); j++) E[j + S] = D[j];
                E.shrink();
                return E;
            }
        }
        return *this;
    }

    // Calculate f(X + c) from f(X), O(NlogN)
    P shift(T c) const {
        const int n = (int)this->size();
        P ret = *this;
        for (int i = 0; i < n; i++) ret[i] *= T::fac(i);
        std::reverse(ret.begin(), ret.end());
        P exp_cx(n, 1);
        for (int i = 1; i < n; i++) exp_cx[i] = exp_cx[i - 1] * c * T(i).inv();
        ret = ret * exp_cx;
        ret.resize(n);
        std::reverse(ret.begin(), ret.end());
        for (int i = 0; i < n; i++) ret[i] *= T::facinv(i);
        return ret;
    }

    T coeff(int i) const {
        if ((int)this->size() <= i or i < 0) return T(0);
        return (*this)[i];
    }

    T eval(T x) const {
        T ret = 0, w = 1;
        for (auto &v : *this) ret += w * v, w *= x;
        return ret;
    }
};
