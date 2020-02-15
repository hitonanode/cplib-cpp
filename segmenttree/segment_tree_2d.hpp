#pragma once
#include <iostream>
#include <vector>

// 2D Segment Tree (point-update, range-get)
// - 0-indexed
// - Conditions for operations:
//   - datamerge: [TDATA, TDATA] -> TDATA, e(defaultDATA, x) == x, e(x, y) == e(y, x)
//   - data2ret: [TDATA, TQUERY] -> TRET, f(defaultDATA, q) == defaultRET
//   - retmerge: [TRET, TRET] -> TRET, g(defaultRET, x) == x, g(x, y) = g(y, x)
//   - commutability f(e(x, y), q) == g(f(x, q), f(y, q))
template<typename TDATA, typename TRET, typename TQUERY, typename E, typename F, typename G>
struct SegmentTree2D
{
    int H, W;
    int hhead, whead;
    TDATA defaultDATA;
    TRET defaultRET;
    E datamerge;
    F data2ret;
    G retmerge;
    int DH, DW;
    std::vector<TDATA> data;
    inline TDATA& at(int h, int w) { return data[DW * h + w]; }

    inline void _merge_w(int h, int w) {
        if (2 * w + 2 < DW) at(h, w) = datamerge(at(h, 2 * w + 1), at(h, 2 * w + 2));
        else if (2 * w + 2 == DW) at(h, w) = at(h, 2 * w + 1);
        else at(h, w) = defaultDATA;
    }
    inline void _merge_h(int h, int w) {
        if (2 * h + 2 < DH) at(h, w) = datamerge(at(2 * h + 1, w), at(2 * h + 2, w));
        else if (2 * h + 2 == DH) at(h, w) = at(2 * h + 1, w);
        else at(h, w) = defaultDATA;
    }
    SegmentTree2D(const std::vector<std::vector<TDATA>> &mat, TDATA defaultDATA, E datamerge, F data2ret, G retmerge)
        : H(mat.size()), W(mat[0].size()), defaultDATA(defaultDATA),
          defaultRET(data2ret(defaultDATA, TQUERY(0))),
          datamerge(datamerge), data2ret(data2ret), retmerge(retmerge)
    {
        int Htmp = 1, Wtmp = 1;
        while (Htmp < H) Htmp <<= 1;
        while (Wtmp < W) Wtmp <<= 1;
        hhead = Htmp - 1, whead = Wtmp - 1;
        DH = hhead + H, DW = whead + W;
        data.assign(DH * DW, defaultDATA);
        for (int h = 0; h < H; h++) for (int w = 0; w < W; w++) {
            at(hhead + h, whead + w) = mat[h][w];
        }
        for (int h = DH - 1; h >= hhead; h--) {
            for (int w = whead - 1; w >= 0; w--) _merge_w(h, w);
        }
        for (int h = hhead - 1; h >= 0; h--) {
            for (int w = 0; w < DW; w++) _merge_h(h, w);
        }
    }
    void update(int h, int w, TDATA x) {
        h += hhead, w += whead;
        at(h, w) = x;
        for (int pos = h; pos;) {
            pos = (pos - 1) / 2;
            _merge_h(pos, w);
        }
        for (int iw = w; iw;) {
            iw = (iw - 1) / 2;
            for (int ih = h;;) {
                _merge_w(ih, iw);
                if (!ih) break;
                ih = (ih - 1) / 2;
            }
        }
    }
    TRET _get_h(int hl, int hr, int wl, int wr, int lo, int hi, int id_, TQUERY q) {
        if (hr <= lo or hi <= hl) return defaultRET;
        if (hl <= lo and hi <= hr) return _get_w(wl, wr, 0, whead + 1, id_, 0, q);
        return retmerge(
            _get_h(hl, hr, wl, wr, lo, (lo + hi) / 2, 2 * id_ + 1, q),
            _get_h(hl, hr, wl, wr, (lo + hi) / 2, hi, 2 * id_ + 2, q));
    }
    TRET _get_w(int wl, int wr, int lo, int hi, int id_h, int id_w, TQUERY q) {
        if (wr <= lo or hi <= wl) return defaultRET;
        if (wl <= lo and hi <= wr) return data2ret(at(id_h, id_w), q);
        return retmerge(
            _get_w(wl, wr, lo, (lo + hi) / 2, id_h, 2 * id_w + 1, q),
            _get_w(wl, wr, (lo + hi) / 2, hi, id_h, 2 * id_w + 2, q));
    }
    // [hl, hr) * [wl, wr)
    TRET get(int hl, int hr, int wl, int wr, TQUERY q) {
        return _get_h(hl, hr, wl, wr, 0, hhead + 1, 0, q);
    }
    friend std::ostream &operator<<(std::ostream &os, SegmentTree2D s) {
        os << "[SegmentTree" << s.H << "*" << s.W << "\n";
        for (int h = 0; h < s.H; h++) {
            os << "[";
            for (int w = 0; w < s.W; w++) os << s.at(h + s.hhead, w + s.whead) << ",";
            os << "]\n";
        }
        os << "]";
        return os;
    }
};
