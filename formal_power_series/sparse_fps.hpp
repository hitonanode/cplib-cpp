#pragma once
#include <algorithm>
#include <cassert>
#include <concepts>
#include <optional>
#include <utility>
#include <vector>

namespace sparse_fps {
// https://github.com/yosupo06/library-checker-problems/issues/767#issuecomment-1166414020

// Calculate f(x)^k up to x^max_deg
template <typename Vec>
    requires std::derived_from<Vec, std::vector<typename Vec::value_type>>
Vec pow(const Vec &f, int max_deg, long long k) {
    using T = typename Vec::value_type;
    assert(k >= 0);

    Vec ret(max_deg + 1);

    if (k == 0) {
        ret[0] = T{1};
        return ret;
    }

    std::vector<std::pair<int, T>> terms;
    int d0 = 0;
    while (d0 < int(f.size()) and d0 <= max_deg and f[d0] == T()) ++d0;
    if (d0 == int(f.size()) or d0 > max_deg) return ret;

    if (d0 and max_deg / d0 < k) return ret;

    for (int d = d0 + 1; d < std::min<int>(max_deg + 1, f.size()); ++d) {
        if (f[d] != T{}) terms.emplace_back(d - d0, f[d]);
    }

    const int bias = d0 * k;
    ret[bias] = f[d0].pow(k);
    const T fd0inv = 1 / f[d0];
    for (int d = 0; bias + d + 1 < int(ret.size()); ++d) {
        // Compare [x^d](k f'g - fg')
        T tmp{0};
        for (auto [i, fi] : terms) {
            int j = d - i;
            if (0 <= j) tmp -= fi * ret[bias + j + 1] * (j + 1);
            j = d - (i - 1);
            if (0 <= j) tmp += fi * i * ret[bias + j] * T(k);
        }
        ret[bias + d + 1] = tmp * fd0inv / (d + 1);
    }

    return ret;
}

template <typename Vec>
    requires std::derived_from<Vec, std::vector<typename Vec::value_type>>
Vec inv(const Vec &f, int max_deg) {
    using T = typename Vec::value_type;
    assert(!f.empty() and f[0] != T{0});

    Vec ret(max_deg + 1);

    std::vector<std::pair<int, T>> terms;
    for (int d = 1; d < (int)f.size() and d <= max_deg; ++d) {
        if (f[d] != T{}) terms.emplace_back(d, f[d]);
    }

    const T f0inv = f[0].inv();
    ret[0] = f0inv;

    for (int d = 1; d <= max_deg; ++d) {
        T tmp{0};
        for (auto [i, fi] : terms) {
            if (i > d) break;
            tmp -= fi * ret[d - i];
        }
        ret[d] = tmp * f0inv;
    }

    return ret;
}

template <typename Vec>
    requires std::derived_from<Vec, std::vector<typename Vec::value_type>>
Vec log(const Vec &f, int max_deg) {
    using T = typename Vec::value_type;
    assert(!f.empty() and f[0] != T{0});

    const auto inv = sparse_fps::inv(f, max_deg);

    std::vector<std::pair<int, T>> df_terms;
    for (int d = 1; d < (int)f.size() and d <= max_deg; ++d) {
        if (f[d] != T{}) df_terms.emplace_back(d - 1, f[d] * T{d});
    }

    Vec ret(max_deg + 1);

    for (int d = 0; d < max_deg; ++d) {
        for (auto [i, fi] : df_terms) {
            const int j = d + i + 1;
            if (j > max_deg) break;
            ret[j] += inv[d] * fi * T{j}.inv();
        }
    }

    return ret;
}

template <typename Vec>
    requires std::derived_from<Vec, std::vector<typename Vec::value_type>>
Vec exp(const Vec &f, int max_deg) {
    using T = typename Vec::value_type;
    assert(f.empty() or f[0] == T{0});

    std::vector<std::pair<int, T>> df_terms;
    for (int d = 1; d < (int)f.size() and d <= max_deg; ++d) {
        if (f[d] != T{}) df_terms.emplace_back(d - 1, f[d] * T{d});
    }

    Vec ret(max_deg + 1);
    ret[0] = T{1};
    // F' = F * f'
    for (int d = 1; d <= max_deg; ++d) {
        T tmp{0};
        for (auto [i, dfi] : df_terms) {
            if (i > d - 1) break;
            tmp += dfi * ret[d - 1 - i];
        }
        ret[d] = tmp * T{d}.inv();
    }

    return ret;
}

template <typename Vec>
    requires std::derived_from<Vec, std::vector<typename Vec::value_type>>
std::optional<Vec> sqrt(const Vec &f, int max_deg) {
    using T = typename Vec::value_type;

    Vec ret(max_deg + 1);

    int d0 = 0;
    while (d0 < int(f.size()) and d0 <= max_deg and f[d0] == T{}) ++d0;
    if (d0 == int(f.size()) or d0 > max_deg) return ret;
    if (d0 & 1) return std::nullopt;

    const T sqrtf0 = f[d0].sqrt();
    if (sqrtf0 == T{}) return std::nullopt;

    std::vector<std::pair<int, T>> terms;
    const T fd0inv = 1 / f[d0];
    for (int d = d0 + 1; d < std::min<int>(max_deg + 1, f.size()); ++d) {
        if (f[d] != T{}) terms.emplace_back(d - d0, f[d] * fd0inv);
    }

    const int bias = d0 / 2;
    const T inv2 = T{2}.inv();
    ret[bias] = sqrtf0;
    for (int d = 0; bias + d + 1 < int(ret.size()); ++d) {
        T tmp{0};
        for (auto [i, fi] : terms) {
            if (i > d + 1) break;
            int j = d - i;
            if (0 <= j) tmp -= fi * ret[bias + j + 1] * (j + 1);
            j = d - (i - 1);
            if (0 <= j) tmp += fi * i * ret[bias + j] * inv2;
        }
        ret[bias + d + 1] = tmp / (d + 1);
    }

    return ret;
}

} // namespace sparse_fps
