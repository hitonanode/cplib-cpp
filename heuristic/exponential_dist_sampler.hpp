#pragma once

#include <cmath>
#include <cstdint>
#include <array>

template <int D> struct ExponentialDistSampler {
    std::array<double, (1 << D)> minuslogps;

    constexpr ExponentialDistSampler() {
        for (int i = 0; i < (1 << D); ++i) minuslogps.at(i) = -log((0.5 + i) / (1 << D));
    }

    double sample(uint32_t random_mask) const {
        return minuslogps.at(random_mask & ((1 << D) - 1));
    }

    // p ~ U(0, 1) => -log(p) ~ Ex(1)
    // P[exp(-|dx| / T) >= p] = P[|dx| <= -log(p) * T]
    bool check_sa(double abs_dx, double T, uint32_t random_mask) const {
        return abs_dx <= minuslogps.at(random_mask & ((1 << D) - 1)) * T;
    }
};
// const ExponentialDistSampler<16> log_ps;
