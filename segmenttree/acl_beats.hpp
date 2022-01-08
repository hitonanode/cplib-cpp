#pragma once
#include "acl_lazysegtree.hpp"

// CUT begin
template <class S, S (*op)(S, S), S (*e)(), class F, S (*mapping)(F, S), F (*composition)(F, F),
          F (*id)()>
class segtree_beats : public atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> {
    using Base = atcoder::lazy_segtree<S, op, e, F, mapping, composition, id>;
    using Base::lazy_segtree;
    void all_apply(int k, F f) const override {
        Base::d[k] = mapping(f, Base::d[k]);
        if (k < Base::size) {
            Base::lz[k] = composition(f, Base::lz[k]);
            if (Base::d[k].fail) Base::push(k), Base::update(k);
        }
    }
};

namespace RangeChMinMaxAddSum {
#include <algorithm>

template <typename Num>
inline Num second_lowest(Num a, Num a2, Num c, Num c2) noexcept { // a < a2, c < c2
    return a == c ? std::min(a2, c2) : a2 <= c ? a2 : c2 <= a ? c2 : std::max(a, c);
}
template <typename Num>
inline Num second_highest(Num a, Num a2, Num b, Num b2) noexcept { // a > a2, b > b2
    return a == b ? std::max(a2, b2) : a2 >= b ? a2 : b2 >= a ? b2 : std::min(a, b);
}

using BNum = long long;
constexpr BNum BINF = 1LL << 61;

struct S {
    BNum lo, hi, lo2, hi2, sum;
    unsigned sz, nlo, nhi;
    bool fail;
    S() : lo(BINF), hi(-BINF), lo2(BINF), hi2(-BINF), sum(0), sz(0), nlo(0), nhi(0), fail(0) {}
    S(BNum x, unsigned sz_ = 1)
        : lo(x), hi(x), lo2(BINF), hi2(-BINF), sum(x * sz_), sz(sz_), nlo(sz_), nhi(sz_), fail(0) {}
    friend std::ostream &operator<<(std::ostream &os, const S s) {
        return os << "[(" << s.lo << "x" << s.nlo << ", " << s.lo2 << ", " << s.hi2 << ", " << s.hi
                  << "x" << s.nhi << "), sz=" << s.sz << ", sum=" << s.sum << "]";
    }
};

S e() { return S(); }
S op(S l, S r) {
    if (l.lo > l.hi) return r;
    if (r.lo > r.hi) return l;
    S ret;
    ret.lo = std::min(l.lo, r.lo), ret.hi = std::max(l.hi, r.hi);
    ret.lo2 = second_lowest(l.lo, l.lo2, r.lo, r.lo2),
    ret.hi2 = second_highest(l.hi, l.hi2, r.hi, r.hi2);
    ret.sum = l.sum + r.sum, ret.sz = l.sz + r.sz;
    ret.nlo = l.nlo * (l.lo <= r.lo) + r.nlo * (r.lo <= l.lo);
    ret.nhi = l.nhi * (l.hi >= r.hi) + r.nhi * (r.hi >= l.hi);
    return ret;
}
struct F {
    BNum lb, ub, bias;
    F() : lb(-BINF), ub(BINF), bias(0) {}
    F(BNum chmax_, BNum chmin_, BNum add) : lb(chmax_), ub(chmin_), bias(add) {}
    static F chmin(BNum x) noexcept { return F(-BINF, x, BNum(0)); }
    static F chmax(BNum x) noexcept { return F(x, BINF, BNum(0)); }
    static F add(BNum x) noexcept { return F(-BINF, BINF, x); };
};

F composition(F fnew, F fold) {
    F ret;
    ret.lb = std::max(std::min(fold.lb + fold.bias, fnew.ub), fnew.lb) - fold.bias;
    ret.ub = std::min(std::max(fold.ub + fold.bias, fnew.lb), fnew.ub) - fold.bias;
    ret.bias = fold.bias + fnew.bias;
    return ret;
}
F id() { return F(); }
S mapping(F f, S x) {
    if (x.sz == 0) return e();
    if (x.lo == x.hi or f.lb == f.ub or f.lb >= x.hi or f.ub < x.lo)
        return S(std::min(std::max(x.lo, f.lb), f.ub) + f.bias, x.sz);
    if (x.lo2 == x.hi) {
        x.lo = x.hi2 = std::max(x.lo, f.lb) + f.bias, x.hi = x.lo2 = std::min(x.hi, f.ub) + f.bias;
        x.sum = x.lo * x.nlo + x.hi * x.nhi;
        return x;
    }
    if (f.lb < x.lo2 and f.ub > x.hi2) {
        BNum nxt_lo = std::max(x.lo, f.lb), nxt_hi = std::min(x.hi, f.ub);
        x.sum += (nxt_lo - x.lo) * x.nlo - (x.hi - nxt_hi) * x.nhi + f.bias * x.sz;
        x.lo = nxt_lo + f.bias, x.hi = nxt_hi + f.bias, x.lo2 += f.bias, x.hi2 += f.bias;
        return x;
    }
    x.fail = 1;
    return x;
}
using segtree = segtree_beats<S, op, e, F, mapping, composition, id>;
} // namespace RangeChMinMaxAddSum
