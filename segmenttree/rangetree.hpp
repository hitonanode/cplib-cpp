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
    std::vector<std::pair<Coordinate, Coordinate>> _pts;
    std::vector<std::vector<Coordinate>> _range2ys;
    std::vector<atcoder::segtree<S, op, e>> segtrees;
    void _set(int v, Coordinate y, S val) {
        auto i = std::distance(_range2ys[v].begin(), std::lower_bound(_range2ys[v].begin(), _range2ys[v].end(), y));
        segtrees[v].set(i, val);
    }
    void _add(int v, Coordinate y, S val) {
        auto i = std::distance(_range2ys[v].begin(), std::lower_bound(_range2ys[v].begin(), _range2ys[v].end(), y));
        segtrees[v].set(i, op(segtrees[v].get(i), val));
    }
    S _prod(int v, Coordinate yl, Coordinate yr) const {
        auto il = std::distance(_range2ys[v].begin(), std::lower_bound(_range2ys[v].begin(), _range2ys[v].end(), yl));
        auto ir = std::distance(_range2ys[v].begin(), std::lower_bound(_range2ys[v].begin(), _range2ys[v].end(), yr));
        return segtrees[v].prod(il, ir);
    }

public:
    rangetree() = default;
    void add_point(Coordinate x, Coordinate y) noexcept { _pts.emplace_back(x, y); }
    void build() {
        std::sort(_pts.begin(), _pts.end());
        _pts.erase(std::unique(_pts.begin(), _pts.end()), _pts.end());
        n = _pts.size();

        _range2ys.resize(n * 2);
        for (int i = 0; i < n; i++) _range2ys[n + i] = {_pts[i].second};
        for (int i = n - 1; i > 0; i--) {
            auto &lch = _range2ys[i * 2];
            auto &rch = _range2ys[i * 2 + 1];
            std::merge(lch.begin(), lch.end(), rch.begin(), rch.end(), std::back_inserter(_range2ys[i]));
            _range2ys[i].erase(std::unique(_range2ys[i].begin(), _range2ys[i].end()), _range2ys[i].end());
        }
        for (const auto &v : _range2ys) segtrees.emplace_back(v.size());
    }
    void set(Coordinate x, Coordinate y, S val) {
        int i = std::distance(_pts.begin(), std::lower_bound(_pts.begin(), _pts.end(), std::make_pair(x, y)));
        assert(i < n and _pts[i] == std::make_pair(x, y));
        for (i += n; i; i >>= 1) _set(i, y, val);
    }
    void add(Coordinate x, Coordinate y, S val) {
        int i = std::distance(_pts.begin(), std::lower_bound(_pts.begin(), _pts.end(), std::make_pair(x, y)));
        assert(i < n and _pts[i] == std::make_pair(x, y));
        for (i += n; i; i >>= 1) _add(i, y, val);
    }
    S sum(Coordinate xl, Coordinate xr, Coordinate yl, Coordinate yr) const {
        auto compx = [](std::pair<Coordinate, Coordinate> l, std::pair<Coordinate, Coordinate> r) {
            return l.first < r.first;
        };
        int l = n + std::distance(_pts.begin(), std::lower_bound(_pts.begin(), _pts.end(), std::make_pair(xl, yr), compx));
        int r = n + std::distance(_pts.begin(), std::lower_bound(_pts.begin(), _pts.end(), std::make_pair(xr, yr), compx));
        S ret = e();
        while (l < r) {
            if (l & 1) ret = op(ret, _prod(l++, yl, yr));
            if (r & 1) ret = op(ret, _prod(--r, yl, yr));
            l >>= 1, r >>= 1;
        }
        return ret;
    }
};
