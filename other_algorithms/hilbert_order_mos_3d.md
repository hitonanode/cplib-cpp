---
title: 3D points to Hilbert order, used for Mo with update （3 次元空間の点の Hilbert order への変換， Mo's algorithm （「時空間 Mo」）への応用）
documentation_of: ./hilbert_order_mos_3d.hpp
---

点 $(x, y, z)$ の 3 次元のヒルベルト曲線上の端点からの距離を計算する．

コンテストでの応用上重要な特徴として，座標の値が $n$ 以下の $q$ 個の点列をこの値をキーにソートする（ヒルベルトソート）ことで，パスのマンハッタン距離の総和が $O(n q^{2/3})$ で抑えられる．

Mo with update などの用途でクエリ処理順序の決定に利用可能で，例えば更新ありの Mo's algorithm は $O(n q^{2/3})$ で解けることになる．

## 使用方法

```cpp
unsigned x, y, z;
unsigned long long h = encode_hilbert_order_3d<unsigned long long>(x, y, z);
```

### Mo with update への応用

長さ $n$ の列と $q$ 個のクエリが与えられて， $x, y$ が区間の両端 $l, r$ に対応し， $z$ が更新時刻 $t$ に対応するタイプの問題は，特に以下のようなコードで処理できる．なおこの手の出題ではジャッジが $O(nq)$ と $O(n q^{2/3})$ を区別する必要があるため，定数倍の実装には気をつけた方がよい．

#### クエリ情報・更新情報取得

```cpp
int tick = 0;
vector<tuple<unsigned long long, int, int, int, int>> queries;
vector<tuple<int, int, int>> updates;

for (int q = 0; q < Q; ++q) {
    int tp, l, r, p, x;
    cin >> tp;
    if (tp == 1) {
        cin >> l >> r;
        --l;
        const int nq = queries.size();
        queries.emplace_back(encode_hilbert_order_3d<unsigned long long>(tick, l, r), l, r, tick, nq);
    } else {
        cin >> p >> x;
        --p;
        updates.emplace_back(p, A.at(p), x);
        A.at(p) = x;
        ++tick;
    }
}
```

#### 解取得処理の実行

```cpp
sort(queries.begin(), queries.end());

int l = 0, r = 0;

vector<int> vcnt(zs.size());  // 区間に現れる各値の計数
vector<int> vhist(N + 2);  // 配列 vcnt の頻度分布
vhist.at(0) = vcnt.size();

auto add_val = [&](int v) -> void {
    const int cnt = vcnt[v];
    vcnt[v]++;
    vhist[cnt]--;
    vhist[cnt + 1]++;
};

auto remove_val = [&](int v) -> void {
    --vcnt[v];
    const int cnt = vcnt[v];
    vhist[cnt]++;
    vhist[cnt + 1]--;
};

vector<int> ret(queries.size(), -1);

for (const auto &[_, ltgt, rtgt, ticktgt, nq] : queries) {
    while (tick < ticktgt) {
        auto [p, oldval, newval] = updates[tick];
        A[p] = newval;
        if (l <= p and p < r) {
            remove_val(oldval);
            add_val(newval);
        }
        ++tick;
    }

    while (tick > ticktgt) {
        --tick;
        auto [p, oldval, newval] = updates[tick];
        A[p] = oldval;
        if (l <= p and p < r) {
            remove_val(newval);
            add_val(oldval);
        }
    }

    while (ltgt < l) add_val(A[--l]);

    while (r < rtgt) add_val(A[r++]);

    while (l < ltgt) remove_val(A[l++]);

    while (rtgt < r) remove_val(A[--r]);

    /* solve subproblem
    ret.at(nq) = ***;
    */
}
```

## 問題例

列の要素更新ありの Mo's algorithm が必要な問題例を以下に挙げる．

- [Codeforces Round 466 (Div. 2) F. Machine Learning - Codeforces](https://codeforces.com/contest/940/problem/F)
- [Educational Codeforces Round 103 (Rated for Div. 2) G. Minimum Difference - Codeforces](https://codeforces.com/contest/1476/problem/G)
- [Primitive Queries \| CodeChef](https://www.codechef.com/problems/DISTNUM3)
  - 木のパスクエリ処理・要素更新ありの Mo's algorithm で解ける．

## Links

- [An alternative sorting order for Mo's algorithm - Codeforces](https://codeforces.com/blog/entry/61203)
- [Mo's algorithm - アルゴリズムとデータ構造大全](https://take44444.github.io/Algorithm-Book/range/mo/main.html)
- [[2308.05673] Algorithms for Encoding and Decoding 3D Hilbert Orderings](https://arxiv.org/abs/2308.05673)
