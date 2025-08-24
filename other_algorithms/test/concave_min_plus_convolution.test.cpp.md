---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other_algorithms/smawk.hpp
    title: Totally Monotone Matrix Searching (SMAWK), concave max-plus / min-plus
      convolution
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/min_plus_convolution_concave_arbitrary
    links:
    - https://judge.yosupo.jp/problem/min_plus_convolution_concave_arbitrary
  bundledCode: "#line 1 \"other_algorithms/test/concave_min_plus_convolution.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/min_plus_convolution_concave_arbitrary\"\
    \n\n#line 2 \"other_algorithms/smawk.hpp\"\n#include <cassert>\n#include <functional>\n\
    #include <numeric>\n#include <utility>\n#include <vector>\n\n// SMAWK: finding\
    \ minima of totally monotone function f(i, j) (0 <= i < N, 0 <= j < M) for each\
    \ i\n// Constraints: every submatrix of f(i, j) is monotone (= totally monotone).\n\
    // Complexity: O(N + M)\n// Reference:\n// https://topcoder-g-hatena-ne-jp.jag-icpc.org/spaghetti_source/20120923/1348327542.html\n\
    // http://web.cs.unlv.edu/larmore/Courses/CSC477/monge.pdf\n// Verify: https://codeforces.com/contest/1423/submission/98368491\n\
    template <class T>\nstd::vector<std::pair<int, T>> SMAWK(int N, int M, const std::function<T(int\
    \ i, int j)> &weight) {\n    std::vector<std::pair<int, T>> minima(N);\n\n   \
    \ auto rec = [&](auto &&self, const std::vector<int> &js, int ib, int ie, int\
    \ id) {\n        if (ib > ie) return;\n        std::vector<int> js2;\n       \
    \ int i = ib;\n        for (int j : js) {\n            while (!js2.empty() and\
    \ weight(i, js2.back()) >= weight(i, j)) js2.pop_back(), i -= id;\n          \
    \  if (int(js2.size()) != (ie - ib) / id) js2.push_back(j), i += id;\n       \
    \ }\n        self(self, js2, ib + id, ie, id * 2);\n\n        for (int i = ib,\
    \ q = 0; i <= ie; i += id * 2) {\n            const int jt = (i + id <= ie ? minima[i\
    \ + id].first : js.back());\n            T fm = 0;\n            bool init = true;\n\
    \            for (; q < int(js.size()); ++q) {\n                const T fq = weight(i,\
    \ js[q]);\n                if (init or fm > fq) fm = fq, minima[i] = std::make_pair(js[q],\
    \ fq);\n                init = false;\n                if (js[q] == jt) break;\n\
    \            }\n        }\n    };\n\n    std::vector<int> js(M);\n    std::iota(js.begin(),\
    \ js.end(), 0);\n    rec(rec, js, 0, N - 1, 1);\n\n    return minima;\n}\n\n//\
    \ Find minima of totally ANTI-monotone function f(i, j) (0 <= i < N, 0 <= j <\
    \ M) for each i\n// Constraints: every submatrix of f(i, j) is anti-monotone.\n\
    // Complexity: O(N + M)\ntemplate <class T>\nstd::vector<std::pair<int, T>>\n\
    SMAWKAntiMonotone(int N, int M, const std::function<T(int i, int j)> &weight)\
    \ {\n    auto minima = SMAWK<T>(N, M, [&](int i, int j) -> T { return weight(i,\
    \ M - 1 - j); });\n    for (auto &p : minima) p.first = M - 1 - p.first;\n   \
    \ return minima;\n}\n\n// Concave max-plus convolution\n// **b MUST BE CONCAVE**\n\
    // Complexity: O(n + m)\n// Verify: https://www.codechef.com/problems/MAXPREFFLIP\n\
    template <class S, S INF>\nstd::vector<S> concave_max_plus_convolution(const std::vector<S>\
    \ &a, const std::vector<S> &b) {\n    const int n = a.size(), m = b.size();\n\n\
    \    auto is_concave = [&](const std::vector<S> &u) -> bool {\n        for (int\
    \ i = 1; i + 1 < int(u.size()); ++i) {\n            if (u[i - 1] + u[i + 1] >\
    \ u[i] + u[i]) return false;\n        }\n        return true;\n    };\n    assert(is_concave(b));\n\
    \n    auto select = [&](int i, int j) -> S {\n        int aidx = j, bidx = i -\
    \ j;\n        if (bidx < 0 or bidx >= m or aidx >= n) return INF;\n        return\
    \ -(a[aidx] + b[bidx]);\n    };\n    const auto minima = SMAWK<S>(n + m - 1, n,\
    \ select);\n    std::vector<S> ret;\n    for (auto x : minima) ret.push_back(-x.second);\n\
    \    return ret;\n}\n\n// Concave min-plus convolution\n// **b MUST BE CONCAVE**\n\
    // Complexity: O((n + m)log(n + m))\ntemplate <class S>\nstd::vector<S> concave_min_plus_convolution(const\
    \ std::vector<S> &a, const std::vector<S> &b) {\n    const int n = a.size(), m\
    \ = b.size();\n\n    auto is_concave = [&](const std::vector<S> &u) -> bool {\n\
    \        for (int i = 1; i + 1 < int(u.size()); ++i) {\n            if (u[i -\
    \ 1] + u[i + 1] > u[i] + u[i]) return false;\n        }\n        return true;\n\
    \    };\n    assert(is_concave(b));\n\n    std::vector<S> ret(n + m - 1);\n  \
    \  std::vector<int> argmin(n + m - 1, -1);\n\n    // mat[i][j] = a[j] + b[i -\
    \ j]\n    auto is_valid = [&](int i, int j) { return 0 <= i - j and i - j < m;\
    \ };\n    auto has_valid = [&](int il, int ir, int jl, int jr) {\n        if (il\
    \ >= ir or jl >= jr) return false;\n        return is_valid(il, jl) or is_valid(il,\
    \ jr - 1) or is_valid(ir - 1, jl) or\n               is_valid(ir - 1, jr - 1);\n\
    \    };\n\n    auto rec = [&](auto &&self, int il, int ir, int jl, int jr) ->\
    \ void {\n        if (!has_valid(il, ir, jl, jr)) return;\n\n        if (is_valid(il,\
    \ jr - 1) and is_valid(ir - 1, jl)) {\n            auto select = [&](int i, int\
    \ j) -> S { return a[j + jl] + b[(i + il) - (j + jl)]; };\n            const auto\
    \ res = SMAWKAntiMonotone<S>(ir - il, jr - jl, select);\n            for (int\
    \ idx = 0; idx < ir - il; ++idx) {\n                const int i = il + idx;\n\
    \                if (argmin[i] == -1 or res[idx].second < ret[i]) {\n        \
    \            ret[i] = res[idx].second;\n                    argmin[i] = res[idx].first\
    \ + jl;\n                }\n            }\n        } else {\n            if (const\
    \ int di = ir - il, dj = jr - jl; di > dj) {\n                const int im = (il\
    \ + ir) / 2;\n                self(self, il, im, jl, jr);\n                self(self,\
    \ im, ir, jl, jr);\n            } else {\n                const int jm = (jl +\
    \ jr) / 2;\n                self(self, il, ir, jl, jm);\n                self(self,\
    \ il, ir, jm, jr);\n            }\n        }\n    };\n\n    rec(rec, 0, n + m\
    \ - 1, 0, n);\n\n    return ret;\n    // return argmin;  // If you want argmin\
    \ (0 <= argmin[idx] < len(a))\n}\n#line 4 \"other_algorithms/test/concave_min_plus_convolution.test.cpp\"\
    \n\n#include <iostream>\n#line 7 \"other_algorithms/test/concave_min_plus_convolution.test.cpp\"\
    \nusing namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    int N, M;\n    cin >> N >> M;\n    vector<int> A(N), B(M);\n    for (auto\
    \ &a : A) cin >> a;\n    for (auto &b : B) cin >> b;\n\n    vector<int> ret =\
    \ concave_min_plus_convolution<int>(B, A);\n\n    for (int i = 0; i < N + M -\
    \ 1; ++i) cout << ret[i] << \" \\n\"[i + 1 == N + M - 1];\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/min_plus_convolution_concave_arbitrary\"\
    \n\n#include \"../smawk.hpp\"\n\n#include <iostream>\n#include <vector>\nusing\
    \ namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    int N, M;\n    cin >> N >> M;\n    vector<int> A(N), B(M);\n    for (auto\
    \ &a : A) cin >> a;\n    for (auto &b : B) cin >> b;\n\n    vector<int> ret =\
    \ concave_min_plus_convolution<int>(B, A);\n\n    for (int i = 0; i < N + M -\
    \ 1; ++i) cout << ret[i] << \" \\n\"[i + 1 == N + M - 1];\n}\n"
  dependsOn:
  - other_algorithms/smawk.hpp
  isVerificationFile: true
  path: other_algorithms/test/concave_min_plus_convolution.test.cpp
  requiredBy: []
  timestamp: '2025-08-24 23:54:21+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: other_algorithms/test/concave_min_plus_convolution.test.cpp
layout: document
redirect_from:
- /verify/other_algorithms/test/concave_min_plus_convolution.test.cpp
- /verify/other_algorithms/test/concave_min_plus_convolution.test.cpp.html
title: other_algorithms/test/concave_min_plus_convolution.test.cpp
---
