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
  bundledCode: "#line 2 \"heuristic/exponential_dist_sampler.hpp\"\n\n#include <cmath>\n\
    #include <cstdint>\n#include <array>\n\ntemplate <int D> struct ExponentialDistSampler\
    \ {\n    std::array<double, (1 << D)> minuslogps;\n\n    constexpr ExponentialDistSampler()\
    \ {\n        for (int i = 0; i < (1 << D); ++i) minuslogps.at(i) = -log((0.5 +\
    \ i) / (1 << D));\n    }\n\n    double sample(uint32_t random_mask) const {\n\
    \        return minuslogps.at(random_mask & ((1 << D) - 1));\n    }\n\n    //\
    \ p ~ U(0, 1) => -log(p) ~ Ex(1)\n    // P[exp(-|dx| / T) >= p] = P[|dx| <= -log(p)\
    \ * T]\n    bool check_sa(double abs_dx, double T, uint32_t random_mask) const\
    \ {\n        return abs_dx <= minuslogps.at(random_mask & ((1 << D) - 1)) * T;\n\
    \    }\n};\n// const ExponentialDistSampler<16> log_ps;\n"
  code: "#pragma once\n\n#include <cmath>\n#include <cstdint>\n#include <array>\n\n\
    template <int D> struct ExponentialDistSampler {\n    std::array<double, (1 <<\
    \ D)> minuslogps;\n\n    constexpr ExponentialDistSampler() {\n        for (int\
    \ i = 0; i < (1 << D); ++i) minuslogps.at(i) = -log((0.5 + i) / (1 << D));\n \
    \   }\n\n    double sample(uint32_t random_mask) const {\n        return minuslogps.at(random_mask\
    \ & ((1 << D) - 1));\n    }\n\n    // p ~ U(0, 1) => -log(p) ~ Ex(1)\n    // P[exp(-|dx|\
    \ / T) >= p] = P[|dx| <= -log(p) * T]\n    bool check_sa(double abs_dx, double\
    \ T, uint32_t random_mask) const {\n        return abs_dx <= minuslogps.at(random_mask\
    \ & ((1 << D) - 1)) * T;\n    }\n};\n// const ExponentialDistSampler<16> log_ps;\n"
  dependsOn: []
  isVerificationFile: false
  path: heuristic/exponential_dist_sampler.hpp
  requiredBy: []
  timestamp: '2024-03-01 09:07:31+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: heuristic/exponential_dist_sampler.hpp
layout: document
title: "Fast sampler of exponential distribution \uFF08\u9AD8\u901F\u6307\u6570\u5206\
  \u5E03\u30B5\u30F3\u30D7\u30E9\u30FC\u30FB\u64EC\u4F3C\u713C\u304D\u306A\u307E\u3057\
  \u6CD5\u306E\u9077\u79FB\u5224\u5B9A\uFF09"
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
