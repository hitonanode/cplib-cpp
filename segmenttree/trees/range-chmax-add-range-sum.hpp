#pragma once
#include "../acl_beats.hpp"
#include <algorithm>
#include <type_traits>

// Verified: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0427
template <typename Num, Num INF> struct RangeChmaxAddRangeSum {
    static_assert(std::is_signed<Num>::value, "Num must be signed");

    static Num second_lowest(Num a, Num a2, Num c, Num c2) noexcept { // a < a2, c < c2
        return a == c ? std::min(a2, c2) : a2 <= c ? a2 : c2 <= a ? c2 : std::max(a, c);
    }

    struct S {
        Num lo, lo2, sum;
        unsigned sz, nlo;
        bool fail;
        S() : lo(INF), lo2(INF), sum(0), sz(0), nlo(0), fail(false) {}
        S(Num x, unsigned sz_ = 1)
            : lo(x), lo2(INF), sum(Num(x) * sz_), sz(sz_), nlo(sz_), fail(false) {}
    };

private:
    static S e() { return S(); }

    static S op(S l, S r) {
        S ret;
        ret.lo = std::min(l.lo, r.lo);
        ret.lo2 = second_lowest(l.lo, l.lo2, r.lo, r.lo2);
        ret.sum = l.sum + r.sum, ret.sz = l.sz + r.sz;
        ret.nlo = l.nlo * (l.lo <= r.lo) + r.nlo * (r.lo <= l.lo);
        return ret;
    }

    struct F {
        Num lb, bias;
        F() : lb(-INF), bias(0) {}
        F(Num chmax_, Num add) : lb(chmax_), bias(add) {}
    };

    static F id() { return F(); }

    static S mapping(F f, S x) {
        if (x.sz == 0) return e();
        if (f.lb < x.lo2) {
            Num nxt_lo = std::max(x.lo, f.lb);
            x.sum += (nxt_lo - x.lo) * x.nlo + f.bias * x.sz;
            x.lo = nxt_lo + f.bias, x.lo2 += f.bias;
            return x;
        }
        x.fail = 1;
        return x;
    }

public:
    static F composition(F fnew, F fold) {
        F ret;
        ret.lb = std::max(fold.lb + fold.bias, fnew.lb) - fold.bias;
        ret.bias = fold.bias + fnew.bias;
        return ret;
    }

    static F Chmax(Num x) noexcept { return F(x, Num(0)); }
    static F Add(Num x) noexcept { return F(-INF, x); };

    static S Gen(Num x, unsigned sz = 1) { return S{x, sz}; }

    using segtree = segtree_beats<S, op, e, F, mapping, composition, id>;
};
/* Usage:
using RCARS = RangeChmaxAddRangeSum<long long, (1LL << 60)>;
vector<RCARS::S> init;
for (auto a : A) init.push_back(RCARS::Gen(a, 1));
RCARS::segtree tree(init);

tree.apply(l, r, RCARS::Chmax(x));
tree.apply(l, r, RCARS::Add(x));
auto p = tree.prod(l, r);
*/
