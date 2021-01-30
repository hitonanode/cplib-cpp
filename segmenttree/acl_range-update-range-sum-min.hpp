#pragma once
#include <algorithm>

// CUT begin
#include "acl_lazysegtree.hpp"
namespace rangeupdaterangesummin {
using Int = long long;
const Int INF = 101010101010LL;
struct S {
    Int sum;
    int sz;
    Int minval;
};
using F = std::pair<bool, Int>;
S op(S a, S b) { return S{a.sum + b.sum, a.sz + b.sz, std::min(a.minval, b.minval)}; }
S mapping(F f, S x) { return f.first ? S{x.sz * f.second, x.sz, f.second} : x; }
F composition(F later, F conventional) { return later.first ? later : conventional; }
S e() { return S{0, 0, INF}; }
F id() { return std::make_pair(false, INF); }
using RangeUpdateRangeSumMin = atcoder::lazy_segtree<S, op, e, F, mapping, composition, id>;
}; // namespace rangeupdaterangesummin
using rangeupdaterangesummin::RangeUpdateRangeSumMin;
using rangeupdaterangesummin::S;
// Example of usage: https://codeforces.com/contest/1439/submission/98816580
