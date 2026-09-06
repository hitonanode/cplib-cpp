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
    - https://math.mit.edu/~goemans/18438F09/lec13.pdf
  bundledCode: "#line 2 \"combinatorial_opt/matroid_union.hpp\"\n#include <cassert>\n\
    #include <utility>\n#include <vector>\n\n// CUT begin\n// Union matroid augment\n\
    // From I1, I2 (independent, exclusive),\n// - find I1' and I2' s.t. |I1'| + |I2'|\
    \ = |I1| + |I2| + 1 and return true\n// - or return false\n// Complexity: O(n(c\
    \ + r)) (r: current rank, c: circuit query)\n// Algorithm based on https://math.mit.edu/~goemans/18438F09/lec13.pdf\n\
    // Verified: CodeChef HAMEL\ntemplate <class M1, class M2, class State1, class\
    \ State2, class T = int>\nbool augment_union_matroid(M1 &matroid1, M2 &matroid2,\
    \ State1 &I1, State2 &I2,\n                           const std::vector<T> &weights)\
    \ {\n    const int M = matroid1.size();\n    const int gt = M;\n    std::vector<std::vector<int>>\
    \ rev(M + 1);\n    std::vector<int> color(M, -1);\n    matroid1.set(I1);\n   \
    \ matroid2.set(I2);\n    for (int e = 0; e < M; e++) {\n        if (!I1[e]) {\n\
    \            auto c = matroid1.circuit(e);\n            if (c.empty()) rev[gt].push_back(e),\
    \ color[e] = 0;\n            for (int f : c) {\n                if (f != e) rev[f].push_back(e);\n\
    \            }\n        }\n        if (!I2[e]) {\n            auto c = matroid2.circuit(e);\n\
    \            if (c.empty()) rev[gt].push_back(e), color[e] = 1;\n            for\
    \ (int f : c) {\n                if (f != e) rev[f].push_back(e);\n          \
    \  }\n        }\n    }\n    // Find a shortest exchange path to gt from every\
    \ augmentable element.\n    std::vector<int> next(M + 1, -1), q{gt};\n    next[gt]\
    \ = gt;\n    for (int i = 0; i < int(q.size()); ++i) {\n        for (int e : rev[q[i]])\
    \ {\n            if (next[e] >= 0) continue;\n            next[e] = q[i];\n  \
    \          q.push_back(e);\n        }\n    }\n\n    // Minimize the added weight\
    \ independently of the number of exchanges.\n    int start = -1;\n    for (int\
    \ e = 0; e < M; ++e) {\n        if (I1[e] or I2[e] or next[e] < 0) continue;\n\
    \        if (start < 0 or (!weights.empty() and weights[e] < weights[start]))\
    \ start = e;\n    }\n    if (start < 0) return false;\n\n    std::vector<int>\
    \ aug_path;\n    for (int e = start; e != gt; e = next[e]) aug_path.push_back(e);\n\
    \    int c0 = -1;\n    if (I1[aug_path.back()]) c0 = 1;\n    if (I2[aug_path.back()])\
    \ c0 = 0;\n    if (c0 < 0) c0 = color[aug_path.back()];\n    for (int k = int(aug_path.size())\
    \ - 1; k >= 0; --k) {\n        int e = aug_path[k];\n        (c0 ? I2 : I1)[e]\
    \ = 1, (c0 ? I1 : I2)[e] = 0;\n        c0 ^= 1;\n    }\n    return true;\n}\n\n\
    // (Min weight) matroid partition\ntemplate <class M1, class M2, class T = int>\n\
    std::pair<std::vector<bool>, std::vector<bool>>\nMinWeightMaxIndepSetInUnionMatroid(M1\
    \ mat1, M2 mat2, const std::vector<T> &weights = {}) {\n    using State = std::vector<bool>;\n\
    \    assert(mat1.size() == mat2.size());\n    const int M = mat1.size();\n   \
    \ State I1(M), I2(M);\n    while (augment_union_matroid(mat1, mat2, I1, I2, weights))\
    \ {}\n    return {I1, I2};\n}\n"
  code: "#pragma once\n#include <cassert>\n#include <utility>\n#include <vector>\n\
    \n// CUT begin\n// Union matroid augment\n// From I1, I2 (independent, exclusive),\n\
    // - find I1' and I2' s.t. |I1'| + |I2'| = |I1| + |I2| + 1 and return true\n//\
    \ - or return false\n// Complexity: O(n(c + r)) (r: current rank, c: circuit query)\n\
    // Algorithm based on https://math.mit.edu/~goemans/18438F09/lec13.pdf\n// Verified:\
    \ CodeChef HAMEL\ntemplate <class M1, class M2, class State1, class State2, class\
    \ T = int>\nbool augment_union_matroid(M1 &matroid1, M2 &matroid2, State1 &I1,\
    \ State2 &I2,\n                           const std::vector<T> &weights) {\n \
    \   const int M = matroid1.size();\n    const int gt = M;\n    std::vector<std::vector<int>>\
    \ rev(M + 1);\n    std::vector<int> color(M, -1);\n    matroid1.set(I1);\n   \
    \ matroid2.set(I2);\n    for (int e = 0; e < M; e++) {\n        if (!I1[e]) {\n\
    \            auto c = matroid1.circuit(e);\n            if (c.empty()) rev[gt].push_back(e),\
    \ color[e] = 0;\n            for (int f : c) {\n                if (f != e) rev[f].push_back(e);\n\
    \            }\n        }\n        if (!I2[e]) {\n            auto c = matroid2.circuit(e);\n\
    \            if (c.empty()) rev[gt].push_back(e), color[e] = 1;\n            for\
    \ (int f : c) {\n                if (f != e) rev[f].push_back(e);\n          \
    \  }\n        }\n    }\n    // Find a shortest exchange path to gt from every\
    \ augmentable element.\n    std::vector<int> next(M + 1, -1), q{gt};\n    next[gt]\
    \ = gt;\n    for (int i = 0; i < int(q.size()); ++i) {\n        for (int e : rev[q[i]])\
    \ {\n            if (next[e] >= 0) continue;\n            next[e] = q[i];\n  \
    \          q.push_back(e);\n        }\n    }\n\n    // Minimize the added weight\
    \ independently of the number of exchanges.\n    int start = -1;\n    for (int\
    \ e = 0; e < M; ++e) {\n        if (I1[e] or I2[e] or next[e] < 0) continue;\n\
    \        if (start < 0 or (!weights.empty() and weights[e] < weights[start]))\
    \ start = e;\n    }\n    if (start < 0) return false;\n\n    std::vector<int>\
    \ aug_path;\n    for (int e = start; e != gt; e = next[e]) aug_path.push_back(e);\n\
    \    int c0 = -1;\n    if (I1[aug_path.back()]) c0 = 1;\n    if (I2[aug_path.back()])\
    \ c0 = 0;\n    if (c0 < 0) c0 = color[aug_path.back()];\n    for (int k = int(aug_path.size())\
    \ - 1; k >= 0; --k) {\n        int e = aug_path[k];\n        (c0 ? I2 : I1)[e]\
    \ = 1, (c0 ? I1 : I2)[e] = 0;\n        c0 ^= 1;\n    }\n    return true;\n}\n\n\
    // (Min weight) matroid partition\ntemplate <class M1, class M2, class T = int>\n\
    std::pair<std::vector<bool>, std::vector<bool>>\nMinWeightMaxIndepSetInUnionMatroid(M1\
    \ mat1, M2 mat2, const std::vector<T> &weights = {}) {\n    using State = std::vector<bool>;\n\
    \    assert(mat1.size() == mat2.size());\n    const int M = mat1.size();\n   \
    \ State I1(M), I2(M);\n    while (augment_union_matroid(mat1, mat2, I1, I2, weights))\
    \ {}\n    return {I1, I2};\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: combinatorial_opt/matroid_union.hpp
  requiredBy: []
  timestamp: '2026-09-06 11:24:08+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: combinatorial_opt/matroid_union.hpp
layout: document
title: "Matroid union \uFF08\u30DE\u30C8\u30ED\u30A4\u30C9\u306E\u5408\u4F75\uFF09"
---

2つのマトロイド $M\_{1} = (E, \mathcal{I}\_{1}), M_{2} = (E, \mathcal{I}\_{2})$, $\mathcal{I}\_{1}$ に関して独立な集合 $I_1$, $\mathcal{I}\_{2}$ に関して独立な集合 $I\_2$ で $I\_1 \cap I\_2 = \emptyset$ を満たすものが与えられたとき，$I'\_1 + I'\_2 = I\_1 + I\_2 + \\{ e \\}$ を満たす新たな排反な独立集合 $I'\_1, I'\_2$ を見つけるアルゴリズム．特に重み最小の $e$ から貪欲に追加を試すことで，「合併したマトロイド」の最小重みサイズ $k$ 独立集合が $k = 1, 2, \dots$ について順次求められる．

これを応用すると，与えられた重み付き無向グラフについて，辺素な二つの全域木であって重みの総和が最小なものを見つけることも可能．

## アルゴリズムの概要

$\|E\| = n$ として，各要素 $e \in E$ に終点 $t$ を加えた $n + 1$ 頂点の有向グラフに次の要領で辺を張る．すべての辺は重みなしとする．

- $e \notin I\_j$ かつ $I\_j + \\{e \\}$ が $M\_j$ における独立集合のとき，$e \rightarrow t$ を張る．$(j = 1, 2)$
- $e \notin I\_j$ かつ $I\_j + \\{e \\}$ が $M\_j$ における従属集合のとき，サーキットに含まれる $e$ 以外の各 $f$ について $e \rightarrow f$ を張る．$(j = 1, 2)$

辺を逆向きにしたグラフで $t$ から BFS を行い，各要素から $t$ への最短路を求める．$e \notin I\_1 \cup I\_2$ で $t$ に到達可能な要素のうち，重み $w(e)$ が最小のものを追加する．このとき重みと交換回数は足し合わせず，まず追加要素の重みを最小化し，その要素からの交換回数を最小化する．該当する要素がなければ $I\_1 \cup I\_2$ は既に合併したマトロイド上の最大独立集合である．

選んだ $e$ から $t$ への最短路上で，要素を $I\_1$ と $I\_2$ の間で移動させる．最短路を使うことで独立性が保たれ，合併集合には $e$ だけが新たに加わる．重みを省略した場合は，追加可能ないずれかの要素を選ぶ．

本コードには実装されていないが，3 個以上のマトロイドの合併に対しても同様のアルゴリズムが適用可能である．

## 使用方法

- `bool augment_union_matroid(matroid1, matroid2, I1, I2, weight)` 関数は，上述の追加可能な重み最小要素 $e$ を見つけ，$I\_1$ および $I\_2$ を追加後の状態に更新する．要素の追加が行われたならば `true` を，そうでなければ `false` を返す．
- `pair<vector<bool>, vector<bool>> MinWeightMaxIndepSetInUnionMatroid(matroid1, matroid2, weight)` 関数は，`augment_union_matroid()` 関数を繰り返し適用することで，2つのマトロイドを合併したマトロイドにおける（重み最小な）最大独立集合を構成する．

## 問題例

- [Hamel Paths \| CodeChef](https://www.codechef.com/problems/HAMEL) 無向グラフから2つの全域木を作る．
- [SRM 685 Div.1 450 FoxAirline2](https://community.topcoder.com/stat?c=problem_statement&pm=14194&rd=16689) 無向グラフから2つの全域木を作れるか判定する．
- [2018 TCO Round 3A 1000 ColoringEdgesDiv1](https://community.topcoder.com/stat?c=problem_statement&pm=14909&rd=17198) 各頂点の次数が3の単純無向グラフ（$n \le 1000, m = 3n/2$）の辺を2つの全域森に分割する方法を構成する．最初に乱択で辺を追加して全域森2つの初期解を構成し，その後全ての辺を割り当て終えるまで `augment_union_matroid()` を真面目に使用するというヒューリスティックによって [最大 200 ms 程度の実行時間で用意された全ケースに通る](https://vjudge.net/solution/32788901)（ただし，後述するように無向グラフの全域森への分割にはより高速なアルゴリズムが存在する：`edge_disjoint_min_spanning_forests.hpp` 参照）．

## 参考文献・リンク

- [1] J. Edmonds, "Minimum partition of a matroid into independent subsets,"
  J. Res. Nat. Bur. Standards Sect. B 69, 67-72, 1965.
- [18.438: Advanced Combinatorial Optimization, Fall 2009](http://www-math.mit.edu/~goemans/18438F09/18438.html): [lec13.pdf](http://www-math.mit.edu/~goemans/18438F09/lec13.pdf)
- [Matroid partitioning - Wikipedia](https://en.wikipedia.org/wiki/Matroid_partitioning#cite_ref-e65_3-0)
- [離散最適化基礎論 (2015年度後学期) 組合せ最適化におけるマトロイドの役割](http://dopal.cs.uec.ac.jp/okamotoy/lect/2015/matroid/): [handout12.pdf](http://dopal.cs.uec.ac.jp/okamotoy/lect/2015/matroid/handout12.pdf)
- [AlgoWiki - Matroid](https://wiki.algo.is/Matroid) 問題へのリンクが豊富．
- [様々な全域木問題](https://www.slideshare.net/tmaehara/ss-17402143) 特に無向グラフのの辺素な全域森への分割を考える場合，より高速なアルゴリズムが存在する．
