#include <cassert>
#include <limits>
#include <type_traits>

// Dyadic rational, surreal numbers （超現実数）
// https://atcoder.jp/contests/abc229/submissions/28887690
template <class Int, class Uint = unsigned long long> struct DyadicRational {
    Int integ; // 整数部分
    Uint frac; // 小数部分の分子

    static constexpr int FracLen = std::numeric_limits<Uint>::digits - 1; // 2^63
    static constexpr Uint denom = Uint(1) << FracLen;                     // 小数部分の分母

    DyadicRational(Int x = 0) : integ(x), frac(0) {
        static_assert(
            0 < FracLen and FracLen < std::numeric_limits<Uint>::digits, "FracLen value error");
        static_assert(std::is_signed<Int>::value == true, "Int must be signed");
    }
    static DyadicRational _construct(Int x, Uint frac_) {
        DyadicRational ret(x);
        ret.frac = frac_;
        return ret;
    }
    double to_double() const { return integ + double(frac) / denom; }

    // static DyadicRational from_rational(Int num, int lg_den);
    bool operator==(const DyadicRational &r) const { return integ == r.integ and frac == r.frac; }
    bool operator!=(const DyadicRational &r) const { return integ != r.integ or frac != r.frac; }
    bool operator<(const DyadicRational &r) const {
        return integ != r.integ ? integ < r.integ : frac < r.frac;
    }
    bool operator<=(const DyadicRational &r) const { return (*this == r) or (*this < r); }
    bool operator>(const DyadicRational &r) const { return r < *this; }
    bool operator>=(const DyadicRational &r) const { return r <= *this; }

    DyadicRational operator+(const DyadicRational &r) const {
        auto i = integ + r.integ;
        auto f = frac + r.frac;
        if (f >= denom) ++i, f -= denom; // overflow
        return DyadicRational::_construct(i, f);
    }
    DyadicRational operator-(const DyadicRational &r) const {
        auto i = integ - r.integ;
        auto f = frac - r.frac;
        if (f > denom) --i, f += denom; // overflow
        return DyadicRational::_construct(i, f);
    }
    DyadicRational operator-() const { return DyadicRational() - *this; }
    DyadicRational &operator+=(const DyadicRational &r) { return *this = *this + r; }

    DyadicRational right() const {
        if (frac == 0) {
            if (integ >= 0) {
                return DyadicRational(integ + 1);
            } else {
                return DyadicRational::_construct(integ, Uint(1) << (FracLen - 1));
            }
        }
        int d = __builtin_ctzll(frac);
        return DyadicRational::_construct(integ, frac ^ (Uint(1) << (d - 1)));
    }
    DyadicRational left() const {
        if (frac == 0) {
            if (integ <= 0) {
                return DyadicRational(integ - 1);
            } else {
                return DyadicRational::_construct(integ - 1, Uint(1) << (FracLen - 1));
            }
        }
        int d = __builtin_ctzll(frac);
        return DyadicRational::_construct(integ, frac ^ (Uint(3) << (d - 1)));
    }

    // Surreal number { l | r }
    static DyadicRational surreal(const DyadicRational &l, const DyadicRational &r) {
        assert(l < r);
        DyadicRational x(0);
        if (l.integ > 0) x = DyadicRational(l.integ);
        if (r.integ < 0) x = DyadicRational(r.integ);
        while (true) {
            if (x <= l) {
                x = x.right();
            } else if (x >= r) {
                x = x.left();
            } else {
                break;
            }
        }
        return x;
    }
    template <class OStream> friend OStream &operator<<(OStream &os, const DyadicRational &x) {
        return os << x.to_double();
    }
};
// using dyrational = DyadicRational<long long>;
