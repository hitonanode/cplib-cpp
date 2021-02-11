---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/simplex.hpp
    title: "Simplex method \uFF08\u5358\u4F53\u6CD5\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/1122
    links:
    - https://yukicoder.me/problems/no/1122
  bundledCode: "#line 2 \"combinatorial_opt/simplex.hpp\"\n#include <cmath>\n#include\
    \ <numeric>\n#include <vector>\n\n// CUT begin\n// Maximize cx s.t. Ax <= b, x\
    \ >= 0\n// Implementation idea: https://kopricky.github.io/code/Computation_Advanced/simplex.html\n\
    // Refer to https://hitonanode.github.io/cplib-cpp/combinatorial_opt/simplex.hpp\n\
    template <typename Float = double, int DEPS = 30> struct Simplex {\n    const\
    \ Float EPS = Float(1.0) / (1LL << DEPS);\n    int N, M;\n    std::vector<int>\
    \ idx;\n    std::vector<std::vector<Float>> a;\n    int i_ch, j_ch;\n\n    void\
    \ initialize(const std::vector<std::vector<Float>> &A, const std::vector<Float>\
    \ &b, const std::vector<Float> &c) {\n        N = c.size(), M = A.size();\n\n\
    \        a.assign(M + 2, std::vector<Float>(N + 2));\n        i_ch = M;\n    \
    \    for (int i = 0; i < M; i++) {\n            for (int j = 0; j < N; j++) a[i][j]\
    \ = -A[i][j];\n            a[i][N] = 1, a[i][N + 1] = b[i];\n            if (a[i_ch][N\
    \ + 1] > a[i][N + 1]) i_ch = i;\n        }\n        for (int j = 0; j < N; j++)\
    \ a[M][j] = c[j];\n        a[M + 1][N] = -1;\n\n        idx.resize(N + M + 1);\n\
    \        std::iota(idx.begin(), idx.end(), 0);\n    }\n\n    inline Float abs_(Float\
    \ x) noexcept { return x > -x ? x : -x; }\n    void solve() {\n        std::vector<int>\
    \ jupd;\n        for (j_ch = N;;) {\n            if (i_ch < M) {\n           \
    \     std::swap(idx[j_ch], idx[i_ch + N + 1]);\n                a[i_ch][j_ch]\
    \ = Float(1) / a[i_ch][j_ch];\n                jupd.clear();\n               \
    \ for (int j = 0; j < N + 2; j++) {\n                    if (j != j_ch) {\n  \
    \                      a[i_ch][j] *= -a[i_ch][j_ch];\n                       \
    \ if (abs_(a[i_ch][j]) > EPS) jupd.push_back(j);\n                    }\n    \
    \            }\n                for (int i = 0; i < M + 2; i++) {\n          \
    \          if (abs_(a[i][j_ch]) < EPS or i == i_ch) continue;\n              \
    \      for (auto j : jupd) a[i][j] += a[i][j_ch] * a[i_ch][j];\n             \
    \       a[i][j_ch] *= a[i_ch][j_ch];\n                }\n            }\n\n   \
    \         j_ch = -1;\n            for (int j = 0; j < N + 1; j++) {\n        \
    \        if (j_ch < 0 or idx[j_ch] > idx[j]) {\n                    if (a[M +\
    \ 1][j] > EPS or (abs_(a[M + 1][j]) < EPS and a[M][j] > EPS)) j_ch = j;\n    \
    \            }\n            }\n            if (j_ch < 0) break;\n\n          \
    \  i_ch = -1;\n            for (int i = 0; i < M; i++) {\n                if (a[i][j_ch]\
    \ < -EPS) {\n                    if (i_ch < 0) {\n                        i_ch\
    \ = i;\n                    } else if (a[i_ch][N + 1] / a[i_ch][j_ch] - a[i][N\
    \ + 1] / a[i][j_ch] < -EPS) {\n                        i_ch = i;\n           \
    \         } else if (a[i_ch][N + 1] / a[i_ch][j_ch] - a[i][N + 1] / a[i][j_ch]\
    \ < EPS and idx[i_ch] > idx[i]) {\n                        i_ch = i;\n       \
    \             }\n                }\n            }\n            if (i_ch < 0) {\n\
    \                is_infty = true;\n                break;\n            }\n   \
    \     }\n        if (a[M + 1][N + 1] < -EPS) {\n            infeasible = true;\n\
    \            return;\n        }\n        x.assign(N, 0);\n        for (int i =\
    \ 0; i < M; i++) {\n            if (idx[N + 1 + i] < N) x[idx[N + 1 + i]] = a[i][N\
    \ + 1];\n        }\n        ans = a[M][N + 1];\n    }\n    Simplex(const std::vector<std::vector<Float>>\
    \ &A, const std::vector<Float> &b, const std::vector<Float> &c) {\n        is_infty\
    \ = infeasible = false;\n        initialize(A, b, c);\n        solve();\n    }\n\
    \    bool is_infty;\n    bool infeasible;\n    std::vector<Float> x;\n    Float\
    \ ans;\n};\n#line 2 \"combinatorial_opt/test/simplex.multiprecision.test.cpp\"\
    \n#include <boost/multiprecision/cpp_dec_float.hpp>\n#include <iostream>\n#line\
    \ 5 \"combinatorial_opt/test/simplex.multiprecision.test.cpp\"\n#define PROBLEM\
    \ \"https://yukicoder.me/problems/no/1122\"\nusing namespace std;\n\nint main()\
    \ {\n    using Float = boost::multiprecision::cpp_dec_float_50;\n    vector<Float>\
    \ B(5);\n    for (auto &x : B) cin >> x;\n    vector<vector<Float>> A{{1, 1, 1,\
    \ 0, 0}, {0, 1, 1, 1, 0}, {0, 0, 1, 1, 1}, {1, 0, 0, 1, 1}, {1, 1, 0, 0, 1}};\n\
    \    vector<Float> C(5, 1);\n    Simplex<Float, 30> simplex(A, B, C);\n    cout\
    \ << llround(simplex.ans - 0.17) << '\\n'; // I haven't proved yet this always\
    \ returns correct answer.\n}\n"
  code: "#include \"../simplex.hpp\"\n#include <boost/multiprecision/cpp_dec_float.hpp>\n\
    #include <iostream>\n#include <vector>\n#define PROBLEM \"https://yukicoder.me/problems/no/1122\"\
    \nusing namespace std;\n\nint main() {\n    using Float = boost::multiprecision::cpp_dec_float_50;\n\
    \    vector<Float> B(5);\n    for (auto &x : B) cin >> x;\n    vector<vector<Float>>\
    \ A{{1, 1, 1, 0, 0}, {0, 1, 1, 1, 0}, {0, 0, 1, 1, 1}, {1, 0, 0, 1, 1}, {1, 1,\
    \ 0, 0, 1}};\n    vector<Float> C(5, 1);\n    Simplex<Float, 30> simplex(A, B,\
    \ C);\n    cout << llround(simplex.ans - 0.17) << '\\n'; // I haven't proved yet\
    \ this always returns correct answer.\n}\n"
  dependsOn:
  - combinatorial_opt/simplex.hpp
  isVerificationFile: true
  path: combinatorial_opt/test/simplex.multiprecision.test.cpp
  requiredBy: []
  timestamp: '2021-02-11 23:49:12+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: combinatorial_opt/test/simplex.multiprecision.test.cpp
layout: document
redirect_from:
- /verify/combinatorial_opt/test/simplex.multiprecision.test.cpp
- /verify/combinatorial_opt/test/simplex.multiprecision.test.cpp.html
title: combinatorial_opt/test/simplex.multiprecision.test.cpp
---
