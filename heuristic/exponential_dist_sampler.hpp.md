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
  bundledCode: "#line 2 \"heuristic/exponential_dist_sampler.hpp\"\n\n#include <cassert>\n\
    #include <cmath>\n#include <cstdint>\n#include <array>\n\ntemplate <int D> struct\
    \ ExponentialDistSampler {\n    std::array<double, (1 << D)> minuslogps;\n\n \
    \   constexpr ExponentialDistSampler() {\n        for (int i = 0; i < (1 << D);\
    \ ++i) minuslogps.at(i) = -log((0.5 + i) / (1 << D));\n    }\n\n    double sample(uint32_t\
    \ random_mask) const {\n        return minuslogps.at(random_mask & ((1 << D) -\
    \ 1));\n    }\n\n    // p ~ U(0, 1) => -log(p) ~ Ex(1)\n    // P[exp(-|dx| / T)\
    \ >= p] = P[|dx| <= -log(p) * T]\n    bool check_sa(double abs_dx, double T, uint32_t\
    \ random_mask) const {\n        return abs_dx <= minuslogps.at(random_mask & ((1\
    \ << D) - 1)) * T;\n    }\n};\nconst ExponentialDistSampler<16> log_ps;\n\ntemplate\
    \ <int UPDATE_INTERVAL = 256> struct Annealer {\n    static_assert(UPDATE_INTERVAL\
    \ > 0);\n\n    double temp;\n    double ratio;\n    int next_update = UPDATE_INTERVAL;\n\
    \n    Annealer(double start_temp, double end_temp, int iterations) : temp(start_temp)\
    \ {\n        assert(iterations > 0);\n        const int updates = (iterations\
    \ - 1) / UPDATE_INTERVAL;\n        ratio = updates == 0 ? 1.0 : pow(end_temp /\
    \ start_temp, 1.0 / updates);\n        // ratio = updates == 0 ? 0.0 : (end_temp\
    \ - start_temp) / updates;\n    }\n\n    void update(int iter) {\n        if (iter\
    \ >= next_update) {\n            temp *= ratio;\n            // temp += ratio;\n\
    \            next_update += UPDATE_INTERVAL;\n        }\n    }\n\n    template\
    \ <class RNG, class Sampler>\n    bool accept_score(int delta_score, RNG &rng,\
    \ const Sampler &sampler) const {\n        if (delta_score >= 0) return true;\n\
    \        return sampler.check_sa(-delta_score, temp, rng.next_u16());\n    }\n\
    \n    template <class RNG, class Sampler>\n    bool accept_cost(int delta_cost,\
    \ RNG &rng, const Sampler &sampler) const {\n        if (delta_cost <= 0) return\
    \ true;\n        return sampler.check_sa(delta_cost, temp, rng.next_u16());\n\
    \    }\n};\n"
  code: "#pragma once\n\n#include <cassert>\n#include <cmath>\n#include <cstdint>\n\
    #include <array>\n\ntemplate <int D> struct ExponentialDistSampler {\n    std::array<double,\
    \ (1 << D)> minuslogps;\n\n    constexpr ExponentialDistSampler() {\n        for\
    \ (int i = 0; i < (1 << D); ++i) minuslogps.at(i) = -log((0.5 + i) / (1 << D));\n\
    \    }\n\n    double sample(uint32_t random_mask) const {\n        return minuslogps.at(random_mask\
    \ & ((1 << D) - 1));\n    }\n\n    // p ~ U(0, 1) => -log(p) ~ Ex(1)\n    // P[exp(-|dx|\
    \ / T) >= p] = P[|dx| <= -log(p) * T]\n    bool check_sa(double abs_dx, double\
    \ T, uint32_t random_mask) const {\n        return abs_dx <= minuslogps.at(random_mask\
    \ & ((1 << D) - 1)) * T;\n    }\n};\nconst ExponentialDistSampler<16> log_ps;\n\
    \ntemplate <int UPDATE_INTERVAL = 256> struct Annealer {\n    static_assert(UPDATE_INTERVAL\
    \ > 0);\n\n    double temp;\n    double ratio;\n    int next_update = UPDATE_INTERVAL;\n\
    \n    Annealer(double start_temp, double end_temp, int iterations) : temp(start_temp)\
    \ {\n        assert(iterations > 0);\n        const int updates = (iterations\
    \ - 1) / UPDATE_INTERVAL;\n        ratio = updates == 0 ? 1.0 : pow(end_temp /\
    \ start_temp, 1.0 / updates);\n        // ratio = updates == 0 ? 0.0 : (end_temp\
    \ - start_temp) / updates;\n    }\n\n    void update(int iter) {\n        if (iter\
    \ >= next_update) {\n            temp *= ratio;\n            // temp += ratio;\n\
    \            next_update += UPDATE_INTERVAL;\n        }\n    }\n\n    template\
    \ <class RNG, class Sampler>\n    bool accept_score(int delta_score, RNG &rng,\
    \ const Sampler &sampler) const {\n        if (delta_score >= 0) return true;\n\
    \        return sampler.check_sa(-delta_score, temp, rng.next_u16());\n    }\n\
    \n    template <class RNG, class Sampler>\n    bool accept_cost(int delta_cost,\
    \ RNG &rng, const Sampler &sampler) const {\n        if (delta_cost <= 0) return\
    \ true;\n        return sampler.check_sa(delta_cost, temp, rng.next_u16());\n\
    \    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: heuristic/exponential_dist_sampler.hpp
  requiredBy: []
  timestamp: '2026-08-28 23:19:00+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: heuristic/exponential_dist_sampler.hpp
layout: document
title: "Fast sampler of exponential distribution \uFF08\u9AD8\u901F\u6307\u6570\u5206\
  \u5E03\u30B5\u30F3\u30D7\u30E9\u30FC\u30FB\u64EC\u4F3C\u713C\u304D\u306A\u307E\u3057\
  \u6CD5\u306E\u9077\u79FB\u5224\u5B9A\uFF09"
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
