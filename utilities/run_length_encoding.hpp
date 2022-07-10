#pragma once
#include <string>
#include <utility>
#include <vector>

// Run length encoding
template <class T> std::vector<std::pair<T, int>> run_length_encoding(const std::vector<T> &v) {
    std::vector<std::pair<T, int>> ret;
    for (const T &x : v) {
        if (ret.empty() or ret.back().first != x) ret.emplace_back(x, 0);
        ++ret.back().second;
    }
    return ret;
}

// aabaacddd -> [(a, 2), (b, 1), (a, 2), (c, 1), (d, 3)]
// Each character in s must be char
std::vector<std::pair<char, int>> run_length_encoding(const std::string &s) {
    std::vector<char> tmp(s.begin(), s.end());
    return run_length_encoding<char>(tmp);
}
