#pragma once
#include <cassert>
#include <queue>
#include <tuple>
#include <vector>

namespace linear_sum_assignment {

template <class T> struct Result {
    T opt;
    std::vector<int> mate;
    std::vector<T> f, g; // dual variables
};

template <class T>
T augment(int nr, int nc, const std::vector<std::vector<T>> &C, std::vector<T> &f, std::vector<T> &g,
          int s, // source row
          std::vector<int> &mate,
          std::vector<int> &mate_inv, // duplicates are allowed (used for k-best algorithms)
          int fixed_rows = 0 // Ignore first rows and corresponding columns (used for k-best algorithms)
) {

    assert(0 <= s and s < nr);
    assert(mate.at(s) < 0);

    static std::vector<T> dist;
    static std::vector<int> prv;
    dist.resize(nc);
    prv.resize(nc);

    std::vector<bool> done(nc);

    for (int i = 0; i < fixed_rows; ++i) {
        if (int j = mate.at(i); j >= 0) done.at(j) = 1;
    }

    {
        int h = 0;
        while (done.at(h)) ++h;

        f.at(s) = C.at(s).at(h) - g.at(h);
        for (int j = h + 1; j < nc; ++j) {
            if (done.at(j)) continue;
            f.at(s) = std::min(f.at(s), C.at(s).at(j) - g.at(j));
        }
    }

    for (int j = 0; j < nc; ++j) {
        if (!done.at(j)) {
            dist.at(j) = C.at(s).at(j) - f.at(s) - g.at(j);
            prv.at(j) = -1;
        }
    }

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

        if (mate_inv.at(j1) < 0) {
            t = j1;
            break;
        }

        done.at(j1) = 1;
        stk = {j1};

        while (!stk.empty()) {
            const int j2 = stk.back();
            const int i = mate_inv.at(j2);
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
                    prv.at(j) = j2;
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

    for (int i = 0; i < fixed_rows; ++i) {
        if (const int j = mate.at(i); j >= 0) done.at(j) = 0;
    }

    for (int j = 0; j < nc; ++j) {
        if (!done.at(j)) continue;

        g.at(j) -= len - dist.at(j);
    }

    for (int i = fixed_rows; i < nr; ++i) {
        const int j = mate.at(i);
        if (j < 0 or !done.at(j) or j >= nc) continue;
        f.at(i) += len - dist.at(j);
    }

    T ret = T();

    for (int cur = t; cur >= 0;) {
        const int nxt = prv.at(cur);
        if (nxt < 0) {
            mate_inv.at(cur) = s;
            mate.at(s) = cur;
            ret += C.at(s).at(cur);
            break;
        }
        const int i = mate_inv.at(nxt);

        ret += C.at(i).at(cur) - C.at(i).at(nxt);

        mate_inv.at(cur) = i;
        mate.at(i) = cur;
        cur = nxt;
    }

    return ret;
}

// Complexity: O(nr^2 nc)
template <class T> Result<T> _solve(int nr, int nc, const std::vector<std::vector<T>> &C) {

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
template <class T> Result<T> solve(int nr, int nc, const std::vector<std::vector<T>> &C) {

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

template <class T> struct best_assignments {

    struct Node {
        T opt;
        std::vector<int> mate;
        std::vector<T> f, g; // dual variables
        int fixed_rows;
        std::vector<int> banned_js; // C[fixed_rows][j] が inf となる j の集合

        // for priority queue
        // NOTE: reverse order
        bool operator<(const Node &rhs) const { return opt > rhs.opt; }

        linear_sum_assignment::Result<T> to_output(bool transpose) const {
            if (transpose) {
                std::vector<int> mate2(g.size(), -1);
                for (int i = 0; i < (int)mate.size(); ++i) mate2.at(mate.at(i)) = i;
                return {opt, mate2, g, f};
            } else {
                return {opt, mate, f, g};
            }
        }
    };

    bool transpose;
    int nr_, nc_;
    T inf;
    std::vector<std::vector<T>> C_, Ctmp_;
    std::priority_queue<Node> pq;

    best_assignments(int nr, int nc, const std::vector<std::vector<T>> &C, T inf)
        : transpose(nr > nc), inf(inf) {

        assert((int)C.size() == nr);
        for (int i = 0; i < nr; ++i) assert((int)C.at(i).size() == nc);

        nr_ = transpose ? nc : nr;
        nc_ = transpose ? nr : nc;

        C_.assign(nr_ + (nr_ != nc_), std::vector<T>(nc_, T()));
        for (int i = 0; i < nr; ++i) {
            for (int j = 0; j < nc; ++j) {
                C_.at(transpose ? j : i).at(transpose ? i : j) = C.at(i).at(j);
            }
        }

        Ctmp_ = C_;

        auto [opt, mate, f, g] = linear_sum_assignment::solve(C_.size(), nc, C_);

        pq.emplace(Node{opt, std::move(mate), std::move(f), std::move(g), 0, {}});
    }

    bool finished() const { return pq.empty(); }

    linear_sum_assignment::Result<T> yield() {
        assert(!pq.empty());

        const Node ret = pq.top();
        pq.pop();

        for (int fixed_rows = ret.fixed_rows; fixed_rows < nr_; ++fixed_rows) {
            std::vector<int> banned_js;
            if (fixed_rows == ret.fixed_rows) banned_js = ret.banned_js;

            const int s = fixed_rows;
            banned_js.push_back(ret.mate.at(s));

            if ((int)banned_js.size() >= nc_) continue;

            auto f = ret.f;
            auto g = ret.g;
            auto mate = ret.mate;

            std::vector<int> mate_inv(nc_, nr_);
            for (int i = 0; i < nr_; ++i) mate_inv.at(mate.at(i)) = i;

            std::vector<int> iscoldone(nc_);
            for (int i = 0; i < fixed_rows; ++i) iscoldone.at(mate.at(i)) = 1;

            for (int j : banned_js) Ctmp_.at(s).at(j) = inf;

            mate_inv.at(mate.at(s)) = -1;
            mate.at(s) = -1;

            auto aug = linear_sum_assignment::augment(
                nr_, nc_, Ctmp_, f, g, s, mate, mate_inv, fixed_rows);

            for (int j = 0; j < nc_; ++j) {
                if (mate_inv.at(j) < 0) { // nrows < ncols
                    g.at(j) = -f.back();
                    for (int i = fixed_rows; i < nr_; ++i) {
                        g.at(j) = std::min(g.at(j), Ctmp_.at(i).at(j) - f.at(i));
                    }
                }
            }

            if (Ctmp_.at(s).at(mate.at(s)) < inf) {
                pq.emplace(Node{
                    ret.opt + aug - C_.at(s).at(ret.mate.at(s)),
                    std::move(mate),
                    std::move(f),
                    std::move(g),
                    fixed_rows,
                    banned_js,
                });
            }

            for (int j : banned_js) Ctmp_.at(s).at(j) = C_.at(s).at(j);
        }

        return ret.to_output(transpose);
    }
};
