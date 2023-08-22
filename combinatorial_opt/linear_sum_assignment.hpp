#pragma once
#include <cassert>
#include <tuple>
#include <vector>

namespace linear_sum_assignment {

template <class T>
T augment(int nr, int nc, const std::vector<std::vector<T>> &C, std::vector<T> &f,
          std::vector<T> &g, int s, std::vector<int> &mate, std::vector<int> &mate_inv) {

    assert(0 <= s and s < nr);
    assert(mate.at(s) < 0);

    static std::vector<T> dist;
    static std::vector<int> prv;
    dist.resize(nc);
    prv.resize(nc);

    f.at(s) = C.at(s).at(0) - g.at(0);
    for (int j = 1; j < nc; ++j) f.at(s) = std::min(f.at(s), C.at(s).at(j) - g.at(j));

    for (int j = 0; j < nc; ++j) {
        dist.at(j) = C.at(s).at(j) - f.at(s) - g.at(j);
        prv.at(j) = s;
    }

    std::vector<bool> done(nc);

    int t = -1;
    std::vector<int> stk;

    while (t == -1) {
        int j1 = -1;
        for (int j = 0; j < nc; ++j) {
            if (done.at(j)) continue;
            if (j1 == -1 or dist.at(j) < dist.at(j1) or
                (dist.at(j) == dist.at(j1) and mate_inv.at(j) < 0)) {
                j1 = j;
            }
        }

        if (j1 == -1) return false;

        if (mate_inv.at(j1) < 0) {
            t = j1;
            break;
        }

        done.at(j1) = 1;
        stk = {j1};

        while (!stk.empty()) {
            const int i = mate_inv.at(stk.back());
            if (i < 0) {
                t = stk.back();
                break;
            }
            stk.pop_back();

            for (int j = 0; j < nc; ++j) {
                if (done.at(j)) continue;

                const T len = C.at(i).at(j) - f.at(i) - g.at(j);

                if (dist.at(j) > dist.at(j1) + len) {
                    dist.at(j) = dist.at(j1) + len;
                    prv.at(j) = i;
                }

                if (len == T()) {
                    stk.push_back(j);
                    done.at(j) = 1;
                }
            }
        }
    }

    const T len = dist.at(t);

    f.at(s) += len;

    T ret = len;

    for (int j = 0; j < nc; ++j) {
        if (!done.at(j)) continue;

        g.at(j) -= len - dist.at(j);
        if (mate_inv.at(j) >= 0) {
            f.at(mate_inv.at(j)) += len - dist.at(j);
        } else {
            ret -= len - dist.at(j);
        }
    }

    for (int cur = t; cur >= 0;) {
        const int i = prv.at(cur);
        mate_inv.at(cur) = i;
        if (i == -1) break;
        std::swap(cur, mate.at(i));
    }

    return ret;
}

// Complexity: O(nr^2 nc)
template <class T>
std::tuple<T, std::vector<int>, std::vector<T>, std::vector<T>>
_solve(int nr, int nc, const std::vector<std::vector<T>> &C) {

    assert(nr <= nc);

    std::vector<int> mate(nr, -1);
    std::vector<int> mate_inv(nc, -1);
    std::vector<T> f(nr), g(nc); // dual variables, f[i] + g[j] <= C[i][j] holds

    if (nr == 0 or nc == 0) return {T(), mate, f, g};

    if (nr == nc) {
        // Column reduction
        for (int j = nc - 1; j >= 0; --j) {
            g.at(j) = C.at(0).at(j) - f.at(0);
            int imin = 0;
            for (int i = 1; i < nr; ++i) {
                if (g.at(j) > C.at(i).at(j) - f.at(i)) {
                    imin = i;
                    g.at(j) = C.at(i).at(j) - f.at(i);
                }
            }

            if (mate.at(imin) < 0) {
                mate.at(imin) = j;
                mate_inv.at(j) = imin;
            } else if (g.at(j) < g.at(mate.at(imin))) {
                mate_inv.at(mate.at(imin)) = -1;
                mate.at(imin) = j;
                mate_inv.at(j) = imin;
            }
        }

        // Reduction transfer (can be omitted)
        if (nc > 1) {
            for (int i = 0; i < nr; ++i) {
                if (mate.at(i) < 0) continue;
                T best = C.at(i).at(0) - g.at(0), second_best = C.at(i).at(1) - g.at(1);
                int argbest = 0;
                if (best > second_best) std::swap(best, second_best), argbest = 1;

                for (int j = 2; j < nc; ++j) {
                    if (T val = C.at(i).at(j) - g.at(j); val < best) {
                        second_best = best;
                        best = val;
                        argbest = j;
                    } else if (val < second_best) {
                        second_best = val;
                    }
                }

                g.at(argbest) -= second_best - best;
                f.at(i) = second_best;
            }
        }

        // Augmenting row reduction: not implemented
    }

    // Augmentation
    for (int i = 0; i < nr; ++i) {
        if (mate.at(i) < 0) augment(nr, nc, C, f, g, i, mate, mate_inv);
    }

    T ret = 0;
    for (int i = 0; i < nr; ++i) ret += C.at(i).at(mate.at(i));

    return {ret, mate, std::move(f), std::move(g)};
}

// Jonker–Volgenant algorithm: find minimum weight assignment
// Dual problem (nr == nc): maximize sum(f) + sum(g) s.t. f_i + g_j <= C_ij
// Complexity: O(nr nc min(nr, nc))
template <class T>
std::tuple<T, std::vector<int>, std::vector<T>, std::vector<T>>
solve(int nr, int nc, const std::vector<std::vector<T>> &C) {

    const bool transpose = (nr > nc);

    if (!transpose) return _solve(nr, nc, C);

    std::vector trans(nc, std::vector<T>(nr));

    for (int i = 0; i < nr; ++i) {
        for (int j = 0; j < nc; ++j) trans.at(j).at(i) = C.at(i).at(j);
    }

    auto [v, mate, f, g] = _solve(nc, nr, trans);

    std::vector<int> mate2(nr, -1);
    for (int j = 0; j < nc; ++j) {
        if (mate.at(j) >= 0) mate2.at(mate.at(j)) = j;
    }

    return {v, mate2, g, f};
}

} // namespace linear_sum_assignment
