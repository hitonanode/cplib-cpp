#pragma once
#include <cassert>
#include <vector>

// CUT begin
// solve Mx = y based on Levinson recursion
//
// M = [
// [ t_(N-1) t_(N-2) ... t_1 t_0     ]
// [ t_N     t_(N-1) ... t_2 t_1     ]
// [ ...                             ]
// [ t_(N*2-2)       ...     t_(N-1) ]]
//
// Complexity: O(N^2)
// Reference: <https://en.wikipedia.org/wiki/Levinson_recursion>
// return: - x = N-dim vector (if all principal minors of M are nonsingular)
//         - empty vector     (otherwise)
template <typename T>
std::vector<T> levinson_recursion(const std::vector<T> &toeplitz, const std::vector<T> &y) {
    const int N = y.size();
    assert(int(toeplitz.size()) == N * 2 - 1);
    std::vector<T> x(N);
    std::vector<T> fn(1), en(1);
    if (toeplitz[N - 1] == 0) {
        return {};
    }
    fn[0] = en[0] = toeplitz[N - 1].inv();
    x[0] = fn[0] * y[0];
    for (int n = 1; n < N; n++) {
        T ef = 0, eb = 0;
        for (int i = 0; i < n; i++) {
            ef += fn[i] * toeplitz[N - 1 + n - i];
            eb += en[i] * toeplitz[N - 2 - i];
        }
        if (ef * eb == 1) {
            return {};
        }
        auto nxtfn = fn, nxten = en;
        nxtfn.emplace_back(0), nxten.insert(nxten.begin(), 0);
        for (int i = 0; i < n; i++) {
            nxtfn[i + 1] -= ef * en[i];
            nxten[i] -= eb * fn[i];
        }
        T c = (1 - ef * eb).inv();
        for (int i = 0; i < n + 1; i++) {
            nxtfn[i] *= c, nxten[i] *= c;
        }
        fn = nxtfn, en = nxten;

        T z = y[n];
        for (int i = 0; i < n; i++) {
            z -= x[i] * toeplitz[N - 1 + n - i];
        }
        for (int i = 0; i < n + 1; i++) {
            x[i] += en[i] * z;
        }
    }
    return x;
}
