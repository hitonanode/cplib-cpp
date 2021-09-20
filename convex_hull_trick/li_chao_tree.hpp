#pragma once
#include <algorithm>
#include <cassert>
#include <tuple>
#include <vector>

// Li-Chao tree
// init() : set x's where we will execute get(x) queries
// insert_segment(l, r, a, b): update by ax + b in [l, r)
// get(x): get min
template <class T, class T_MP> struct li_chao_tree {
    int _n, _head;
    std::vector<T> xs;
    li_chao_tree() : _n(0), _head(0) {}

    struct _Line {
        T a, b;
        int line_idx;
        bool is_valid;
        T_MP eval(T x) const noexcept { return T_MP(a) * x + b; }
    };

    std::vector<_Line> lines;
    struct LCR {
        T l, c, r;
    };
    std::vector<LCR> lcr;

    void init(const std::vector<T> &xs_) {
        xs = xs_;
        std::sort(xs.begin(), xs.end());
        xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
        _n = xs.size();
        _head = 1;
        while (_head < _n) _head <<= 1;
        lines.assign(_head * 2, {0, 0, -1, false});
        lcr.resize(_head * 2);
        for (int i = 0; i < _n; ++i) lcr[_head + i] = {xs[i], xs[i], xs[i]};
        for (int i = _head - 1; i; --i) {
            int l = i * 2, r = i * 2 + 1;
            lcr[i] = {lcr[l].l, lcr[r].l, lcr[r].r};
        }
    }

    int il, ir;
    void _rec(int now, int nowl, int nowr, _Line line_add) {
        const int nowc = (nowl + nowr) / 2;

        if (nowl >= ir or nowr <= il) {
            return;
        } else if (il <= nowl and nowr <= ir) {
            if (!lines[now].is_valid) {
                lines[now] = line_add;
                return;
            }
            bool upd_l = lines[now].eval(lcr[now].l) > line_add.eval(lcr[now].l);
            bool upd_c = lines[now].eval(lcr[now].c) > line_add.eval(lcr[now].c);
            bool upd_r = lines[now].eval(lcr[now].r) > line_add.eval(lcr[now].r);
            if (upd_l and upd_c and upd_r) {
                lines[now] = line_add;
                return;
            } else if (upd_c and upd_r) {
                std::swap(lines[now], line_add);
                _rec(now * 2, nowl, nowc, line_add);
            } else if (upd_l and upd_c) {
                std::swap(lines[now], line_add);
                _rec(now * 2 + 1, nowc, nowr, line_add);
            } else if (upd_l) {
                _rec(now * 2, nowl, nowc, line_add);
            } else if (upd_r) {
                _rec(now * 2 + 1, nowc, nowr, line_add);
            } else {
                return;
            }
        } else {
            if (il < nowc) _rec(now * 2, nowl, nowc, line_add);
            if (ir > nowc) _rec(now * 2 + 1, nowc, nowr, line_add);
        }
    }

    void insert_line(T a, T b, int idx = -1) {
        il = 0, ir = _n;
        if (il >= ir) return;
        _rec(1, 0, _head, _Line{a, b, idx, true});
    }
    void insert_segment(T xl, T xr, T a, T b, int idx = -1) {
        il = std::lower_bound(xs.begin(), xs.end(), xl) - xs.begin();
        ir = std::lower_bound(xs.begin(), xs.end(), xr) - xs.begin();
        if (il >= ir) return;
        _rec(1, 0, _head, _Line{a, b, idx, true});
    }
    struct Ret {
        T line_a, line_b;
        int line_idx;
        bool is_valid;
        T_MP minval;
    };
    Ret _get_i(int i, T x) {
        i += _head;
        _Line ret = lines[i];
        T_MP val = ret.is_valid ? ret.eval(x) : 0;
        for (i /= 2; i; i /= 2) {
            if (!lines[i].is_valid) continue;
            T_MP tmp = lines[i].eval(x);
            if (!ret.is_valid or tmp < val) ret = lines[i], val = tmp;
        }
        return {ret.a, ret.b, ret.line_idx, ret.is_valid, val};
    }

    Ret get(T x) {
        int i = std::lower_bound(xs.begin(), xs.end(), x) - xs.begin();
        assert(i < _n and xs[i] == x);
        return _get_i(i, x);
    }
};
