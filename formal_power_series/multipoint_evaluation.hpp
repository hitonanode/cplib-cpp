#pragma once
#include "formal_power_series.hpp"
#include <cassert>
#include <vector>

// CUT begin
// multipoint polynomial evaluation
// input: xs = [x_0, ..., x_{N - 1}]: points to evaluate
//        f = \sum_i^M f_i x^i
// Complexity: O(N (lgN)^2) building, O(N (lgN)^2 + M lg M) evaluation
template <typename Tfield> struct MultipointEvaluation {
    int nx;
    using polynomial = FormalPowerSeries<Tfield>;
    std::vector<polynomial> segtree;
    MultipointEvaluation(const std::vector<Tfield> &xs) : nx(xs.size()) {
        segtree.resize(nx * 2 - 1);
        for (int i = 0; i < nx; i++) { segtree[nx - 1 + i] = {-xs[i], 1}; }
        for (int i = nx - 2; i >= 0; i--) { segtree[i] = segtree[2 * i + 1] * segtree[2 * i + 2]; }
    }
    std::vector<Tfield> ret;
    void _eval_rec(polynomial f, int now) {
        f %= segtree[now];
        if (now - (nx - 1) >= 0) {
            ret[now - (nx - 1)] = f.coeff(0);
            return;
        }
        _eval_rec(f, 2 * now + 1);
        _eval_rec(f, 2 * now + 2);
    }
    std::vector<Tfield> evaluate_polynomial(polynomial f) {
        ret.resize(nx);
        _eval_rec(f, 0);
        return ret;
    }

    std::vector<Tfield> _interpolate_coeffs;
    polynomial _rec_interpolation(int now, const std::vector<Tfield> &ys) const {
        int i = now - (nx - 1);
        if (i >= 0) return {ys[i]};
        auto retl = _rec_interpolation(2 * now + 1, ys);
        auto retr = _rec_interpolation(2 * now + 2, ys);
        return retl * segtree[2 * now + 2] + retr * segtree[2 * now + 1];
    }
    std::vector<Tfield> polynomial_interpolation(std::vector<Tfield> ys) {
        assert(nx == int(ys.size()));
        if (_interpolate_coeffs.empty()) {
            _interpolate_coeffs = evaluate_polynomial(segtree[0].differential());
            for (auto &x : _interpolate_coeffs) x = x.inv();
        }
        for (int i = 0; i < nx; i++) ys[i] *= _interpolate_coeffs[i];
        return _rec_interpolation(0, ys);
    }
};
