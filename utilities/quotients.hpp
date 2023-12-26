#pragma once
#include <algorithm>
#include <vector>

// Generate all quotients of n
// return: n/1, n/2, ..., n
// Complexity: O(sqrt(n))
template <class T = long long> std::vector<T> get_quotients(T n) {
    std::vector<T> res;
    for (T x = 1;; ++x) {
        if (x * x >= n) {
            const int sz = res.size();
            if (x * x == n) res.push_back(x);
            res.reserve(res.size() + sz);
            for (int i = sz - 1; i >= 0; --i) {
                T tmp = n / res.at(i);
                if (tmp < x) continue;
                if (tmp == x and tmp * tmp == n) continue;
                res.push_back(tmp);
            }
            return res;
        } else {
            res.push_back(x);
        }
    }
}
