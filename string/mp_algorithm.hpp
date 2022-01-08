#pragma once
#include <string>
#include <vector>

// CUT begin
// MP (Morris-Pratt) algorithm (length of longest nontrivial matching for
// prefix & suffix of s[0:i] for each i)
// Input: std::string of length N
// Output: std::vector<int> of size N + 1
// Complexity: O(N)
// Sample:
// - `teletelepathy` -> [-1, 0, 0, 0, 0, 1, 2, 3, 4, 0, 0, 1, 0, 0]
// Reference: <https://snuke.hatenablog.com/entry/2014/12/01/235807>
std::vector<int> mp_algorithm(std::string s) {
    int N = s.length();
    std::vector<int> ret(N + 1, -1);
    int j = -1;
    for (int i = 0; i < N; i++) {
        while (j >= 0 and s[i] != s[j]) j = ret[j];
        ret[i + 1] = ++j;
    }
    return ret;
}
