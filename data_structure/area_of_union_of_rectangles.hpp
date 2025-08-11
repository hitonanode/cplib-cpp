#pragma once
#include <algorithm>
#include <vector>

#include "segmenttree/acl_lazysegtree.hpp"

template <class T> class AreaOfUnionOfRectangles {
    struct Rectangle {
        T xl, xr, yl, yr;
    };
    std::vector<Rectangle> rectangles;

    struct S {
        int min = 1 << 30;
        T width = T{};
        T min_width = T{};
        T nonzero_width() const { return width - (min == 0) * min_width; }
    };
    static S op(S l, S r) {
        T min_width = (l.min <= r.min) * l.min_width + (l.min >= r.min) * r.min_width;
        return {std::min(l.min, r.min), l.width + r.width, min_width};
    }
    static S e() { return S{}; }
    using F = int;
    static S mapping(F f, S x) { return {x.min + f, x.width, x.min_width}; }
    static F composition(F f, F g) { return f + g; }
    static F id() { return 0; }

public:
    void add_rectangle(T xl, T xr, T yl, T yr) { rectangles.push_back(Rectangle{xl, xr, yl, yr}); }

    T solve() const {
        std::vector<T> xs;
        xs.reserve(rectangles.size() * 2);
        for (auto r : rectangles) xs.push_back(r.xl), xs.push_back(r.xr);
        std::sort(xs.begin(), xs.end());
        xs.erase(std::unique(xs.begin(), xs.end()), xs.end());

        if (xs.size() <= 1) return T{};

        auto seg = [&]() {
            std::vector<S> inits;
            inits.reserve((int)xs.size() - 1);
            for (int i = 0; i < (int)xs.size() - 1; ++i) {
                inits.emplace_back(S{0, xs[i + 1] - xs[i], xs[i + 1] - xs[i]});
            }
            return atcoder::lazy_segtree<S, op, e, F, mapping, composition, id>{inits};
        }();

        std::vector<std::tuple<T, int, int, bool>> updates;
        updates.reserve(rectangles.size() * 2);
        for (auto r : rectangles) {
            const int ixl = std::lower_bound(xs.begin(), xs.end(), r.xl) - xs.begin();
            const int ixr = std::lower_bound(xs.begin(), xs.end(), r.xr) - xs.begin();
            updates.emplace_back(r.yl, ixl, ixr, true);
            updates.emplace_back(r.yr, ixl, ixr, false);
        }

        std::sort(updates.begin(), updates.end());
        T current_y = std::get<0>(updates.front());
        T res{0};
        for (auto [y, il, ir, tp] : updates) {
            if (y != current_y) {
                res += (y - current_y) * seg.all_prod().nonzero_width();
                current_y = y;
            }
            seg.apply(il, ir, tp ? 1 : -1);
        }

        return res;
    }
};
