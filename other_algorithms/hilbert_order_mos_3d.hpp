#pragma once
#include <cassert>
#include <limits>
#include <tuple>
#include <type_traits>
#include <utility>

// Encode 3D point (x, y, z) to Hilbert order
// Implementation based on https://arxiv.org/abs/2308.05673
template <class Uint = unsigned long long> Uint encode_hilbert_order_3d(Uint x, Uint y, Uint z) {
    static_assert(std::is_unsigned_v<Uint>);
    static_assert(std::numeric_limits<Uint>::digits >= 64);
    auto update = [](Uint x, Uint y, Uint z, unsigned w, unsigned o) -> std::tuple<Uint, Uint, Uint> {
        if (o == 0) return {z, x, y};
        if (o == 1) return {y, z, x - w};
        if (o == 2) return {y, z - w, x - w};
        if (o == 3) return {w - x - 1, y, 2 * w - z - 1};
        if (o == 4) return {w - x - 1, y - w, 2 * w - z - 1};
        if (o == 5) return {2 * w - y - 1, 2 * w - z - 1, x - w};
        if (o == 6) return {2 * w - y - 1, w - z - 1, x - w};
        if (o == 7) return {z, w - x - 1, 2 * w - y - 1};
        assert(false);
    };

    int rmin = 1;
    while ((x | y | z) >> rmin) ++rmin;

    assert(rmin * 3 <= (int)sizeof(Uint) * 8);

    const int t = (-rmin % 3 + 3) % 3;
    if (t == 1) {
        std::swap(y, z);
        std::swap(x, y);
    } else if (t == 2) {
        std::swap(x, y);
        std::swap(y, z);
    }

    Uint h = 0;

    for (Uint w = Uint(1) << (rmin - 1); w; w >>= 1) {
        bool bx = (x >= w), by = (y >= w), bz = (z >= w);
        unsigned o = (bx ^ by ^ bz) + 2 * (by ^ bz) + 4 * by;
        h = 8 * h + o;
        std::tie(x, y, z) = update(x, y, z, w, o);
    }

    return h;
}
