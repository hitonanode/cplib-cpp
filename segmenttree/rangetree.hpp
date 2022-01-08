#pragma once
#include "acl_segtree.hpp"
#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

// CUT begin
// 逆元を要求しない領域木
template <class S, S (*op)(S, S), S (*e)(), class Coordinate> class rangetree {
    int n;
    using Pt = std::pair<Coordinate, Coordinate>;
    std::vector<Pt> _pts;
    std::vector<std::vector<Pt>> _range2yxs;
    std::vector<atcoder::segtree<S, op, e>> segtrees;
    void _set(int v, Pt p, S val) {
        auto i = std::distance(
            _range2yxs[v].begin(),
            std::lower_bound(_range2yxs[v].begin(), _range2yxs[v].end(), Pt{p.second, p.first}));
        segtrees[v].set(i, val);
    }
    void _add(int v, Pt p, S val) {
        auto i = std::distance(
            _range2yxs[v].begin(),
            std::lower_bound(_range2yxs[v].begin(), _range2yxs[v].end(), Pt{p.second, p.first}));
        segtrees[v].set(i, op(segtrees[v].get(i), val));
    }
    S _prod(int v, Coordinate yl, Coordinate yr) const {
        auto comp = [&](const Pt &l, const Pt &r) { return l.first < r.first; };
        auto il = std::distance(
            _range2yxs[v].begin(),
            std::lower_bound(_range2yxs[v].begin(), _range2yxs[v].end(), Pt{yl, yl}, comp));
        auto ir = std::distance(
            _range2yxs[v].begin(),
            std::lower_bound(_range2yxs[v].begin(), _range2yxs[v].end(), Pt{yr, yr}, comp));
        return segtrees[v].prod(il, ir);
    }

public:
    rangetree() = default;
    void add_point(Coordinate x, Coordinate y) noexcept { _pts.emplace_back(x, y); }
    void build() {
        std::sort(_pts.begin(), _pts.end());
        _pts.erase(std::unique(_pts.begin(), _pts.end()), _pts.end());
        n = _pts.size();

        _range2yxs.resize(n * 2);
        for (int i = 0; i < n; i++) _range2yxs[n + i] = {{_pts[i].second, _pts[i].first}};
        for (int i = n - 1; i > 0; i--) {
            auto &lch = _range2yxs[i * 2];
            auto &rch = _range2yxs[i * 2 + 1];
            std::merge(
                lch.begin(), lch.end(), rch.begin(), rch.end(), std::back_inserter(_range2yxs[i]));
            _range2yxs[i].erase(
                std::unique(_range2yxs[i].begin(), _range2yxs[i].end()), _range2yxs[i].end());
        }
        for (const auto &v : _range2yxs) segtrees.emplace_back(v.size());
    }
    void set(Coordinate x, Coordinate y, S val) {
        int i = std::distance(_pts.begin(), std::lower_bound(_pts.begin(), _pts.end(), Pt{x, y}));
        assert(i < n and _pts[i] == std::make_pair(x, y));
        for (i += n; i; i >>= 1) _set(i, {x, y}, val);
    }
    void add(Coordinate x, Coordinate y, S val) {
        int i = std::distance(_pts.begin(), std::lower_bound(_pts.begin(), _pts.end(), Pt{x, y}));
        assert(i < n and _pts[i] == std::make_pair(x, y));
        for (i += n; i; i >>= 1) _add(i, {x, y}, val);
    }
    S prod(Coordinate xl, Coordinate xr, Coordinate yl, Coordinate yr) const {
        auto comp = [](const Pt &l, const Pt &r) { return l.first < r.first; };
        int l = n + std::distance(_pts.begin(),
                                  std::lower_bound(_pts.begin(), _pts.end(), Pt{xl, yr}, comp));
        int r = n + std::distance(_pts.begin(),
                                  std::lower_bound(_pts.begin(), _pts.end(), Pt{xr, yr}, comp));
        S ret = e();
        while (l < r) {
            if (l & 1) ret = op(ret, _prod(l++, yl, yr));
            if (r & 1) ret = op(ret, _prod(--r, yl, yr));
            l >>= 1, r >>= 1;
        }
        return ret;
    }
    S get(Coordinate x, Coordinate y) const { return prod(x, x + 1, y, y + 1); }
};
