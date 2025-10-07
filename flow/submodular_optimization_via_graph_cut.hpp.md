---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: flow/test/submodular_opt.aoj2496.test.cpp
    title: flow/test/submodular_opt.aoj2496.test.cpp
  - icon: ':heavy_check_mark:'
    path: flow/test/submodular_opt.aoj2903.test.cpp
    title: flow/test/submodular_opt.aoj2903.test.cpp
  - icon: ':heavy_check_mark:'
    path: flow/test/submodular_opt.aoj2943.test.cpp
    title: flow/test/submodular_opt.aoj2943.test.cpp
  - icon: ':heavy_check_mark:'
    path: flow/test/submodular_opt.aoj3058.test.cpp
    title: flow/test/submodular_opt.aoj3058.test.cpp
  - icon: ':heavy_check_mark:'
    path: flow/test/submodular_opt.yuki119.test.cpp
    title: flow/test/submodular_opt.yuki119.test.cpp
  - icon: ':heavy_check_mark:'
    path: flow/test/submodular_opt.yuki1479.test.cpp
    title: flow/test/submodular_opt.yuki1479.test.cpp
  - icon: ':heavy_check_mark:'
    path: flow/test/submodular_opt.yuki1541.test.cpp
    title: flow/test/submodular_opt.yuki1541.test.cpp
  - icon: ':heavy_check_mark:'
    path: flow/test/submodular_opt.yuki1900.test.cpp
    title: flow/test/submodular_opt.yuki1900.test.cpp
  - icon: ':heavy_check_mark:'
    path: flow/test/submodular_opt.yuki1984.test.cpp
    title: flow/test/submodular_opt.yuki1984.test.cpp
  - icon: ':heavy_check_mark:'
    path: flow/test/submodular_opt.yuki2320.test.cpp
    title: flow/test/submodular_opt.yuki2320.test.cpp
  - icon: ':heavy_check_mark:'
    path: flow/test/submodular_opt.yuki2713.test.cpp
    title: flow/test/submodular_opt.yuki2713.test.cpp
  - icon: ':heavy_check_mark:'
    path: flow/test/submodular_opt.yuki3201.test.cpp
    title: flow/test/submodular_opt.yuki3201.test.cpp
  - icon: ':heavy_check_mark:'
    path: flow/test/submodular_opt.yuki957.test.cpp
    title: flow/test/submodular_opt.yuki957.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://noshi91.hatenablog.com/entry/2021/06/29/044225
  bundledCode: "#line 2 \"flow/submodular_optimization_via_graph_cut.hpp\"\n#include\
    \ <algorithm>\n#include <array>\n#include <cassert>\n#include <map>\n#include\
    \ <tuple>\n#include <utility>\n#include <vector>\n\n#include <atcoder/maxflow>\n\
    \ntemplate <class VarName = int, class Cost = long long> class SubmodularOptimizationViaGraphCut\
    \ {\n    struct Bipartite {\n        std::vector<std::vector<std::pair<int, bool>>>\
    \ to;\n        Bipartite(int nvar) : to(nvar) {}\n\n        void Same(int idx1,\
    \ int idx2) {\n            to.at(idx1).emplace_back(idx2, false);\n          \
    \  to.at(idx2).emplace_back(idx1, false);\n        }\n\n        void Diff(int\
    \ idx1, int idx2) {\n            to.at(idx1).emplace_back(idx2, true);\n     \
    \       to.at(idx2).emplace_back(idx1, true);\n        }\n\n        std::pair<bool,\
    \ std::vector<bool>> Coloring() const {\n            const int nvar = to.size();\n\
    \            std::vector<bool> is_flipped(nvar, false), visited(nvar, false);\n\
    \            bool failed = false;\n\n            auto rec = [&](auto &&self, int\
    \ now) -> void {\n                visited.at(now) = true;\n                for\
    \ (auto [nxt, w] : to.at(now)) {\n                    const bool next_val = is_flipped.at(now)\
    \ ^ w;\n                    if (visited.at(nxt)) {\n                        if\
    \ (is_flipped.at(nxt) != next_val) {\n                            failed = true;\n\
    \                            return;\n                        }\n            \
    \        } else {\n                        is_flipped.at(nxt) = next_val;\n  \
    \                      self(self, nxt);\n                    }\n             \
    \   }\n            };\n\n            for (int i = 0; i < nvar; ++i) {\n      \
    \          if (visited.at(i)) continue;\n                rec(rec, i);\n      \
    \          if (failed) return {false, {}};\n            }\n\n            return\
    \ {true, is_flipped};\n        }\n    };\n\n    struct Submodular {\n        static\
    \ bool Check(Cost f00, Cost f01, Cost f10, Cost f11) {\n            return f00\
    \ + f11 <= f01 + f10;\n        }\n\n        static bool Check(const std::array<Cost,\
    \ 4> &f) { return Check(f[0], f[1], f[2], f[3]); }\n\n        static bool Check(const\
    \ std::array<Cost, 8> &f) {\n            return Check(f[0], f[1], f[2], f[3])\
    \ and Check(f[4], f[5], f[6], f[7]) and\n                   Check(f[0], f[1],\
    \ f[4], f[5]) and Check(f[2], f[3], f[6], f[7]) and\n                   Check(f[0],\
    \ f[2], f[4], f[6]) and Check(f[1], f[3], f[5], f[7]);\n        }\n    };\n\n\
    \    template <int Size>\n    static std::array<Cost, Size> Transpose(const std::array<Cost,\
    \ Size> &f, int flip_mask) {\n        std::array<Cost, Size> ret;\n        for\
    \ (int i = 0; i < Size; ++i) ret.at(i ^ flip_mask) = f.at(i);\n        return\
    \ ret;\n    }\n\n    template <int Size> int GetSubmodularFlips(const std::array<Cost,\
    \ Size> &f) const {\n        int ret = 0;\n        for (int flip_mask = 0; flip_mask\
    \ < (int)f.size(); ++flip_mask) {\n            if (Submodular::Check(Transpose<Size>(f,\
    \ flip_mask))) ret |= 1 << flip_mask;\n        }\n        return ret;\n    }\n\
    \n    std::map<VarName, int> to_internal_idx;\n    std::vector<VarName> to_var_name;\n\
    \n    Cost f0 = Cost{};\n    std::map<int, std::array<Cost, 2>> unary;\n    std::map<std::tuple<int,\
    \ int>, std::array<Cost, 4>> binary;\n    std::map<std::tuple<int, int, int>,\
    \ std::array<Cost, 8>> ternary;\n    std::map<std::vector<std::pair<int, bool>>,\
    \ Cost> satisfy_all;\n\n    int RegisterOrGetIndex(const VarName &name) {\n  \
    \      if (!to_internal_idx.count(name)) {\n            to_internal_idx[name]\
    \ = to_internal_idx.size();\n            to_var_name.push_back(name);\n      \
    \  }\n        return to_internal_idx.at(name);\n    }\n\npublic:\n    SubmodularOptimizationViaGraphCut()\
    \ {}\n\n    // Impose constant `cost`\n    void Impose(Cost cost) { f0 += cost;\
    \ }\n\n    // Impose `cost` when `x == tf`\n    void Impose(const VarName &x,\
    \ bool tf, Cost cost) {\n        const int idx = RegisterOrGetIndex(x);\n    \
    \    unary[idx][(int)tf] += cost;\n    }\n\n    // Impose `cost` when `x1 == tf1\
    \ and x2 == tf2`\n    void Impose(const VarName &x1, bool tf1, const VarName &x2,\
    \ bool tf2, Cost cost) {\n        int idx1 = RegisterOrGetIndex(x1);\n       \
    \ int idx2 = RegisterOrGetIndex(x2);\n        assert(idx1 != idx2);\n        if\
    \ (idx1 > idx2) {\n            std::swap(idx1, idx2);\n            std::swap(tf1,\
    \ tf2);\n        }\n        binary[std::make_tuple(idx1, idx2)][(tf1 << 1) | tf2]\
    \ += cost;\n    }\n\n    // Impose `cost` when `x1 == tf1, x2 == tf2 and x3 ==\
    \ tf3`\n    // !!Not verified enough!!\n    void Impose(const VarName &x1, bool\
    \ tf1, const VarName &x2, bool tf2, const VarName &x3,\n                bool tf3,\
    \ Cost cost) {\n        int idx1 = RegisterOrGetIndex(x1);\n        int idx2 =\
    \ RegisterOrGetIndex(x2);\n        int idx3 = RegisterOrGetIndex(x3);\n      \
    \  assert(idx1 != idx2 and idx1 != idx3 and idx2 != idx3);\n        if (idx1 >\
    \ idx2) std::swap(idx1, idx2), std::swap(tf1, tf2);\n        if (idx1 > idx3)\
    \ std::swap(idx1, idx3), std::swap(tf1, tf3);\n        if (idx2 > idx3) std::swap(idx2,\
    \ idx3), std::swap(tf2, tf3);\n        ternary[std::make_tuple(idx1, idx2, idx3)][(tf1\
    \ << 2) | (tf2 << 1) | tf3] += cost;\n    }\n\n    // IntVar [0, k) is represented\
    \ by (k - 1) variables:\n    // TTTT...T => 0\n    // FTTT...T => 1\n    // FFTT...T\
    \ => 2\n    // ...\n    // FFFF...F => vars.size() (= k - 1)\n    struct IntVar\
    \ {\n        std::vector<VarName> vars;\n\n        const VarName &at(int i) const\
    \ {\n            assert(0 <= i and i < (int)vars.size());\n            return\
    \ vars.at(i);\n        }\n\n        int size() const { return vars.size(); }\n\
    \    };\n\n    IntVar GenIntVar(const std::vector<VarName> &vars, Cost inf) {\n\
    \        for (int i = 1; i < (int)vars.size(); ++i) {\n            Then(vars.at(i),\
    \ false, vars.at(i - 1), false, inf);\n        }\n\n        return IntVar{vars};\n\
    \    }\n\n    // https://noshi91.hatenablog.com/entry/2021/06/29/044225\n    void\
    \ Impose(const IntVar &iv, const std::vector<Cost> &costs) {\n        assert(iv.size()\
    \ + 1 == (int)costs.size());\n\n        const int k = costs.size();\n        Impose(costs.at(k\
    \ - 1));\n        for (int i = k - 2; i >= 0; --i) Impose(iv.at(i), true, costs.at(i)\
    \ - costs.at(i + 1));\n    }\n\n    // If `iv1 >= min1 and iv2 <= max2` satisfy,\
    \ impose `cost`\n    void ImposeLbUb(const IntVar &iv1, int min1, const IntVar\
    \ &iv2, int max2, Cost cost) {\n        // iv >= t <=> iv[t - 1] == false or t\
    \ <= 0\n        // iv <= t <=> iv[t] == true or t >= iv.size()\n        if ((int)iv1.size()\
    \ < min1 or max2 < 0) return;\n        if (min1 <= 0 and max2 >= (int)iv2.size())\
    \ {\n            Impose(cost);\n        } else if (min1 <= 0) {\n            Impose(iv2.at(max2),\
    \ true, cost);\n        } else if (max2 >= (int)iv2.size()) {\n            Impose(iv1.at(min1\
    \ - 1), false, cost);\n        } else {\n            Impose(iv1.at(min1 - 1),\
    \ false, iv2.at(max2), true, cost);\n        }\n    }\n\n    void Impose(const\
    \ IntVar &vx, const IntVar &vy, std::vector<std::vector<Cost>> costs) {\n    \
    \    assert(vx.size() + 1 == (int)costs.size());\n        assert(vy.size() + 1\
    \ == (int)costs.at(0).size());\n\n        std::vector<Cost> tmp = costs.at(0);\n\
    \        Impose(vy, tmp);\n        for (auto &v : costs) {\n            for (int\
    \ j = 0; j < (int)v.size(); ++j) v.at(j) -= tmp.at(j);\n        }\n\n        tmp.clear();\n\
    \        for (auto &v : costs) {\n            const Cost r = v.back();\n     \
    \       tmp.emplace_back(r);\n            for (auto &x : v) x -= r;\n        }\n\
    \        Impose(vx, tmp);\n\n        // cost is now like:\n        // 00...000\n\
    \        // **...**0\n        // ...\n        // **...**0\n        for (auto &v\
    \ : costs) {\n            for (int j = 1; j < (int)v.size(); ++j) v.at(j - 1)\
    \ -= v.at(j);\n        }\n\n        for (int j = 0; j < (int)costs.at(0).size();\
    \ ++j) {\n            for (int i = (int)costs.size() - 1; i; --i) {\n        \
    \        costs.at(i).at(j) -= costs.at(i - 1).at(j);\n            }\n        }\n\
    \n        for (int x = 1; x < (int)costs.size(); ++x) {\n            for (int\
    \ y = 0; y + 1 < (int)costs.at(0).size(); ++y) {\n                ImposeLbUb(vx,\
    \ x, vy, y, costs.at(x).at(y));\n            }\n        }\n    }\n\n    // Impose\
    \ `penalty` when `(x1 == tf1) => (x2 == tf2)` is NOT satisfied\n    void Then(const\
    \ VarName &x1, bool tf1, const VarName &x2, bool tf2, Cost penalty) {\n      \
    \  Impose(x1, tf1, x2, !tf2, penalty);\n    }\n\n    // Impose `cost` when `x1\
    \ != x2`\n    void ImposeIfDifferent(const VarName &x1, const VarName &x2, Cost\
    \ cost) {\n        Impose(x1, true, x2, false, cost);\n        Impose(x1, false,\
    \ x2, true, cost);\n    }\n\n    // Impose `cost` when `x1 == x2`\n    void ImposeIfSame(const\
    \ VarName &x1, const VarName &x2, Cost cost) {\n        Impose(x1, true, x2, true,\
    \ cost);\n        Impose(x1, false, x2, false, cost);\n    }\n\n    // Impose\
    \ `penalty` when NOT all of `x == tf` in `consts` are satisfied\n    void ImposeIfNotAll(const\
    \ std::vector<std::pair<VarName, bool>> &consts, Cost penalty) {\n        if (consts.empty())\
    \ return;\n\n        std::vector<std::pair<int, bool>> internal_vars;\n      \
    \  for (const auto &[x, tf] : consts) {\n            const int idx = RegisterOrGetIndex(x);\n\
    \            internal_vars.emplace_back(idx, tf);\n        }\n        std::sort(internal_vars.begin(),\
    \ internal_vars.end());\n        internal_vars.erase(\n            std::unique(internal_vars.begin(),\
    \ internal_vars.end()), internal_vars.end());\n        satisfy_all[internal_vars]\
    \ += penalty;\n    }\n\n    struct Result {\n        bool solved = false;\n  \
    \      Cost total_cost = Cost{};\n        std::map<VarName, bool> x;\n    };\n\
    \n    Result Solve() const {\n        const int nvar = to_internal_idx.size();\n\
    \n        Bipartite bp(nvar);\n\n        for (const auto &[indices, f] : binary)\
    \ {\n            auto [idx1, idx2] = indices;\n            const int mask = GetSubmodularFlips<4>(f);\n\
    \            if (!mask) return Result{false};\n\n            if (!(mask & ((1\
    \ << 0b00) | (1 << 0b11)))) bp.Diff(idx1, idx2);\n            if (!(mask & ((1\
    \ << 0b01) | (1 << 0b10)))) bp.Same(idx1, idx2);\n        }\n\n        for (const\
    \ auto &[indices, f] : ternary) {\n            auto [idx1, idx2, idx3] = indices;\n\
    \            const int m = GetSubmodularFlips<8>(f);\n            if (!m) return\
    \ Result{false};\n\n            // I believe these constraints are necessary and\
    \ sufficient (based on LP solver results)\n            if (!(m & ((1 << 0b000)\
    \ | (1 << 0b011) | (1 << 0b100) | (1 << 0b111))))\n                bp.Diff(idx2,\
    \ idx3);\n            if (!(m & ((1 << 0b001) | (1 << 0b010) | (1 << 0b101) |\
    \ (1 << 0b110))))\n                bp.Same(idx2, idx3);\n\n            if (!(m\
    \ & ((1 << 0b000) | (1 << 0b101) | (1 << 0b010) | (1 << 0b111))))\n          \
    \      bp.Diff(idx1, idx3);\n            if (!(m & ((1 << 0b001) | (1 << 0b100)\
    \ | (1 << 0b011) | (1 << 0b110))))\n                bp.Same(idx1, idx3);\n\n \
    \           if (!(m & ((1 << 0b000) | (1 << 0b110) | (1 << 0b001) | (1 << 0b111))))\n\
    \                bp.Diff(idx1, idx2);\n            if (!(m & ((1 << 0b010) | (1\
    \ << 0b100) | (1 << 0b011) | (1 << 0b101))))\n                bp.Same(idx1, idx2);\n\
    \        }\n\n        for (const auto &[var_flags, penalty] : satisfy_all) {\n\
    \            if (penalty < Cost{}) return Result{false};\n            for (auto\
    \ [idx, tf] : var_flags) {\n                auto [idx0, tf0] = var_flags.front();\n\
    \                if (tf == tf0) {\n                    bp.Same(idx, idx0);\n \
    \               } else {\n                    bp.Diff(idx, idx0);\n          \
    \      }\n            }\n        }\n\n        Cost base = f0;\n        std::vector<Cost>\
    \ actual_unary(nvar);\n        std::map<std::tuple<int, int>, Cost> actual_binary_ft;\n\
    \        std::map<std::pair<std::vector<int>, bool>, Cost> actual_require_all;\n\
    \n        auto ResolveUnary = [&](int idx, const std::array<Cost, 2> &f) {\n \
    \           const Cost f0 = f[0b0], f1 = f[0b1];\n            base += f0;\n  \
    \          actual_unary[idx] += f1 - f0;\n        };\n\n        auto ResolveBinary\
    \ = [&](int idx1, int idx2, const std::array<Cost, 4> &f) {\n            const\
    \ Cost A = f[0b00], B = f[0b01], C = f[0b10], D = f[0b11];\n            base +=\
    \ A;\n            ResolveUnary(idx1, {Cost{}, C - A});\n            ResolveUnary(idx2,\
    \ {Cost{}, D - C});\n            const Cost w = (B + C) - (A + D);\n         \
    \   assert(w >= Cost{});\n            if (w > Cost{}) actual_binary_ft[{idx1,\
    \ idx2}] += w;\n        };\n\n        auto ResolveTernary = [&](int idx1, int\
    \ idx2, int idx3, const std::array<Cost, 8> &f) {\n            const Cost A =\
    \ f[0b000], B = f[0b001], C = f[0b010], D = f[0b011], E = f[0b100],\n        \
    \               F = f[0b101], G = f[0b110], H = f[0b111];\n            const Cost\
    \ P = (A + D + F + G) - (B + C + E + H);\n\n            if (P >= Cost{}) {\n \
    \               base += A;\n                ResolveUnary(idx1, {Cost{}, F - B});\n\
    \                ResolveUnary(idx2, {Cost{}, G - E});\n                ResolveUnary(idx3,\
    \ {Cost{}, D - C});\n                ResolveBinary(idx2, idx3, {Cost{}, (B + C)\
    \ - (A + D), Cost{}, Cost{}});\n                ResolveBinary(idx1, idx3, {Cost{},\
    \ Cost{}, (B + E) - (A + F), Cost{}});\n                ResolveBinary(idx1, idx2,\
    \ {Cost{}, (C + E) - (A + G), Cost{}, Cost{}});\n\n                base -= P;\n\
    \                if (P) { actual_require_all[{std::vector<int>{idx1, idx2, idx3},\
    \ true}] += P; }\n            } else {\n                base += H;\n         \
    \       ResolveUnary(idx1, {C - G, Cost{}});\n                ResolveUnary(idx2,\
    \ {B - D, Cost{}});\n                ResolveUnary(idx3, {E - F, Cost{}});\n  \
    \              ResolveBinary(idx2, idx3, {Cost{}, Cost{}, (F + G) - (E + H), Cost{}});\n\
    \                ResolveBinary(idx1, idx3, {Cost{}, (D + G) - (C + H), Cost{},\
    \ Cost{}});\n                ResolveBinary(idx1, idx2, {Cost{}, Cost{}, (D + F)\
    \ - (B + H), Cost{}});\n\n                base += P;\n                if (P) {\
    \ actual_require_all[{std::vector<int>{idx1, idx2, idx3}, false}] += -P; }\n \
    \           }\n        };\n\n        const auto [is_bipartite, flipped] = bp.Coloring();\n\
    \        if (!is_bipartite) return Result{false};\n\n        for (auto [idx, f]\
    \ : unary) {\n            f = Transpose<2>(f, flipped.at(idx));\n            ResolveUnary(idx,\
    \ f);\n        }\n\n        for (auto [indices, f] : binary) {\n            auto\
    \ [idx1, idx2] = indices;\n            f = Transpose<4>(f, (flipped.at(idx1) <<\
    \ 1) | flipped.at(idx2));\n            ResolveBinary(idx1, idx2, f);\n       \
    \ }\n\n        for (auto [indices, f] : ternary) {\n            auto [idx1, idx2,\
    \ idx3] = indices;\n            f = Transpose<8>(\n                f, (flipped.at(idx1)\
    \ << 2) | (flipped.at(idx2) << 1) | flipped.at(idx3));\n            ResolveTernary(idx1,\
    \ idx2, idx3, f);\n        }\n\n        for (auto &[var_flags, penalty] : satisfy_all)\
    \ {\n            assert(var_flags.size());\n            const auto [idx0, tf0]\
    \ = var_flags.front();\n            std::vector<int> vars;\n            for (const\
    \ auto &[idx, tf] : var_flags) {\n                assert((tf ^ flipped.at(idx))\
    \ == (tf0 ^ flipped.at(idx0)));\n                vars.push_back(idx);\n      \
    \      }\n            actual_require_all[{vars, tf0 ^ flipped.at(idx0)}] += penalty;\n\
    \        }\n\n        const int v_false = nvar + actual_require_all.size();\n\
    \        const int v_true = v_false + 1;\n        atcoder::mf_graph<Cost> mf(v_true\
    \ + 1);\n\n        for (int idx = 0; idx < nvar; ++idx) {\n            const Cost\
    \ cost = actual_unary.at(idx);\n            if (cost > Cost{}) mf.add_edge(v_false,\
    \ idx, cost);\n            if (cost < Cost{}) {\n                base += cost;\n\
    \                mf.add_edge(idx, v_true, -cost);\n            }\n        }\n\n\
    \        for (auto [indices, f] : actual_binary_ft) {\n            assert(f >=\
    \ Cost{});\n            auto [idx1, idx2] = indices;\n            if (f > Cost{})\
    \ mf.add_edge(idx1, idx2, f);\n        }\n\n        int head = nvar;\n\n     \
    \   for (const auto &[var_flags, penalty] : actual_require_all) {\n          \
    \  auto [vars, flg] = var_flags;\n            assert(penalty >= Cost{});\n   \
    \         if (flg) {\n                for (int i : vars) mf.add_edge(i, head,\
    \ penalty);\n                mf.add_edge(head++, v_true, penalty);\n         \
    \   } else {\n                for (int i : vars) mf.add_edge(head, i, penalty);\n\
    \                mf.add_edge(v_false, head++, penalty);\n            }\n     \
    \   }\n\n        assert(head == v_false);\n\n        const Cost flow = mf.flow(v_false,\
    \ v_true);\n        const Cost total_cost = base + flow;\n\n        auto min_cut\
    \ = mf.min_cut(v_false);\n        std::map<VarName, bool> sol;\n        for (int\
    \ i = 0; i < nvar; ++i) {\n            const bool xi = !min_cut.at(i) ^ flipped.at(i);\n\
    \            sol[to_var_name.at(i)] = xi;\n        }\n\n        return {true,\
    \ total_cost, sol};\n    }\n};\n"
  code: "#pragma once\n#include <algorithm>\n#include <array>\n#include <cassert>\n\
    #include <map>\n#include <tuple>\n#include <utility>\n#include <vector>\n\n#include\
    \ <atcoder/maxflow>\n\ntemplate <class VarName = int, class Cost = long long>\
    \ class SubmodularOptimizationViaGraphCut {\n    struct Bipartite {\n        std::vector<std::vector<std::pair<int,\
    \ bool>>> to;\n        Bipartite(int nvar) : to(nvar) {}\n\n        void Same(int\
    \ idx1, int idx2) {\n            to.at(idx1).emplace_back(idx2, false);\n    \
    \        to.at(idx2).emplace_back(idx1, false);\n        }\n\n        void Diff(int\
    \ idx1, int idx2) {\n            to.at(idx1).emplace_back(idx2, true);\n     \
    \       to.at(idx2).emplace_back(idx1, true);\n        }\n\n        std::pair<bool,\
    \ std::vector<bool>> Coloring() const {\n            const int nvar = to.size();\n\
    \            std::vector<bool> is_flipped(nvar, false), visited(nvar, false);\n\
    \            bool failed = false;\n\n            auto rec = [&](auto &&self, int\
    \ now) -> void {\n                visited.at(now) = true;\n                for\
    \ (auto [nxt, w] : to.at(now)) {\n                    const bool next_val = is_flipped.at(now)\
    \ ^ w;\n                    if (visited.at(nxt)) {\n                        if\
    \ (is_flipped.at(nxt) != next_val) {\n                            failed = true;\n\
    \                            return;\n                        }\n            \
    \        } else {\n                        is_flipped.at(nxt) = next_val;\n  \
    \                      self(self, nxt);\n                    }\n             \
    \   }\n            };\n\n            for (int i = 0; i < nvar; ++i) {\n      \
    \          if (visited.at(i)) continue;\n                rec(rec, i);\n      \
    \          if (failed) return {false, {}};\n            }\n\n            return\
    \ {true, is_flipped};\n        }\n    };\n\n    struct Submodular {\n        static\
    \ bool Check(Cost f00, Cost f01, Cost f10, Cost f11) {\n            return f00\
    \ + f11 <= f01 + f10;\n        }\n\n        static bool Check(const std::array<Cost,\
    \ 4> &f) { return Check(f[0], f[1], f[2], f[3]); }\n\n        static bool Check(const\
    \ std::array<Cost, 8> &f) {\n            return Check(f[0], f[1], f[2], f[3])\
    \ and Check(f[4], f[5], f[6], f[7]) and\n                   Check(f[0], f[1],\
    \ f[4], f[5]) and Check(f[2], f[3], f[6], f[7]) and\n                   Check(f[0],\
    \ f[2], f[4], f[6]) and Check(f[1], f[3], f[5], f[7]);\n        }\n    };\n\n\
    \    template <int Size>\n    static std::array<Cost, Size> Transpose(const std::array<Cost,\
    \ Size> &f, int flip_mask) {\n        std::array<Cost, Size> ret;\n        for\
    \ (int i = 0; i < Size; ++i) ret.at(i ^ flip_mask) = f.at(i);\n        return\
    \ ret;\n    }\n\n    template <int Size> int GetSubmodularFlips(const std::array<Cost,\
    \ Size> &f) const {\n        int ret = 0;\n        for (int flip_mask = 0; flip_mask\
    \ < (int)f.size(); ++flip_mask) {\n            if (Submodular::Check(Transpose<Size>(f,\
    \ flip_mask))) ret |= 1 << flip_mask;\n        }\n        return ret;\n    }\n\
    \n    std::map<VarName, int> to_internal_idx;\n    std::vector<VarName> to_var_name;\n\
    \n    Cost f0 = Cost{};\n    std::map<int, std::array<Cost, 2>> unary;\n    std::map<std::tuple<int,\
    \ int>, std::array<Cost, 4>> binary;\n    std::map<std::tuple<int, int, int>,\
    \ std::array<Cost, 8>> ternary;\n    std::map<std::vector<std::pair<int, bool>>,\
    \ Cost> satisfy_all;\n\n    int RegisterOrGetIndex(const VarName &name) {\n  \
    \      if (!to_internal_idx.count(name)) {\n            to_internal_idx[name]\
    \ = to_internal_idx.size();\n            to_var_name.push_back(name);\n      \
    \  }\n        return to_internal_idx.at(name);\n    }\n\npublic:\n    SubmodularOptimizationViaGraphCut()\
    \ {}\n\n    // Impose constant `cost`\n    void Impose(Cost cost) { f0 += cost;\
    \ }\n\n    // Impose `cost` when `x == tf`\n    void Impose(const VarName &x,\
    \ bool tf, Cost cost) {\n        const int idx = RegisterOrGetIndex(x);\n    \
    \    unary[idx][(int)tf] += cost;\n    }\n\n    // Impose `cost` when `x1 == tf1\
    \ and x2 == tf2`\n    void Impose(const VarName &x1, bool tf1, const VarName &x2,\
    \ bool tf2, Cost cost) {\n        int idx1 = RegisterOrGetIndex(x1);\n       \
    \ int idx2 = RegisterOrGetIndex(x2);\n        assert(idx1 != idx2);\n        if\
    \ (idx1 > idx2) {\n            std::swap(idx1, idx2);\n            std::swap(tf1,\
    \ tf2);\n        }\n        binary[std::make_tuple(idx1, idx2)][(tf1 << 1) | tf2]\
    \ += cost;\n    }\n\n    // Impose `cost` when `x1 == tf1, x2 == tf2 and x3 ==\
    \ tf3`\n    // !!Not verified enough!!\n    void Impose(const VarName &x1, bool\
    \ tf1, const VarName &x2, bool tf2, const VarName &x3,\n                bool tf3,\
    \ Cost cost) {\n        int idx1 = RegisterOrGetIndex(x1);\n        int idx2 =\
    \ RegisterOrGetIndex(x2);\n        int idx3 = RegisterOrGetIndex(x3);\n      \
    \  assert(idx1 != idx2 and idx1 != idx3 and idx2 != idx3);\n        if (idx1 >\
    \ idx2) std::swap(idx1, idx2), std::swap(tf1, tf2);\n        if (idx1 > idx3)\
    \ std::swap(idx1, idx3), std::swap(tf1, tf3);\n        if (idx2 > idx3) std::swap(idx2,\
    \ idx3), std::swap(tf2, tf3);\n        ternary[std::make_tuple(idx1, idx2, idx3)][(tf1\
    \ << 2) | (tf2 << 1) | tf3] += cost;\n    }\n\n    // IntVar [0, k) is represented\
    \ by (k - 1) variables:\n    // TTTT...T => 0\n    // FTTT...T => 1\n    // FFTT...T\
    \ => 2\n    // ...\n    // FFFF...F => vars.size() (= k - 1)\n    struct IntVar\
    \ {\n        std::vector<VarName> vars;\n\n        const VarName &at(int i) const\
    \ {\n            assert(0 <= i and i < (int)vars.size());\n            return\
    \ vars.at(i);\n        }\n\n        int size() const { return vars.size(); }\n\
    \    };\n\n    IntVar GenIntVar(const std::vector<VarName> &vars, Cost inf) {\n\
    \        for (int i = 1; i < (int)vars.size(); ++i) {\n            Then(vars.at(i),\
    \ false, vars.at(i - 1), false, inf);\n        }\n\n        return IntVar{vars};\n\
    \    }\n\n    // https://noshi91.hatenablog.com/entry/2021/06/29/044225\n    void\
    \ Impose(const IntVar &iv, const std::vector<Cost> &costs) {\n        assert(iv.size()\
    \ + 1 == (int)costs.size());\n\n        const int k = costs.size();\n        Impose(costs.at(k\
    \ - 1));\n        for (int i = k - 2; i >= 0; --i) Impose(iv.at(i), true, costs.at(i)\
    \ - costs.at(i + 1));\n    }\n\n    // If `iv1 >= min1 and iv2 <= max2` satisfy,\
    \ impose `cost`\n    void ImposeLbUb(const IntVar &iv1, int min1, const IntVar\
    \ &iv2, int max2, Cost cost) {\n        // iv >= t <=> iv[t - 1] == false or t\
    \ <= 0\n        // iv <= t <=> iv[t] == true or t >= iv.size()\n        if ((int)iv1.size()\
    \ < min1 or max2 < 0) return;\n        if (min1 <= 0 and max2 >= (int)iv2.size())\
    \ {\n            Impose(cost);\n        } else if (min1 <= 0) {\n            Impose(iv2.at(max2),\
    \ true, cost);\n        } else if (max2 >= (int)iv2.size()) {\n            Impose(iv1.at(min1\
    \ - 1), false, cost);\n        } else {\n            Impose(iv1.at(min1 - 1),\
    \ false, iv2.at(max2), true, cost);\n        }\n    }\n\n    void Impose(const\
    \ IntVar &vx, const IntVar &vy, std::vector<std::vector<Cost>> costs) {\n    \
    \    assert(vx.size() + 1 == (int)costs.size());\n        assert(vy.size() + 1\
    \ == (int)costs.at(0).size());\n\n        std::vector<Cost> tmp = costs.at(0);\n\
    \        Impose(vy, tmp);\n        for (auto &v : costs) {\n            for (int\
    \ j = 0; j < (int)v.size(); ++j) v.at(j) -= tmp.at(j);\n        }\n\n        tmp.clear();\n\
    \        for (auto &v : costs) {\n            const Cost r = v.back();\n     \
    \       tmp.emplace_back(r);\n            for (auto &x : v) x -= r;\n        }\n\
    \        Impose(vx, tmp);\n\n        // cost is now like:\n        // 00...000\n\
    \        // **...**0\n        // ...\n        // **...**0\n        for (auto &v\
    \ : costs) {\n            for (int j = 1; j < (int)v.size(); ++j) v.at(j - 1)\
    \ -= v.at(j);\n        }\n\n        for (int j = 0; j < (int)costs.at(0).size();\
    \ ++j) {\n            for (int i = (int)costs.size() - 1; i; --i) {\n        \
    \        costs.at(i).at(j) -= costs.at(i - 1).at(j);\n            }\n        }\n\
    \n        for (int x = 1; x < (int)costs.size(); ++x) {\n            for (int\
    \ y = 0; y + 1 < (int)costs.at(0).size(); ++y) {\n                ImposeLbUb(vx,\
    \ x, vy, y, costs.at(x).at(y));\n            }\n        }\n    }\n\n    // Impose\
    \ `penalty` when `(x1 == tf1) => (x2 == tf2)` is NOT satisfied\n    void Then(const\
    \ VarName &x1, bool tf1, const VarName &x2, bool tf2, Cost penalty) {\n      \
    \  Impose(x1, tf1, x2, !tf2, penalty);\n    }\n\n    // Impose `cost` when `x1\
    \ != x2`\n    void ImposeIfDifferent(const VarName &x1, const VarName &x2, Cost\
    \ cost) {\n        Impose(x1, true, x2, false, cost);\n        Impose(x1, false,\
    \ x2, true, cost);\n    }\n\n    // Impose `cost` when `x1 == x2`\n    void ImposeIfSame(const\
    \ VarName &x1, const VarName &x2, Cost cost) {\n        Impose(x1, true, x2, true,\
    \ cost);\n        Impose(x1, false, x2, false, cost);\n    }\n\n    // Impose\
    \ `penalty` when NOT all of `x == tf` in `consts` are satisfied\n    void ImposeIfNotAll(const\
    \ std::vector<std::pair<VarName, bool>> &consts, Cost penalty) {\n        if (consts.empty())\
    \ return;\n\n        std::vector<std::pair<int, bool>> internal_vars;\n      \
    \  for (const auto &[x, tf] : consts) {\n            const int idx = RegisterOrGetIndex(x);\n\
    \            internal_vars.emplace_back(idx, tf);\n        }\n        std::sort(internal_vars.begin(),\
    \ internal_vars.end());\n        internal_vars.erase(\n            std::unique(internal_vars.begin(),\
    \ internal_vars.end()), internal_vars.end());\n        satisfy_all[internal_vars]\
    \ += penalty;\n    }\n\n    struct Result {\n        bool solved = false;\n  \
    \      Cost total_cost = Cost{};\n        std::map<VarName, bool> x;\n    };\n\
    \n    Result Solve() const {\n        const int nvar = to_internal_idx.size();\n\
    \n        Bipartite bp(nvar);\n\n        for (const auto &[indices, f] : binary)\
    \ {\n            auto [idx1, idx2] = indices;\n            const int mask = GetSubmodularFlips<4>(f);\n\
    \            if (!mask) return Result{false};\n\n            if (!(mask & ((1\
    \ << 0b00) | (1 << 0b11)))) bp.Diff(idx1, idx2);\n            if (!(mask & ((1\
    \ << 0b01) | (1 << 0b10)))) bp.Same(idx1, idx2);\n        }\n\n        for (const\
    \ auto &[indices, f] : ternary) {\n            auto [idx1, idx2, idx3] = indices;\n\
    \            const int m = GetSubmodularFlips<8>(f);\n            if (!m) return\
    \ Result{false};\n\n            // I believe these constraints are necessary and\
    \ sufficient (based on LP solver results)\n            if (!(m & ((1 << 0b000)\
    \ | (1 << 0b011) | (1 << 0b100) | (1 << 0b111))))\n                bp.Diff(idx2,\
    \ idx3);\n            if (!(m & ((1 << 0b001) | (1 << 0b010) | (1 << 0b101) |\
    \ (1 << 0b110))))\n                bp.Same(idx2, idx3);\n\n            if (!(m\
    \ & ((1 << 0b000) | (1 << 0b101) | (1 << 0b010) | (1 << 0b111))))\n          \
    \      bp.Diff(idx1, idx3);\n            if (!(m & ((1 << 0b001) | (1 << 0b100)\
    \ | (1 << 0b011) | (1 << 0b110))))\n                bp.Same(idx1, idx3);\n\n \
    \           if (!(m & ((1 << 0b000) | (1 << 0b110) | (1 << 0b001) | (1 << 0b111))))\n\
    \                bp.Diff(idx1, idx2);\n            if (!(m & ((1 << 0b010) | (1\
    \ << 0b100) | (1 << 0b011) | (1 << 0b101))))\n                bp.Same(idx1, idx2);\n\
    \        }\n\n        for (const auto &[var_flags, penalty] : satisfy_all) {\n\
    \            if (penalty < Cost{}) return Result{false};\n            for (auto\
    \ [idx, tf] : var_flags) {\n                auto [idx0, tf0] = var_flags.front();\n\
    \                if (tf == tf0) {\n                    bp.Same(idx, idx0);\n \
    \               } else {\n                    bp.Diff(idx, idx0);\n          \
    \      }\n            }\n        }\n\n        Cost base = f0;\n        std::vector<Cost>\
    \ actual_unary(nvar);\n        std::map<std::tuple<int, int>, Cost> actual_binary_ft;\n\
    \        std::map<std::pair<std::vector<int>, bool>, Cost> actual_require_all;\n\
    \n        auto ResolveUnary = [&](int idx, const std::array<Cost, 2> &f) {\n \
    \           const Cost f0 = f[0b0], f1 = f[0b1];\n            base += f0;\n  \
    \          actual_unary[idx] += f1 - f0;\n        };\n\n        auto ResolveBinary\
    \ = [&](int idx1, int idx2, const std::array<Cost, 4> &f) {\n            const\
    \ Cost A = f[0b00], B = f[0b01], C = f[0b10], D = f[0b11];\n            base +=\
    \ A;\n            ResolveUnary(idx1, {Cost{}, C - A});\n            ResolveUnary(idx2,\
    \ {Cost{}, D - C});\n            const Cost w = (B + C) - (A + D);\n         \
    \   assert(w >= Cost{});\n            if (w > Cost{}) actual_binary_ft[{idx1,\
    \ idx2}] += w;\n        };\n\n        auto ResolveTernary = [&](int idx1, int\
    \ idx2, int idx3, const std::array<Cost, 8> &f) {\n            const Cost A =\
    \ f[0b000], B = f[0b001], C = f[0b010], D = f[0b011], E = f[0b100],\n        \
    \               F = f[0b101], G = f[0b110], H = f[0b111];\n            const Cost\
    \ P = (A + D + F + G) - (B + C + E + H);\n\n            if (P >= Cost{}) {\n \
    \               base += A;\n                ResolveUnary(idx1, {Cost{}, F - B});\n\
    \                ResolveUnary(idx2, {Cost{}, G - E});\n                ResolveUnary(idx3,\
    \ {Cost{}, D - C});\n                ResolveBinary(idx2, idx3, {Cost{}, (B + C)\
    \ - (A + D), Cost{}, Cost{}});\n                ResolveBinary(idx1, idx3, {Cost{},\
    \ Cost{}, (B + E) - (A + F), Cost{}});\n                ResolveBinary(idx1, idx2,\
    \ {Cost{}, (C + E) - (A + G), Cost{}, Cost{}});\n\n                base -= P;\n\
    \                if (P) { actual_require_all[{std::vector<int>{idx1, idx2, idx3},\
    \ true}] += P; }\n            } else {\n                base += H;\n         \
    \       ResolveUnary(idx1, {C - G, Cost{}});\n                ResolveUnary(idx2,\
    \ {B - D, Cost{}});\n                ResolveUnary(idx3, {E - F, Cost{}});\n  \
    \              ResolveBinary(idx2, idx3, {Cost{}, Cost{}, (F + G) - (E + H), Cost{}});\n\
    \                ResolveBinary(idx1, idx3, {Cost{}, (D + G) - (C + H), Cost{},\
    \ Cost{}});\n                ResolveBinary(idx1, idx2, {Cost{}, Cost{}, (D + F)\
    \ - (B + H), Cost{}});\n\n                base += P;\n                if (P) {\
    \ actual_require_all[{std::vector<int>{idx1, idx2, idx3}, false}] += -P; }\n \
    \           }\n        };\n\n        const auto [is_bipartite, flipped] = bp.Coloring();\n\
    \        if (!is_bipartite) return Result{false};\n\n        for (auto [idx, f]\
    \ : unary) {\n            f = Transpose<2>(f, flipped.at(idx));\n            ResolveUnary(idx,\
    \ f);\n        }\n\n        for (auto [indices, f] : binary) {\n            auto\
    \ [idx1, idx2] = indices;\n            f = Transpose<4>(f, (flipped.at(idx1) <<\
    \ 1) | flipped.at(idx2));\n            ResolveBinary(idx1, idx2, f);\n       \
    \ }\n\n        for (auto [indices, f] : ternary) {\n            auto [idx1, idx2,\
    \ idx3] = indices;\n            f = Transpose<8>(\n                f, (flipped.at(idx1)\
    \ << 2) | (flipped.at(idx2) << 1) | flipped.at(idx3));\n            ResolveTernary(idx1,\
    \ idx2, idx3, f);\n        }\n\n        for (auto &[var_flags, penalty] : satisfy_all)\
    \ {\n            assert(var_flags.size());\n            const auto [idx0, tf0]\
    \ = var_flags.front();\n            std::vector<int> vars;\n            for (const\
    \ auto &[idx, tf] : var_flags) {\n                assert((tf ^ flipped.at(idx))\
    \ == (tf0 ^ flipped.at(idx0)));\n                vars.push_back(idx);\n      \
    \      }\n            actual_require_all[{vars, tf0 ^ flipped.at(idx0)}] += penalty;\n\
    \        }\n\n        const int v_false = nvar + actual_require_all.size();\n\
    \        const int v_true = v_false + 1;\n        atcoder::mf_graph<Cost> mf(v_true\
    \ + 1);\n\n        for (int idx = 0; idx < nvar; ++idx) {\n            const Cost\
    \ cost = actual_unary.at(idx);\n            if (cost > Cost{}) mf.add_edge(v_false,\
    \ idx, cost);\n            if (cost < Cost{}) {\n                base += cost;\n\
    \                mf.add_edge(idx, v_true, -cost);\n            }\n        }\n\n\
    \        for (auto [indices, f] : actual_binary_ft) {\n            assert(f >=\
    \ Cost{});\n            auto [idx1, idx2] = indices;\n            if (f > Cost{})\
    \ mf.add_edge(idx1, idx2, f);\n        }\n\n        int head = nvar;\n\n     \
    \   for (const auto &[var_flags, penalty] : actual_require_all) {\n          \
    \  auto [vars, flg] = var_flags;\n            assert(penalty >= Cost{});\n   \
    \         if (flg) {\n                for (int i : vars) mf.add_edge(i, head,\
    \ penalty);\n                mf.add_edge(head++, v_true, penalty);\n         \
    \   } else {\n                for (int i : vars) mf.add_edge(head, i, penalty);\n\
    \                mf.add_edge(v_false, head++, penalty);\n            }\n     \
    \   }\n\n        assert(head == v_false);\n\n        const Cost flow = mf.flow(v_false,\
    \ v_true);\n        const Cost total_cost = base + flow;\n\n        auto min_cut\
    \ = mf.min_cut(v_false);\n        std::map<VarName, bool> sol;\n        for (int\
    \ i = 0; i < nvar; ++i) {\n            const bool xi = !min_cut.at(i) ^ flipped.at(i);\n\
    \            sol[to_var_name.at(i)] = xi;\n        }\n\n        return {true,\
    \ total_cost, sol};\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: flow/submodular_optimization_via_graph_cut.hpp
  requiredBy: []
  timestamp: '2025-08-05 22:25:17+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - flow/test/submodular_opt.yuki2320.test.cpp
  - flow/test/submodular_opt.yuki2713.test.cpp
  - flow/test/submodular_opt.aoj3058.test.cpp
  - flow/test/submodular_opt.yuki1541.test.cpp
  - flow/test/submodular_opt.aoj2943.test.cpp
  - flow/test/submodular_opt.aoj2903.test.cpp
  - flow/test/submodular_opt.yuki957.test.cpp
  - flow/test/submodular_opt.yuki1984.test.cpp
  - flow/test/submodular_opt.aoj2496.test.cpp
  - flow/test/submodular_opt.yuki1900.test.cpp
  - flow/test/submodular_opt.yuki3201.test.cpp
  - flow/test/submodular_opt.yuki1479.test.cpp
  - flow/test/submodular_opt.yuki119.test.cpp
documentation_of: flow/submodular_optimization_via_graph_cut.hpp
layout: document
title: "Submodular function optimization via graph cut \uFF08\u6700\u5C0F\u30AB\u30C3\
  \u30C8\u5E30\u7740\u306B\u3088\u308B\u52A3\u30E2\u30B8\u30E5\u30E9\u95A2\u6570\u306E\
  \u6700\u5C0F\u5316\uFF09"
---

一定の条件を満たす [pseudo-boolean 関数](https://en.wikipedia.org/wiki/Pseudo-Boolean_function) の最小化問題（プログラミングコンテストの文脈における「燃やす埋める問題」）を，特定のグラフの最小カットに帰着させて解く．
解くのに失敗した場合は `Solve()` 関数の結果の `solved` が `false` となる．

本コードの特長として，入力されたコスト関数のいくつかの変数の真偽を反転させてコスト関数の各項を劣モジュラにする方法を予め探索する処理が含まれている．

## 使用方法

### 通常の pseudo-boolean 最適化（いわゆる「燃やす埋める問題」）

最小 $s$-$t$ カットを求め，始点側の連結成分の頂点に真偽値 `false`、終点側に `true` を割り当てる．

```cpp
using V = pair<int, int>;
SubmodularOptimizationViaGraphCut<V> so;  // 頂点の型は int でなくとも（ std::map の key にできれば）よい

so.Impose({0, 0}, true, 100);  // 頂点 (0, 0) が true をとる場合 100 のコスト（ペナルティ）

so.Impose(-500);  // コスト関数の定数項に -500 を加算

vector<pair<V, bool>> conditions;
so.ImposeIfNotAll(conditions, 50); // 「conditions に含まれる全頂点がそれぞれ与えられた真偽値を満たす」に反した場合 50 のコスト

const auto res = so.Solve();
assert(res.solved);
cout << res.total_cost << '\n';
```

### 変数が少数の整数値をとる場合（いわゆる $k$ 値最小カット問題）

この場合， $0$ 以上 $k$ 未満の値をとる整数変数を $k - 1$ 個の頂点 $(v\_1, \ldots, v\_{k - 1})$ で表現する．各頂点 $v\_{i + 1}$ から $v\_{i}$ に十分容量の大きい辺を張る． 解においてこれらの頂点における真偽値の割当が `F...FT...T` という形になることが保証される．これに含まれる `F` の個数がもとの整数変数の解における値である．

```cpp
using V = pair<int, int>;
SubmodularOptimizationViaGraphCut<V> so;
const long long inf = 1LL << 30;

const auto x = so.GenIntVar({V{i, 0}, V{i, 1}}, inf); // Create int value 0 <= x < 3
so.Impose(x, {5LL, 0LL, 3LL}); // Impose cost function f(x) = 5 (if x = 0), 0 (if x = 1), 3 (if x = 2).
so.ImposeLbUb(x, 2, y, 0, 5000); // If x >= 2 && y <= 0, impose cost by 5000
```

## 問題例

- [燃やす埋める練習問題１ \| MojaCoder](https://mojacoder.app/users/_kanpurin_/problems/project_selection_problem001)
- [燃やす埋める練習問題２ \| MojaCoder](https://mojacoder.app/users/_kanpurin_/problems/project_selection_problem002)
- [燃やす埋める練習問題３ \| MojaCoder](https://mojacoder.app/users/_kanpurin_/problems/project_selection_problem003)
- [燃やす埋める練習問題４ \| MojaCoder](https://mojacoder.app/users/_kanpurin_/problems/project_selection_problem004)
- [燃やす埋める練習問題5 \| MojaCoder](https://mojacoder.app/users/_kanpurin_/problems/project_selection_problem005)
- [25365번: Kingdom Partition](https://www.acmicpc.net/problem/25365)
  - そのままではこのライブラリでは解けず， 4 状態へと拡張してやる必要がある．

ほか，多くの問題を CI check に利用している．

## 参考文献・リンク

- [燃やす埋める問題と劣モジュラ関数のグラフ表現可能性 その① - 私と理論](https://theory-and-me.hatenablog.com/entry/2020/03/13/180935)
- [燃やす埋める問題と劣モジュラ関数のグラフ表現可能性 その② グラフ構築編 - 私と理論](https://theory-and-me.hatenablog.com/entry/2020/03/17/180157)
- [最小カット問題の k 値への一般化 - noshi91のメモ](https://noshi91.hatenablog.com/entry/2021/06/29/044225)
