#pragma once
#include <string>
#include <vector>

// CUT begin
// Manacher's Algorithm: radius of palindromes
// Input: std::string of length N
// Output: std::vector<int> of size N
// Complexity: O(N)
// Sample:
// - `sakanakanandaka` -> [1, 1, 2, 1, 4, 1, 4, 1, 2, 2, 1, 1, 1, 2, 1]
// Reference: <https://snuke.hatenablog.com/entry/2014/12/02/235837>
std::vector<int> manacher(std::string S)
{
    std::vector<int> res(S.length());
    int i = 0, j = 0;
    while (i < (int)S.size()) {
        while (i - j >= 0 and i + j < (int)S.size() and S[i - j] == S[i + j]) j++;
        res[i] = j;
        int k = 1;
        while (i - k >= 0 and i + k < (int)S.size() and k + res[i - k] < j) res[i + k] = res[i - k], k++;
        i += k, j -= k;
    }
    return res;
}
