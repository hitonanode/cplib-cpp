#pragma once
#include "formal_power_series/formal_power_series.hpp"
#include <vector>

// multipoint polynomial evaluation
// input: xs = [x_0, ..., x_{N - 1}]: points to evaluate
//        f = \sum_i^M f_i x^i
// Complexity: O(N (lgN)^2) building, O(N (lgN)^2 + M lg M) evaluation
template <typename _Tfield>
struct MultipointEvaluation
{
    int nx;
    int head;
    using polynomial = FormalPowerSeries<_Tfield>;
    std::vector<polynomial> segtree;
    MultipointEvaluation(const std::vector<_Tfield> &xs) : nx(xs.size())
    {
        head = 1;
        while (1 << head < nx) head++;
        segtree.resize(2 << head);
        for (int i = 0; i < 1 << head; i++)
        {
            segtree[(1 << head) + i] = {i < nx ? -xs[i] : 0, 1};
        }
        for (int i = 1 << head; --i;)
        {
            segtree[i] = segtree[2 * i] * segtree[2 * i + 1];
        }
    }
    std::vector<_Tfield> ret;
    void _dfs_eval(polynomial f, int now)
    {
        f %= segtree[now];
        if (now - (1 << head) >= 0)
        {
            if ((now - (1 << head)) < nx) ret[now - (1 << head)] = f.coeff(0);
            return;
        }
        _dfs_eval(f, 2 * now);
        _dfs_eval(f, 2 * now + 1);
    }
    std::vector<_Tfield> evaluate_polynomial(polynomial f)
    {
        ret.resize(nx);
        _dfs_eval(f, 1);
        return ret;
    }
};
