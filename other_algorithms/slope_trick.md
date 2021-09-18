---
title: Slope trick （区分線形凸関数に関する特定の更新を高速に扱う手法）
documentation_of: ./slope_trick.hpp
---

区分線形凸関数 $f(x)$ に関して傾きが 1 変化する $x$ 座標の多重集合と，$f(x)$ が最小値をとる区間を常に保持する．

```cpp
slope_trick<long long> f; // f(x) := 0                                    O(1)
f.add_const(b);           // f(x) += b                                    O(1)
f.add_relu(a);            // f(x) += max(x - a, 0)                        O(log N)
f.add_irelu(a);           // f(x) += max(a - x, 0)                        O(log N)
f.add_abs(a);             // f(x) += |x - a|                              O(log N)
f.move_left_curve(w);     // f(x) <- min_{0 <= y <= w} f(x + y),  w >= 0  O(1)
f.move_right_curve(w);    // f(x) <- min_{0 <= y <= w} f(x - y),  w >= 0  O(1)
f.translate(dx);          // f(x) <- f(x - dx)                            O(1)
f.merge_destructive(g);   // f(x) += g(x), g(x) broken                    O(min(N_f, N_g) log (N_f + N_g))
auto v = f.get_min().min; // v = min_x f(x)                               O(1)
y = f.get_destructive(x); // y = f(x), f(x) broken                        O(log N)
```

## 問題例

- [Codeforces LATOKEN Round 1 (Div. 1 + Div. 2) G. A New Beginning](https://codeforces.com/contest/1534/problem/G)
- [AtCoder Beginner Contest 217 H - Snuketoon](https://atcoder.jp/contests/abc217/tasks/abc217_h)

## Links

- [slope trick (1) 解説編 \| maspyのHP](https://maspypy.com/slope-trick-1-%E8%A7%A3%E8%AA%AC%E7%B7%A8)
- [Slope-Trick \| Luzhiled’s Library](https://ei1333.github.io/library/structure/others/slope-trick.cpp)
