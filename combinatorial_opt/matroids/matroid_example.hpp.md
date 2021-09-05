---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"combinatorial_opt/matroids/matroid_example.hpp\"\n#include\
    \ <vector>\n\nstruct MatroidExample {\n    using Element = int;\n\n    int size()\
    \ const; // # of elements of set we consider\n\n    // If I is NOT independent\
    \ or e \\in I, undefined.\n    // If I is independent and I + {e} is not, return\
    \ elements of the circuit.\n    // If I + {e} is also independent, return empty\
    \ vector.\n    template <class State = std::vector<bool>> void set(State I);\n\
    \    std::vector<Element> circuit(Element e) const;\n};\n"
  code: "#pragma once\n#include <vector>\n\nstruct MatroidExample {\n    using Element\
    \ = int;\n\n    int size() const; // # of elements of set we consider\n\n    //\
    \ If I is NOT independent or e \\in I, undefined.\n    // If I is independent\
    \ and I + {e} is not, return elements of the circuit.\n    // If I + {e} is also\
    \ independent, return empty vector.\n    template <class State = std::vector<bool>>\
    \ void set(State I);\n    std::vector<Element> circuit(Element e) const;\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: combinatorial_opt/matroids/matroid_example.hpp
  requiredBy: []
  timestamp: '2021-09-05 18:41:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: combinatorial_opt/matroids/matroid_example.hpp
layout: document
title: "\u30DE\u30C8\u30ED\u30A4\u30C9\u30AF\u30E9\u30B9\u306E\u30A4\u30F3\u30BF\u30FC\
  \u30D5\u30A7\u30FC\u30B9\u306E\u8AAC\u660E"
---

本リポジトリで一般的なマトロイドに対して適用されるアルゴリズムは，以下のようなメソッドを持つマトロイドクラスを前提に動作する．

- `int size() const` 台集合の要素数を返す関数．
- `template <class State = std::vector<bool>> void set(const State &I);` 現在の部分集合を独立集合 $I$ で更新する．
- `std::vector<Element> circuit(Element e) const;` （$I$ が独立で）$I + e$ が従属集合である場合，サーキットを返す． $I + e$ も独立の場合，空ベクトルを返す．マトロイド交差アルゴリズムなど，体感的にはサーキットクエリの重さが時間計算量にダイレクトに影響するため，`set()` による前処理と `circuit()` による取得の両者の効率化が重要である．
