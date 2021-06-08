#pragma once
#include <string>
#include <vector>

// CUT begin
// MP (Morris-Pratt) algorithm
// (length of longest nontrivial matching for prefix & suffix of s[0:i] for each i)
// Input: std::string of length N
// Output: std::vector<int> of size N
// Complexity: O(N)
// Sample:
// - `teletelepathy` -> [0, 0, 0, 0, 1, 2, 3, 4, 0, 0, 1, 0, 0]
// https://snuke.hatenablog.com/entry/2014/12/01/235807
template <typename T> std::vector<int> mp_algorithm(const std::vector<T> &s) {
    int N = s.size();
    std::vector<int> ret(N, -1);
    int j = -1;
    for (int i = 0; i < N; i++) {
        while (j >= 0 and s[i] != s[j]) j = j ? ret[j - 1] : -1;
        ret[i] = ++j;
    }
    return ret;
}

std::vector<int> mp_algorithm(const std::string &s) {
    const int N = int(s.size());
    std::vector<int> v(N);
    for (int i = 0; i < N; i++) v[i] = s[i];
    return mp_algorithm(v);
}
