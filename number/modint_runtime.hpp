#pragma once
#include <iostream>
#include <set>
#include <vector>

// CUT begin
struct ModIntRuntime {
    using lint = long long int;
    static int mod() { return md; }
    int val;
    static int md;
    static std::vector<ModIntRuntime> &facs() {
        static std::vector<ModIntRuntime> facs_;
        return facs_;
    }
    static int &get_primitive_root() {
        static int primitive_root_ = 0;
        if (!primitive_root_) {
            primitive_root_ = [&]() {
                std::set<int> fac;
                int v = md - 1;
                for (lint i = 2; i * i <= v; i++)
                    while (v % i == 0) fac.insert(i), v /= i;
                if (v > 1) fac.insert(v);
                for (int g = 1; g < md; g++) {
                    bool ok = true;
                    for (auto i : fac)
                        if (ModIntRuntime(g).power((md - 1) / i) == 1) {
                            ok = false;
                            break;
                        }
                    if (ok) return g;
                }
                return -1;
            }();
        }
        return primitive_root_;
    }
    static void set_mod(const int &m) {
        if (md != m) facs().clear();
        md = m;
        get_primitive_root() = 0;
    }
    ModIntRuntime &_setval(lint v) {
        val = (v >= md ? v - md : v);
        return *this;
    }
    ModIntRuntime() : val(0) {}
    ModIntRuntime(lint v) { _setval(v % md + md); }
    explicit operator bool() const { return val != 0; }
    ModIntRuntime operator+(const ModIntRuntime &x) const {
        return ModIntRuntime()._setval((lint)val + x.val);
    }
    ModIntRuntime operator-(const ModIntRuntime &x) const {
        return ModIntRuntime()._setval((lint)val - x.val + md);
    }
    ModIntRuntime operator*(const ModIntRuntime &x) const {
        return ModIntRuntime()._setval((lint)val * x.val % md);
    }
    ModIntRuntime operator/(const ModIntRuntime &x) const {
        return ModIntRuntime()._setval((lint)val * x.inv() % md);
    }
    ModIntRuntime operator-() const { return ModIntRuntime()._setval(md - val); }
    ModIntRuntime &operator+=(const ModIntRuntime &x) { return *this = *this + x; }
    ModIntRuntime &operator-=(const ModIntRuntime &x) { return *this = *this - x; }
    ModIntRuntime &operator*=(const ModIntRuntime &x) { return *this = *this * x; }
    ModIntRuntime &operator/=(const ModIntRuntime &x) { return *this = *this / x; }
    friend ModIntRuntime operator+(lint a, const ModIntRuntime &x) {
        return ModIntRuntime()._setval(a % md + x.val);
    }
    friend ModIntRuntime operator-(lint a, const ModIntRuntime &x) {
        return ModIntRuntime()._setval(a % md - x.val + md);
    }
    friend ModIntRuntime operator*(lint a, const ModIntRuntime &x) {
        return ModIntRuntime()._setval(a % md * x.val % md);
    }
    friend ModIntRuntime operator/(lint a, const ModIntRuntime &x) {
        return ModIntRuntime()._setval(a % md * x.inv() % md);
    }
    bool operator==(const ModIntRuntime &x) const { return val == x.val; }
    bool operator!=(const ModIntRuntime &x) const { return val != x.val; }
    bool operator<(const ModIntRuntime &x) const { return val < x.val; } // To use std::map<ModIntRuntime, T>
    friend std::istream &operator>>(std::istream &is, ModIntRuntime &x) {
        lint t;
        return is >> t, x = ModIntRuntime(t), is;
    }
    friend std::ostream &operator<<(std::ostream &os, const ModIntRuntime &x) { return os << x.val; }

    lint power(lint n) const {
        lint ans = 1, tmp = this->val;
        while (n) {
            if (n & 1) ans = ans * tmp % md;
            tmp = tmp * tmp % md;
            n /= 2;
        }
        return ans;
    }
    ModIntRuntime pow(lint n) const { return power(n); }
    lint inv() const { return this->power(md - 2); }

    ModIntRuntime fac() const {
        int l0 = facs().size();
        if (l0 > this->val) return facs()[this->val];

        facs().resize(this->val + 1);
        for (int i = l0; i <= this->val; i++)
            facs()[i] = (i == 0 ? ModIntRuntime(1) : facs()[i - 1] * ModIntRuntime(i));
        return facs()[this->val];
    }

    ModIntRuntime doublefac() const {
        lint k = (this->val + 1) / 2;
        return (this->val & 1) ? ModIntRuntime(k * 2).fac() / (ModIntRuntime(2).pow(k) * ModIntRuntime(k).fac())
                               : ModIntRuntime(k).fac() * ModIntRuntime(2).pow(k);
    }

    ModIntRuntime nCr(const ModIntRuntime &r) const {
        return (this->val < r.val) ? ModIntRuntime(0) : this->fac() / ((*this - r).fac() * r.fac());
    }

    ModIntRuntime sqrt() const {
        if (val == 0) return 0;
        if (md == 2) return val;
        if (power((md - 1) / 2) != 1) return 0;
        ModIntRuntime b = 1;
        while (b.power((md - 1) / 2) == 1) b += 1;
        int e = 0, m = md - 1;
        while (m % 2 == 0) m >>= 1, e++;
        ModIntRuntime x = power((m - 1) / 2), y = (*this) * x * x;
        x *= (*this);
        ModIntRuntime z = b.power(m);
        while (y != 1) {
            int j = 0;
            ModIntRuntime t = y;
            while (t != 1) j++, t *= t;
            z = z.power(1LL << (e - j - 1));
            x *= z, z *= z, y *= z;
            e = j;
        }
        return ModIntRuntime(std::min(x.val, md - x.val));
    }
};
int ModIntRuntime::md = 1;
