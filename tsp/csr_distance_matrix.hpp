#pragma once

#include <algorithm>
#include <utility>
#include <vector>

template <class T> class csr_distance_matrix {

    int _rows = 0;
    std::vector<int> begins;
    std::vector<std::pair<int, T>> vals;

public:
    csr_distance_matrix() : csr_distance_matrix({}, 0) {}

    csr_distance_matrix(const std::vector<std::tuple<int, int, T>> &init, int rows)
        : _rows(rows), begins(rows + 1) {
        std::vector<int> degs(rows);
        for (const auto &p : init) ++degs.at(std::get<0>(p));

        for (int i = 0; i < rows; ++i) begins.at(i + 1) = begins.at(i) + degs.at(i);

        vals.resize(init.size(), std::make_pair(-1, T()));
        for (auto [i, j, w] : init) vals.at(begins.at(i + 1) - (degs.at(i)--)) = {j, w};
    }

    void apply_pi(const std::vector<T> &pi) {
        for (int i = 0; i < n(); ++i) {
            for (auto &[j, d] : adjacents(i)) d += pi.at(i) + pi.at(j);
        }
    }

    int n() const noexcept { return _rows; }

    struct adjacents_sequence {
        csr_distance_matrix *ptr;
        int from;

        using iterator = typename std::vector<std::pair<int, T>>::iterator;
        iterator begin() { return std::next(ptr->vals.begin(), ptr->begins.at(from)); }
        iterator end() { return std::next(ptr->vals.begin(), ptr->begins.at(from + 1)); }
    };

    struct const_adjacents_sequence {
        const csr_distance_matrix *ptr;
        const int from;

        using const_iterator = typename std::vector<std::pair<int, T>>::const_iterator;
        const_iterator begin() const {
            return std::next(ptr->vals.cbegin(), ptr->begins.at(from));
        }
        const_iterator end() const {
            return std::next(ptr->vals.cbegin(), ptr->begins.at(from + 1));
        }
    };

    adjacents_sequence adjacents(int from) { return {this, from}; }

    const_adjacents_sequence adjacents(int from) const { return {this, from}; }
    const_adjacents_sequence operator()(int from) const { return {this, from}; }
};

template <class DistanceMatrix> auto build_adjacent_info(const DistanceMatrix &dist, int sz) {
    using T = decltype((*dist.adjacents(0).begin()).second);

    const std::vector<std::vector<T>> alpha = calc_lkh_alpha(dist);

    std::vector<std::tuple<int, int, T>> adjacent_edges;

    std::vector<std::tuple<T, T, int>> candidates;
    for (int i = 0; i < dist.n(); ++i) {
        candidates.clear();
        for (auto [j, d] : dist.adjacents(i)) {
            if (i != j) candidates.emplace_back(alpha.at(i).at(j), d, j);
        }

        const int final_sz = std::min<int>(sz, candidates.size());
        std::nth_element(candidates.begin(), candidates.begin() + final_sz, candidates.end());

        candidates.resize(final_sz);
        std::sort(candidates.begin(), candidates.end(),
                  [&](const auto &l, const auto &r) { return std::get<1>(l) < std::get<1>(r); });
        for (auto [alpha, dij, j] : candidates) adjacent_edges.emplace_back(i, j, dij);
    }
    return csr_distance_matrix(adjacent_edges, dist.n());
}
