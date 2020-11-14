#pragma once
#include <numeric>
#include <vector>

// CUT begin
// Euler's totient function
// Complexity: O(NlgN)
std::vector<int> euler_phi(int N)
{
    std::vector<int> ret(N + 1);
    std::iota(ret.begin(), ret.end(), 0);
    for (int p = 2; p <= N; p++) {
        if (ret[p] == p) {
            ret[p] = p - 1;
            for (int i = p * 2; i <= N; i += p) {
                ret[i] = ret[i] / p * (p - 1);
            }
        }
    }
    return ret;
}
