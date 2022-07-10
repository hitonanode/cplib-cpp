#pragma once
#include <algorithm>
#include <utility>
#include <vector>

// Key class must be comparable
// Example: [(2, 3), (1, 5), (2, 2), (2, 3), (1, 4)] -> [(1, [5, 4]), (2, [3, 2, 3])]
// Verified: https://atcoder.jp/contests/abc259/tasks/abc259_h
template <class Key, class Value>
std::vector<std::pair<Key, std::vector<Value>>> groupby(std::vector<std::pair<Key, Value>> xs) {
    using KV = std::pair<Key, Value>;
    std::stable_sort(
        xs.begin(), xs.end(), [&](const KV &l, const KV &r) { return l.first < r.first; });

    std::vector<std::pair<Key, std::vector<Value>>> ret;
    for (const auto &x : xs) {
        if (ret.empty() or ret.back().first != x.first) {
            ret.emplace_back(x.first, std::vector<Value>());
        }
        ret.back().second.push_back(x.second);
    }
    return ret;
}
