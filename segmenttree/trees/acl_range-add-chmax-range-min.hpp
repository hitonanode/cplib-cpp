#pragma once
#include "../acl_lazysegtree.hpp"
#include <algorithm>

namespace RangeAddChmaxRangeMin {

using S = long long;
constexpr S INF = 1LL << 60;

S e() { return INF; }

S op(S l, S r) { return std::min(l, r); }

struct F {
    // meaning: max(lower_bound, x) + bias
    S lower_bound, bias;
    F() : lower_bound(-INF), bias(0) {}
    F(S lower_bound, S bias) : lower_bound(lower_bound), bias(bias) {}
    static F chmax(S x) { return F(x, S()); }
    static F add(S x) { return F(-INF, x); }
};

F id() { return F(); }

S mapping(F f, S x) { return std::max(f.lower_bound, x) + f.bias; }

F composition(F fnew, F gold) {
    return F(std::max(gold.lower_bound + gold.bias, fnew.lower_bound) - gold.bias,
             gold.bias + fnew.bias);
}

using segtree = atcoder::lazy_segtree<S, op, e, F, mapping, composition, id>;
}; // namespace RangeAddChmaxRangeMin
