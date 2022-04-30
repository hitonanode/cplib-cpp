#include <type_traits>

namespace dual_number_ {
struct has_id_method_impl {
    template <class T_> static auto check(T_ *) -> decltype(T_::id(), std::true_type());
    template <class T_> static auto check(...) -> std::false_type;
};
template <class T_> struct has_id : decltype(has_id_method_impl::check<T_>(nullptr)) {};
} // namespace dual_number_

// Dual number （二重数）
// Verified: https://atcoder.jp/contests/abc235/tasks/abc235_f
template <class T> struct DualNumber {
    T a, b; // a + bx

    template <typename T2, typename std::enable_if<dual_number_::has_id<T2>::value>::type * = nullptr>
    static T2 _T_id() {
        return T2::id();
    }
    template <typename T2, typename std::enable_if<!dual_number_::has_id<T2>::value>::type * = nullptr>
    static T2 _T_id() {
        return T2(1);
    }

    DualNumber(T x = T(), T y = T()) : a(x), b(y) {}
    static DualNumber id() { return DualNumber(_T_id<T>(), T()); }
    explicit operator bool() const { return a != T() or b != T(); }
    DualNumber operator+(const DualNumber &x) const { return DualNumber(a + x.a, b + x.b); }
    DualNumber operator-(const DualNumber &x) const { return DualNumber(a - x.a, b - x.b); }
    DualNumber operator*(const DualNumber &x) const {
        return DualNumber(a * x.a, b * x.a + a * x.b);
    }
    DualNumber operator/(const DualNumber &x) const {
        T cinv = _T_id<T>() / x.a;
        return DualNumber(a * cinv, (b * x.a - a * x.b) * cinv * cinv);
    }
    DualNumber operator-() const { return DualNumber(-a, -b); }
    DualNumber &operator+=(const DualNumber &x) { return *this = *this + x; }
    DualNumber &operator-=(const DualNumber &x) { return *this = *this - x; }
    DualNumber &operator*=(const DualNumber &x) { return *this = *this * x; }
    DualNumber &operator/=(const DualNumber &x) { return *this = *this / x; }
    bool operator==(const DualNumber &x) const { return a == x.a and b == x.b; }
    bool operator!=(const DualNumber &x) const { return !(*this == x); }
    bool operator<(const DualNumber &x) const { return (a != x.a ? a < x.a : b < x.b); }
    template <class OStream> friend OStream &operator<<(OStream &os, const DualNumber &x) {
        return os << '{' << x.a << ',' << x.b << '}';
    }

    T eval(const T &x) const { return a + b * x; }
    T root() const { return (-a) / b; } // Solve a + bx = 0 (b \neq 0 is assumed)
};
