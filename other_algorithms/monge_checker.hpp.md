---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://hackmd.io/@tatyam-prime/monge1
  bundledCode: "#line 2 \"other_algorithms/monge_checker.hpp\"\n\n#include <sstream>\n\
    #include <string>\n\n// Check whether cost(i, j) is Monge or not\n// Complexity:\
    \ O(nm)\n// https://hackmd.io/@tatyam-prime/monge1\ntemplate <bool only_upper\
    \ = false>\nstd::string check_matrix_monge(auto cost, auto inf, int n, int m)\
    \ {\n    if (m < 0) m = n;\n\n    auto Detect = [n, m, inf](auto f) -> std::tuple<bool,\
    \ int, int> {\n        for (int i = 0; i + 1 < n; ++i) {\n            for (int\
    \ j = only_upper ? (i + 2) : 0; j + 1 < m; ++j) {\n                const auto\
    \ f00 = f(i, j), f01 = f(i, j + 1), f10 = f(i + 1, j),\n                     \
    \      f11 = f(i + 1, j + 1);\n                if (f00 >= inf or f01 >= inf) continue;\n\
    \                if (f00 + f11 > f10 + f01) { return {false, i, j}; }\n      \
    \      }\n        }\n        return {true, -1, -1};\n    };\n\n    if (auto [is_monge,\
    \ i, j] = Detect(cost); is_monge) {\n        return \"Monge OK\";\n    } else\
    \ if (auto [is_anti_monge, ai, aj] = Detect([&cost, inf](int i, int j) {\n   \
    \                auto ret = cost(i, j);\n                   return ret == inf\
    \ ? inf : -ret;\n               });\n               is_anti_monge) {\n       \
    \ return \"Not Monge, but Anti-Monge OK\";\n    } else {\n        std::stringstream\
    \ ret;\n        ret << \"Not Monge!\\n\";\n        ret << \"    j=\" << std::to_string(j)\
    \ << \"   j=\" << std::to_string(j + 1) << \"\\n\";\n        ret << \"i=\" <<\
    \ std::to_string(i) << \" \" << cost(i, j) << \" \" << cost(i, j + 1) << \"\\\
    n\";\n        ret << \"i=\" << std::to_string(i + 1) << \" \" << cost(i + 1, j)\
    \ << \" \" << cost(i + 1, j + 1);\n        return ret.str();\n    }\n}\n\n// Check\
    \ whether graph weight is Monge or not\n// Complexity: O(n^2)\nstd::string check_dag_monge(auto\
    \ cost, auto inf, int n) {\n    return check_matrix_monge<true>(cost, inf, n,\
    \ n);\n}\n"
  code: "#pragma once\n\n#include <sstream>\n#include <string>\n\n// Check whether\
    \ cost(i, j) is Monge or not\n// Complexity: O(nm)\n// https://hackmd.io/@tatyam-prime/monge1\n\
    template <bool only_upper = false>\nstd::string check_matrix_monge(auto cost,\
    \ auto inf, int n, int m) {\n    if (m < 0) m = n;\n\n    auto Detect = [n, m,\
    \ inf](auto f) -> std::tuple<bool, int, int> {\n        for (int i = 0; i + 1\
    \ < n; ++i) {\n            for (int j = only_upper ? (i + 2) : 0; j + 1 < m; ++j)\
    \ {\n                const auto f00 = f(i, j), f01 = f(i, j + 1), f10 = f(i +\
    \ 1, j),\n                           f11 = f(i + 1, j + 1);\n                if\
    \ (f00 >= inf or f01 >= inf) continue;\n                if (f00 + f11 > f10 +\
    \ f01) { return {false, i, j}; }\n            }\n        }\n        return {true,\
    \ -1, -1};\n    };\n\n    if (auto [is_monge, i, j] = Detect(cost); is_monge)\
    \ {\n        return \"Monge OK\";\n    } else if (auto [is_anti_monge, ai, aj]\
    \ = Detect([&cost, inf](int i, int j) {\n                   auto ret = cost(i,\
    \ j);\n                   return ret == inf ? inf : -ret;\n               });\n\
    \               is_anti_monge) {\n        return \"Not Monge, but Anti-Monge OK\"\
    ;\n    } else {\n        std::stringstream ret;\n        ret << \"Not Monge!\\\
    n\";\n        ret << \"    j=\" << std::to_string(j) << \"   j=\" << std::to_string(j\
    \ + 1) << \"\\n\";\n        ret << \"i=\" << std::to_string(i) << \" \" << cost(i,\
    \ j) << \" \" << cost(i, j + 1) << \"\\n\";\n        ret << \"i=\" << std::to_string(i\
    \ + 1) << \" \" << cost(i + 1, j) << \" \" << cost(i + 1, j + 1);\n        return\
    \ ret.str();\n    }\n}\n\n// Check whether graph weight is Monge or not\n// Complexity:\
    \ O(n^2)\nstd::string check_dag_monge(auto cost, auto inf, int n) {\n    return\
    \ check_matrix_monge<true>(cost, inf, n, n);\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: other_algorithms/monge_checker.hpp
  requiredBy: []
  timestamp: '2025-07-23 23:05:34+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: other_algorithms/monge_checker.hpp
layout: document
title: Monge checker
---

与えられた一般の $n \times m$ 行列や $n$ 頂点 DAG の重み行列の Monge 性および Anti-Monge 性を確認し，以下の結果を出力する．

- Monge であった場合， `Monge OK` と出力
- Monge ではないが anti-Monge であった場合， `Not Monge, but Anti-Monge OK` と出力
- Monge でも anti-Monge でもない場合， `Not Monge!` と出力し，続けて Monge 性に反する $2 \times 2$ 小行列を出力

計算量は $O(nm)$ や $O(n^2)$ なので，ジャッジへの提出にこの関数の実行を含めると TLE となりうるので注意．

## 使用方法

行列を `std::vector<std::vector<long long>>` 等の形で直接与えるのではなく， `int` 2 つを引数として重みを返す関数 `cost(int, int)` を引数として与えればよい．

### $n$ 頂点 DAG の辺重み関数の Monge 性判定

```cpp
int n;  // 頂点: 0, 1, ..., (n - 1)
using T = long long;
T INF;
auto cost = [&](int i, int j) -> T {
    // Return weight of directed edge i->j, or INF if the edge does not exist.
};

cerr << check_dag_monge(cost, INF, n) << endl;
```

## Monge 性の確認方法

隣接する 2 行と 2 列の要素からなる全ての $2 \times 2$ 小行列に対する Monge 性を確認すればよい [1]．

## Links

- [1] [[Monge まとめ①] Monge 性とは？ - HackMD](https://hackmd.io/@tatyam-prime/monge1)
