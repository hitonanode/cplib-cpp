#include <limits>

// min-plus 半環・トロピカル半環（加法が min, 乗法が plus, 零元が INF, 単位元が 0）
// INF = numeric_limits<T>::max() / 2 を超えたら INF に clamp する
// Verified: https://yukicoder.me/problems/no/1340
template <class T> struct min_plus_semiring {
    T val;
    static const T _T_inf() {
        static_assert(std::numeric_limits<T>::max() > 0,
                      "std::numeric_limits<>::max() must be properly defined");
        return std::numeric_limits<T>::max() / 2;
    }
    min_plus_semiring() : val(_T_inf()) {}
    min_plus_semiring(T x) : val(x) {}
    static min_plus_semiring id() { return min_plus_semiring(0); }
    min_plus_semiring operator+(const min_plus_semiring &r) const {
        return (this->val > r.val ? r.val : this->val);
    }
    min_plus_semiring &operator+=(const min_plus_semiring &r) { return *this = *this + r; }
    min_plus_semiring operator*(const min_plus_semiring &r) const {
        if (this->val == _T_inf() or r.val == _T_inf()) return min_plus_semiring();
        T tmp = this->val + r.val; // Watch out for overflow
        return _T_inf() < tmp ? min_plus_semiring() : min_plus_semiring(tmp);
    }
    min_plus_semiring &operator*=(const min_plus_semiring &r) { return *this = *this * r; }
    bool operator==(const min_plus_semiring &r) const { return this->val == r.val; }
    bool operator!=(const min_plus_semiring &r) const { return !(*this == r); }
    bool operator<(const min_plus_semiring &x) const { return this->val < x.val; }
    bool operator>(const min_plus_semiring &x) const { return this->val > x.val; }
    template <class OStream> friend OStream &operator<<(OStream &os, const min_plus_semiring &x) {
        return os << x.val;
    }
};
