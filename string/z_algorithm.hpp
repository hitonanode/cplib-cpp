#pragma once
#include <string>
#include <vector>

// CUT begin
// Z algorithm (length of longest common prefix for s[0:N] & s[i:N] for each i)
// Complexity: O(N)
// <http://snuke.hatenablog.com/entry/2014/12/03/214243>
template <typename T>
std::vector<int> z_algorithm(const std::vector<T> &s) {
    const int N = s.size();
    if (N == 0) return {};
    std::vector<int> ans(N);
    ans[0] = N;
    int i = 1, j = 0;
    while (i < N) {
        while (i + j < N and s[j] == s[i + j]) ++j;
        ans[i] = j;
        if (!j) {
            ++i;
            continue;
        }
        int k = 1;
        while (i + k < N and k + ans[k] < j) ans[i + k] = ans[k], ++k;
        i += k;
        j -= k;
    }
    return ans;
}

std::vector<int> z_algorithm(const std::string &s) {
    const int N = int(s.size());
    std::vector<int> v(N);
    for (int i = 0; i < N; i++) v[i] = s[i];
    return z_algorithm(v);
}
