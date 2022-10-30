---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/test/simplex.easy.test.cpp
    title: combinatorial_opt/test/simplex.easy.test.cpp
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/test/simplex.maxflow.test.cpp
    title: combinatorial_opt/test/simplex.maxflow.test.cpp
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/test/simplex.mcf.test.cpp
    title: combinatorial_opt/test/simplex.mcf.test.cpp
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/test/simplex.multiprecision.test.cpp
    title: combinatorial_opt/test/simplex.multiprecision.test.cpp
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/test/simplex.shortestpath.test.cpp
    title: combinatorial_opt/test/simplex.shortestpath.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://hitonanode.github.io/cplib-cpp/combinatorial_opt/simplex.hpp
    - https://kopricky.github.io/code/Computation_Advanced/simplex.html
  bundledCode: "#line 2 \"combinatorial_opt/simplex.hpp\"\n#include <algorithm>\n\
    #include <chrono>\n#include <cmath>\n#include <numeric>\n#include <random>\n#include\
    \ <vector>\n\n// Maximize cx s.t. Ax <= b, x >= 0\n// Implementation idea: https://kopricky.github.io/code/Computation_Advanced/simplex.html\n\
    // Refer to https://hitonanode.github.io/cplib-cpp/combinatorial_opt/simplex.hpp\n\
    template <typename Float = double, int DEPS = 30, bool Randomize = true> struct\
    \ Simplex {\n    const Float EPS = Float(1.0) / (1LL << DEPS);\n    int N, M;\n\
    \    std::vector<int> shuffle_idx;\n    std::vector<int> idx;\n    std::vector<std::vector<Float>>\
    \ mat;\n    int i_ch, j_ch;\n\nprivate:\n    void _initialize(const std::vector<std::vector<Float>>\
    \ &A, const std::vector<Float> &b,\n                     const std::vector<Float>\
    \ &c) {\n        N = c.size(), M = A.size();\n\n        mat.assign(M + 2, std::vector<Float>(N\
    \ + 2));\n        i_ch = M;\n        for (int i = 0; i < M; i++) {\n         \
    \   for (int j = 0; j < N; j++) mat[i][j] = -A[i][j];\n            mat[i][N] =\
    \ 1, mat[i][N + 1] = b[i];\n            if (mat[i_ch][N + 1] > mat[i][N + 1])\
    \ i_ch = i;\n        }\n        for (int j = 0; j < N; j++) mat[M][j] = c[j];\n\
    \        mat[M + 1][N] = -1;\n\n        idx.resize(N + M + 1);\n        std::iota(idx.begin(),\
    \ idx.end(), 0);\n    }\n\n    inline Float abs_(Float x) noexcept { return x\
    \ > -x ? x : -x; }\n    void _solve() {\n        std::vector<int> jupd;\n    \
    \    for (nb_iter = 0, j_ch = N;; nb_iter++) {\n            if (i_ch < M) {\n\
    \                std::swap(idx[j_ch], idx[i_ch + N + 1]);\n                mat[i_ch][j_ch]\
    \ = Float(1) / mat[i_ch][j_ch];\n                jupd.clear();\n             \
    \   for (int j = 0; j < N + 2; j++) {\n                    if (j != j_ch) {\n\
    \                        mat[i_ch][j] *= -mat[i_ch][j_ch];\n                 \
    \       if (abs_(mat[i_ch][j]) > EPS) jupd.push_back(j);\n                   \
    \ }\n                }\n                for (int i = 0; i < M + 2; i++) {\n  \
    \                  if (abs_(mat[i][j_ch]) < EPS or i == i_ch) continue;\n    \
    \                for (auto j : jupd) mat[i][j] += mat[i][j_ch] * mat[i_ch][j];\n\
    \                    mat[i][j_ch] *= mat[i_ch][j_ch];\n                }\n   \
    \         }\n\n            j_ch = -1;\n            for (int j = 0; j < N + 1;\
    \ j++) {\n                if (j_ch < 0 or idx[j_ch] > idx[j]) {\n            \
    \        if (mat[M + 1][j] > EPS or (abs_(mat[M + 1][j]) < EPS and mat[M][j] >\
    \ EPS))\n                        j_ch = j;\n                }\n            }\n\
    \            if (j_ch < 0) break;\n\n            i_ch = -1;\n            for (int\
    \ i = 0; i < M; i++) {\n                if (mat[i][j_ch] < -EPS) {\n         \
    \           if (i_ch < 0) {\n                        i_ch = i;\n             \
    \       } else if (mat[i_ch][N + 1] / mat[i_ch][j_ch] - mat[i][N + 1] / mat[i][j_ch]\
    \ <\n                               -EPS) {\n                        i_ch = i;\n\
    \                    } else if (mat[i_ch][N + 1] / mat[i_ch][j_ch] - mat[i][N\
    \ + 1] / mat[i][j_ch] <\n                                   EPS and\n        \
    \                       idx[i_ch] > idx[i]) {\n                        i_ch =\
    \ i;\n                    }\n                }\n            }\n            if\
    \ (i_ch < 0) {\n                is_infty = true;\n                break;\n   \
    \         }\n        }\n        if (mat[M + 1][N + 1] < -EPS) {\n            infeasible\
    \ = true;\n            return;\n        }\n        x.assign(N, 0);\n        for\
    \ (int i = 0; i < M; i++) {\n            if (idx[N + 1 + i] < N) x[idx[N + 1 +\
    \ i]] = mat[i][N + 1];\n        }\n        ans = mat[M][N + 1];\n    }\n\npublic:\n\
    \    Simplex(std::vector<std::vector<Float>> A, std::vector<Float> b, std::vector<Float>\
    \ c) {\n        is_infty = infeasible = false;\n\n        if (Randomize) {\n \
    \           std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());\n\
    \n            std::vector<std::pair<std::vector<Float>, Float>> Abs;\n       \
    \     for (unsigned i = 0; i < A.size(); i++) Abs.emplace_back(A[i], b[i]);\n\
    \            std::shuffle(Abs.begin(), Abs.end(), rng);\n            A.clear(),\
    \ b.clear();\n            for (auto &&Ab : Abs) A.emplace_back(Ab.first), b.emplace_back(Ab.second);\n\
    \n            shuffle_idx.resize(c.size());\n            std::iota(shuffle_idx.begin(),\
    \ shuffle_idx.end(), 0);\n            std::shuffle(shuffle_idx.begin(), shuffle_idx.end(),\
    \ rng);\n            auto Atmp = A;\n            auto ctmp = c;\n            for\
    \ (unsigned i = 0; i < A.size(); i++) {\n                for (unsigned j = 0;\
    \ j < A[i].size(); j++) A[i][j] = Atmp[i][shuffle_idx[j]];\n            }\n  \
    \          for (unsigned j = 0; j < c.size(); j++) c[j] = ctmp[shuffle_idx[j]];\n\
    \        }\n\n        _initialize(A, b, c);\n        _solve();\n\n        if (Randomize\
    \ and x.size() == c.size()) {\n            auto xtmp = x;\n            for (unsigned\
    \ j = 0; j < c.size(); j++) x[shuffle_idx[j]] = xtmp[j];\n        }\n    }\n \
    \   unsigned nb_iter;\n    bool is_infty;\n    bool infeasible;\n    std::vector<Float>\
    \ x;\n    Float ans;\n\n    static void\n    dual(std::vector<std::vector<Float>>\
    \ &A, std::vector<Float> &b, std::vector<Float> &c) {\n        const int n = b.size(),\
    \ m = c.size();\n        std::vector<std::vector<Float>> At(m, std::vector<Float>(n));\n\
    \        for (int i = 0; i < n; ++i) {\n            for (int j = 0; j < m; ++j)\
    \ At[j][i] = -A[i][j];\n        }\n        A = At;\n        for (int i = 0; i\
    \ < n; ++i) b[i] = -b[i];\n        for (int j = 0; j < m; ++j) c[j] = -c[j];\n\
    \        b.swap(c);\n    }\n};\n"
  code: "#pragma once\n#include <algorithm>\n#include <chrono>\n#include <cmath>\n\
    #include <numeric>\n#include <random>\n#include <vector>\n\n// Maximize cx s.t.\
    \ Ax <= b, x >= 0\n// Implementation idea: https://kopricky.github.io/code/Computation_Advanced/simplex.html\n\
    // Refer to https://hitonanode.github.io/cplib-cpp/combinatorial_opt/simplex.hpp\n\
    template <typename Float = double, int DEPS = 30, bool Randomize = true> struct\
    \ Simplex {\n    const Float EPS = Float(1.0) / (1LL << DEPS);\n    int N, M;\n\
    \    std::vector<int> shuffle_idx;\n    std::vector<int> idx;\n    std::vector<std::vector<Float>>\
    \ mat;\n    int i_ch, j_ch;\n\nprivate:\n    void _initialize(const std::vector<std::vector<Float>>\
    \ &A, const std::vector<Float> &b,\n                     const std::vector<Float>\
    \ &c) {\n        N = c.size(), M = A.size();\n\n        mat.assign(M + 2, std::vector<Float>(N\
    \ + 2));\n        i_ch = M;\n        for (int i = 0; i < M; i++) {\n         \
    \   for (int j = 0; j < N; j++) mat[i][j] = -A[i][j];\n            mat[i][N] =\
    \ 1, mat[i][N + 1] = b[i];\n            if (mat[i_ch][N + 1] > mat[i][N + 1])\
    \ i_ch = i;\n        }\n        for (int j = 0; j < N; j++) mat[M][j] = c[j];\n\
    \        mat[M + 1][N] = -1;\n\n        idx.resize(N + M + 1);\n        std::iota(idx.begin(),\
    \ idx.end(), 0);\n    }\n\n    inline Float abs_(Float x) noexcept { return x\
    \ > -x ? x : -x; }\n    void _solve() {\n        std::vector<int> jupd;\n    \
    \    for (nb_iter = 0, j_ch = N;; nb_iter++) {\n            if (i_ch < M) {\n\
    \                std::swap(idx[j_ch], idx[i_ch + N + 1]);\n                mat[i_ch][j_ch]\
    \ = Float(1) / mat[i_ch][j_ch];\n                jupd.clear();\n             \
    \   for (int j = 0; j < N + 2; j++) {\n                    if (j != j_ch) {\n\
    \                        mat[i_ch][j] *= -mat[i_ch][j_ch];\n                 \
    \       if (abs_(mat[i_ch][j]) > EPS) jupd.push_back(j);\n                   \
    \ }\n                }\n                for (int i = 0; i < M + 2; i++) {\n  \
    \                  if (abs_(mat[i][j_ch]) < EPS or i == i_ch) continue;\n    \
    \                for (auto j : jupd) mat[i][j] += mat[i][j_ch] * mat[i_ch][j];\n\
    \                    mat[i][j_ch] *= mat[i_ch][j_ch];\n                }\n   \
    \         }\n\n            j_ch = -1;\n            for (int j = 0; j < N + 1;\
    \ j++) {\n                if (j_ch < 0 or idx[j_ch] > idx[j]) {\n            \
    \        if (mat[M + 1][j] > EPS or (abs_(mat[M + 1][j]) < EPS and mat[M][j] >\
    \ EPS))\n                        j_ch = j;\n                }\n            }\n\
    \            if (j_ch < 0) break;\n\n            i_ch = -1;\n            for (int\
    \ i = 0; i < M; i++) {\n                if (mat[i][j_ch] < -EPS) {\n         \
    \           if (i_ch < 0) {\n                        i_ch = i;\n             \
    \       } else if (mat[i_ch][N + 1] / mat[i_ch][j_ch] - mat[i][N + 1] / mat[i][j_ch]\
    \ <\n                               -EPS) {\n                        i_ch = i;\n\
    \                    } else if (mat[i_ch][N + 1] / mat[i_ch][j_ch] - mat[i][N\
    \ + 1] / mat[i][j_ch] <\n                                   EPS and\n        \
    \                       idx[i_ch] > idx[i]) {\n                        i_ch =\
    \ i;\n                    }\n                }\n            }\n            if\
    \ (i_ch < 0) {\n                is_infty = true;\n                break;\n   \
    \         }\n        }\n        if (mat[M + 1][N + 1] < -EPS) {\n            infeasible\
    \ = true;\n            return;\n        }\n        x.assign(N, 0);\n        for\
    \ (int i = 0; i < M; i++) {\n            if (idx[N + 1 + i] < N) x[idx[N + 1 +\
    \ i]] = mat[i][N + 1];\n        }\n        ans = mat[M][N + 1];\n    }\n\npublic:\n\
    \    Simplex(std::vector<std::vector<Float>> A, std::vector<Float> b, std::vector<Float>\
    \ c) {\n        is_infty = infeasible = false;\n\n        if (Randomize) {\n \
    \           std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());\n\
    \n            std::vector<std::pair<std::vector<Float>, Float>> Abs;\n       \
    \     for (unsigned i = 0; i < A.size(); i++) Abs.emplace_back(A[i], b[i]);\n\
    \            std::shuffle(Abs.begin(), Abs.end(), rng);\n            A.clear(),\
    \ b.clear();\n            for (auto &&Ab : Abs) A.emplace_back(Ab.first), b.emplace_back(Ab.second);\n\
    \n            shuffle_idx.resize(c.size());\n            std::iota(shuffle_idx.begin(),\
    \ shuffle_idx.end(), 0);\n            std::shuffle(shuffle_idx.begin(), shuffle_idx.end(),\
    \ rng);\n            auto Atmp = A;\n            auto ctmp = c;\n            for\
    \ (unsigned i = 0; i < A.size(); i++) {\n                for (unsigned j = 0;\
    \ j < A[i].size(); j++) A[i][j] = Atmp[i][shuffle_idx[j]];\n            }\n  \
    \          for (unsigned j = 0; j < c.size(); j++) c[j] = ctmp[shuffle_idx[j]];\n\
    \        }\n\n        _initialize(A, b, c);\n        _solve();\n\n        if (Randomize\
    \ and x.size() == c.size()) {\n            auto xtmp = x;\n            for (unsigned\
    \ j = 0; j < c.size(); j++) x[shuffle_idx[j]] = xtmp[j];\n        }\n    }\n \
    \   unsigned nb_iter;\n    bool is_infty;\n    bool infeasible;\n    std::vector<Float>\
    \ x;\n    Float ans;\n\n    static void\n    dual(std::vector<std::vector<Float>>\
    \ &A, std::vector<Float> &b, std::vector<Float> &c) {\n        const int n = b.size(),\
    \ m = c.size();\n        std::vector<std::vector<Float>> At(m, std::vector<Float>(n));\n\
    \        for (int i = 0; i < n; ++i) {\n            for (int j = 0; j < m; ++j)\
    \ At[j][i] = -A[i][j];\n        }\n        A = At;\n        for (int i = 0; i\
    \ < n; ++i) b[i] = -b[i];\n        for (int j = 0; j < m; ++j) c[j] = -c[j];\n\
    \        b.swap(c);\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: combinatorial_opt/simplex.hpp
  requiredBy: []
  timestamp: '2022-10-30 13:35:32+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - combinatorial_opt/test/simplex.multiprecision.test.cpp
  - combinatorial_opt/test/simplex.shortestpath.test.cpp
  - combinatorial_opt/test/simplex.mcf.test.cpp
  - combinatorial_opt/test/simplex.maxflow.test.cpp
  - combinatorial_opt/test/simplex.easy.test.cpp
documentation_of: combinatorial_opt/simplex.hpp
layout: document
title: "Simplex method \uFF08\u5358\u4F53\u6CD5\uFF09"
---

本実装のテクニックの大部分は [kopricky さんの実装](https://kopricky.github.io/code/Computation_Advanced/simplex.html) [2] を参考に書かれたものです．

## 解いてくれる問題

$\mathbf{A} \mathbf{x} \le \mathbf{b}, \ \mathbf{x} \ge \mathbf{0}$ のもと $\mathbf{c}^T \mathbf{x}$ を最大化．

## コードの要点

### initialize() について

解きたい問題に実行可能解が存在するか，また解が有限の値に収まるかは自明ではない．この状況に効率的に対処するために，（カジュアルに $\infty$ が登場して全く厳密な表現ではないが）もとの問題を解く代わりに

$\displaystyle
    \mathbf{M} = \begin{pmatrix}
    -\mathbf{A} & \mathbf{1} & \mathbf{b} \newline\\
    \mathbf{c}^\top & -\infty & 0
    \end{pmatrix}, \quad
    \mathbf{x}' = \begin{pmatrix} \mathbf{x} \newline\\ x_{N + 1} \newline\\ 1
    \end{pmatrix}
$

とおいて， $\mathbf{M} \mathbf{x}'$ の最終要素以外の全ての要素が非負という条件のもと $\mathbf{M} \mathbf{x}'$ の最終要素を最大化する問題を解くことにする．$x_{N + 1}$ の値を十分大きくすることでこの問題には必ず実行可能解が存在することに注意．また本実装では行列を二行拡張し，目的関数の値を上位・下位の二桁の位取りで記述することで無限大を表現している．最終的に $x_{N + 1} > 0$ ならば解は存在しない．

### 基底変数の取り替え

本問題は，$N$ 個の独立変数 $\mathbf{x} = [x_1, \dots, x_N]$ と $M$ 個の従属変数 $\mathbf{y} = [y_1, \dots, y_M], \ y_i = f_i(\mathbf{x})$, $f_i$ はアフィン関数，があって，$\mathbf{x} \ge 0, \ \mathbf{y} \ge 0$ のもとでの何らかのアフィン関数 $g(\mathbf{x})$ の最大化問題とみなせる．このとき，$x_j$ と $y_i$ は対称的な関係にあるから，適宜 $x_j$ と $y_i$ の要素を交換し，別の座標系 $[x_1, \dots, x_{j - 1}, y_i, x_{j + 1}, \dots, x_N]$ に乗り換えてしまっても大丈夫そうである（$N$ 次元 Euclid 空間という多様体に，様々な局所座標が入っているということ）．最大値を求めるのに都合の良い座標系へと次々に乗り換えていく（座標系の原点が，実行可能領域である多面体の特定の頂点に対応する）というのが単体法のやっていることである．

ある時点での独立変数を $\mathbf{x} = [x_1, \dots, x_j, \dots, x_N]$，従属変数を $\mathbf{y} = [y_1, \dots, y_i, \dots, y_M]$ とおいて，$\mathbf{y} = \mathbf{M} \mathbf{x}$ と書けるとする（定数項は適宜ベクトルを拡張して表現したものとする）．
簡単のため，非基底変数 $x_N$ と基底変数 $y_M$ を取り替えるとする．これを行うには，$\mathbf{y}' = [y_1, \dots, y_{M - 1}, x_N], \ \mathbf{x}' = [x_1, \dots, x_{N - 1}, y_M]$ として，$\mathbf{y}' = \mathbf{M}' \mathbf{x}'$ をみたす $\mathbf{M}'$ を求めればよい．これは，もともと $\mathbf{M}$ が

$\displaystyle
\mathbf{M} = 
\begin{pmatrix}
\mathbf{A} & \mathbf{b} \newline\\
\mathbf{c}^\top & d
\end{pmatrix}
$

と書けていたとすると，

$\displaystyle
\mathbf{M}' = 
\begin{pmatrix}
\mathbf{A} - \frac{\mathbf{b}\mathbf{c}^\top}{d} & \frac{\mathbf{b}}{d} \newline\\
-\frac{\mathbf{c}^\top}{d} & \frac{1}{d}
\end{pmatrix}
$

と書き下せる．

### 次の反復で取り替える基底の決定法

#### $x_j$ の決定

- ひとまずその時点で $c_j$ が正となるものを選ぶ．
  - 複数存在する場合は添字番号最小（Bland's rule）
- $\mathbf{c}$ の全要素が $0$ ならこれ以上解が改善しないので終了．

#### $y_i$ の決定

- 最も不等式制約が厳しいものを選ぶ．
  - さもなくば原点が実行可能領域から飛び出るので
  - 複数存在する場合は添字番号最小（Bland's rule）

### ワーストケースの回避

- 指数回のステップを要する恣意的なケースが知られている．
- 特に [1] の p.43 (2.71) で挙げられているケースに関しては，変数・制約の順序をランダムに取り換えることで回避が可能であることを経験的に確認したので，デフォルトでこれを行うことにした．
- ただし，常にシャッフルした方がよいわけではなく，[最小費用流の問題](https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B) ではむしろ遅くなった．

## 問題例

- [AtCoder jag2018summer-day3 H - Enlarge Circles](https://atcoder.jp/contests/jag2018summer-day3/tasks/jag2018summer_day3_h)
- [SRM 694 Div.1 900 SRMDiv0Easy](https://community.topcoder.com/tc?module=ProblemDetail&rd=16766&pm=14319)
  - $N - 1$ 個の等式制約（$2(N - 1)$ 個の不等式制約に翻訳）と $Q$ 個の不等式制約下での $Q$ 変数 LP として本ソルバに与える
  - System Test Passed (34 ms)

## Reference

- [1] 梅谷「しっかり学ぶ数理最適化」講談社 2020.
  - 単体法の導出にあたって新たに $M$ 個のスラック変数を導入していて，このライブラリのアルゴリズムとは少々（少なくとも見た目において）違う（あまりちゃんと読んでいないが，確かめると実は同じかもしれない）．
- [2] https://kopricky.github.io/code/Computation_Advanced/simplex.html
