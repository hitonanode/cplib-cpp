#include <algorithm>
#include <vector>

// Hook length formula
// Complexity: O(sum(hook))
// Verify: https://yukicoder.me/problems/no/2149
template <class T> T hook_length_formula(std::vector<int> hook) {
    if (hook.empty()) return T(1);
    std::sort(hook.begin(), hook.end());
    std::vector<int> len(hook.back());
    T num(1), den(1);
    int sum = 0;
    for (int l : hook) {
        for (int j = 0; j < l; ++j) num *= ++sum, den *= (++len.at(j)) + l - 1 - j;
    }
    return num / den;
}
