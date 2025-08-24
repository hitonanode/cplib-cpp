#pragma once
#include <cassert>
#include <iostream>
#include <set>
#include <vector>

template <int md> struct ModInt {
    static_assert(md > 1);
    using lint = long long;
    constexpr static int mod() { return md; }
    static int get_primitive_root() {
        static int primitive_root = 0;
        if (!primitive_root) {
            primitive_root = [&]() {
                std::set<int> fac;
                int v = md - 1;
                for (lint i = 2; i * i <= v; i++)
                    while (v % i == 0) fac.insert(i), v /= i;
                if (v > 1) fac.insert(v);
                for (int g = 1; g < md; g++) {
                    bool ok = true;
                    for (auto i : fac)
                        if (ModInt(g).pow((md - 1) / i) == 1) {
                            ok = false;
                            break;
                        }
                    if (ok) return g;
                }
                return -1;
            }();
        }
        return primitive_root;
    }
    int val_;
    int val() const noexcept { return val_; }
    constexpr ModInt() : val_(0) {}
    constexpr ModInt &_setval(lint v) { return val_ = (v >= md ? v - md : v), *this; }
    constexpr ModInt(lint v) { _setval(v % md + md); }
    constexpr explicit operator bool() const { return val_ != 0; }
    constexpr ModInt operator+(const ModInt &x) const {
        return ModInt()._setval((lint)val_ + x.val_);
    }
    constexpr ModInt operator-(const ModInt &x) const {
        return ModInt()._setval((lint)val_ - x.val_ + md);
    }
    constexpr ModInt operator*(const ModInt &x) const {
        return ModInt()._setval((lint)val_ * x.val_ % md);
    }
    constexpr ModInt operator/(const ModInt &x) const {
        return ModInt()._setval((lint)val_ * x.inv().val() % md);
    }
    constexpr ModInt operator-() const { return ModInt()._setval(md - val_); }
    constexpr ModInt &operator+=(const ModInt &x) { return *this = *this + x; }
    constexpr ModInt &operator-=(const ModInt &x) { return *this = *this - x; }
    constexpr ModInt &operator*=(const ModInt &x) { return *this = *this * x; }
    constexpr ModInt &operator/=(const ModInt &x) { return *this = *this / x; }
    friend constexpr ModInt operator+(lint a, const ModInt &x) { return ModInt(a) + x; }
    friend constexpr ModInt operator-(lint a, const ModInt &x) { return ModInt(a) - x; }
    friend constexpr ModInt operator*(lint a, const ModInt &x) { return ModInt(a) * x; }
    friend constexpr ModInt operator/(lint a, const ModInt &x) { return ModInt(a) / x; }
    constexpr bool operator==(const ModInt &x) const { return val_ == x.val_; }
    constexpr bool operator!=(const ModInt &x) const { return val_ != x.val_; }
    constexpr bool operator<(const ModInt &x) const {
        return val_ < x.val_;
    } // To use std::map<ModInt, T>
    friend std::istream &operator>>(std::istream &is, ModInt &x) {
        lint t;
        return is >> t, x = ModInt(t), is;
    }
    constexpr friend std::ostream &operator<<(std::ostream &os, const ModInt &x) {
        return os << x.val_;
    }

    constexpr ModInt pow(lint n) const {
        ModInt ans = 1, tmp = *this;
        while (n) {
            if (n & 1) ans *= tmp;
            tmp *= tmp, n >>= 1;
        }
        return ans;
    }

    static constexpr int cache_limit = std::min(md, 1 << 21);
    static std::vector<ModInt> facs, facinvs, invs;

    constexpr static void _precalculation(int N) {
        const int l0 = facs.size();
        if (N > md) N = md;
        if (N <= l0) return;
        facs.resize(N), facinvs.resize(N), invs.resize(N);
        for (int i = l0; i < N; i++) facs[i] = facs[i - 1] * i;
        facinvs[N - 1] = facs.back().pow(md - 2);
        for (int i = N - 2; i >= l0; i--) facinvs[i] = facinvs[i + 1] * (i + 1);
        for (int i = N - 1; i >= l0; i--) invs[i] = facinvs[i] * facs[i - 1];
    }

    constexpr ModInt inv() const {
        if (this->val_ < cache_limit) {
            if (facs.empty()) facs = {1}, facinvs = {1}, invs = {0};
            while (this->val_ >= int(facs.size())) _precalculation(facs.size() * 2);
            return invs[this->val_];
        } else {
            return this->pow(md - 2);
        }
    }

    constexpr static ModInt fac(int n) {
        assert(n >= 0);
        if (n >= md) return ModInt(0);
        while (n >= int(facs.size())) _precalculation(facs.size() * 2);
        return facs[n];
    }

    constexpr static ModInt facinv(int n) {
        assert(n >= 0);
        if (n >= md) return ModInt(0);
        while (n >= int(facs.size())) _precalculation(facs.size() * 2);
        return facinvs[n];
    }

    constexpr static ModInt doublefac(int n) {
        assert(n >= 0);
        if (n >= md) return ModInt(0);
        long long k = (n + 1) / 2;
        return (n & 1) ? ModInt::fac(k * 2) / (ModInt(2).pow(k) * ModInt::fac(k))
                       : ModInt::fac(k) * ModInt(2).pow(k);
    }

    constexpr static ModInt nCr(int n, int r) {
        assert(n >= 0);
        if (r < 0 or n < r) return ModInt(0);
        return ModInt::fac(n) * ModInt::facinv(r) * ModInt::facinv(n - r);
    }

    constexpr static ModInt nPr(int n, int r) {
        assert(n >= 0);
        if (r < 0 or n < r) return ModInt(0);
        return ModInt::fac(n) * ModInt::facinv(n - r);
    }

    static ModInt binom(int n, int r) {
        static long long bruteforce_times = 0;

        if (r < 0 or n < r) return ModInt(0);
        if (n <= bruteforce_times or n < (int)facs.size()) return ModInt::nCr(n, r);

        r = std::min(r, n - r);

        ModInt ret = ModInt::facinv(r);
        for (int i = 0; i < r; ++i) ret *= n - i;
        bruteforce_times += r;

        return ret;
    }

    // Multinomial coefficient, (k_1 + k_2 + ... + k_m)! / (k_1! k_2! ... k_m!)
    // Complexity: O(sum(ks))
    template <class Vec> static ModInt multinomial(const Vec &ks) {
        ModInt ret{1};
        int sum = 0;
        for (int k : ks) {
            assert(k >= 0);
            ret *= ModInt::facinv(k), sum += k;
        }
        return ret * ModInt::fac(sum);
    }
    template <class... Args> static ModInt multinomial(Args... args) {
        int sum = (0 + ... + args);
        ModInt result = (1 * ... * ModInt::facinv(args));
        return ModInt::fac(sum) * result;
    }

    // Catalan number, C_n = binom(2n, n) / (n + 1) = # of Dyck words of length 2n
    // C_0 = 1, C_1 = 1, C_2 = 2, C_3 = 5, C_4 = 14, ...
    // https://oeis.org/A000108
    // Complexity: O(n)
    static ModInt catalan(int n) {
        if (n < 0) return ModInt(0);
        return ModInt::fac(n * 2) * ModInt::facinv(n + 1) * ModInt::facinv(n);
    }

    ModInt sqrt() const {
        if (val_ == 0) return 0;
        if (md == 2) return val_;
        if (pow((md - 1) / 2) != 1) return 0;
        ModInt b = 1;
        while (b.pow((md - 1) / 2) == 1) b += 1;
        int e = 0, m = md - 1;
        while (m % 2 == 0) m >>= 1, e++;
        ModInt x = pow((m - 1) / 2), y = (*this) * x * x;
        x *= (*this);
        ModInt z = b.pow(m);
        while (y != 1) {
            int j = 0;
            ModInt t = y;
            while (t != 1) j++, t *= t;
            z = z.pow(1LL << (e - j - 1));
            x *= z, z *= z, y *= z;
            e = j;
        }
        return ModInt(std::min(x.val_, md - x.val_));
    }
};
template <int md> std::vector<ModInt<md>> ModInt<md>::facs = {1};
template <int md> std::vector<ModInt<md>> ModInt<md>::facinvs = {1};
template <int md> std::vector<ModInt<md>> ModInt<md>::invs = {0};

using ModInt998244353 = ModInt<998244353>;
// using mint = ModInt<998244353>;
// using mint = ModInt<1000000007>;
