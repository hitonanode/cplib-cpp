#pragma once
#include "../modint.hpp"
#include "acl_lazysegtree.hpp"
#include <utility>

namespace rangeaffinerangesum {
using T = ModInt<998244353>;
using S = std::pair<T, size_t>;
using F = std::pair<T, T>;
S op(S l, S r) { return std::make_pair(l.first + r.first, l.second + r.second); }
S mapping(F f, S x) { return std::make_pair(f.first * x.first + f.second * x.second, x.second); }
F composition(F later, F conv) { return std::make_pair(conv.first * later.first, later.second + later.first * conv.second); }
S e() { return std::make_pair(0, 0); }
F id() { return std::make_pair(1, 0); }
using RangeAffineRangeSum = atcoder::lazy_segtree<S, op, e, F, mapping, composition, id>;
}; // namespace rangeaffinerangesum
using rangeaffinerangesum::F;
using rangeaffinerangesum::RangeAffineRangeSum;
using rangeaffinerangesum::S;
