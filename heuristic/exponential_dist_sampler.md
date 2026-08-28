---
title: Fast sampler of exponential distribution （高速指数分布サンプラー・擬似焼きなまし法の遷移判定）
documentation_of: ./exponential_dist_sampler.hpp
---

母数 $\lambda = 1$ の指数分布を模擬するサンプラーと，これを利用した擬似焼きなまし法 (simulated annealing, SA) の温度・遷移判定を管理するクラス．

`ExponentialDistSampler` は $2^D$ 個の $-\log p$ を構築時に計算する．遷移判定時はテーブルを参照するだけなので，指数関数や対数関数を毎回計算する必要がない．

## `ExponentialDistSampler`

```cpp
constexpr int D = 16;
const ExponentialDistSampler<D> eds;  // 2^D 個のサンプルを前計算
FastRNG rng(123456789);

// 下位 D bit がランダムに分布した mask を与えると x ~ Ex(1) をサンプル
uint32_t mask= rng.next_u16();
double x = eds.sample(mask);

double abs_dx;
double temperature;

// 悪化量 abs_dx、温度 temperature として遷移を受理するか判定
bool accept = eds.check_sa(abs_dx, temperature, mask);
```

`sample(mask)` は `mask` の下位 $D$ bit を利用して，指数分布に従う非負の値を返す．`check_sa(abs_dx, T, mask)` は確率 $\exp(-\lvert dx \rvert / T)$ で真を返す．`mask` の下位 $D$ bit は一様に分布している必要がある．

## `Annealer`

温度を等比的に変化させ，スコア最大化またはコスト最小化の遷移を判定する．以下は `FastRNG::next_u16()` と組み合わせる例である．

```cpp
constexpr int ITERATIONS = 1000000;
constexpr int UPDATE_INTERVAL = 256;

FastRNG rng(123456789);
const ExponentialDistSampler<16> sampler;
Annealer<UPDATE_INTERVAL> annealer(1000.0, 1.0, ITERATIONS);

int score = initial_score;
for (int iter = 0; iter < ITERATIONS; ++iter) {
    annealer.update(iter);

    int delta_score = candidate_score - score;
    if (annealer.accept_score(delta_score, rng, sampler)) {
        score = candidate_score;
        // 状態を candidate に更新
    }
}
```

- `update(iter)`：`UPDATE_INTERVAL` 回ごとに温度を更新する．各反復で呼び出す．
- `accept_score(delta_score, rng, sampler)`：スコア最大化用．`delta_score >= 0` なら必ず受理し，負なら温度に応じた確率で受理する．
- `accept_cost(delta_cost, rng, sampler)`：コスト最小化用．`delta_cost <= 0` なら必ず受理し，正なら温度に応じた確率で受理する．

`start_temp`，`end_temp`，`UPDATE_INTERVAL`，`iterations` には正の値を与えること．`Annealer` は乱数生成器の `next_u16()` を利用するため，組み合わせる `ExponentialDistSampler` では $D \leq 16$ とする．
