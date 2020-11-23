---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - http://web.cs.unlv.edu/larmore/Courses/CSC477/monge.pdf>
    - https://codeforces.com/contest/1423/submission/98368491>
    - https://topcoder-g-hatena-ne-jp.jag-icpc.org/spaghetti_source/20120923/1348327542.html>
  bundledCode: "#line 2 \"other_algorithms/smawk.hpp\"\n#include <functional>\n#include\
    \ <numeric>\n#include <unordered_map>\n#include <utility>\n#include <vector>\n\
    \n// CUT begin\n// SMAWK: finding minima of totally monotone function f(i, j)\
    \ (0 <= i < N, 0 <= j < M) for each i\n// Constraints: every submatrix of f(i,\
    \ j) is monotone.\n// Complexity: O(N + M)\n// Option: `Memorization`: Memorize\
    \ all query results using hashmaps, effective when each query requires heavy complexity\n\
    // Rererence: <https://topcoder-g-hatena-ne-jp.jag-icpc.org/spaghetti_source/20120923/1348327542.html>\n\
    //            <http://web.cs.unlv.edu/larmore/Courses/CSC477/monge.pdf>\n// Verify:\
    \ <https://codeforces.com/contest/1423/submission/98368491>\ntemplate <typename\
    \ T, bool Memorization> struct SMAWK {\n    std::vector<std::pair<int, T>> minima;\n\
    \    std::function<T(int, int)> oracle;\n    std::vector<std::unordered_map<int,\
    \ T>> memo;\n    T _query(int i, int j) {\n        if (Memorization)\n       \
    \     return memo[i].count(j) ? memo[i][j] : (memo[i][j] = oracle(i, j));\n  \
    \      else\n            return oracle(i, j);\n    }\n\n    void _smawk_rec(const\
    \ std::vector<int> &js, int ib, int ie, int id) {\n        if (ib > ie) return;\n\
    \        std::vector<int> js2;\n        int i = ib;\n        for (auto j : js)\
    \ {\n            while (!js2.empty() and _query(i, js2.back()) >= _query(i, j))\
    \ js2.pop_back(), i -= id;\n            if (int(js2.size()) != (ie - ib) / id)\
    \ js2.push_back(j), i += id;\n        }\n        _smawk_rec(js2, ib + id, ie,\
    \ id * 2);\n\n        for (int i = ib, q = 0; i <= ie; i += id * 2) {\n      \
    \      int jt = (i + id <= ie ? minima[i + id].first : js.back());\n         \
    \   T fm = 0;\n            bool init = true;\n            for (; q < int(js.size());\
    \ ++q) {\n                T fq = _query(i, js[q]);\n                if (init or\
    \ fm > fq) fm = fq, minima[i] = std::make_pair(js[q], fq);\n                init\
    \ = false;\n                if (js[q] == jt) break;\n            }\n        }\n\
    \    }\n    SMAWK(int N, int M, std::function<T(int i, int j)> oracle_) : minima(N),\
    \ oracle(oracle_) {\n        if (Memorization) memo.resize(N);\n        std::vector<int>\
    \ js(M);\n        std::iota(js.begin(), js.end(), 0);\n        _smawk_rec(js,\
    \ 0, N - 1, 1);\n    }\n};\n"
  code: "#pragma once\n#include <functional>\n#include <numeric>\n#include <unordered_map>\n\
    #include <utility>\n#include <vector>\n\n// CUT begin\n// SMAWK: finding minima\
    \ of totally monotone function f(i, j) (0 <= i < N, 0 <= j < M) for each i\n//\
    \ Constraints: every submatrix of f(i, j) is monotone.\n// Complexity: O(N + M)\n\
    // Option: `Memorization`: Memorize all query results using hashmaps, effective\
    \ when each query requires heavy complexity\n// Rererence: <https://topcoder-g-hatena-ne-jp.jag-icpc.org/spaghetti_source/20120923/1348327542.html>\n\
    //            <http://web.cs.unlv.edu/larmore/Courses/CSC477/monge.pdf>\n// Verify:\
    \ <https://codeforces.com/contest/1423/submission/98368491>\ntemplate <typename\
    \ T, bool Memorization> struct SMAWK {\n    std::vector<std::pair<int, T>> minima;\n\
    \    std::function<T(int, int)> oracle;\n    std::vector<std::unordered_map<int,\
    \ T>> memo;\n    T _query(int i, int j) {\n        if (Memorization)\n       \
    \     return memo[i].count(j) ? memo[i][j] : (memo[i][j] = oracle(i, j));\n  \
    \      else\n            return oracle(i, j);\n    }\n\n    void _smawk_rec(const\
    \ std::vector<int> &js, int ib, int ie, int id) {\n        if (ib > ie) return;\n\
    \        std::vector<int> js2;\n        int i = ib;\n        for (auto j : js)\
    \ {\n            while (!js2.empty() and _query(i, js2.back()) >= _query(i, j))\
    \ js2.pop_back(), i -= id;\n            if (int(js2.size()) != (ie - ib) / id)\
    \ js2.push_back(j), i += id;\n        }\n        _smawk_rec(js2, ib + id, ie,\
    \ id * 2);\n\n        for (int i = ib, q = 0; i <= ie; i += id * 2) {\n      \
    \      int jt = (i + id <= ie ? minima[i + id].first : js.back());\n         \
    \   T fm = 0;\n            bool init = true;\n            for (; q < int(js.size());\
    \ ++q) {\n                T fq = _query(i, js[q]);\n                if (init or\
    \ fm > fq) fm = fq, minima[i] = std::make_pair(js[q], fq);\n                init\
    \ = false;\n                if (js[q] == jt) break;\n            }\n        }\n\
    \    }\n    SMAWK(int N, int M, std::function<T(int i, int j)> oracle_) : minima(N),\
    \ oracle(oracle_) {\n        if (Memorization) memo.resize(N);\n        std::vector<int>\
    \ js(M);\n        std::iota(js.begin(), js.end(), 0);\n        _smawk_rec(js,\
    \ 0, N - 1, 1);\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: other_algorithms/smawk.hpp
  requiredBy: []
  timestamp: '2020-11-23 12:20:49+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: other_algorithms/smawk.hpp
layout: document
redirect_from:
- /library/other_algorithms/smawk.hpp
- /library/other_algorithms/smawk.hpp.html
title: other_algorithms/smawk.hpp
---
