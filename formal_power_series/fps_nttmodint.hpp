#pragma once

#include "../convolution/ntt.hpp"

#include <algorithm>
#include <cassert>
#include <optional>
#include <vector>

namespace fps_nttmod {

// Calculate the inverse of f(x) mod x^d
// f(x) * g(x) = 1 mod x^d
// If d = -1, d is set to f.size()
// Complexity: O(d log d)
template <class NTTModInt>
std::vector<NTTModInt> inv(const std::vector<NTTModInt> &f, int d = -1) {
    assert(d >= -1);

    const int n = f.size();
    if (d == -1) d = n;

    if (d == 0) return {};

    assert(f.front() != NTTModInt(0));

    using F = std::vector<NTTModInt>;

    F res{f.front().inv()}; // f(x) g_m(x) = 1 mod x^m

    for (int m = 1; m < d; m *= 2) { // g_2m = (2g_m - f g_m^2) mod x^2m
        F g_m{res.cbegin(), res.cbegin() + m};
        g_m.resize(2 * m);
        ntt(g_m, false);

        F f_{f.cbegin(), f.cbegin() + std::min(n, 2 * m)};

        f_.resize(2 * m);
        ntt(f_, false);
        for (int i = 0; i < 2 * m; ++i) f_.at(i) *= g_m.at(i);
        ntt(f_, true);

        std::rotate(f_.begin(), f_.begin() + m, f_.end());
        for (int i = m; i < 2 * m; ++i) f_.at(i) = 0;

        ntt(f_, false);
        for (int i = 0; i < 2 * m; ++i) f_.at(i) *= g_m.at(i);
        ntt(f_, true);

        for (int i = 0; i < m; ++i) f_.at(i) = -f_.at(i);

        res.insert(res.end(), f_.begin(), f_.begin() + m);
    }
    res.resize(d);
    return res;
}

// Calculate the integral of f(x)
// Complexity: O(len(f))
template <class NTTModInt> void integ_inplace(std::vector<NTTModInt> &f) {
    if (f.empty()) return;

    for (int i = (int)f.size() - 1; i > 0; --i) f.at(i) = f.at(i - 1) * NTTModInt(i).inv();
    f.front() = NTTModInt(0);
}

// Calculate the derivative of f(x)
// Complexity: O(len(f))
template <class NTTModInt> void deriv_inplace(std::vector<NTTModInt> &f) {
    if (f.empty()) return;

    for (int i = 1; i < (int)f.size(); ++i) f.at(i - 1) = f.at(i) * i;
    f.back() = NTTModInt(0);
}

// Calculate log f(x) mod x^d
// Require f(0) = 1 mod x^d
// Complexity: O(d log d)
template <class NTTModInt>
std::vector<NTTModInt> log(const std::vector<NTTModInt> &f, int d = -1) {
    assert(d >= -1);

    const int n = f.size();
    if (d < 0) d = n;

    if (d == 0) return {};

    assert(f.front() == NTTModInt(1));

    std::vector<NTTModInt> inv_f = inv(f, d), df{f.cbegin(), f.cbegin() + std::min(d, n)};
    deriv_inplace(df);

    auto ret = nttconv(inv_f, df);
    ret.resize(d);
    integ_inplace(ret);
    return ret;
}

template <class NTTModInt>
std::vector<NTTModInt> exp(const std::vector<NTTModInt> &h, int d = -1) {
    assert(d >= -1);

    const int n = h.size();
    if (d < 0) d = n;

    if (d == 0) return {};

    assert(h.empty() or h.front() == NTTModInt(0));

    using F = std::vector<NTTModInt>;

    F g{1}, g_fft;

    std::vector<NTTModInt> ret(d);
    ret.front() = 1;

    auto h_deriv = h;
    h_deriv.resize(d);
    deriv_inplace(h_deriv);

    for (int m = 1; m < d; m *= 2) {
        F f_fft = ret;
        f_fft.resize(m * 2);
        ntt(f_fft, false);

        // 2a
        if (m > 1) {
            F tmp{f_fft.cbegin(), f_fft.cbegin() + m};
            for (int i = 0; i < m; ++i) tmp.at(i) *= g_fft.at(i);
            ntt(tmp, true);
            tmp.erase(tmp.begin(), tmp.begin() + m / 2);
            tmp.resize(m);
            ntt(tmp, false);
            for (int i = 0; i < m; ++i) tmp.at(i) *= -g_fft.at(i);
            ntt(tmp, true);
            tmp.resize(m / 2);
            g.insert(g.end(), tmp.cbegin(), tmp.cbegin() + m / 2);
        }

        //
        F t{ret.cbegin(), ret.cbegin() + m};
        deriv_inplace(t);

        {
            F r{h_deriv.cbegin(), h_deriv.cbegin() + m - 1};
            r.resize(m);
            ntt(r, false);
            for (int i = 0; i < m; ++i) r.at(i) *= f_fft.at(i);
            ntt(r, true);
            for (int i = 0; i < m; ++i) t.at(i) -= r.at(i);

            std::rotate(t.begin(), t.end() - 1, t.end());
        }

        //
        t.resize(2 * m);
        ntt(t, false);

        g_fft = g;
        g_fft.resize(2 * m);
        ntt(g_fft, false);

        for (int i = 0; i < 2 * m; ++i) t.at(i) *= g_fft.at(i);
        ntt(t, true);
        t.resize(m);

        //
        F v{h.begin() + std::min(m, n), h.begin() + std::min({d, 2 * m, n})};
        v.resize(m);
        t.insert(t.begin(), m - 1, 0);
        t.push_back(0);
        integ_inplace(t);
        for (int i = 0; i < m; ++i) v.at(i) -= t.at(m + i);

        //
        v.resize(2 * m);
        ntt(v, false);
        for (int i = 0; i < 2 * m; ++i) v.at(i) *= f_fft.at(i);
        ntt(v, true);
        v.resize(m);

        for (int i = 0; i < std::min(d - m, m); ++i) ret.at(m + i) = v.at(i);
    }
    return ret;
}

// Calculate f(x)^k mod x^d
// assume 0^0 = 1
template <class NTTModInt>
std::vector<NTTModInt> pow(const std::vector<NTTModInt> &A, long long k, int d = -1) {
    assert(d >= -1);

    const int n = A.size();
    if (d < 0) d = n;

    if (k == 0) {
        std::vector<NTTModInt> ret{NTTModInt(1)}; // assume 0^0 = 1
        ret.resize(d);
        return ret;
    }

    int l = 0;
    long long shift = 0;
    while (l < (int)A.size() and A.at(l) == NTTModInt(0) and shift < d) {
        ++l;
        shift += k;
    }
    if (l == (int)A.size() or shift >= d) return std::vector<NTTModInt>(d, 0);

    const NTTModInt cpow = A.at(l).pow(k), cinv = A.at(l).inv();
    std::vector<NTTModInt> tmp{A.cbegin() + l, A.cbegin() + std::min<int>(n, d - l * k + l)};

    for (auto &x : tmp) x *= cinv;

    tmp = log(tmp, d - l * k);

    for (auto &x : tmp) x *= k;

    tmp = exp(tmp, d - l * k);

    for (auto &x : tmp) x *= cpow;

    tmp.insert(tmp.begin(), l * k, NTTModInt(0));

    tmp.resize(d);

    return tmp;
}

} // namespace fps_nttmod
