#pragma once
using namespace std;
using lint = long long;


constexpr lint MOD = 998244353;
template <int mod>
struct ModInt
{
    using lint = long long;
    int val;
    constexpr ModInt() : val(0) {}
    constexpr void _setval(lint v) { v = (v % mod) + mod; val = v >= mod ? v - mod : v; }
    constexpr ModInt(lint v) { _setval(v); }
    constexpr ModInt operator+(const ModInt &x) const { return ModInt((lint)val + x.val); }
    constexpr ModInt operator-(const ModInt &x) const { return ModInt((lint)val - x.val); }
    constexpr ModInt operator*(const ModInt &x) const { return ModInt((lint)val * x.val); }
    constexpr ModInt operator/(const ModInt &x) const { return ModInt((lint)val * x.inv()); }
    constexpr ModInt operator-() const { return ModInt(-val); }
    constexpr ModInt &operator+=(const ModInt &x) { return *this = *this + x; }
    constexpr ModInt &operator-=(const ModInt &x) { return *this = *this - x; }
    constexpr ModInt &operator*=(const ModInt &x) { return *this = *this * x; }
    constexpr ModInt &operator/=(const ModInt &x) { return *this = *this / x; }
    friend constexpr ModInt operator+(lint a, const ModInt &x) { return ModInt(a % mod + x.val); }
    friend constexpr ModInt operator-(lint a, const ModInt &x) { return ModInt(a % mod - x.val); }
    friend constexpr ModInt operator*(lint a, const ModInt &x) { return ModInt(a % mod * x.val); }
    friend constexpr ModInt operator/(lint a, const ModInt &x) { return ModInt(a % mod * x.inv()); }
    constexpr bool operator==(const ModInt &x) { return val == x.val; }
    constexpr bool operator!=(const ModInt &x) { return val != x.val; }
    friend istream &operator>>(istream &is, ModInt &x) { lint t; is >> t; x = ModInt(t); return is; }
    friend ostream &operator<<(ostream &os, const ModInt &x) { os << x.val;  return os; }

    constexpr lint power(lint n) const {
        lint ans = 1, tmp = this->val;
        while (n) {
            if (n & 1) ans = ans * tmp % mod;
            tmp = tmp * tmp % mod;
            n /= 2;
        }
        return ans;
    }
    constexpr lint inv() const { return this->power(mod - 2); }
    constexpr ModInt operator^(lint n) const { return ModInt(this->power(n)); }
    constexpr ModInt &operator^=(lint n) { return *this = *this ^ n; }

    inline ModInt fac() const {
        static vector<ModInt> facs;
        int l0 = facs.size();
        if (l0 > this->val) return facs[this->val];

        facs.resize(this->val + 1);
        for (int i = l0; i <= this->val; i++) facs[i] = (i == 0 ? ModInt(1) : facs[i - 1] * ModInt(i));
        return facs[this->val];
    }

    ModInt doublefac() const {
        lint k = (this->val + 1) / 2;
        if (this->val & 1) return ModInt(k * 2).fac() / ModInt(2).power(k) / ModInt(k).fac();
        else return ModInt(k).fac() * ModInt(2).power(k);
    }

    ModInt nCr(const ModInt &r) const {
        if (this->val < r.val) return ModInt(0);
        return this->fac() / ((*this - r).fac() * r.fac());
    }
};
using mint = ModInt<MOD>;
