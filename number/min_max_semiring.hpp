#pragma once
#include <limits>

// min-max 半環（加法が min, 乗法が max, 零元が INF, 単位元が -INF）
// Verified: abc236g, abc388f
template <class T> struct min_max_semiring {
    T val;
    min_max_semiring() : val(std::numeric_limits<T>::max()) {
        static_assert(std::numeric_limits<T>::max() > 0,
                      "std::numeric_limits<>::max() must be properly defined");
    }
    min_max_semiring(T x) : val(x) {}
    static min_max_semiring id() { return T(std::numeric_limits<T>::min()); }
    static min_max_semiring max() { return T(); }
    min_max_semiring operator+(const min_max_semiring &r) const {
        return (this->val > r.val ? r.val : this->val);
    }
    min_max_semiring &operator+=(const min_max_semiring &r) { return *this = *this + r; }
    min_max_semiring operator*(const min_max_semiring &r) const {
        return (this->val < r.val ? r.val : this->val);
    }
    min_max_semiring &operator*=(const min_max_semiring &r) { return *this = *this * r; }
    bool operator==(const min_max_semiring &r) const { return this->val == r.val; }
    bool operator!=(const min_max_semiring &r) const { return !(*this == r); }
    bool operator<(const min_max_semiring &r) const { return this->val < r.val; }
    bool operator>(const min_max_semiring &r) const { return this->val > r.val; }
    bool operator<=(const min_max_semiring &r) const { return this->val <= r.val; }
    bool operator>=(const min_max_semiring &r) const { return this->val >= r.val; }
    template <class OStream> friend OStream &operator<<(OStream &os, const min_max_semiring &x) {
        return os << x.val;
    }
};
