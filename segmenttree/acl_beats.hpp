#pragma once
#include "acl_lazysegtree.hpp"

template <class S, auto op, auto e, class F, auto mapping, auto composition, auto id>
class segtree_beats : public atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> {
    using Base = atcoder::lazy_segtree<S, op, e, F, mapping, composition, id>;
    using Base::lazy_segtree;
    void all_apply(int k, F f) override {
        Base::d[k] = mapping(f, Base::d[k]);
        if (k < Base::size) {
            Base::lz[k] = composition(f, Base::lz[k]);
            if (Base::d[k].fail) Base::push(k), Base::update(k);
        }
    }
};
