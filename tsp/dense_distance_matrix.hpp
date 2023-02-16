#pragma once

#include <vector>

template <class T> class dense_distance_matrix {
    int _n;
    std::vector<T> _d;

public:
    dense_distance_matrix(const std::vector<std::vector<T>> &distance_vecvec)
        : _n(distance_vecvec.size()) {
        _d.reserve(n() * n());
        for (const auto &vec : distance_vecvec) _d.insert(end(_d), begin(vec), end(vec));
    }

    template <class U> void apply_pi(const std::vector<U> &pi) {
        for (int i = 0; i < n(); ++i) {
            for (int j = 0; j < n(); ++j) _d.at(i * n() + j) += pi.at(i) + pi.at(j);
        }
    }

    int n() const noexcept { return _n; }

    T dist(int s, int t) const { return _d.at(s * n() + t); }
    T operator()(int s, int t) const { return dist(s, t); }

    struct adjacents_sequence {
        const dense_distance_matrix *ptr;
        int from;
        struct iterator {
            const dense_distance_matrix *ptr;
            int from;
            int to;
            iterator operator++() { return {ptr, from, to++}; }
            std::pair<int, T> operator*() const { return {to, ptr->dist(from, to)}; }
            bool operator!=(const iterator &rhs) const {
                return to != rhs.to or ptr != rhs.ptr or from != rhs.from;
            }
        };
        iterator begin() const { return iterator{ptr, from, 0}; }
        iterator end() const { return iterator{ptr, from, ptr->n()}; }
    };

    adjacents_sequence adjacents(int from) const { return {this, from}; }
};
