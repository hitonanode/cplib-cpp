---
title: マトロイドクラスのインターフェースの説明
documentation_of: ./matroid_example.hpp
---

本リポジトリで一般的なマトロイドに対して適用されるアルゴリズムは，以下のようなメソッドを持つマトロイドクラスを前提に動作する．

- `int size() const` 台集合の要素数を返す関数．
- `template <class State = std::vector<bool>> void set(State I);` 現在の部分集合を独立集合 $I$ で更新する．
- `std::vector<Element> circuit(Element e) const;` （$I$ が独立で）$I + e$ が従属集合である場合，サーキットを返す． $I + e$ も独立の場合，空ベクトルを返す．
