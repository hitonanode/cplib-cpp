---
title: Fast sampler of exponential distribution （高速指数分布サンプラー・擬似焼きなまし法の遷移判定）
documentation_of: ./exponential_dist_sampler.hpp
---

母数 $\lambda = 1$ の指数分布を模擬するサンプラー．

典型的な用途として，擬似焼きなまし法 (simulated annealing, SA) の遷移判定を（指数関数や対数関数の計算を毎回行うことなく）高速に行える．

## 使用方法

```cpp
constexpr int D = 18;
const ExponentialDistSampler<D> eds;  // 2^D 個のサンプルを前計算

// 下位 D bit がランダムに分布した mask を与えると x ~ Ex(1) をサンプル
uint32_t mask;
double x = eds.sample(mask);

double dx;
double T;

// コストの変化が abs(dx), 温度 T のとき焼きなまし法の遷移を受理するか確率的に判定
bool upd = eds.check_sa(abs(dx), T, mask);
```
