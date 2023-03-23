#pragma once

#include "ntt.hpp"
#include <utility>
#include <vector>

// Relaxed multiplication (Online convolution / Online FFT)
// Calculate h(x) = f(x) * g(x)
// both f[i] and g[i] are given online
// Complexity: O(n (log n)^2)
// https://qiita.com/Kiri8128/items/1738d5403764a0e26b4c
template <class NTTModInt> struct relaxed_multiplication {

    std::vector<NTTModInt> f, g, h;

    // fg_prefix_ntts[d] = (NTTs of first 2^d terms of f and g)
    std::vector<std::pair<std::vector<NTTModInt>, std::vector<NTTModInt>>> fg_prefix_ntts;

    const auto &get_fg_prefix_ntt(int d) {
        while (int(fg_prefix_ntts.size()) <= d) {
            int fftlen = 1 << fg_prefix_ntts.size();
            std::vector<NTTModInt> vf(f.begin(), f.begin() + fftlen);
            std::vector<NTTModInt> vg(g.begin(), g.begin() + fftlen);
            ntt(vf, false), ntt(vg, false);
            fg_prefix_ntts.emplace_back(vf, vg);
        }
        return fg_prefix_ntts.at(d);
    }

    relaxed_multiplication() {}

    NTTModInt add(const NTTModInt &f_i, const NTTModInt &g_i) {
        f.push_back(f_i), g.push_back(g_i);
        const int n = f.size(), d = __builtin_ctz(n), D = 1 << d;

        if (size_t gsz = n - 1 + D; h.size() < gsz) h.resize(gsz);

        if (n == D) {
            // Convolve f[0, D) * g[0, D) -> h[D - 1, D * 2 - 1)

            const auto &[nttf, nttg] = get_fg_prefix_ntt(d);
            std::vector<NTTModInt> tmp(nttf.size());
            for (size_t i = 0; i < nttf.size(); ++i) tmp.at(i) = nttf.at(i) * nttg.at(i);
            ntt(tmp, true);

            for (int i = 0; i < n - 1; ++i) h.at(n + i) += tmp.at(i) - h.at(i); // 回り込みを削除
            h.at(n - 1) += tmp.at(n - 1);
        } else {
            // Convolve f[0, 2 * D) * g[n - D, n) -> h[n - 1, n - 1 + D)

            if (d <= 4) { // Bruteforce threshold
                for (int i = n - D; i < n; ++i) {
                    for (int k = n - 1; k < n - 1 + D; ++k) {
                        h.at(k) += f.at(i) * g.at(k - i) + f.at(k - i) * g.at(i);
                    }
                }
            } else {
                std::vector<NTTModInt> tmpf{f.end() - D, f.end()}, tmpg{g.end() - D, g.end()};
                tmpf.resize(D * 2), tmpg.resize(D * 2);
                ntt(tmpf, false), ntt(tmpg, false);

                const auto &[nttf, nttg] = get_fg_prefix_ntt(d + 1);
                for (size_t i = 0; i < tmpf.size(); ++i) {
                    tmpf.at(i) = tmpf.at(i) * nttg.at(i) + tmpg.at(i) * nttf.at(i);
                }
                ntt(tmpf, true);
                for (int i = 0; i < D; ++i) h.at(n - 1 + i) += tmpf.at(D - 1 + i);
            }
        }

        return h.at(n - 1);
    }
};
