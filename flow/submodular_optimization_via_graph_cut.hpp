#pragma once
#include <algorithm>
#include <array>
#include <cassert>
#include <map>
#include <tuple>
#include <utility>
#include <vector>

#include <atcoder/maxflow>

template <class VarName = int, class Cost = long long> class SubmodularOptimizationViaGraphCut {
    struct Bipartite {
        std::vector<std::vector<std::pair<int, bool>>> to;
        Bipartite(int nvar) : to(nvar) {}

        void Same(int idx1, int idx2) {
            to.at(idx1).emplace_back(idx2, false);
            to.at(idx2).emplace_back(idx1, false);
        }

        void Diff(int idx1, int idx2) {
            to.at(idx1).emplace_back(idx2, true);
            to.at(idx2).emplace_back(idx1, true);
        }

        std::pair<bool, std::vector<bool>> Coloring() const {
            const int nvar = to.size();
            std::vector<bool> is_flipped(nvar, false), visited(nvar, false);
            bool failed = false;

            auto rec = [&](auto &&self, int now) -> void {
                visited.at(now) = true;
                for (auto [nxt, w] : to.at(now)) {
                    const bool next_val = is_flipped.at(now) ^ w;
                    if (visited.at(nxt)) {
                        if (is_flipped.at(nxt) != next_val) {
                            failed = true;
                            return;
                        }
                    } else {
                        is_flipped.at(nxt) = next_val;
                        self(self, nxt);
                    }
                }
            };

            for (int i = 0; i < nvar; ++i) {
                if (visited.at(i)) continue;
                rec(rec, i);
                if (failed) return {false, {}};
            }

            return {true, is_flipped};
        }
    };

    struct Submodular {
        static bool Check(Cost f00, Cost f01, Cost f10, Cost f11) {
            return f00 + f11 <= f01 + f10;
        }

        static bool Check(const std::array<Cost, 4> &f) { return Check(f[0], f[1], f[2], f[3]); }

        static bool Check(const std::array<Cost, 8> &f) {
            return Check(f[0], f[1], f[2], f[3]) and Check(f[4], f[5], f[6], f[7]) and
                   Check(f[0], f[1], f[4], f[5]) and Check(f[2], f[3], f[6], f[7]) and
                   Check(f[0], f[2], f[4], f[6]) and Check(f[1], f[3], f[5], f[7]);
        }
    };

    template <int Size>
    static std::array<Cost, Size> Transpose(const std::array<Cost, Size> &f, int flip_mask) {
        std::array<Cost, Size> ret;
        for (int i = 0; i < Size; ++i) ret.at(i ^ flip_mask) = f.at(i);
        return ret;
    }

    template <int Size> int GetSubmodularFlips(const std::array<Cost, Size> &f) const {
        int ret = 0;
        for (int flip_mask = 0; flip_mask < (int)f.size(); ++flip_mask) {
            if (Submodular::Check(Transpose<Size>(f, flip_mask))) ret |= 1 << flip_mask;
        }
        return ret;
    }

    std::map<VarName, int> to_internal_idx;
    std::vector<VarName> to_var_name;

    Cost f0 = Cost{};
    std::map<int, std::array<Cost, 2>> unary;
    std::map<std::tuple<int, int>, std::array<Cost, 4>> binary;
    std::map<std::tuple<int, int, int>, std::array<Cost, 8>> ternary;
    std::map<std::vector<std::pair<int, bool>>, Cost> satisfy_all;

    int RegisterOrGetIndex(const VarName &name) {
        if (!to_internal_idx.count(name)) {
            to_internal_idx[name] = to_internal_idx.size();
            to_var_name.push_back(name);
        }
        return to_internal_idx.at(name);
    }

public:
    SubmodularOptimizationViaGraphCut() {}

    // Impose constant `cost`
    void Impose(Cost cost) { f0 += cost; }

    // Impose `cost` when `x == tf`
    void Impose(const VarName &x, bool tf, Cost cost) {
        const int idx = RegisterOrGetIndex(x);
        unary[idx][(int)tf] += cost;
    }

    // Impose `cost` when `x1 == tf1 and x2 == tf2`
    void Impose(const VarName &x1, bool tf1, const VarName &x2, bool tf2, Cost cost) {
        int idx1 = RegisterOrGetIndex(x1);
        int idx2 = RegisterOrGetIndex(x2);
        assert(idx1 != idx2);
        if (idx1 > idx2) {
            std::swap(idx1, idx2);
            std::swap(tf1, tf2);
        }
        binary[std::make_tuple(idx1, idx2)][(tf1 << 1) | tf2] += cost;
    }

    // Impose `cost` when `x1 == tf1, x2 == tf2 and x3 == tf3`
    // !!Not verified enough!!
    void Impose(const VarName &x1, bool tf1, const VarName &x2, bool tf2, const VarName &x3,
                bool tf3, Cost cost) {
        int idx1 = RegisterOrGetIndex(x1);
        int idx2 = RegisterOrGetIndex(x2);
        int idx3 = RegisterOrGetIndex(x3);
        assert(idx1 != idx2 and idx1 != idx3 and idx2 != idx3);
        if (idx1 > idx2) std::swap(idx1, idx2), std::swap(tf1, tf2);
        if (idx1 > idx3) std::swap(idx1, idx3), std::swap(tf1, tf3);
        if (idx2 > idx3) std::swap(idx2, idx3), std::swap(tf2, tf3);
        ternary[std::make_tuple(idx1, idx2, idx3)][(tf1 << 2) | (tf2 << 1) | tf3] += cost;
    }

    // IntVar [0, k) is represented by (k - 1) variables:
    // TTTT...T => 0
    // FTTT...T => 1
    // FFTT...T => 2
    // ...
    // FFFF...F => vars.size() (= k - 1)
    struct IntVar {
        std::vector<VarName> vars;

        const VarName &at(int i) const {
            assert(0 <= i and i < (int)vars.size());
            return vars.at(i);
        }

        int size() const { return vars.size(); }
    };

    IntVar GenIntVar(const std::vector<VarName> &vars, Cost inf) {
        for (int i = 1; i < (int)vars.size(); ++i) {
            Then(vars.at(i), false, vars.at(i - 1), false, inf);
        }

        return IntVar{vars};
    }

    // https://noshi91.hatenablog.com/entry/2021/06/29/044225
    void Impose(const IntVar &iv, const std::vector<Cost> &costs) {
        assert(iv.size() + 1 == (int)costs.size());

        const int k = costs.size();
        Impose(costs.at(k - 1));
        for (int i = k - 2; i >= 0; --i) Impose(iv.at(i), true, costs.at(i) - costs.at(i + 1));
    }

    // If `iv1 >= min1 and iv2 <= max2` satisfy, impose `cost`
    void ImposeLbUb(const IntVar &iv1, int min1, const IntVar &iv2, int max2, Cost cost) {
        // iv >= t <=> iv[t - 1] == false or t <= 0
        // iv <= t <=> iv[t] == true or t >= iv.size()
        if ((int)iv1.size() < min1 or max2 < 0) return;
        if (min1 <= 0 and max2 >= (int)iv2.size()) {
            Impose(cost);
        } else if (min1 <= 0) {
            Impose(iv2.at(max2), true, cost);
        } else if (max2 >= (int)iv2.size()) {
            Impose(iv1.at(min1 - 1), false, cost);
        } else {
            Impose(iv1.at(min1 - 1), false, iv2.at(max2), true, cost);
        }
    }

    void Impose(const IntVar &vx, const IntVar &vy, std::vector<std::vector<Cost>> costs) {
        assert(vx.size() + 1 == (int)costs.size());
        assert(vy.size() + 1 == (int)costs.at(0).size());

        std::vector<Cost> tmp = costs.at(0);
        Impose(vy, tmp);
        for (auto &v : costs) {
            for (int j = 0; j < (int)v.size(); ++j) v.at(j) -= tmp.at(j);
        }

        tmp.clear();
        for (auto &v : costs) {
            const Cost r = v.back();
            tmp.emplace_back(r);
            for (auto &x : v) x -= r;
        }
        Impose(vx, tmp);

        // cost is now like:
        // 00...000
        // **...**0
        // ...
        // **...**0
        for (auto &v : costs) {
            for (int j = 1; j < (int)v.size(); ++j) v.at(j - 1) -= v.at(j);
        }

        for (int j = 0; j < (int)costs.at(0).size(); ++j) {
            for (int i = (int)costs.size() - 1; i; --i) {
                costs.at(i).at(j) -= costs.at(i - 1).at(j);
            }
        }

        for (int x = 1; x < (int)costs.size(); ++x) {
            for (int y = 0; y + 1 < (int)costs.at(0).size(); ++y) {
                ImposeLbUb(vx, x, vy, y, costs.at(x).at(y));
            }
        }
    }

    // Impose `penalty` when `(x1 == tf1) => (x2 == tf2)` is NOT satisfied
    void Then(const VarName &x1, bool tf1, const VarName &x2, bool tf2, Cost penalty) {
        Impose(x1, tf1, x2, !tf2, penalty);
    }

    // Impose `cost` when `x1 != x2`
    void ImposeIfDifferent(const VarName &x1, const VarName &x2, Cost cost) {
        Impose(x1, true, x2, false, cost);
        Impose(x1, false, x2, true, cost);
    }

    // Impose `cost` when `x1 == x2`
    void ImposeIfSame(const VarName &x1, const VarName &x2, Cost cost) {
        Impose(x1, true, x2, true, cost);
        Impose(x1, false, x2, false, cost);
    }

    // Impose `penalty` when NOT all of `x == tf` in `consts` are satisfied
    void ImposeIfNotAll(const std::vector<std::pair<VarName, bool>> &consts, Cost penalty) {
        if (consts.empty()) return;

        std::vector<std::pair<int, bool>> internal_vars;
        for (const auto &[x, tf] : consts) {
            const int idx = RegisterOrGetIndex(x);
            internal_vars.emplace_back(idx, tf);
        }
        std::sort(internal_vars.begin(), internal_vars.end());
        internal_vars.erase(
            std::unique(internal_vars.begin(), internal_vars.end()), internal_vars.end());
        satisfy_all[internal_vars] += penalty;
    }

    struct Result {
        bool solved = false;
        Cost total_cost = Cost{};
        std::map<VarName, bool> x;
    };

    Result Solve() const {
        const int nvar = to_internal_idx.size();

        Bipartite bp(nvar);

        for (const auto &[indices, f] : binary) {
            auto [idx1, idx2] = indices;
            const int mask = GetSubmodularFlips<4>(f);
            if (!mask) return Result{false};

            if (!(mask & ((1 << 0b00) | (1 << 0b11)))) bp.Diff(idx1, idx2);
            if (!(mask & ((1 << 0b01) | (1 << 0b10)))) bp.Same(idx1, idx2);
        }

        for (const auto &[indices, f] : ternary) {
            auto [idx1, idx2, idx3] = indices;
            const int m = GetSubmodularFlips<8>(f);
            if (!m) return Result{false};

            // I believe these constraints are necessary and sufficient (based on LP solver results)
            if (!(m & ((1 << 0b000) | (1 << 0b011) | (1 << 0b100) | (1 << 0b111))))
                bp.Diff(idx2, idx3);
            if (!(m & ((1 << 0b001) | (1 << 0b010) | (1 << 0b101) | (1 << 0b110))))
                bp.Same(idx2, idx3);

            if (!(m & ((1 << 0b000) | (1 << 0b101) | (1 << 0b010) | (1 << 0b111))))
                bp.Diff(idx1, idx3);
            if (!(m & ((1 << 0b001) | (1 << 0b100) | (1 << 0b011) | (1 << 0b110))))
                bp.Same(idx1, idx3);

            if (!(m & ((1 << 0b000) | (1 << 0b110) | (1 << 0b001) | (1 << 0b111))))
                bp.Diff(idx1, idx2);
            if (!(m & ((1 << 0b010) | (1 << 0b100) | (1 << 0b011) | (1 << 0b101))))
                bp.Same(idx1, idx2);
        }

        for (const auto &[var_flags, penalty] : satisfy_all) {
            if (penalty < Cost{}) return Result{false};
            for (auto [idx, tf] : var_flags) {
                auto [idx0, tf0] = var_flags.front();
                if (tf == tf0) {
                    bp.Same(idx, idx0);
                } else {
                    bp.Diff(idx, idx0);
                }
            }
        }

        Cost base = f0;
        std::vector<Cost> actual_unary(nvar);
        std::map<std::tuple<int, int>, Cost> actual_binary_ft;
        std::map<std::pair<std::vector<int>, bool>, Cost> actual_require_all;

        auto ResolveUnary = [&](int idx, const std::array<Cost, 2> &f) {
            const Cost f0 = f[0b0], f1 = f[0b1];
            base += f0;
            actual_unary[idx] += f1 - f0;
        };

        auto ResolveBinary = [&](int idx1, int idx2, const std::array<Cost, 4> &f) {
            const Cost A = f[0b00], B = f[0b01], C = f[0b10], D = f[0b11];
            base += A;
            ResolveUnary(idx1, {Cost{}, C - A});
            ResolveUnary(idx2, {Cost{}, D - C});
            const Cost w = (B + C) - (A + D);
            assert(w >= Cost{});
            if (w > Cost{}) actual_binary_ft[{idx1, idx2}] += w;
        };

        auto ResolveTernary = [&](int idx1, int idx2, int idx3, const std::array<Cost, 8> &f) {
            const Cost A = f[0b000], B = f[0b001], C = f[0b010], D = f[0b011], E = f[0b100],
                       F = f[0b101], G = f[0b110], H = f[0b111];
            const Cost P = (A + D + F + G) - (B + C + E + H);

            if (P >= Cost{}) {
                base += A;
                ResolveUnary(idx1, {Cost{}, F - B});
                ResolveUnary(idx2, {Cost{}, G - E});
                ResolveUnary(idx3, {Cost{}, D - C});
                ResolveBinary(idx2, idx3, {Cost{}, (B + C) - (A + D), Cost{}, Cost{}});
                ResolveBinary(idx1, idx3, {Cost{}, Cost{}, (B + E) - (A + F), Cost{}});
                ResolveBinary(idx1, idx2, {Cost{}, (C + E) - (A + G), Cost{}, Cost{}});

                base -= P;
                if (P) { actual_require_all[{std::vector<int>{idx1, idx2, idx3}, true}] += P; }
            } else {
                base += H;
                ResolveUnary(idx1, {C - G, Cost{}});
                ResolveUnary(idx2, {B - D, Cost{}});
                ResolveUnary(idx3, {E - F, Cost{}});
                ResolveBinary(idx2, idx3, {Cost{}, Cost{}, (F + G) - (E + H), Cost{}});
                ResolveBinary(idx1, idx3, {Cost{}, (D + G) - (C + H), Cost{}, Cost{}});
                ResolveBinary(idx1, idx2, {Cost{}, Cost{}, (D + F) - (B + H), Cost{}});

                base += P;
                if (P) { actual_require_all[{std::vector<int>{idx1, idx2, idx3}, false}] += -P; }
            }
        };

        const auto [is_bipartite, flipped] = bp.Coloring();
        if (!is_bipartite) return Result{false};

        for (auto [idx, f] : unary) {
            f = Transpose<2>(f, flipped.at(idx));
            ResolveUnary(idx, f);
        }

        for (auto [indices, f] : binary) {
            auto [idx1, idx2] = indices;
            f = Transpose<4>(f, (flipped.at(idx1) << 1) | flipped.at(idx2));
            ResolveBinary(idx1, idx2, f);
        }

        for (auto [indices, f] : ternary) {
            auto [idx1, idx2, idx3] = indices;
            f = Transpose<8>(
                f, (flipped.at(idx1) << 2) | (flipped.at(idx2) << 1) | flipped.at(idx3));
            ResolveTernary(idx1, idx2, idx3, f);
        }

        for (auto &[var_flags, penalty] : satisfy_all) {
            assert(var_flags.size());
            const auto [idx0, tf0] = var_flags.front();
            std::vector<int> vars;
            for (const auto &[idx, tf] : var_flags) {
                assert((tf ^ flipped.at(idx)) == (tf0 ^ flipped.at(idx0)));
                vars.push_back(idx);
            }
            actual_require_all[{vars, tf0 ^ flipped.at(idx0)}] += penalty;
        }

        const int v_false = nvar + actual_require_all.size();
        const int v_true = v_false + 1;
        atcoder::mf_graph<Cost> mf(v_true + 1);

        for (int idx = 0; idx < nvar; ++idx) {
            const Cost cost = actual_unary.at(idx);
            if (cost > Cost{}) mf.add_edge(v_false, idx, cost);
            if (cost < Cost{}) {
                base += cost;
                mf.add_edge(idx, v_true, -cost);
            }
        }

        for (auto [indices, f] : actual_binary_ft) {
            assert(f >= Cost{});
            auto [idx1, idx2] = indices;
            if (f > Cost{}) mf.add_edge(idx1, idx2, f);
        }

        int head = nvar;

        for (const auto &[var_flags, penalty] : actual_require_all) {
            auto [vars, flg] = var_flags;
            assert(penalty >= Cost{});
            if (flg) {
                for (int i : vars) mf.add_edge(i, head, penalty);
                mf.add_edge(head++, v_true, penalty);
            } else {
                for (int i : vars) mf.add_edge(head, i, penalty);
                mf.add_edge(v_false, head++, penalty);
            }
        }

        assert(head == v_false);

        const Cost flow = mf.flow(v_false, v_true);
        const Cost total_cost = base + flow;

        auto min_cut = mf.min_cut(v_false);
        std::map<VarName, bool> sol;
        for (int i = 0; i < nvar; ++i) {
            const bool xi = !min_cut.at(i) ^ flipped.at(i);
            sol[to_var_name.at(i)] = xi;
        }

        return {true, total_cost, sol};
    }
};
