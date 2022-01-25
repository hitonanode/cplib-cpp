#include <limits>

// min-max 半環（加法が min, 乗法が max）
// Verified: abc236g
template <class T> struct min_max_semiring {
    T val;
    min_max_semiring() : val(std::numeric_limits<T>::max()) {
        static_assert(std::numeric_limits<T>::max() > 0,
                      "std::numeric_limits<>::max() must be properly defined");
    }
    min_max_semiring(T x) : val(x) {}
    min_max_semiring operator+(const min_max_semiring &r) const {
        return (this->val > r.val ? r.val : this->val);
    }
    min_max_semiring &operator+=(const min_max_semiring &r) { return *this = *this + r; }
    min_max_semiring operator*(const min_max_semiring &r) const {
        return (this->val < r.val ? r.val : this->val);
    }
    min_max_semiring &operator*=(const min_max_semiring &r) { return *this = *this * r; }
    template <class OStream> friend OStream &operator<<(OStream &os, const min_max_semiring &x) {
        return os << x.val;
    }
    bool operator==(const min_max_semiring &r) const { return this->val == r.val; }
    bool operator!=(const min_max_semiring &r) const { return !(*this == r); }
};
