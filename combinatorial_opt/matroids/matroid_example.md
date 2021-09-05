---
title: マトロイドクラスのインターフェースの説明
documentation_of: ./matroid_example.hpp
---

本リポジトリで一般的なマトロイドに対して適用されるアルゴリズムは，以下のようなメソッドを持つマトロイドクラスを前提に動作する．

- `int size() const` 台集合の要素数を返す関数．
- `template <class State = std::vector<bool>> void set(const State &I);` 現在の部分集合を独立集合 $I$ で更新する．
- `std::vector<Element> circuit(Element e) const;` （$I$ が独立で）$I + e$ が従属集合である場合，サーキットを返す． $I + e$ も独立の場合，空ベクトルを返す．マトロイド交差アルゴリズムなど，体感的にはサーキットクエリの重さが時間計算量にダイレクトに影響するため，`set()` による前処理と `circuit()` による取得の両者の効率化が重要である．
