#pragma once

#include "ntt.hpp"
#include <vector>

// Calculate g = a * f, where f is given online
// Complexity: O(n (log n)^2)
// https://qiita.com/Kiri8128/items/1738d5403764a0e26b4c
template <class NTTModInt> struct semirelaxed_multiplication {

    int maxd = 0;
    std::vector<NTTModInt> a, f, g;
    std::vector<std::vector<NTTModInt>> antt;

    const std::vector<NTTModInt> &get_antt(int d) {
        while (int(antt.size()) <= d) {
            const int D = antt.size(), fftlen = 1 << (D + 1),
                      use_len = std::min<int>(fftlen, a.size());
            std::vector<NTTModInt> v(a.begin(), a.begin() + use_len);
            v.resize(fftlen);
            ntt(v, false);
            antt.push_back(v);
        }
        return antt.at(d);
    }

    semirelaxed_multiplication(const std::vector<NTTModInt> &a_) : a(a_) {
        while (1 << maxd < int(a.size())) ++maxd;
    }

    NTTModInt add(NTTModInt f_i) {
        f.push_back(f_i);
        const int n = f.size(), d = std::min(maxd, __builtin_ctz(n));
        if (size_t gsz = n - 1 + (1 << d); g.size() < gsz) g.resize(gsz);

        // Convolve a[0, 2 ** (d + 1)) * f[n + 1 - 2 ** d, n + 1) -> g[n, n + 2 ** d)
        if (d <= 4) {
            for (int i = n - (1 << d); i < n; ++i) {
                for (int k = n - 1; k < n - 1 + (1 << d) and k - i < int(a.size()); ++k) {
                    g.at(k) += f.at(i) * a.at(k - i);
                }
            }
        } else {
            std::vector<NTTModInt> tmp{f.end() - (1 << d), f.end()};
            tmp.resize(1 << (d + 1));
            ntt(tmp, false);
            const auto &ntta = get_antt(d);
            for (int i = 0; i < int(tmp.size()); ++i) tmp.at(i) *= ntta.at(i);
            ntt(tmp, true);

            for (int i = 0; i < (1 << d); ++i) g.at(n - 1 + i) += tmp.at((1 << d) - 1 + i);
        }

        return g.at(n - 1);
    }
};
