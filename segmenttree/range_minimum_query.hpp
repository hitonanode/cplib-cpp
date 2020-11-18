#pragma once
#include <iostream>
#include <vector>
using namespace std;

// CUT begin
using T = int;
struct RangeMinimumQuery {
    int N;
    T defaultT = 1e9;
    int head;
    vector<T> x;
    T _get(int begin, int end, int pos, int l, int r) const {
        if (r <= begin or l >= end) return defaultT;
        if (l >= begin and r <= end) return x[pos];
        return min(_get(begin, end, 2 * pos + 1, l, (l + r) / 2), _get(begin, end, 2 * pos + 2, (l + r) / 2, r));
    }
    RangeMinimumQuery(int N, T defaultT) : N(N), defaultT(defaultT) {
        int N_tmp = 1;
        while (N_tmp < N) N_tmp <<= 1;
        x.assign(N_tmp * 2, defaultT), head = N_tmp - 1;
    }
    void build(const vector<T> &vals) {
        copy(vals.begin(), vals.end(), x.begin() + head);
        for (int i = head - 1; i >= 0; i--) { x[i] = min(x[i * 2 + 1], x[i * 2 + 2]); }
    }
    RangeMinimumQuery(const vector<T> &vals, T defaultT) : N(vals.size()), defaultT(defaultT) {
        int N_tmp = 1;
        while (N_tmp < N) N_tmp <<= 1;
        x.assign(N_tmp * 2, defaultT), head = N_tmp - 1;
        build(vals);
    }
    RangeMinimumQuery() : RangeMinimumQuery(0, T()) {}
    void update(int pos, T val) {
        pos += head, x[pos] = val;
        while (pos) pos = (pos - 1) / 2, x[pos] = min(x[pos * 2 + 1], x[pos * 2 + 2]);
    }
    T get(int begin, int end) const { return _get(begin, end, 0, 0, (int)x.size() / 2); }
    friend ostream &operator<<(ostream &os, const RangeMinimumQuery &s) {
        os << "[";
        for (int i = 0; i < s.N; i++) os << s.get(i, i + 1) << ",";
        return os << "]";
    }
};
