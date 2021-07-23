#pragma once
#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

// CUT begin
// 領域木
template <class S, void (*opadd)(S &, S), void (*opsub)(S &, S), S (*e)(), class Coordinate>
class rangetree_bit {
    int n;
    std::vector<std::pair<Coordinate, Coordinate>> _pts;
    struct BIT {
        std::vector<S> data;
        BIT(int len) : data(len, e()) {}
        void add(int pos, S v) {
            for (pos++; pos and pos <= int(data.size()); pos += pos & -pos) opadd(data[pos - 1], v);
        }
        S sum(int r) const {
            S ret = e();
            while (r) opadd(ret, data[r - 1]), r -= r & -r;
            return ret;
        }
    };

    std::vector<std::vector<Coordinate>> _range2ys;
    std::vector<BIT> bits;
    void _add_singlenode(int v, Coordinate y, S val) {
        auto i = std::distance(_range2ys[v].begin(), std::lower_bound(_range2ys[v].begin(), _range2ys[v].end(), y));
        bits[v].add(i, val);
    }
    S _get_singlenode(int v, Coordinate y) const {
        auto i = std::distance(_range2ys[v].begin(), std::lower_bound(_range2ys[v].begin(), _range2ys[v].end(), y));
        return bits[v].sum(i);
    }
    S _sum(Coordinate xl, Coordinate xr, Coordinate yr) const { // [xl, xr) * (-INF, yr)
        auto compx = [](std::pair<Coordinate, Coordinate> l, std::pair<Coordinate, Coordinate> r) {
            return l.first < r.first;
        };
        int l = n + std::distance(_pts.begin(), std::lower_bound(_pts.begin(), _pts.end(), std::make_pair(xl, yr), compx));
        int r = n + std::distance(_pts.begin(), std::lower_bound(_pts.begin(), _pts.end(), std::make_pair(xr, yr), compx));
        S ret = e();
        while (l < r) {
            if (l & 1) opadd(ret, _get_singlenode(l++, yr));
            if (r & 1) opadd(ret, _get_singlenode(--r, yr));
            l >>= 1, r >>= 1;
        }
        return ret;
    }

public:
    rangetree_bit() = default;
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
        for (const auto &v : _range2ys) bits.push_back(BIT(v.size()));
    }
    void add(Coordinate x, Coordinate y, S val) {
        int i = std::distance(_pts.begin(), std::lower_bound(_pts.begin(), _pts.end(), std::make_pair(x, y)));
        assert(i < n and _pts[i] == std::make_pair(x, y));
        for (i += n; i; i >>= 1) _add_singlenode(i, y, val);
    }
    S sum(Coordinate xl, Coordinate xr, Coordinate yl, Coordinate yr) const {
        auto ret_r = _sum(xl, xr, yr);
        auto ret_l = _sum(xl, xr, yl);
        opsub(ret_r, ret_l);
        return ret_r;
    }
};
