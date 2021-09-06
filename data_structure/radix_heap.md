---
title: Radix heap （基数ヒープ）
documentation_of: ./radix_heap.hpp
---

`std::priroity_queue` と同様の機能を提供するヒープだが，「最後に取り出した値以上の値しか追加できない」という制約があり，また本実装では符号なし整数型に使用が限られる．ヒープがキーとして持つ整数型のビット数を $D$ とおくと，一度追加した要素に対しては演算が高々 $O(D)$ 回しか発生しないため，クエリ毎の計算量は償却 $O(D)$ で，定数倍にも優れているとされる．Dijkstra 法や各種フローアルゴリズムの定数倍高速化などに活用できる．

## 使用方法

```cpp
radix_heap<unsigned, string> pq, pq2;

pq.push(5, "a");
pq.emplace(1, "b");
cout << pq.top_key() << ' ' << pq.top_label() << '\n'; // 1 b
cout << pq.top().first << ' ' << pq.top().second << '\n'; // 1 b

pq.push(2, "c");
pq.push(3, "d");

cout << "size=" << pq.size() << '\n'; // size=4

while (pq.size()) {
    cout << pq.top_key() << ' ' << pq.top_label() << '\n';
    // 1 b
    // 2 c
    // 3 d
    // 5 a
    pq.pop();
}

pq.push(50, "heap1");
pq2.push(100, "heap2");
pq.swap(pq2);
cout << pq.top_label() << ' ' << pq2.top_label() << '\n'; // heap2 heap1
```

## 問題例

- [No.1288 yuki collection - yukicoder](https://yukicoder.me/problems/no/1288) 最小費用流の計算中に使用するヒープを `std::priority_queue` から `radix_heap` に変更することで定数倍が改善される（[2,261 ms](https://yukicoder.me/submissions/696945) → [886 ms](https://yukicoder.me/submissions/696946)）．
## リンク

- [1] R. K. Ahuja et al., "Faster algorithms for the shortest path problem,"
      Journal of the ACM 37(2), 213-223, 1990.
- [iwiwi/radix-heap: An implementation of radix heap](https://github.com/iwiwi/radix-heap) 本コードはこちらを参考に実装された．こちらは符号付整数型や浮動小数点数型にも対応する．
- [色々なダイクストラ高速化](https://www.slideshare.net/yosupo/ss-46612984)
