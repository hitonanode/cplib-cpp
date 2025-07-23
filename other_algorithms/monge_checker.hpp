#pragma once

#include <sstream>
#include <string>

// Check whether cost(i, j) is Monge or not
// Complexity: O(nm)
// https://hackmd.io/@tatyam-prime/monge1
template <bool only_upper = false>
std::string check_matrix_monge(auto cost, auto inf, int n, int m) {
    if (m < 0) m = n;

    auto Detect = [n, m, inf](auto f) -> std::tuple<bool, int, int> {
        for (int i = 0; i + 1 < n; ++i) {
            for (int j = only_upper ? (i + 2) : 0; j + 1 < m; ++j) {
                const auto f00 = f(i, j), f01 = f(i, j + 1), f10 = f(i + 1, j),
                           f11 = f(i + 1, j + 1);
                if (f00 >= inf or f01 >= inf) continue;
                if (f00 + f11 > f10 + f01) { return {false, i, j}; }
            }
        }
        return {true, -1, -1};
    };

    if (auto [is_monge, i, j] = Detect(cost); is_monge) {
        return "Monge OK";
    } else if (auto [is_anti_monge, ai, aj] = Detect([&cost, inf](int i, int j) {
                   auto ret = cost(i, j);
                   return ret == inf ? inf : -ret;
               });
               is_anti_monge) {
        return "Not Monge, but Anti-Monge OK";
    } else {
        std::stringstream ret;
        ret << "Not Monge!\n";
        ret << "    j=" << std::to_string(j) << "   j=" << std::to_string(j + 1) << "\n";
        ret << "i=" << std::to_string(i) << " " << cost(i, j) << " " << cost(i, j + 1) << "\n";
        ret << "i=" << std::to_string(i + 1) << " " << cost(i + 1, j) << " " << cost(i + 1, j + 1);
        return ret.str();
    }
}

// Check whether graph weight is Monge or not
// Complexity: O(n^2)
std::string check_dag_monge(auto cost, auto inf, int n) {
    return check_matrix_monge<true>(cost, inf, n, n);
}
