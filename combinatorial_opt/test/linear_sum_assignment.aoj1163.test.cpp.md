---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/linear_sum_assignment.hpp
    title: "Linear sum assignment problem, Hungarian algorithm \uFF08\u5272\u5F53\u554F\
      \u984C\u306B\u5BFE\u3059\u308B\u30CF\u30F3\u30AC\u30EA\u30A2\u30F3\u6CD5\uFF09"
  - icon: ':heavy_check_mark:'
    path: utilities/reader.hpp
    title: "\u9AD8\u901F\u6A19\u6E96\u5165\u529B"
  - icon: ':heavy_check_mark:'
    path: utilities/writer.hpp
    title: "\u6A19\u6E96\u51FA\u529B"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1163
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1163
  bundledCode: "#line 1 \"combinatorial_opt/test/linear_sum_assignment.aoj1163.test.cpp\"\
    \n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1163\"\
    \n\n#line 2 \"combinatorial_opt/linear_sum_assignment.hpp\"\n#include <cassert>\n\
    #include <queue>\n#include <tuple>\n#include <vector>\n\nnamespace linear_sum_assignment\
    \ {\n\ntemplate <class T> struct Result {\n    T opt;\n    std::vector<int> mate;\n\
    \    std::vector<T> f, g; // dual variables\n};\n\ntemplate <class T>\nT augment(int\
    \ nr, int nc, const std::vector<std::vector<T>> &C, std::vector<T> &f, std::vector<T>\
    \ &g,\n          int s, // source row\n          std::vector<int> &mate,\n   \
    \       std::vector<int> &mate_inv, // duplicates are allowed (used for k-best\
    \ algorithms)\n          int fixed_rows = 0 // Ignore first rows and corresponding\
    \ columns (used for k-best algorithms)\n) {\n\n    assert(0 <= s and s < nr);\n\
    \    assert(mate.at(s) < 0);\n\n    static std::vector<T> dist;\n    static std::vector<int>\
    \ prv;\n    dist.resize(nc);\n    prv.resize(nc);\n\n    std::vector<bool> done(nc);\n\
    \n    for (int i = 0; i < fixed_rows; ++i) {\n        if (int j = mate.at(i);\
    \ j >= 0) done.at(j) = 1;\n    }\n\n    {\n        int h = 0;\n        while (done.at(h))\
    \ ++h;\n\n        f.at(s) = C.at(s).at(h) - g.at(h);\n        for (int j = h +\
    \ 1; j < nc; ++j) {\n            if (done.at(j)) continue;\n            f.at(s)\
    \ = std::min(f.at(s), C.at(s).at(j) - g.at(j));\n        }\n    }\n\n    for (int\
    \ j = 0; j < nc; ++j) {\n        if (!done.at(j)) {\n            dist.at(j) =\
    \ C.at(s).at(j) - f.at(s) - g.at(j);\n            prv.at(j) = -1;\n        }\n\
    \    }\n\n    int t = -1;\n    std::vector<int> stk;\n\n    while (t == -1) {\n\
    \        int j1 = -1;\n        for (int j = 0; j < nc; ++j) {\n            if\
    \ (done.at(j)) continue;\n            if (j1 == -1 or dist.at(j) < dist.at(j1)\
    \ or\n                (dist.at(j) == dist.at(j1) and mate_inv.at(j) < 0)) {\n\
    \                j1 = j;\n            }\n        }\n\n        if (mate_inv.at(j1)\
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
    \   }\n};\n#line 4 \"combinatorial_opt/test/linear_sum_assignment.aoj1163.test.cpp\"\
    \n\n#line 2 \"utilities/reader.hpp\"\n#include <cstdio>\n#include <string>\n\n\
    // CUT begin\ntemplate <typename T> T rd_integer() {\n    T ret = 0;\n    bool\
    \ minus = false;\n\n    char c = getchar_unlocked();\n    while (!isdigit(c))\
    \ minus |= (c == '-'), c = getchar_unlocked();\n    while (isdigit(c)) ret = (ret\
    \ << 1) + (ret << 3) + (c ^ 48), c = getchar_unlocked();\n\n    return minus ?\
    \ -ret : ret;\n}\nint rdi() { return rd_integer<int>(); }\nlong long rdll() {\
    \ return rd_integer<long long>(); }\nstd::string rdstr() {\n    std::string ret;\n\
    \    char c = getchar_unlocked();\n    while (!isgraph(c)) c = getchar_unlocked();\n\
    \    while (isgraph(c)) ret += c, c = getchar_unlocked();\n    return ret;\n}\n\
    #line 3 \"utilities/writer.hpp\"\n\ntemplate <typename T> void wt_integer(T x,\
    \ char delim) {\n    if (x == 0) {\n        putchar('0'), putchar(delim);\n  \
    \      return;\n    }\n    if (x < 0) putchar('-'), x = -x;\n    static char cache[20];\n\
    \    char *head = cache;\n    while (x) *head = '0' + x % 10, head++, x /= 10;\n\
    \    while (head != cache) putchar(*(--head));\n    putchar(delim);\n}\n#line\
    \ 7 \"combinatorial_opt/test/linear_sum_assignment.aoj1163.test.cpp\"\n\n#include\
    \ <numeric>\n#line 10 \"combinatorial_opt/test/linear_sum_assignment.aoj1163.test.cpp\"\
    \nusing namespace std;\n\nint main() {\n    while (true) {\n        const int\
    \ nr = rdi(), nc = rdi();\n        if (!nr) break;\n\n        std::vector<int>\
    \ B(nr), R(nc);\n        for (auto &x : B) x = rdi();\n        for (auto &x :\
    \ R) x = rdi();\n\n        std::vector C(nr, vector<int>(nc));\n        for (int\
    \ i = 0; i < nr; ++i) {\n            for (int j = 0; j < nc; ++j) { C.at(i).at(j)\
    \ = -(std::gcd(B.at(i), R.at(j)) > 1); }\n        }\n\n        auto [ret, vs,\
    \ f, g] = linear_sum_assignment::solve(nr, nc, C);\n\n        wt_integer(-ret,\
    \ '\\n');\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1163\"\
    \n\n#include \"../linear_sum_assignment.hpp\"\n\n#include \"../../utilities/reader.hpp\"\
    \n#include \"../../utilities/writer.hpp\"\n\n#include <numeric>\n#include <vector>\n\
    using namespace std;\n\nint main() {\n    while (true) {\n        const int nr\
    \ = rdi(), nc = rdi();\n        if (!nr) break;\n\n        std::vector<int> B(nr),\
    \ R(nc);\n        for (auto &x : B) x = rdi();\n        for (auto &x : R) x =\
    \ rdi();\n\n        std::vector C(nr, vector<int>(nc));\n        for (int i =\
    \ 0; i < nr; ++i) {\n            for (int j = 0; j < nc; ++j) { C.at(i).at(j)\
    \ = -(std::gcd(B.at(i), R.at(j)) > 1); }\n        }\n\n        auto [ret, vs,\
    \ f, g] = linear_sum_assignment::solve(nr, nc, C);\n\n        wt_integer(-ret,\
    \ '\\n');\n    }\n}\n"
  dependsOn:
  - combinatorial_opt/linear_sum_assignment.hpp
  - utilities/reader.hpp
  - utilities/writer.hpp
  isVerificationFile: true
  path: combinatorial_opt/test/linear_sum_assignment.aoj1163.test.cpp
  requiredBy: []
  timestamp: '2025-08-24 23:11:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: combinatorial_opt/test/linear_sum_assignment.aoj1163.test.cpp
layout: document
redirect_from:
- /verify/combinatorial_opt/test/linear_sum_assignment.aoj1163.test.cpp
- /verify/combinatorial_opt/test/linear_sum_assignment.aoj1163.test.cpp.html
title: combinatorial_opt/test/linear_sum_assignment.aoj1163.test.cpp
---
