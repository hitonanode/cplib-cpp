#pragma once
#include <string>
#include <utility>
#include <vector>

// CUT begin
// Manacher's Algorithm: radius of palindromes
// Input: std::string or std::vector<T> of length N
// Output: std::vector<int> of size N
// Complexity: O(N)
// Sample:
// - `sakanakanandaka` -> [1, 1, 2, 1, 4, 1, 4, 1, 2, 2, 1, 1, 1, 2, 1]
// Reference: https://snuke.hatenablog.com/entry/2014/12/02/235837
template <typename T> std::vector<int> manacher(const std::vector<T> &S) {
    std::vector<int> res(S.size());
    int i = 0, j = 0;
    while (i < int(S.size())) {
        while (i - j >= 0 and i + j < int(S.size()) and S[i - j] == S[i + j]) j++;
        res[i] = j;
        int k = 1;
        while (i - k >= 0 and i + k < int(S.size()) and k + res[i - k] < j)
            res[i + k] = res[i - k], k++;
        i += k, j -= k;
    }
    return res;
}
std::vector<int> manacher(const std::string &S) {
    std::vector<char> v(S.size());
    for (int i = 0; i < int(S.size()); i++) v[i] = S[i];
    return manacher(v);
}

template <typename T>
std::vector<std::pair<int, int>> enumerate_palindromes(const std::vector<T> &vec) {
    std::vector<T> v;
    const int N = vec.size();
    for (int i = 0; i < N - 1; i++) {
        v.push_back(vec[i]);
        v.push_back(-1);
    }
    v.push_back(vec.back());
    const auto man = manacher(v);
    std::vector<std::pair<int, int>> ret;
    for (int i = 0; i < N * 2 - 1; i++) {
        if (i & 1) {
            int w = man[i] / 2;
            ret.emplace_back((i + 1) / 2 - w, (i + 1) / 2 + w);
        } else {
            int w = (man[i] - 1) / 2;
            ret.emplace_back(i / 2 - w, i / 2 + w + 1);
        }
    }
    return ret;
}

std::vector<std::pair<int, int>> enumerate_palindromes(const std::string &S) {
    std::vector<char> v(S.size());
    for (int i = 0; i < int(S.size()); i++) v[i] = S[i];
    return enumerate_palindromes<char>(v);
}
