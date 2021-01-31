#pragma once
#include "../acl_beats.hpp"

// CUT begin
// Verified: https://csacademy.com/contest/round-70/task/and-or-max
namespace RangeBitwiseAndOrRangeMax {
using UINT = uint32_t;
constexpr UINT digit = 20;
constexpr int mask = (1 << digit) - 1;

struct S {
    UINT max;
    UINT upper;
    UINT lower;
    bool fail;
    S(UINT x = 0) : max(x), upper(x), lower(x), fail(false) {}
};

S e() { return S(); }

S op(S l, S r) {
    l.max = std::max(l.max, r.max);
    l.upper |= r.upper;
    l.lower &= r.lower;
    return l;
}

struct F {
    UINT bit_and;
    UINT bit_or;
    F() : bit_and(mask), bit_or(0) {}
    F(UINT a, UINT o) : bit_and(a), bit_or(o) {}
    static F b_and(UINT a) noexcept { return {a, 0}; }
    static F b_or(UINT a) noexcept { return {mask, a}; }
};

F composition(F fnew, F fold) { return F{fnew.bit_and & fold.bit_and, fnew.bit_or | (fnew.bit_and & fold.bit_or)}; }

F id() { return F(); }

S mapping(F f, S x) {
    if ((x.upper - x.lower) & (~f.bit_and | f.bit_or)) {
        x.fail = true;
        return x;
    }
    x.upper = (x.upper & f.bit_and) | f.bit_or;
    x.lower = (x.lower & f.bit_and) | f.bit_or;
    x.max = (x.max & f.bit_and) | f.bit_or;
    return x;
}
using segtree = segtree_beats<S, op, e, F, mapping, composition, id>;
} // namespace RangeBitwiseAndOrRangeMax
