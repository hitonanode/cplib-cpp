#pragma once
#include <algorithm>
#include <utility>
#include <vector>

// Sort segments and erase not maximal ones
// {{0, 2}, {1, 5}, {3, 4}} => {{0, 2}, {1, 5}}
// {{1, 3}, {0, 1}, {1, 3}} => {{0, 1}, {1, 3}}  // remove duplicates
// Verified: abc254g https://atcoder.jp/contests/abc254/tasks/abc254_g
template <class T> std::vector<std::pair<T, T>> sort_maximal(std::vector<std::pair<T, T>> ranges) {
    std::sort(ranges.begin(), ranges.end());
    std::vector<std::pair<T, T>> ret;
    for (const auto &p : ranges) {
        if (!ret.empty() and ret.back().first == p.first) ret.pop_back();
        if (ret.empty() or ret.back().second < p.second) ret.push_back(p);
    }
    return ret;
}
