#pragma once
#include <algorithm>
#include <memory>
#include <vector>

enum class LisType {
    StrictlyIncreasing,
    Nondecreasing,
};

// Calculate (only) length of longest increasing subsequence (LIS)
// Complexity: O(n log n)
template <class T>
int lis_length(const std::vector<T> &seq, LisType lis_type = LisType::StrictlyIncreasing) {
    std::vector<T> dp;
    for (const T &x : seq) {
        if (auto itr = (lis_type == LisType::StrictlyIncreasing
                            ? std::lower_bound(begin(dp), end(dp), x)
                            : std::upper_bound(begin(dp), end(dp), x));
            itr == end(dp)) {
            dp.push_back(x);
        } else {
            *itr = x;
        }
    }
    return dp.size();
}

template <class T> struct longest_increasing_subsequence {

    LisType lis_type_ = LisType::StrictlyIncreasing;
    int current_idx = 0;

    struct Node {
        std::shared_ptr<Node> par;
        int len, idx;
        T v;
    };

    std::vector<T> dp;
    std::vector<std::shared_ptr<Node>> ptrs;

    // Complexity: O(1)
    longest_increasing_subsequence(LisType lis_type) : lis_type_(lis_type) {}

    // Complexity: O(N log N)
    longest_increasing_subsequence(const std::vector<T> &seq, LisType lis_type)
        : lis_type_(lis_type) {
        for (const T &x : seq) add(x);
    }

    // Complexity: O(log N)
    std::shared_ptr<Node> add(const T &x) {
        auto itr =
            (lis_type_ == LisType::StrictlyIncreasing ? std::lower_bound(begin(dp), end(dp), x)
                                                      : std::upper_bound(begin(dp), end(dp), x));
        int cur = std::distance(begin(dp), itr);
        std::shared_ptr<Node> prv = (begin(dp) == itr ? nullptr : ptrs.at(cur - 1));

        std::shared_ptr<Node> node(
            new Node{prv, (prv == nullptr ? 0 : prv->len) + 1, current_idx++, x});

        if (itr == end(dp)) {
            dp.push_back(x), ptrs.push_back(node);
        } else {
            dp.at(cur) = x, ptrs.at(cur) = node;
        }
        return node;
    }

    std::shared_ptr<Node> head() const { return ptrs.empty() ? nullptr : ptrs.back(); }

    // LIS をなす添字列を出力
    // Complexity: O(N)
    std::vector<int> get_lis_indices() const {
        std::vector<int> ret;
        for (auto ptr = head(); ptr != nullptr; ptr = ptr->par) ret.push_back(ptr->idx);
        std::reverse(ret.begin(), ret.end());
        return ret;
    }
};
