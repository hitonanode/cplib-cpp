# Algorithms for strings (or general sequences)

## Contents

- `manacher.hpp` Manacherのアルゴリズム（各位置を中心とする最長回文長の線形時間構築）
- `mp_algotirhm` MP法（Morris-Pratt）

## 各アルゴリズム概要

### Manacherのアルゴリズム

各要素を中心とする最長の回文の長さを格納したvectorを返す．

- <https://snuke.hatenablog.com/entry/2014/12/02/235837>
- イメージ： [5 1 2 1 5 3 4 3] -> [1, 1, 3, 1, 1, 1, 2, 1]

すなわち奇数長の回文しか検出しないので，偶数長の回文も見つけるには一つおきにダミーの値を入れること．

### MP法

長さNの入力に対し，`i`文字目までの部分文字列（1-indexed）の接頭辞と接尾辞の最長の一致長を全ての`i`に対して線形時間で構築．
