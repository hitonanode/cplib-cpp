#pragma once
#include <cassert>
#include <utility>

struct GaussianInteger {
    using Int = long long;
    using G = GaussianInteger;
    Int x, y; // x + yi

    Int re() const noexcept { return x; }
    Int im() const noexcept { return y; }

    explicit GaussianInteger(Int x_ = 0, Int y_ = 0) : x(x_), y(y_) {}

    G &operator+=(const G &n) {
        x += n.x, y += n.y;
        return *this;
    }
    G &operator-=(const G &n) {
        x -= n.x, y -= n.y;
        return *this;
    }
    G &operator*=(const G &n) {
        const Int nx = x * n.x - y * n.y, ny = x * n.y + y * n.x;
        x = nx, y = ny;
        return *this;
    }

    // Euclidean division
    G &operator/=(const G &n) {
        const Int d = n.norm();
        assert(d != 0);
        const Int nx = x * n.x + y * n.y, ny = y * n.x - x * n.y;
        auto div_round = [](Int num, Int den) {
            return (num >= 0) ? (num + den / 2) / den : (num - den / 2) / den;
        };
        x = div_round(nx, d), y = div_round(ny, d);
        return *this;
    }

    G &operator%=(const G &n) {
        *this -= (*this / n) * n;
        return *this;
    }

    G operator+(const G &n) const { return G(*this) += n; }
    G operator-(const G &n) const { return G(*this) -= n; }
    G operator*(const G &n) const { return G(*this) *= n; }
    G operator/(const G &n) const { return G(*this) /= n; }
    G operator%(const G &n) const { return G(*this) %= n; }

    Int norm() const { return x * x + y * y; }

    G conj() const { return G{x, -y}; }

    static G gcd(G a, G b) {
        while (b.x != 0 or b.y != 0) {
            a %= b;
            std::swap(a, b);
        }
        return a.canonical();
    }
    friend G gcd(G a, G b) { return G::gcd(a, b); }

    bool operator==(const G &n) const { return x == n.x and y == n.y; }
    bool operator!=(const G &n) const { return !(*this == n); }

    template <class OStream> friend OStream &operator<<(OStream &os, const G &g) {
        return os << g.x << (g.y >= 0 ? "+" : "") << g.y << "i";
    }

    // move to first quadrant (x > 0, y >= 0)
    G canonical() const {
        if (x > 0 and y >= 0) return *this;
        if (x <= 0 and y > 0) return G{y, -x};
        if (x < 0 and y <= 0) return G{-x, -y};
        return G{-y, x};
    }

    std::pair<Int, Int> to_pair() const { return {x, y}; }
};
