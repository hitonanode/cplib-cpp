---
data:
  _extendedDependsOn: []
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
    #include <tuple>\n#include <vector>\n\nnamespace linear_sum_assignment {\n\ntemplate\
    \ <class T>\nT augment(int nr, int nc, const std::vector<std::vector<T>> &C, std::vector<T>\
    \ &f,\n          std::vector<T> &g, int s, std::vector<int> &mate, std::vector<int>\
    \ &mate_inv) {\n\n    assert(0 <= s and s < nr);\n    assert(mate.at(s) < 0);\n\
    \n    static std::vector<T> dist;\n    static std::vector<int> prv;\n    dist.resize(nc);\n\
    \    prv.resize(nc);\n\n    f.at(s) = C.at(s).at(0) - g.at(0);\n    for (int j\
    \ = 1; j < nc; ++j) f.at(s) = std::min(f.at(s), C.at(s).at(j) - g.at(j));\n\n\
    \    for (int j = 0; j < nc; ++j) {\n        dist.at(j) = C.at(s).at(j) - f.at(s)\
    \ - g.at(j);\n        prv.at(j) = s;\n    }\n\n    std::vector<bool> done(nc);\n\
    \n    int t = -1;\n    std::vector<int> stk;\n\n    while (t == -1) {\n      \
    \  int j1 = -1;\n        for (int j = 0; j < nc; ++j) {\n            if (done.at(j))\
    \ continue;\n            if (j1 == -1 or dist.at(j) < dist.at(j1) or\n       \
    \         (dist.at(j) == dist.at(j1) and mate_inv.at(j) < 0)) {\n            \
    \    j1 = j;\n            }\n        }\n\n        if (j1 == -1) return false;\n\
    \n        if (mate_inv.at(j1) < 0) {\n            t = j1;\n            break;\n\
    \        }\n\n        done.at(j1) = 1;\n        stk = {j1};\n\n        while (!stk.empty())\
    \ {\n            const int i = mate_inv.at(stk.back());\n            if (i < 0)\
    \ {\n                t = stk.back();\n                break;\n            }\n\
    \            stk.pop_back();\n\n            for (int j = 0; j < nc; ++j) {\n \
    \               if (done.at(j)) continue;\n\n                const T len = C.at(i).at(j)\
    \ - f.at(i) - g.at(j);\n\n                if (dist.at(j) > dist.at(j1) + len)\
    \ {\n                    dist.at(j) = dist.at(j1) + len;\n                   \
    \ prv.at(j) = i;\n                }\n\n                if (len == T()) {\n   \
    \                 stk.push_back(j);\n                    done.at(j) = 1;\n   \
    \             }\n            }\n        }\n    }\n\n    const T len = dist.at(t);\n\
    \n    f.at(s) += len;\n\n    T ret = len;\n\n    for (int j = 0; j < nc; ++j)\
    \ {\n        if (!done.at(j)) continue;\n\n        g.at(j) -= len - dist.at(j);\n\
    \        if (mate_inv.at(j) >= 0) {\n            f.at(mate_inv.at(j)) += len -\
    \ dist.at(j);\n        } else {\n            ret -= len - dist.at(j);\n      \
    \  }\n    }\n\n    for (int cur = t; cur >= 0;) {\n        const int i = prv.at(cur);\n\
    \        mate_inv.at(cur) = i;\n        if (i == -1) break;\n        std::swap(cur,\
    \ mate.at(i));\n    }\n\n    return ret;\n}\n\n// Complexity: O(nr^2 nc)\ntemplate\
    \ <class T>\nstd::tuple<T, std::vector<int>, std::vector<T>, std::vector<T>>\n\
    _solve(int nr, int nc, const std::vector<std::vector<T>> &C) {\n\n    assert(nr\
    \ <= nc);\n\n    std::vector<int> mate(nr, -1);\n    std::vector<int> mate_inv(nc,\
    \ -1);\n    std::vector<T> f(nr), g(nc); // dual variables, f[i] + g[j] <= C[i][j]\
    \ holds\n\n    if (nr == 0 or nc == 0) return {T(), mate, f, g};\n\n    if (nr\
    \ == nc) {\n        // Column reduction\n        for (int j = nc - 1; j >= 0;\
    \ --j) {\n            g.at(j) = C.at(0).at(j) - f.at(0);\n            int imin\
    \ = 0;\n            for (int i = 1; i < nr; ++i) {\n                if (g.at(j)\
    \ > C.at(i).at(j) - f.at(i)) {\n                    imin = i;\n              \
    \      g.at(j) = C.at(i).at(j) - f.at(i);\n                }\n            }\n\n\
    \            if (mate.at(imin) < 0) {\n                mate.at(imin) = j;\n  \
    \              mate_inv.at(j) = imin;\n            } else if (g.at(j) < g.at(mate.at(imin)))\
    \ {\n                mate_inv.at(mate.at(imin)) = -1;\n                mate.at(imin)\
    \ = j;\n                mate_inv.at(j) = imin;\n            }\n        }\n\n \
    \       // Reduction transfer (can be omitted)\n        if (nc > 1) {\n      \
    \      for (int i = 0; i < nr; ++i) {\n                if (mate.at(i) < 0) continue;\n\
    \                T best = C.at(i).at(0) - g.at(0), second_best = C.at(i).at(1)\
    \ - g.at(1);\n                int argbest = 0;\n                if (best > second_best)\
    \ std::swap(best, second_best), argbest = 1;\n\n                for (int j = 2;\
    \ j < nc; ++j) {\n                    if (T val = C.at(i).at(j) - g.at(j); val\
    \ < best) {\n                        second_best = best;\n                   \
    \     best = val;\n                        argbest = j;\n                    }\
    \ else if (val < second_best) {\n                        second_best = val;\n\
    \                    }\n                }\n\n                g.at(argbest) -=\
    \ second_best - best;\n                f.at(i) = second_best;\n            }\n\
    \        }\n\n        // Augmenting row reduction: not implemented\n    }\n\n\
    \    // Augmentation\n    for (int i = 0; i < nr; ++i) {\n        if (mate.at(i)\
    \ < 0) augment(nr, nc, C, f, g, i, mate, mate_inv);\n    }\n\n    T ret = 0;\n\
    \    for (int i = 0; i < nr; ++i) ret += C.at(i).at(mate.at(i));\n\n    return\
    \ {ret, mate, std::move(f), std::move(g)};\n}\n\n// Jonker\u2013Volgenant algorithm:\
    \ find minimum weight assignment\n// Dual problem (nr == nc): maximize sum(f)\
    \ + sum(g) s.t. f_i + g_j <= C_ij\n// Complexity: O(nr nc min(nr, nc))\ntemplate\
    \ <class T>\nstd::tuple<T, std::vector<int>, std::vector<T>, std::vector<T>>\n\
    solve(int nr, int nc, const std::vector<std::vector<T>> &C) {\n\n    const bool\
    \ transpose = (nr > nc);\n\n    if (!transpose) return _solve(nr, nc, C);\n\n\
    \    std::vector trans(nc, std::vector<T>(nr));\n\n    for (int i = 0; i < nr;\
    \ ++i) {\n        for (int j = 0; j < nc; ++j) trans.at(j).at(i) = C.at(i).at(j);\n\
    \    }\n\n    auto [v, mate, f, g] = _solve(nc, nr, trans);\n\n    std::vector<int>\
    \ mate2(nr, -1);\n    for (int j = 0; j < nc; ++j) {\n        if (mate.at(j) >=\
    \ 0) mate2.at(mate.at(j)) = j;\n    }\n\n    return {v, mate2, g, f};\n}\n\n}\
    \ // namespace linear_sum_assignment\n#line 4 \"combinatorial_opt/test/linear_sum_assignment.aoj1163.test.cpp\"\
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
    \ <iostream>\n\n#include <numeric>\n#line 12 \"combinatorial_opt/test/linear_sum_assignment.aoj1163.test.cpp\"\
    \nusing namespace std;\n\nint main() {\n    while (true) {\n        const int\
    \ nr = rdi(), nc = rdi();\n        if (!nr) break;\n\n        std::vector<int>\
    \ B(nr), R(nc);\n        for (auto &x : B) x = rdi();\n        for (auto &x :\
    \ R) x = rdi();\n\n        std::vector C(nr, vector<int>(nc));\n        for (int\
    \ i = 0; i < nr; ++i) {\n            for (int j = 0; j < nc; ++j) { C.at(i).at(j)\
    \ = -(std::gcd(B.at(i), R.at(j)) > 1); }\n        }\n\n        auto [ret, vs,\
    \ f, g] = linear_sum_assignment::solve(nr, nc, C);\n\n        wt_integer(-ret,\
    \ '\\n');\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1163\"\
    \n\n#include \"combinatorial_opt/linear_sum_assignment.hpp\"\n\n#include \"utilities/reader.hpp\"\
    \n#include \"utilities/writer.hpp\"\n\n#include <iostream>\n\n#include <numeric>\n\
    #include <vector>\nusing namespace std;\n\nint main() {\n    while (true) {\n\
    \        const int nr = rdi(), nc = rdi();\n        if (!nr) break;\n\n      \
    \  std::vector<int> B(nr), R(nc);\n        for (auto &x : B) x = rdi();\n    \
    \    for (auto &x : R) x = rdi();\n\n        std::vector C(nr, vector<int>(nc));\n\
    \        for (int i = 0; i < nr; ++i) {\n            for (int j = 0; j < nc; ++j)\
    \ { C.at(i).at(j) = -(std::gcd(B.at(i), R.at(j)) > 1); }\n        }\n\n      \
    \  auto [ret, vs, f, g] = linear_sum_assignment::solve(nr, nc, C);\n\n       \
    \ wt_integer(-ret, '\\n');\n    }\n}\n"
  dependsOn: []
  isVerificationFile: true
  path: combinatorial_opt/test/linear_sum_assignment.aoj1163.test.cpp
  requiredBy: []
  timestamp: '2023-08-22 20:35:28+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: combinatorial_opt/test/linear_sum_assignment.aoj1163.test.cpp
layout: document
redirect_from:
- /verify/combinatorial_opt/test/linear_sum_assignment.aoj1163.test.cpp
- /verify/combinatorial_opt/test/linear_sum_assignment.aoj1163.test.cpp.html
title: combinatorial_opt/test/linear_sum_assignment.aoj1163.test.cpp
---
