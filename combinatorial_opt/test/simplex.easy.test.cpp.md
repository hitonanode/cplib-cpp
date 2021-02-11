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
    ERROR: 1e-6
    PROBLEM: https://yukicoder.me/problems/771
    links:
    - https://yukicoder.me/problems/771
  bundledCode: "#line 2 \"combinatorial_opt/simplex.hpp\"\n#include <cmath>\n#include\
    \ <numeric>\n#include <vector>\n\n// CUT begin\n// Maximize cx s.t. Ax <= b, x\
    \ >= 0\n// Implementation idea: https://kopricky.github.io/code/Computation_Advanced/simplex.html\n\
    // Refer to https://hitonanode.github.io/cplib-cpp/combinatorial_opt/simplex.hpp\n\
    template <typename Float = double, int DEPS = 30> struct Simplex {\n    const\
    \ Float EPS = Float(1.0) / (1LL << DEPS);\n    int N, M;\n    std::vector<int>\
    \ idx;\n    std::vector<std::vector<Float>> mat;\n    int i_ch, j_ch;\n\n    void\
    \ initialize(const std::vector<std::vector<Float>> &A, const std::vector<Float>\
    \ &b, const std::vector<Float> &c) {\n        N = c.size(), M = A.size();\n\n\
    \        mat.assign(M + 2, std::vector<Float>(N + 2));\n        i_ch = M;\n  \
    \      for (int i = 0; i < M; i++) {\n            for (int j = 0; j < N; j++)\
    \ mat[i][j] = -A[i][j];\n            mat[i][N] = 1, mat[i][N + 1] = b[i];\n  \
    \          if (mat[i_ch][N + 1] > mat[i][N + 1]) i_ch = i;\n        }\n      \
    \  for (int j = 0; j < N; j++) mat[M][j] = c[j];\n        mat[M + 1][N] = -1;\n\
    \n        idx.resize(N + M + 1);\n        std::iota(idx.begin(), idx.end(), 0);\n\
    \    }\n\n    inline Float abs_(Float x) noexcept { return x > -x ? x : -x; }\n\
    \    void solve() {\n        std::vector<int> jupd;\n        for (j_ch = N;;)\
    \ {\n            if (i_ch < M) {\n                std::swap(idx[j_ch], idx[i_ch\
    \ + N + 1]);\n                mat[i_ch][j_ch] = Float(1) / mat[i_ch][j_ch];\n\
    \                jupd.clear();\n                for (int j = 0; j < N + 2; j++)\
    \ {\n                    if (j != j_ch) {\n                        mat[i_ch][j]\
    \ *= -mat[i_ch][j_ch];\n                        if (abs_(mat[i_ch][j]) > EPS)\
    \ jupd.push_back(j);\n                    }\n                }\n             \
    \   for (int i = 0; i < M + 2; i++) {\n                    if (abs_(mat[i][j_ch])\
    \ < EPS or i == i_ch) continue;\n                    for (auto j : jupd) mat[i][j]\
    \ += mat[i][j_ch] * mat[i_ch][j];\n                    mat[i][j_ch] *= mat[i_ch][j_ch];\n\
    \                }\n            }\n\n            j_ch = -1;\n            for (int\
    \ j = 0; j < N + 1; j++) {\n                if (j_ch < 0 or idx[j_ch] > idx[j])\
    \ {\n                    if (mat[M + 1][j] > EPS or (abs_(mat[M + 1][j]) < EPS\
    \ and mat[M][j] > EPS)) j_ch = j;\n                }\n            }\n        \
    \    if (j_ch < 0) break;\n\n            i_ch = -1;\n            for (int i =\
    \ 0; i < M; i++) {\n                if (mat[i][j_ch] < -EPS) {\n             \
    \       if (i_ch < 0) {\n                        i_ch = i;\n                 \
    \   } else if (mat[i_ch][N + 1] / mat[i_ch][j_ch] - mat[i][N + 1] / mat[i][j_ch]\
    \ < -EPS) {\n                        i_ch = i;\n                    } else if\
    \ (mat[i_ch][N + 1] / mat[i_ch][j_ch] - mat[i][N + 1] / mat[i][j_ch] < EPS and\
    \ idx[i_ch] > idx[i]) {\n                        i_ch = i;\n                 \
    \   }\n                }\n            }\n            if (i_ch < 0) {\n       \
    \         is_infty = true;\n                break;\n            }\n        }\n\
    \        if (mat[M + 1][N + 1] < -EPS) {\n            infeasible = true;\n   \
    \         return;\n        }\n        x.assign(N, 0);\n        for (int i = 0;\
    \ i < M; i++) {\n            if (idx[N + 1 + i] < N) x[idx[N + 1 + i]] = mat[i][N\
    \ + 1];\n        }\n        ans = mat[M][N + 1];\n    }\n    Simplex(const std::vector<std::vector<Float>>\
    \ &A, const std::vector<Float> &b, const std::vector<Float> &c) {\n        is_infty\
    \ = infeasible = false;\n        initialize(A, b, c);\n        solve();\n    }\n\
    \    bool is_infty;\n    bool infeasible;\n    std::vector<Float> x;\n    Float\
    \ ans;\n};\n#line 2 \"combinatorial_opt/test/simplex.easy.test.cpp\"\n#include\
    \ <iomanip>\n#include <iostream>\n#line 5 \"combinatorial_opt/test/simplex.easy.test.cpp\"\
    \n#define PROBLEM \"https://yukicoder.me/problems/771\"\n#define ERROR 1e-6\n\
    using namespace std;\n\nint main() {\n    double C, D;\n    cin >> C >> D;\n \
    \   vector<vector<double>> A{{3.0 / 4.0, 2.0 / 7.0}, {1.0 / 4.0, 5.0 / 7.0}};\n\
    \    vector<double> b{C, D};\n    vector<double> c{1000, 2000};\n    Simplex<>\
    \ simplex(A, b, c);\n    cout << fixed << setprecision(10) << simplex.ans << '\\\
    n';\n}\n"
  code: "#include \"../simplex.hpp\"\n#include <iomanip>\n#include <iostream>\n#include\
    \ <vector>\n#define PROBLEM \"https://yukicoder.me/problems/771\"\n#define ERROR\
    \ 1e-6\nusing namespace std;\n\nint main() {\n    double C, D;\n    cin >> C >>\
    \ D;\n    vector<vector<double>> A{{3.0 / 4.0, 2.0 / 7.0}, {1.0 / 4.0, 5.0 / 7.0}};\n\
    \    vector<double> b{C, D};\n    vector<double> c{1000, 2000};\n    Simplex<>\
    \ simplex(A, b, c);\n    cout << fixed << setprecision(10) << simplex.ans << '\\\
    n';\n}\n"
  dependsOn:
  - combinatorial_opt/simplex.hpp
  isVerificationFile: true
  path: combinatorial_opt/test/simplex.easy.test.cpp
  requiredBy: []
  timestamp: '2021-02-11 23:53:14+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: combinatorial_opt/test/simplex.easy.test.cpp
layout: document
redirect_from:
- /verify/combinatorial_opt/test/simplex.easy.test.cpp
- /verify/combinatorial_opt/test/simplex.easy.test.cpp.html
title: combinatorial_opt/test/simplex.easy.test.cpp
---
