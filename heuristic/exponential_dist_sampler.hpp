#pragma once

#include <cassert>
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
const ExponentialDistSampler<16> log_ps;

template <int UPDATE_INTERVAL = 256> struct Annealer {
    static_assert(UPDATE_INTERVAL > 0);

    double temp;
    double ratio;
    int next_update = UPDATE_INTERVAL;

    Annealer(double start_temp, double end_temp, int iterations) : temp(start_temp) {
        assert(iterations > 0);
        const int updates = (iterations - 1) / UPDATE_INTERVAL;
        ratio = updates == 0 ? 1.0 : pow(end_temp / start_temp, 1.0 / updates);
        // ratio = updates == 0 ? 0.0 : (end_temp - start_temp) / updates;
    }

    void update(int iter) {
        if (iter >= next_update) {
            temp *= ratio;
            // temp += ratio;
            next_update += UPDATE_INTERVAL;
        }
    }

    template <class RNG, class Sampler>
    bool accept_score(int delta_score, RNG &rng, const Sampler &sampler) const {
        if (delta_score >= 0) return true;
        return sampler.check_sa(-delta_score, temp, rng.next_u16());
    }

    template <class RNG, class Sampler>
    bool accept_cost(int delta_cost, RNG &rng, const Sampler &sampler) const {
        if (delta_cost <= 0) return true;
        return sampler.check_sa(delta_cost, temp, rng.next_u16());
    }
};
