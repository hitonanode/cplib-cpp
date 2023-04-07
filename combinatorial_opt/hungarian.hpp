#pragma once
#include <algorithm>
#include <cassert>
#include <optional>
#include <vector>

// Solve assignment problem by Hungarian algorithm
// dual problem: maximize sum(f) - sum(g) s.t. f_i - g_j <= C_ij
// Ccomplexity: O(nm min(n, m))
// https://www.slideshare.net/joisino/ss-249394573
template <class T> std::pair<T, std::vector<int>> hungarian(const std::vector<std::vector<T>> &C) {
    if (C.empty()) return {T(), {}};

    const int n = C.size(), m = C.front().size();

    if (n < m) {
        std::vector transC(m, std::vector<T>(n));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) transC.at(j).at(i) = C.at(i).at(j);
        }
        auto j2i = hungarian(transC);
        std::vector<int> ret(n, -1);
        for (int j = 0; j < m; ++j) {
            if (j2i.second.at(j) >= 0) ret.at(j2i.second.at(j)) = j;
        }
        return {j2i.first, ret};
    }

    std::vector<T> f(n, T()), g(m, T());

    // Make dual variables feasible
    for (int j = 0; j < m; ++j) {
        g[j] = f[0] - C[0][j];
        for (int i = 0; i < n; ++i) g[j] = std::max(g[j], f[i] - C[i][j]);
    }

    std::vector<int> lmate(n, -1);
    std::vector<std::optional<int>> rmate(m, std::nullopt);

    std::vector<int> rreach(m, -1);
    std::vector<int> rprv(m, -1);

    std::vector<int> lvisited;

    for (int i = 0; i < n; ++i) {
        lvisited = {i};
        int cur = 0;
        int reachable_r = -1;

        while (reachable_r < 0) {

            auto check_l = [&]() -> void {
                int l = lvisited[cur++];
                for (int j = 0; j < m; ++j) {
                    if (rreach[j] == i) continue;
                    if (f[l] - g[j] == C[l][j]) {
                        rreach[j] = i;
                        rprv[j] = l;
                        if (rmate[j].has_value()) {
                            lvisited.push_back(rmate[j].value());
                        } else {
                            reachable_r = j;
                            cur = lvisited.size();
                            return;
                        }
                    }
                }
            };
            while (cur < int(lvisited.size())) check_l();

            if (reachable_r < 0) {
                T min_diff = T();
                int min_l = -1, min_r = -1;
                for (int l : lvisited) {
                    for (int j = 0; j < m; ++j) {
                        if (rreach[j] == i) continue;
                        if (T diff = C[l][j] + g[j] - f[l]; min_l < 0 or min_diff > diff) {
                            min_diff = diff;
                            min_l = l;
                            min_r = j;
                        }
                    }
                }

                if (min_r < 0) {
                    assert(i >= m);
                    int l = lvisited.front();
                    for (int t : lvisited) {
                        if (f.at(l) < f.at(t)) l = t;
                    }
                    if (lmate.at(l) >= 0) {
                        reachable_r = lmate.at(l);
                        rmate.at(lmate.at(l)) = std::nullopt;
                        lmate.at(l) = -1;
                    }
                    break;
                }

                for (int l : lvisited) f[l] += min_diff;
                for (int j = 0; j < m; ++j) {
                    if (rreach[j] == i) g[j] += min_diff;
                }
                rreach.at(min_r) = i;
                rprv.at(min_r) = min_l;

                if (rmate.at(min_r).has_value()) {
                    lvisited.push_back(rmate.at(min_r).value());
                } else {
                    reachable_r = min_r;
                }
            }
        }

        for (int h = reachable_r; h >= 0;) {
            int l = rprv.at(h), nxth = lmate.at(l);
            rmate.at(h) = l;
            lmate.at(l) = h;
            h = nxth;
        }
    }

    T sol = T();
    for (int i = 0; i < n; ++i) {
        if (lmate.at(i) >= 0) sol += C.at(i).at(lmate.at(i));
    }
    return {sol, lmate};
}
