#include <cassert>
#include <vector>

// n-dimentional index <-> 1-dimentional index converter
// [a_0, ..., a_{dim - 1}] <-> a_0 + a_1 * size_0 + ... + a_{dim - 1} * (size_0 * ... * size_{dim - 2})
template <class T = int> struct multidim_index {
    int dim = 0;
    T _size = 1;
    std::vector<T> sizes;
    std::vector<T> weights;

    multidim_index() = default;

    explicit multidim_index(const std::vector<T> &sizes)
        : dim(sizes.size()), sizes(sizes), weights(dim, T(1)) {
        for (int d = 0; d < (int)sizes.size(); ++d) {
            assert(sizes.at(d) > 0);
            _size *= sizes.at(d);
            if (d >= 1) weights.at(d) = weights.at(d - 1) * sizes.at(d - 1);
        }
    }

    T size() const { return _size; }

    T flat_index(const std::vector<T> &encoded_vec) const {
        assert((int)encoded_vec.size() == (int)sizes.size());
        T ret = 0;
        for (int d = 0; d < (int)sizes.size(); ++d) {
            assert(0 <= encoded_vec.at(d) and encoded_vec.at(d) < sizes.at(d));
            ret += encoded_vec.at(d) * weights.at(d);
        }
        return ret;
    }

    std::vector<T> encode(T flat_index) const {
        assert(0 <= flat_index and flat_index < size());
        std::vector<T> ret(sizes.size());
        for (int d = (int)sizes.size() - 1; d >= 0; --d) {
            ret.at(d) = flat_index / weights.at(d);
            flat_index %= weights.at(d);
        }
        return ret;
    }

    template <class F> void lo_to_hi(F f) {
        for (int d = 0; d < (int)sizes.size(); ++d) {
            if (sizes.at(d) == 1) continue;

            T i = 0;
            std::vector<T> ivec(sizes.size());

            int cur = sizes.size();

            while (true) {
                f(i, i + weights.at(d));
                --cur;

                while (cur >= 0 and ivec.at(cur) + 1 == sizes.at(cur) - (cur == d)) {
                    i -= ivec.at(cur) * weights.at(cur);
                    ivec.at(cur--) = 0;
                }

                if (cur < 0) break;

                ++ivec.at(cur);
                i += weights.at(cur);
                cur = sizes.size();
            }
        }
    }

    // Subset sum (fast zeta transform)
    template <class U> void subset_sum(std::vector<U> &vec) {
        assert((T)vec.size() == size());
        lo_to_hi([&](T lo, T hi) { vec.at(hi) += vec.at(lo); });
    }

    // Inverse of subset sum (fast moebius transform)
    template <class U> void subset_sum_inv(std::vector<U> &vec) {
        assert((T)vec.size() == size());
        const T s = size() - 1;
        lo_to_hi([&](T dummylo, T dummyhi) { vec.at(s - dummylo) -= vec.at(s - dummyhi); });
    }

    // Superset sum (fast zeta transform)
    template <class U> void superset_sum(std::vector<U> &vec) {
        assert((T)vec.size() == size());
        const T s = size() - 1;
        lo_to_hi([&](T dummylo, T dummyhi) { vec.at(s - dummyhi) += vec.at(s - dummylo); });
    }

    // Inverse of superset sum (fast moebius transform)
    template <class U> void superset_sum_inv(std::vector<U> &vec) {
        assert((T)vec.size() == size());
        lo_to_hi([&](T lo, T hi) { vec.at(lo) -= vec.at(hi); });
    }
};
