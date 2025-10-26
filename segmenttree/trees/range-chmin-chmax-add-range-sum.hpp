#pragma once
#include "../acl_beats.hpp"

#include <algorithm>
#include <cassert>
#include <type_traits>

template <typename Num, Num INF> struct RangeChminChmaxAddRangeSum {
    static_assert(std::is_signed<Num>::value, "Num must be signed");

    struct S {
        Num lo, hi, lo2, hi2, sum;
        unsigned sz, nlo, nhi;
        bool fail;
        S() : lo(INF), hi(-INF), lo2(INF), hi2(-INF), sum(0), sz(0), nlo(0), nhi(0), fail(0) {}
        S(Num x, unsigned sz_)
            : lo(x), hi(x), lo2(INF), hi2(-INF), sum(x * sz_), sz(sz_), nlo(sz_), nhi(sz_),
              fail(0) {}

        template <class OStream> friend OStream &operator<<(OStream &os, const S s) {
            return os << "[(" << s.lo << "x" << s.nlo << ", " << s.lo2 << ", " << s.hi2 << ", "
                      << s.hi << "x" << s.nhi << "), sz=" << s.sz << ", sum=" << s.sum << "]";
        }
    };

private:
    static Num second_lowest(Num a, Num a2, Num c, Num c2) noexcept {
        assert(a <= a2); // a < a2 or a == a2 == INF
        assert(c <= c2); // c < c2 or c == c2 == -INF
        return a == c ? std::min(a2, c2) : a2 <= c ? a2 : c2 <= a ? c2 : std::max(a, c);
    }

    static Num second_highest(Num a, Num a2, Num b, Num b2) noexcept {
        assert(a >= a2); // a > a2 or a == a2 == -INF
        assert(b >= b2); // b > b2 or b == b2 == INF
        return a == b ? std::max(a2, b2) : a2 >= b ? a2 : b2 >= a ? b2 : std::min(a, b);
    }

    static S e() { return S(); }

    static S op(S l, S r) {
        if (l.lo > l.hi) return r;
        if (r.lo > r.hi) return l;
        S ret;
        ret.lo = std::min(l.lo, r.lo);
        ret.hi = std::max(l.hi, r.hi);
        ret.lo2 = second_lowest(l.lo, l.lo2, r.lo, r.lo2),
        ret.hi2 = second_highest(l.hi, l.hi2, r.hi, r.hi2);
        ret.sum = l.sum + r.sum;
        ret.sz = l.sz + r.sz;
        ret.nlo = l.nlo * (l.lo <= r.lo) + r.nlo * (r.lo <= l.lo);
        ret.nhi = l.nhi * (l.hi >= r.hi) + r.nhi * (r.hi >= l.hi);
        return ret;
    }

    struct F {
        Num lb, ub, bias;
        F() : lb(-INF), ub(INF), bias(0) {}
        F(Num chmax_, Num chmin_, Num add) : lb(chmax_), ub(chmin_), bias(add) {}
    };

    static F composition(F fnew, F fold) {
        F ret;
        ret.lb = std::max(std::min(fold.lb + fold.bias, fnew.ub), fnew.lb) - fold.bias;
        ret.ub = std::min(std::max(fold.ub + fold.bias, fnew.lb), fnew.ub) - fold.bias;
        ret.bias = fold.bias + fnew.bias;
        return ret;
    }

    static F id() { return F(); }

    static S mapping(F f, S x) {
        if (x.sz == 0) return e();

        // f の作用後 x の要素が 1 種類だけになるケース
        if (x.lo == x.hi or f.lb == f.ub or f.lb >= x.hi or f.ub <= x.lo) {
            return S(std::min(std::max(x.lo, f.lb), f.ub) + f.bias, x.sz);
        }

        // 2 種類 -> 1 種類
        if (x.lo2 == x.hi) {
            x.lo = x.hi2 = std::max(x.lo, f.lb) + f.bias;
            x.hi = x.lo2 = std::min(x.hi, f.ub) + f.bias;
            x.sum = x.lo * x.nlo + x.hi * x.nhi;
            return x;
        }

        // lo と lo2, hi と hi2 が潰れないケース
        if (f.lb < x.lo2 and f.ub > x.hi2) {
            Num nxt_lo = std::max(x.lo, f.lb), nxt_hi = std::min(x.hi, f.ub);
            x.sum += (nxt_lo - x.lo) * x.nlo - (x.hi - nxt_hi) * x.nhi + f.bias * x.sz;
            x.lo = nxt_lo + f.bias, x.hi = nxt_hi + f.bias, x.lo2 += f.bias, x.hi2 += f.bias;
            return x;
        }

        x.fail = 1;
        return x;
    }

public:
    static F Chmin(Num x) noexcept { return F(-INF, x, Num(0)); }
    static F Chmax(Num x) noexcept { return F(x, INF, Num(0)); }
    static F Add(Num x) noexcept { return F(-INF, INF, x); };

    static S Gen(Num x, unsigned sz = 1) noexcept { return S(x, sz); }

    using segtree = segtree_beats<S, op, e, F, mapping, composition, id>;
};
/* Usage:
using RCCARS = RangeChminChmaxAddRangeSum<long long, (1LL << 60)>;

vector<RCCARS::S> init;
for (long long a : A) init.push_back(RCCARS::Gen(a));

RCCARS::segtree segtree(init);

segtree.apply(l, r, RCCARS::Chmin(b));
segtree.apply(l, r, RCCARS::Chmax(b));
segtree.apply(l, r, RCCARS::Add(b));

long long ret = segtree.prod(l, r).sum;
*/
