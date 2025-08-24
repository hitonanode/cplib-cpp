---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/test/linear_sum_assignment.aoj1163.test.cpp
    title: combinatorial_opt/test/linear_sum_assignment.aoj1163.test.cpp
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/test/linear_sum_assignment.test.cpp
    title: combinatorial_opt/test/linear_sum_assignment.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"combinatorial_opt/linear_sum_assignment.hpp\"\n#include\
    \ <cassert>\n#include <queue>\n#include <tuple>\n#include <vector>\n\nnamespace\
    \ linear_sum_assignment {\n\ntemplate <class T> struct Result {\n    T opt;\n\
    \    std::vector<int> mate;\n    std::vector<T> f, g; // dual variables\n};\n\n\
    template <class T>\nT augment(int nr, int nc, const std::vector<std::vector<T>>\
    \ &C, std::vector<T> &f, std::vector<T> &g,\n          int s, // source row\n\
    \          std::vector<int> &mate,\n          std::vector<int> &mate_inv, // duplicates\
    \ are allowed (used for k-best algorithms)\n          int fixed_rows = 0 // Ignore\
    \ first rows and corresponding columns (used for k-best algorithms)\n) {\n\n \
    \   assert(0 <= s and s < nr);\n    assert(mate.at(s) < 0);\n\n    static std::vector<T>\
    \ dist;\n    static std::vector<int> prv;\n    dist.resize(nc);\n    prv.resize(nc);\n\
    \n    std::vector<bool> done(nc);\n\n    for (int i = 0; i < fixed_rows; ++i)\
    \ {\n        if (int j = mate.at(i); j >= 0) done.at(j) = 1;\n    }\n\n    {\n\
    \        int h = 0;\n        while (done.at(h)) ++h;\n\n        f.at(s) = C.at(s).at(h)\
    \ - g.at(h);\n        for (int j = h + 1; j < nc; ++j) {\n            if (done.at(j))\
    \ continue;\n            f.at(s) = std::min(f.at(s), C.at(s).at(j) - g.at(j));\n\
    \        }\n    }\n\n    for (int j = 0; j < nc; ++j) {\n        if (!done.at(j))\
    \ {\n            dist.at(j) = C.at(s).at(j) - f.at(s) - g.at(j);\n           \
    \ prv.at(j) = -1;\n        }\n    }\n\n    int t = -1;\n    std::vector<int> stk;\n\
    \n    while (t == -1) {\n        int j1 = -1;\n        for (int j = 0; j < nc;\
    \ ++j) {\n            if (done.at(j)) continue;\n            if (j1 == -1 or dist.at(j)\
    \ < dist.at(j1) or\n                (dist.at(j) == dist.at(j1) and mate_inv.at(j)\
    \ < 0)) {\n                j1 = j;\n            }\n        }\n\n        if (mate_inv.at(j1)\
    \ < 0) {\n            t = j1;\n            break;\n        }\n\n        done.at(j1)\
    \ = 1;\n        stk = {j1};\n\n        while (!stk.empty()) {\n            const\
    \ int j2 = stk.back();\n            const int i = mate_inv.at(j2);\n         \
    \   if (i < 0) {\n                t = stk.back();\n                break;\n  \
    \          }\n            stk.pop_back();\n\n            for (int j = 0; j < nc;\
    \ ++j) {\n                if (done.at(j)) continue;\n\n                const T\
    \ len = C.at(i).at(j) - f.at(i) - g.at(j);\n\n                if (dist.at(j) >\
    \ dist.at(j1) + len) {\n                    dist.at(j) = dist.at(j1) + len;\n\
    \                    prv.at(j) = j2;\n                }\n\n                if\
    \ (len == T()) {\n                    stk.push_back(j);\n                    done.at(j)\
    \ = 1;\n                }\n            }\n        }\n    }\n\n    const T len\
    \ = dist.at(t);\n\n    f.at(s) += len;\n\n    for (int i = 0; i < fixed_rows;\
    \ ++i) {\n        if (const int j = mate.at(i); j >= 0) done.at(j) = 0;\n    }\n\
    \n    for (int j = 0; j < nc; ++j) {\n        if (!done.at(j)) continue;\n\n \
    \       g.at(j) -= len - dist.at(j);\n    }\n\n    for (int i = fixed_rows; i\
    \ < nr; ++i) {\n        const int j = mate.at(i);\n        if (j < 0 or !done.at(j)\
    \ or j >= nc) continue;\n        f.at(i) += len - dist.at(j);\n    }\n\n    T\
    \ ret = T();\n\n    for (int cur = t; cur >= 0;) {\n        const int nxt = prv.at(cur);\n\
    \        if (nxt < 0) {\n            mate_inv.at(cur) = s;\n            mate.at(s)\
    \ = cur;\n            ret += C.at(s).at(cur);\n            break;\n        }\n\
    \        const int i = mate_inv.at(nxt);\n\n        ret += C.at(i).at(cur) - C.at(i).at(nxt);\n\
    \n        mate_inv.at(cur) = i;\n        mate.at(i) = cur;\n        cur = nxt;\n\
    \    }\n\n    return ret;\n}\n\n// Complexity: O(nr^2 nc)\ntemplate <class T>\
    \ Result<T> _solve(int nr, int nc, const std::vector<std::vector<T>> &C) {\n\n\
    \    assert(nr <= nc);\n\n    std::vector<int> mate(nr, -1);\n    std::vector<int>\
    \ mate_inv(nc, -1);\n    std::vector<T> f(nr), g(nc); // dual variables, f[i]\
    \ + g[j] <= C[i][j] holds\n\n    if (nr == 0 or nc == 0) return {T(), mate, f,\
    \ g};\n\n    if (nr == nc) {\n        // Column reduction\n        for (int j\
    \ = nc - 1; j >= 0; --j) {\n            g.at(j) = C.at(0).at(j) - f.at(0);\n \
    \           int imin = 0;\n            for (int i = 1; i < nr; ++i) {\n      \
    \          if (g.at(j) > C.at(i).at(j) - f.at(i)) {\n                    imin\
    \ = i;\n                    g.at(j) = C.at(i).at(j) - f.at(i);\n             \
    \   }\n            }\n\n            if (mate.at(imin) < 0) {\n               \
    \ mate.at(imin) = j;\n                mate_inv.at(j) = imin;\n            } else\
    \ if (g.at(j) < g.at(mate.at(imin))) {\n                mate_inv.at(mate.at(imin))\
    \ = -1;\n                mate.at(imin) = j;\n                mate_inv.at(j) =\
    \ imin;\n            }\n        }\n\n        // Reduction transfer (can be omitted)\n\
    \        if (nc > 1) {\n            for (int i = 0; i < nr; ++i) {\n         \
    \       if (mate.at(i) < 0) continue;\n                T best = C.at(i).at(0)\
    \ - g.at(0), second_best = C.at(i).at(1) - g.at(1);\n                int argbest\
    \ = 0;\n                if (best > second_best) std::swap(best, second_best),\
    \ argbest = 1;\n\n                for (int j = 2; j < nc; ++j) {\n           \
    \         if (T val = C.at(i).at(j) - g.at(j); val < best) {\n               \
    \         second_best = best;\n                        best = val;\n         \
    \               argbest = j;\n                    } else if (val < second_best)\
    \ {\n                        second_best = val;\n                    }\n     \
    \           }\n\n                g.at(argbest) -= second_best - best;\n      \
    \          f.at(i) = second_best;\n            }\n        }\n\n        // Augmenting\
    \ row reduction: not implemented\n    }\n\n    // Augmentation\n    for (int i\
    \ = 0; i < nr; ++i) {\n        if (mate.at(i) < 0) augment(nr, nc, C, f, g, i,\
    \ mate, mate_inv);\n    }\n\n    T ret = 0;\n    for (int i = 0; i < nr; ++i)\
    \ ret += C.at(i).at(mate.at(i));\n\n    return {ret, mate, std::move(f), std::move(g)};\n\
    }\n\n// Jonker\u2013Volgenant algorithm: find minimum weight assignment\n// Dual\
    \ problem (nr == nc): maximize sum(f) + sum(g) s.t. f_i + g_j <= C_ij\n// Complexity:\
    \ O(nr nc min(nr, nc))\ntemplate <class T> Result<T> solve(int nr, int nc, const\
    \ std::vector<std::vector<T>> &C) {\n\n    const bool transpose = (nr > nc);\n\
    \n    if (!transpose) return _solve(nr, nc, C);\n\n    std::vector trans(nc, std::vector<T>(nr));\n\
    \n    for (int i = 0; i < nr; ++i) {\n        for (int j = 0; j < nc; ++j) trans.at(j).at(i)\
    \ = C.at(i).at(j);\n    }\n\n    auto [v, mate, f, g] = _solve(nc, nr, trans);\n\
    \n    std::vector<int> mate2(nr, -1);\n    for (int j = 0; j < nc; ++j) {\n  \
    \      if (mate.at(j) >= 0) mate2.at(mate.at(j)) = j;\n    }\n\n    return {v,\
    \ mate2, g, f};\n}\n\n} // namespace linear_sum_assignment\n\ntemplate <class\
    \ T> struct best_assignments {\n\n    struct Node {\n        T opt;\n        std::vector<int>\
    \ mate;\n        std::vector<T> f, g; // dual variables\n        int fixed_rows;\n\
    \        std::vector<int> banned_js; // C[fixed_rows][j] \u304C inf \u3068\u306A\
    \u308B j \u306E\u96C6\u5408\n\n        // for priority queue\n        // NOTE:\
    \ reverse order\n        bool operator<(const Node &rhs) const { return opt >\
    \ rhs.opt; }\n\n        linear_sum_assignment::Result<T> to_output(bool transpose)\
    \ const {\n            if (transpose) {\n                std::vector<int> mate2(g.size(),\
    \ -1);\n                for (int i = 0; i < (int)mate.size(); ++i) mate2.at(mate.at(i))\
    \ = i;\n                return {opt, mate2, g, f};\n            } else {\n   \
    \             return {opt, mate, f, g};\n            }\n        }\n    };\n\n\
    \    bool transpose;\n    int nr_, nc_;\n    T inf;\n    std::vector<std::vector<T>>\
    \ C_, Ctmp_;\n    std::priority_queue<Node> pq;\n\n    best_assignments(int nr,\
    \ int nc, const std::vector<std::vector<T>> &C, T inf)\n        : transpose(nr\
    \ > nc), inf(inf) {\n\n        assert((int)C.size() == nr);\n        for (int\
    \ i = 0; i < nr; ++i) assert((int)C.at(i).size() == nc);\n\n        nr_ = transpose\
    \ ? nc : nr;\n        nc_ = transpose ? nr : nc;\n\n        C_.assign(nr_ + (nr_\
    \ != nc_), std::vector<T>(nc_, T()));\n        for (int i = 0; i < nr; ++i) {\n\
    \            for (int j = 0; j < nc; ++j) {\n                C_.at(transpose ?\
    \ j : i).at(transpose ? i : j) = C.at(i).at(j);\n            }\n        }\n\n\
    \        Ctmp_ = C_;\n\n        auto [opt, mate, f, g] = linear_sum_assignment::solve(C_.size(),\
    \ nc, C_);\n\n        pq.emplace(Node{opt, std::move(mate), std::move(f), std::move(g),\
    \ 0, {}});\n    }\n\n    bool finished() const { return pq.empty(); }\n\n    linear_sum_assignment::Result<T>\
    \ yield() {\n        assert(!pq.empty());\n\n        const Node ret = pq.top();\n\
    \        pq.pop();\n\n        for (int fixed_rows = ret.fixed_rows; fixed_rows\
    \ < nr_; ++fixed_rows) {\n            std::vector<int> banned_js;\n          \
    \  if (fixed_rows == ret.fixed_rows) banned_js = ret.banned_js;\n\n          \
    \  const int s = fixed_rows;\n            banned_js.push_back(ret.mate.at(s));\n\
    \n            if ((int)banned_js.size() >= nc_) continue;\n\n            auto\
    \ f = ret.f;\n            auto g = ret.g;\n            auto mate = ret.mate;\n\
    \n            std::vector<int> mate_inv(nc_, nr_);\n            for (int i = 0;\
    \ i < nr_; ++i) mate_inv.at(mate.at(i)) = i;\n\n            std::vector<int> iscoldone(nc_);\n\
    \            for (int i = 0; i < fixed_rows; ++i) iscoldone.at(mate.at(i)) = 1;\n\
    \n            for (int j : banned_js) Ctmp_.at(s).at(j) = inf;\n\n           \
    \ mate_inv.at(mate.at(s)) = -1;\n            mate.at(s) = -1;\n\n            auto\
    \ aug = linear_sum_assignment::augment(\n                nr_, nc_, Ctmp_, f, g,\
    \ s, mate, mate_inv, fixed_rows);\n\n            for (int j = 0; j < nc_; ++j)\
    \ {\n                if (mate_inv.at(j) < 0) { // nrows < ncols\n            \
    \        g.at(j) = -f.back();\n                    for (int i = fixed_rows; i\
    \ < nr_; ++i) {\n                        g.at(j) = std::min(g.at(j), Ctmp_.at(i).at(j)\
    \ - f.at(i));\n                    }\n                }\n            }\n\n   \
    \         if (Ctmp_.at(s).at(mate.at(s)) < inf) {\n                pq.emplace(Node{\n\
    \                    ret.opt + aug - C_.at(s).at(ret.mate.at(s)),\n          \
    \          std::move(mate),\n                    std::move(f),\n             \
    \       std::move(g),\n                    fixed_rows,\n                    banned_js,\n\
    \                });\n            }\n\n            for (int j : banned_js) Ctmp_.at(s).at(j)\
    \ = C_.at(s).at(j);\n        }\n\n        return ret.to_output(transpose);\n \
    \   }\n};\n"
  code: "#pragma once\n#include <cassert>\n#include <queue>\n#include <tuple>\n#include\
    \ <vector>\n\nnamespace linear_sum_assignment {\n\ntemplate <class T> struct Result\
    \ {\n    T opt;\n    std::vector<int> mate;\n    std::vector<T> f, g; // dual\
    \ variables\n};\n\ntemplate <class T>\nT augment(int nr, int nc, const std::vector<std::vector<T>>\
    \ &C, std::vector<T> &f, std::vector<T> &g,\n          int s, // source row\n\
    \          std::vector<int> &mate,\n          std::vector<int> &mate_inv, // duplicates\
    \ are allowed (used for k-best algorithms)\n          int fixed_rows = 0 // Ignore\
    \ first rows and corresponding columns (used for k-best algorithms)\n) {\n\n \
    \   assert(0 <= s and s < nr);\n    assert(mate.at(s) < 0);\n\n    static std::vector<T>\
    \ dist;\n    static std::vector<int> prv;\n    dist.resize(nc);\n    prv.resize(nc);\n\
    \n    std::vector<bool> done(nc);\n\n    for (int i = 0; i < fixed_rows; ++i)\
    \ {\n        if (int j = mate.at(i); j >= 0) done.at(j) = 1;\n    }\n\n    {\n\
    \        int h = 0;\n        while (done.at(h)) ++h;\n\n        f.at(s) = C.at(s).at(h)\
    \ - g.at(h);\n        for (int j = h + 1; j < nc; ++j) {\n            if (done.at(j))\
    \ continue;\n            f.at(s) = std::min(f.at(s), C.at(s).at(j) - g.at(j));\n\
    \        }\n    }\n\n    for (int j = 0; j < nc; ++j) {\n        if (!done.at(j))\
    \ {\n            dist.at(j) = C.at(s).at(j) - f.at(s) - g.at(j);\n           \
    \ prv.at(j) = -1;\n        }\n    }\n\n    int t = -1;\n    std::vector<int> stk;\n\
    \n    while (t == -1) {\n        int j1 = -1;\n        for (int j = 0; j < nc;\
    \ ++j) {\n            if (done.at(j)) continue;\n            if (j1 == -1 or dist.at(j)\
    \ < dist.at(j1) or\n                (dist.at(j) == dist.at(j1) and mate_inv.at(j)\
    \ < 0)) {\n                j1 = j;\n            }\n        }\n\n        if (mate_inv.at(j1)\
    \ < 0) {\n            t = j1;\n            break;\n        }\n\n        done.at(j1)\
    \ = 1;\n        stk = {j1};\n\n        while (!stk.empty()) {\n            const\
    \ int j2 = stk.back();\n            const int i = mate_inv.at(j2);\n         \
    \   if (i < 0) {\n                t = stk.back();\n                break;\n  \
    \          }\n            stk.pop_back();\n\n            for (int j = 0; j < nc;\
    \ ++j) {\n                if (done.at(j)) continue;\n\n                const T\
    \ len = C.at(i).at(j) - f.at(i) - g.at(j);\n\n                if (dist.at(j) >\
    \ dist.at(j1) + len) {\n                    dist.at(j) = dist.at(j1) + len;\n\
    \                    prv.at(j) = j2;\n                }\n\n                if\
    \ (len == T()) {\n                    stk.push_back(j);\n                    done.at(j)\
    \ = 1;\n                }\n            }\n        }\n    }\n\n    const T len\
    \ = dist.at(t);\n\n    f.at(s) += len;\n\n    for (int i = 0; i < fixed_rows;\
    \ ++i) {\n        if (const int j = mate.at(i); j >= 0) done.at(j) = 0;\n    }\n\
    \n    for (int j = 0; j < nc; ++j) {\n        if (!done.at(j)) continue;\n\n \
    \       g.at(j) -= len - dist.at(j);\n    }\n\n    for (int i = fixed_rows; i\
    \ < nr; ++i) {\n        const int j = mate.at(i);\n        if (j < 0 or !done.at(j)\
    \ or j >= nc) continue;\n        f.at(i) += len - dist.at(j);\n    }\n\n    T\
    \ ret = T();\n\n    for (int cur = t; cur >= 0;) {\n        const int nxt = prv.at(cur);\n\
    \        if (nxt < 0) {\n            mate_inv.at(cur) = s;\n            mate.at(s)\
    \ = cur;\n            ret += C.at(s).at(cur);\n            break;\n        }\n\
    \        const int i = mate_inv.at(nxt);\n\n        ret += C.at(i).at(cur) - C.at(i).at(nxt);\n\
    \n        mate_inv.at(cur) = i;\n        mate.at(i) = cur;\n        cur = nxt;\n\
    \    }\n\n    return ret;\n}\n\n// Complexity: O(nr^2 nc)\ntemplate <class T>\
    \ Result<T> _solve(int nr, int nc, const std::vector<std::vector<T>> &C) {\n\n\
    \    assert(nr <= nc);\n\n    std::vector<int> mate(nr, -1);\n    std::vector<int>\
    \ mate_inv(nc, -1);\n    std::vector<T> f(nr), g(nc); // dual variables, f[i]\
    \ + g[j] <= C[i][j] holds\n\n    if (nr == 0 or nc == 0) return {T(), mate, f,\
    \ g};\n\n    if (nr == nc) {\n        // Column reduction\n        for (int j\
    \ = nc - 1; j >= 0; --j) {\n            g.at(j) = C.at(0).at(j) - f.at(0);\n \
    \           int imin = 0;\n            for (int i = 1; i < nr; ++i) {\n      \
    \          if (g.at(j) > C.at(i).at(j) - f.at(i)) {\n                    imin\
    \ = i;\n                    g.at(j) = C.at(i).at(j) - f.at(i);\n             \
    \   }\n            }\n\n            if (mate.at(imin) < 0) {\n               \
    \ mate.at(imin) = j;\n                mate_inv.at(j) = imin;\n            } else\
    \ if (g.at(j) < g.at(mate.at(imin))) {\n                mate_inv.at(mate.at(imin))\
    \ = -1;\n                mate.at(imin) = j;\n                mate_inv.at(j) =\
    \ imin;\n            }\n        }\n\n        // Reduction transfer (can be omitted)\n\
    \        if (nc > 1) {\n            for (int i = 0; i < nr; ++i) {\n         \
    \       if (mate.at(i) < 0) continue;\n                T best = C.at(i).at(0)\
    \ - g.at(0), second_best = C.at(i).at(1) - g.at(1);\n                int argbest\
    \ = 0;\n                if (best > second_best) std::swap(best, second_best),\
    \ argbest = 1;\n\n                for (int j = 2; j < nc; ++j) {\n           \
    \         if (T val = C.at(i).at(j) - g.at(j); val < best) {\n               \
    \         second_best = best;\n                        best = val;\n         \
    \               argbest = j;\n                    } else if (val < second_best)\
    \ {\n                        second_best = val;\n                    }\n     \
    \           }\n\n                g.at(argbest) -= second_best - best;\n      \
    \          f.at(i) = second_best;\n            }\n        }\n\n        // Augmenting\
    \ row reduction: not implemented\n    }\n\n    // Augmentation\n    for (int i\
    \ = 0; i < nr; ++i) {\n        if (mate.at(i) < 0) augment(nr, nc, C, f, g, i,\
    \ mate, mate_inv);\n    }\n\n    T ret = 0;\n    for (int i = 0; i < nr; ++i)\
    \ ret += C.at(i).at(mate.at(i));\n\n    return {ret, mate, std::move(f), std::move(g)};\n\
    }\n\n// Jonker\u2013Volgenant algorithm: find minimum weight assignment\n// Dual\
    \ problem (nr == nc): maximize sum(f) + sum(g) s.t. f_i + g_j <= C_ij\n// Complexity:\
    \ O(nr nc min(nr, nc))\ntemplate <class T> Result<T> solve(int nr, int nc, const\
    \ std::vector<std::vector<T>> &C) {\n\n    const bool transpose = (nr > nc);\n\
    \n    if (!transpose) return _solve(nr, nc, C);\n\n    std::vector trans(nc, std::vector<T>(nr));\n\
    \n    for (int i = 0; i < nr; ++i) {\n        for (int j = 0; j < nc; ++j) trans.at(j).at(i)\
    \ = C.at(i).at(j);\n    }\n\n    auto [v, mate, f, g] = _solve(nc, nr, trans);\n\
    \n    std::vector<int> mate2(nr, -1);\n    for (int j = 0; j < nc; ++j) {\n  \
    \      if (mate.at(j) >= 0) mate2.at(mate.at(j)) = j;\n    }\n\n    return {v,\
    \ mate2, g, f};\n}\n\n} // namespace linear_sum_assignment\n\ntemplate <class\
    \ T> struct best_assignments {\n\n    struct Node {\n        T opt;\n        std::vector<int>\
    \ mate;\n        std::vector<T> f, g; // dual variables\n        int fixed_rows;\n\
    \        std::vector<int> banned_js; // C[fixed_rows][j] \u304C inf \u3068\u306A\
    \u308B j \u306E\u96C6\u5408\n\n        // for priority queue\n        // NOTE:\
    \ reverse order\n        bool operator<(const Node &rhs) const { return opt >\
    \ rhs.opt; }\n\n        linear_sum_assignment::Result<T> to_output(bool transpose)\
    \ const {\n            if (transpose) {\n                std::vector<int> mate2(g.size(),\
    \ -1);\n                for (int i = 0; i < (int)mate.size(); ++i) mate2.at(mate.at(i))\
    \ = i;\n                return {opt, mate2, g, f};\n            } else {\n   \
    \             return {opt, mate, f, g};\n            }\n        }\n    };\n\n\
    \    bool transpose;\n    int nr_, nc_;\n    T inf;\n    std::vector<std::vector<T>>\
    \ C_, Ctmp_;\n    std::priority_queue<Node> pq;\n\n    best_assignments(int nr,\
    \ int nc, const std::vector<std::vector<T>> &C, T inf)\n        : transpose(nr\
    \ > nc), inf(inf) {\n\n        assert((int)C.size() == nr);\n        for (int\
    \ i = 0; i < nr; ++i) assert((int)C.at(i).size() == nc);\n\n        nr_ = transpose\
    \ ? nc : nr;\n        nc_ = transpose ? nr : nc;\n\n        C_.assign(nr_ + (nr_\
    \ != nc_), std::vector<T>(nc_, T()));\n        for (int i = 0; i < nr; ++i) {\n\
    \            for (int j = 0; j < nc; ++j) {\n                C_.at(transpose ?\
    \ j : i).at(transpose ? i : j) = C.at(i).at(j);\n            }\n        }\n\n\
    \        Ctmp_ = C_;\n\n        auto [opt, mate, f, g] = linear_sum_assignment::solve(C_.size(),\
    \ nc, C_);\n\n        pq.emplace(Node{opt, std::move(mate), std::move(f), std::move(g),\
    \ 0, {}});\n    }\n\n    bool finished() const { return pq.empty(); }\n\n    linear_sum_assignment::Result<T>\
    \ yield() {\n        assert(!pq.empty());\n\n        const Node ret = pq.top();\n\
    \        pq.pop();\n\n        for (int fixed_rows = ret.fixed_rows; fixed_rows\
    \ < nr_; ++fixed_rows) {\n            std::vector<int> banned_js;\n          \
    \  if (fixed_rows == ret.fixed_rows) banned_js = ret.banned_js;\n\n          \
    \  const int s = fixed_rows;\n            banned_js.push_back(ret.mate.at(s));\n\
    \n            if ((int)banned_js.size() >= nc_) continue;\n\n            auto\
    \ f = ret.f;\n            auto g = ret.g;\n            auto mate = ret.mate;\n\
    \n            std::vector<int> mate_inv(nc_, nr_);\n            for (int i = 0;\
    \ i < nr_; ++i) mate_inv.at(mate.at(i)) = i;\n\n            std::vector<int> iscoldone(nc_);\n\
    \            for (int i = 0; i < fixed_rows; ++i) iscoldone.at(mate.at(i)) = 1;\n\
    \n            for (int j : banned_js) Ctmp_.at(s).at(j) = inf;\n\n           \
    \ mate_inv.at(mate.at(s)) = -1;\n            mate.at(s) = -1;\n\n            auto\
    \ aug = linear_sum_assignment::augment(\n                nr_, nc_, Ctmp_, f, g,\
    \ s, mate, mate_inv, fixed_rows);\n\n            for (int j = 0; j < nc_; ++j)\
    \ {\n                if (mate_inv.at(j) < 0) { // nrows < ncols\n            \
    \        g.at(j) = -f.back();\n                    for (int i = fixed_rows; i\
    \ < nr_; ++i) {\n                        g.at(j) = std::min(g.at(j), Ctmp_.at(i).at(j)\
    \ - f.at(i));\n                    }\n                }\n            }\n\n   \
    \         if (Ctmp_.at(s).at(mate.at(s)) < inf) {\n                pq.emplace(Node{\n\
    \                    ret.opt + aug - C_.at(s).at(ret.mate.at(s)),\n          \
    \          std::move(mate),\n                    std::move(f),\n             \
    \       std::move(g),\n                    fixed_rows,\n                    banned_js,\n\
    \                });\n            }\n\n            for (int j : banned_js) Ctmp_.at(s).at(j)\
    \ = C_.at(s).at(j);\n        }\n\n        return ret.to_output(transpose);\n \
    \   }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: combinatorial_opt/linear_sum_assignment.hpp
  requiredBy: []
  timestamp: '2024-11-25 22:28:29+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - combinatorial_opt/test/linear_sum_assignment.aoj1163.test.cpp
  - combinatorial_opt/test/linear_sum_assignment.test.cpp
documentation_of: combinatorial_opt/linear_sum_assignment.hpp
layout: document
title: "Linear sum assignment problem, Hungarian algorithm \uFF08\u5272\u5F53\u554F\
  \u984C\u306B\u5BFE\u3059\u308B\u30CF\u30F3\u30AC\u30EA\u30A2\u30F3\u6CD5\uFF09"
---

$r$ 行 $c$ 列の行列を入力とした割当問題（二部グラフの最小重み最大マッチング問題）を解く．計算量は `augment()` 一回あたり $O(rc)$ で，全体で $O(rc \min(r, c))$．

オーソドックスな Hungarian algorithm の実装ではなく， Jonker–Volgenant algorithm の工夫を一部取り入れることで定数倍高速化を試みている．

また，割当問題の上位 $k$ 個の解を効率的に列挙するクラス `best_assignments` も提供している．このクラスのコンストラクタや `yield()` を呼び出し毎に $O(rc \min{r, c})$ の時間計算量が発生する．

## 解いてくれる問題

主問題として，オーソドックスな線形重み割当問題を解く．

LP 緩和の双対問題を考えると，特に $r = c$ の場合，以下の問題のソルバとしても利用できる．

$\displaystyle
\begin{array}{rl}
\text{maximize} & \sum\_{i} f\_i + \sum\_j g\_j \\
\text{s.t.} & f\_{i} + g\_{j} \le C\_{ij}
\end{array}
$

## 使用方法

### 割当問題（最適解の計算）

```cpp
vector C(r, vector<long long>(c));

long long min_weight;
vector<int> mate;
vector<long long> f, g;

std::tie(min_weight, mate, f, g) = linear_sum_assignment::solve(r, c, C);
```

`mate[i]` は第 $i$ 行が何列目の要素と対応するかを示す（ $r > c$ で，第 $i$ 行に対応する要素が存在しない場合は $-1$）．

また， `f[i]` および `g[j]` は最適解における双対変数の一例を示す．すなわち，任意の $i, j$ について $f\_i + g\_j \le C\_{ij}$ が成立し，特に第 $i$ 行と第 $j$ 列が対応する場合は等号が成立する．この双対変数は，行列の一部要素に更新を加えた場合の最適解の変化を効率的に追うために利用できる．

### 割当問題の $k$-best 解列挙

```cpp
int r, c;

vector<vector<int>> C;
int inf;

best_assignments<int> gen(r, c, cost, inf);

// 解の生成
for (int t = 0; t < k; ++t) {
    if (ba.finished()) break;
    auto [opt, mate, f, g] = ba.yield();
}
```

## 問題例

- [Library Checker: Assignment Problem](https://judge.yosupo.jp/problem/assignment)

## 文献・リンク集

- [Lecture 8: Assignment Algorithms](https://cyberlab.engr.uconn.edu/wp-content/uploads/sites/2576/2018/09/Lecture_8.pdf)
- [1] K. G. Murty, "An algorithm for ranking all the assignments in order of increasing cost," Operations Research, 16(3), 682–687, 1968.
- [2] M.L. Miller, H.S. Stone, I.J. Cox, "Optimizing Murty's ranked assignment method," IEEE Transactions on Aerospace and Electronic Systems, 33(3), 851-862, 1997.
