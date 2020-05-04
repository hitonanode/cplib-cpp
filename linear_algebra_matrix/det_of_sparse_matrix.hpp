#pragma once
#include <cassert>
#include <numeric>
#include <utility>
#include <vector>

#include "random/rand_nondeterministic.hpp"
#include "linear_algebra_matrix/linear_recurrence.hpp"

// CUT begin
// Sparse matrix on ModInt/ModIntRuntime
template <typename _Tp>
struct sparse_matrix
{
    int H, W;
    std::vector<std::vector<std::pair<int, _Tp>>> vals;
    sparse_matrix(int H = 0, int W = 0) : H(H), W(W), vals(H) {}
    void add_element(int i, int j, _Tp val)
    {
        assert(i >= 0 and i < H);
        assert(j >= 0 and i < W);
        vals[i].emplace_back(j, val);
    }
    _Tp eval_bilinear(const std::vector<_Tp> &vl, const std::vector<_Tp> &vr) const
    {
        assert(vl.size() == H and vr.size() == W);
        _Tp ret = 0;
        for (int i = 0; i < H; i++)
        {
            for (const auto &p : vals[i])
            {
                ret += vl[i] * p.second * vr[p.first];
            }
        }
        return ret;
    }
    static std::vector<_Tp> prod(const sparse_matrix<_Tp> &M, const std::vector<_Tp> &vec)
    {
        assert(M.W == int(vec.size()));
        std::vector<_Tp> ret(M.H);
        for (int i = 0; i < M.H; i++)
        {
            for (const auto &p : M.vals[i])
            {
                ret[i] += p.second * vec[p.first];
            }
        }
        return ret;
    }
    _Tp Determinant() const
    {
        assert(H == W);
        const int N = H, hi = _Tp::get_mod();
        std::vector<_Tp> b(N), u(N), D(N);
        for (int i = 0; i < N; i++)
        {
            b[i] = rnd(1, hi), u[i] = rnd(1, hi), D[i] = rnd(1, hi);
        }
        std::vector<_Tp> uMDib(2 * N);
        for (int i = 0; i < 2 * N; i++)
        {
            uMDib[i] = std::inner_product(u.begin(), u.end(), b.begin(), _Tp(0));
            for (int j = 0; j < N; j++)
            {
                b[j] *= D[j];
            }
            b = prod(*this, b);
        }
        auto ret = linear_recurrence<_Tp>(uMDib);
        _Tp det = ret.second.back() * (N % 2 ? -1 : 1);
        _Tp ddet = 1;
        for (auto d : D) ddet *= d;
        return det / ddet;
    }
};
