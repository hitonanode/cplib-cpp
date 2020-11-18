#pragma once
#include <iostream>
#include <vector>

// CUT begin
// 1-indexed BIT (i : [1, len])
template <typename T> struct BIT : std::vector<T> {
    BIT(int len = 0) : std::vector<T>(len + 1) {}
    void reset() { fill(this->begin(), this->end(), 0); }
    void add(int pos, T v) {
        while (pos > 0 and pos < (int)this->size()) (*this)[pos] += v, pos += pos & -pos;
    }
    T sum(int pos) const { // (0, pos]
        T res = 0;
        while (pos > 0) res += (*this)[pos], pos -= pos & -pos;
        return res;
    }
    friend std::ostream &operator<<(std::ostream &os, const BIT &bit) {
        T prv = 0;
        os << '[';
        for (int i = 1; i < (int)bit.size(); i++) {
            T now = bit.sum(i);
            os << now - prv << ",";
            prv = now;
        }
        return os << ']';
    }
};
