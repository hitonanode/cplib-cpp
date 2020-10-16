#pragma once
#include "formal_power_series/formal_power_series.hpp"

// CUT begin
// multipoint polynomial evaluation
// input: xs = [x_0, ..., x_{N - 1}]: points to evaluate
//        f = \sum_i^M f_i x^i
// Complexity: O(N (lgN)^2) building, O(N (lgN)^2 + M lg M) evaluation
template <typename Tfield>
struct MultipointEvaluation
{
    int nx;
    using polynomial = FormalPowerSeries<Tfield>;
    std::vector<polynomial> segtree;
    MultipointEvaluation(const std::vector<Tfield> &xs) : nx(xs.size())
    {
        segtree.resize(nx * 2 - 1);
        for (int i = 0; i < nx; i++)
        {
            segtree[nx - 1 + i] = {-xs[i], 1};
        }
        for (int i = nx - 2; i >= 0; i--)
        {
            segtree[i] = segtree[2 * i + 1] * segtree[2 * i + 2];
        }
    }
    std::vector<Tfield> ret;
    std::vector<Tfield> evaluate_polynomial(polynomial f)
    {
        ret.resize(nx);
        auto rec = [&](auto &&rec, polynomial f, int now) -> void {
            f %= segtree[now];
            if (now - (nx - 1) >= 0)
            {
                ret[now - (nx - 1)] = f.coeff(0);
                return;
            }
            rec(rec, f, 2 * now + 1);
            rec(rec, f, 2 * now + 2);
        };
        rec(rec, f, 0);
        return ret;
    }

    std::vector<Tfield> _interpolate_coeffs;
    std::vector<Tfield> polynomial_interpolation(std::vector<Tfield> ys)
    {
        assert(nx == int(ys.size()));
        if (_interpolate_coeffs.empty())
        {
            _interpolate_coeffs = evaluate_polynomial(segtree[0].differential());
            for (auto &x : _interpolate_coeffs) x = x.inv();
        }
        for (int i = 0; i < nx; i++) ys[i] *= _interpolate_coeffs[i];

        auto rec = [&](auto &&rec, int now) -> polynomial {
            int i = now - (nx - 1);
            if (i >= 0) return {ys[i]};
            auto retl = rec(rec, 2 * now + 1);
            auto retr = rec(rec, 2 * now + 2);
            return retl * segtree[2 * now + 2] + retr * segtree[2 * now + 1];
        };
        return rec(rec, 0);
    }
};
