#pragma once
#include "ntt.hpp"
#include <cassert>
#include <numeric>
#include <vector>

// CUT begin
// Multivariate convolution (Linear, overflow cutoff)
// Complexity: $O(kN \log N + k^2 N)$
// Note that the vectors store the infomation in **column-major order**
// Implementation idea: https://rushcheyo.blog.uoj.ac/blog/6547
// Details of my implementation: https://hitonanode.github.io/cplib-cpp/convolution/multivar_ntt.hpp
template <typename MODINT> struct multivar_ntt {
    int K, N, fftlen;
    std::vector<int> dim;
    std::vector<int> chi;
    MODINT invfftlen;

private:
    void _initialize(const std::vector<int> &dim_) {
        dim = dim_;
        K = dim_.size();
        N = std::accumulate(dim_.begin(), dim_.end(), 1, [&](int l, int r) { return l * r; });
        fftlen = 1;
        while (fftlen < N * 2) fftlen <<= 1;
        invfftlen = MODINT(fftlen).inv();

        chi.resize(fftlen);
        int t = 1;
        for (auto d : dim_) {
            t *= d;
            for (int s = t; s < fftlen; s += t) chi[s] += 1;
        }
        for (int i = 0; i + 1 < fftlen; i++) {
            chi[i + 1] += chi[i];
            if (chi[i + 1] >= K) chi[i + 1] -= K;
        }
    }

    std::vector<MODINT> _convolve(const std::vector<MODINT> &f, const std::vector<MODINT> &g) const {
        assert(int(f.size()) == N);
        assert(int(g.size()) == N);
        if (dim.empty()) return {f[0] * g[0]};
        std::vector<std::vector<MODINT>> fex(K, std::vector<MODINT>(fftlen)), gex(K, std::vector<MODINT>(fftlen));
        for (int i = 0; i < N; i++) fex[chi[i]][i] = f[i], gex[chi[i]][i] = g[i];
        for (auto &vec : fex) ntt(vec, false);
        for (auto &vec : gex) ntt(vec, false);
        std::vector<std::vector<MODINT>> hex(K, std::vector<MODINT>(fftlen));
        for (int df = 0; df < K; df++) {
            for (int dg = 0; dg < K; dg++) {
                int dh = (df + dg < K) ? df + dg : df + dg - K;
                for (int i = 0; i < fftlen; i++) hex[dh][i] += fex[df][i] * gex[dg][i];
            }
        }
        for (auto &vec : hex) ntt(vec, true);
        std::vector<MODINT> ret(N);
        for (int i = 0; i < N; i++) ret[i] = hex[chi[i]][i];
        return ret;
    }

public:
    multivar_ntt(const std::vector<int> &dim_) { _initialize(dim_); }
    std::vector<MODINT> operator()(const std::vector<MODINT> &f, const std::vector<MODINT> &g) const {
        return _convolve(f, g);
    }
};
