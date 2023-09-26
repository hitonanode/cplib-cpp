#pragma once
#include <algorithm>
#include <vector>

// CUT begin
// 0-indexed BIT (binary indexed tree / Fenwick tree) (i : [0, len))
template <class T> struct BIT {
    int n;
    std::vector<T> data;
    BIT(int len = 0) : n(len), data(len) {}
    BIT(const std::vector<T> &v) : n(v.size()), data(v.size()) {
        T p = 0;
        for (int i = 0; i < n; i++) {
            data[i] = p += v[i];
        }
        for (int j = n - 1; j >= 0; j--) {
            const int i = j & (j + 1);
            if (i > 0) data[j] -= data[i - 1];
        }
    }
    void reset() { std::fill(data.begin(), data.end(), T(0)); }
    void add(int pos, T v) { // a[pos] += v
        pos++;
        while (pos > 0 and pos <= n) data[pos - 1] += v, pos += pos & -pos;
    }
    T sum(int k) const { // a[0] + ... + a[k - 1]
        T res = 0;
        while (k > 0) res += data[k - 1], k -= k & -k;
        return res;
    }

    T sum(int l, int r) const { return sum(r) - sum(l); } // a[l] + ... + a[r - 1]

    template <class OStream> friend OStream &operator<<(OStream &os, const BIT &bit) {
        T prv = 0;
        os << '[';
        for (int i = 1; i <= bit.n; i++) {
            T now = bit.sum(i);
            os << now - prv << ',', prv = now;
        }
        return os << ']';
    }
};
