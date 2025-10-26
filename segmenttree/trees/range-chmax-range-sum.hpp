#pragma once
#include <algorithm>
#include <type_traits>
#include "../acl_beats.hpp"

// Verified: https://yukicoder.me/problems/no/3314
template <typename Num, Num INF> struct RangeChmaxRangeSum {
    static_assert(std::is_signed<Num>::value, "Num must be signed");

    struct S {
        Num lo, lo2, sum;
        unsigned sz, nlo;
        bool fail;
        S() : lo(INF), lo2(INF), sum(0), sz(0), nlo(0), fail(false) {}
        S(Num x, unsigned sz_ = 1)
            : lo(x), lo2(INF), sum(Num(x) * sz_), sz(sz_), nlo(sz_), fail(false) {}
    };

private:
    using F = Num;
    RangeChmaxRangeSum() = default;

    static Num second_lowest(Num a, Num a2, Num c, Num c2) noexcept { // a < a2, c < c2
        return a == c ? std::min(a2, c2) : a2 <= c ? a2 : c2 <= a ? c2 : std::max(a, c);
    }

    static S op(S l, S r) {
        S ret;
        ret.lo = std::min(l.lo, r.lo);
        ret.lo2 = second_lowest(l.lo, l.lo2, r.lo, r.lo2);
        ret.sum = l.sum + r.sum, ret.sz = l.sz + r.sz;
        ret.nlo = l.nlo * (l.lo <= r.lo) + r.nlo * (r.lo <= l.lo);
        return ret;
    }

    static S e() { return S{}; }

    static F composition(F fnew, F fold) { return std::max(fnew, fold); }

    static F id() { return -INF; }

    static S mapping(F f, S x) {
        if (x.sz == 0) return e();
        if (f < x.lo2) {
            Num nxt_lo = std::max(x.lo, f);
            x.sum += (nxt_lo - x.lo) * x.nlo;
            x.lo = nxt_lo;
            return x;
        }
        x.fail = 1;
        return x;
    }

public:
    static F Chmax(Num x) { return x; }

    static S Gen(Num x, unsigned sz = 1) { return S{x, sz}; }

    using segtree = segtree_beats<S, op, e, F, mapping, composition, id>;
};
/* Usage:
using RCRS = RangeChmaxRangeSum<long long, (1LL << 60)>;
vector<RCRS::S> init;
for (auto a : A) init.push_back(RCRS::Gen(a, 1));
RCRS::segtree tree(init);

tree.apply(l, r, RCRS::Chmax(x));
auto p = tree.prod(l, r);
*/
