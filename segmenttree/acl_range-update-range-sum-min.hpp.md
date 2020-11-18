---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: segmenttree/acl_lazysegtree.hpp
    title: segmenttree/acl_lazysegtree.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://codeforces.com/contest/1439/submission/98816580>
  bundledCode: "#line 2 \"segmenttree/acl_range-update-range-sum-min.hpp\"\n#include\
    \ <algorithm>\n\n// CUT begin\n#line 1 \"segmenttree/acl_lazysegtree.hpp\"\n//\
    \ Reference: <https://atcoder.github.io/ac-library/document_ja/lazysegtree.html>\n\
    //            <https://betrue12.hateblo.jp/entry/2020/09/22/194541>\n//      \
    \      <https://betrue12.hateblo.jp/entry/2020/09/23/005940>\n#ifndef ATCODER_INTERNAL_BITOP_HPP\n\
    #define ATCODER_INTERNAL_BITOP_HPP 1\n\n#ifdef _MSC_VER\n#include <intrin.h>\n\
    #endif\n\nnamespace atcoder {\n\nnamespace internal {\n\n// @param n `0 <= n`\n\
    // @return minimum non-negative `x` s.t. `n <= 2**x`\nint ceil_pow2(int n) {\n\
    \    int x = 0;\n    while ((1U << x) < (unsigned int)(n)) x++;\n    return x;\n\
    }\n\n// @param n `1 <= n`\n// @return minimum non-negative `x` s.t. `(n & (1 <<\
    \ x)) != 0`\nint bsf(unsigned int n) {\n#ifdef _MSC_VER\n    unsigned long index;\n\
    \    _BitScanForward(&index, n);\n    return index;\n#else\n    return __builtin_ctz(n);\n\
    #endif\n}\n\n} // namespace internal\n\n} // namespace atcoder\n\n#endif // ATCODER_INTERNAL_BITOP_HPP\n\
    #ifndef ATCODER_LAZYSEGTREE_HPP\n#define ATCODER_LAZYSEGTREE_HPP 1\n\n#line 44\
    \ \"segmenttree/acl_lazysegtree.hpp\"\n#include <cassert>\n#include <iostream>\n\
    #include <vector>\n\n// #include \"atcoder/internal_bit\"\n\nnamespace atcoder\
    \ {\n\ntemplate <class S, S (*op)(S, S), S (*e)(), class F, S (*mapping)(F, S),\
    \ F (*composition)(F, F), F (*id)()> struct lazy_segtree {\npublic:\n    lazy_segtree()\
    \ : lazy_segtree(0) {}\n    lazy_segtree(int n) : lazy_segtree(std::vector<S>(n,\
    \ e())) {}\n    lazy_segtree(const std::vector<S>& v) : _n(int(v.size())) {\n\
    \        log = internal::ceil_pow2(_n);\n        size = 1 << log;\n        d =\
    \ std::vector<S>(2 * size, e());\n        lz = std::vector<F>(size, id());\n \
    \       for (int i = 0; i < _n; i++) d[size + i] = v[i];\n        for (int i =\
    \ size - 1; i >= 1; i--) { update(i); }\n    }\n\n    void set(int p, S x) {\n\
    \        assert(0 <= p && p < _n);\n        p += size;\n        for (int i = log;\
    \ i >= 1; i--) push(p >> i);\n        d[p] = x;\n        for (int i = 1; i <=\
    \ log; i++) update(p >> i);\n    }\n\n    S get(int p) {\n        assert(0 <=\
    \ p && p < _n);\n        p += size;\n        for (int i = log; i >= 1; i--) push(p\
    \ >> i);\n        return d[p];\n    }\n\n    S prod(int l, int r) {\n        assert(0\
    \ <= l && l <= r && r <= _n);\n        if (l == r) return e();\n\n        l +=\
    \ size;\n        r += size;\n\n        for (int i = log; i >= 1; i--) {\n    \
    \        if (((l >> i) << i) != l) push(l >> i);\n            if (((r >> i) <<\
    \ i) != r) push(r >> i);\n        }\n\n        S sml = e(), smr = e();\n     \
    \   while (l < r) {\n            if (l & 1) sml = op(sml, d[l++]);\n         \
    \   if (r & 1) smr = op(d[--r], smr);\n            l >>= 1;\n            r >>=\
    \ 1;\n        }\n\n        return op(sml, smr);\n    }\n\n    S all_prod() { return\
    \ d[1]; }\n\n    void apply(int p, F f) {\n        assert(0 <= p && p < _n);\n\
    \        p += size;\n        for (int i = log; i >= 1; i--) push(p >> i);\n  \
    \      d[p] = mapping(f, d[p]);\n        for (int i = 1; i <= log; i++) update(p\
    \ >> i);\n    }\n    void apply(int l, int r, F f) {\n        assert(0 <= l &&\
    \ l <= r && r <= _n);\n        if (l == r) return;\n\n        l += size;\n   \
    \     r += size;\n\n        for (int i = log; i >= 1; i--) {\n            if (((l\
    \ >> i) << i) != l) push(l >> i);\n            if (((r >> i) << i) != r) push((r\
    \ - 1) >> i);\n        }\n\n        {\n            int l2 = l, r2 = r;\n     \
    \       while (l < r) {\n                if (l & 1) all_apply(l++, f);\n     \
    \           if (r & 1) all_apply(--r, f);\n                l >>= 1;\n        \
    \        r >>= 1;\n            }\n            l = l2;\n            r = r2;\n \
    \       }\n\n        for (int i = 1; i <= log; i++) {\n            if (((l >>\
    \ i) << i) != l) update(l >> i);\n            if (((r >> i) << i) != r) update((r\
    \ - 1) >> i);\n        }\n    }\n\n    template <bool (*g)(S)> int max_right(int\
    \ l) {\n        return max_right(l, [](S x) { return g(x); });\n    }\n    template\
    \ <class G> int max_right(int l, G g) {\n        assert(0 <= l && l <= _n);\n\
    \        assert(g(e()));\n        if (l == _n) return _n;\n        l += size;\n\
    \        for (int i = log; i >= 1; i--) push(l >> i);\n        S sm = e();\n \
    \       do {\n            while (l % 2 == 0) l >>= 1;\n            if (!g(op(sm,\
    \ d[l]))) {\n                while (l < size) {\n                    push(l);\n\
    \                    l = (2 * l);\n                    if (g(op(sm, d[l]))) {\n\
    \                        sm = op(sm, d[l]);\n                        l++;\n  \
    \                  }\n                }\n                return l - size;\n  \
    \          }\n            sm = op(sm, d[l]);\n            l++;\n        } while\
    \ ((l & -l) != l);\n        return _n;\n    }\n\n    template <bool (*g)(S)> int\
    \ min_left(int r) {\n        return min_left(r, [](S x) { return g(x); });\n \
    \   }\n    template <class G> int min_left(int r, G g) {\n        assert(0 <=\
    \ r && r <= _n);\n        assert(g(e()));\n        if (r == 0) return 0;\n   \
    \     r += size;\n        for (int i = log; i >= 1; i--) push((r - 1) >> i);\n\
    \        S sm = e();\n        do {\n            r--;\n            while (r > 1\
    \ && (r % 2)) r >>= 1;\n            if (!g(op(d[r], sm))) {\n                while\
    \ (r < size) {\n                    push(r);\n                    r = (2 * r +\
    \ 1);\n                    if (g(op(d[r], sm))) {\n                        sm\
    \ = op(d[r], sm);\n                        r--;\n                    }\n     \
    \           }\n                return r + 1 - size;\n            }\n         \
    \   sm = op(d[r], sm);\n        } while ((r & -r) != r);\n        return 0;\n\
    \    }\n\nprivate:\n    int _n, size, log;\n    std::vector<S> d;\n    std::vector<F>\
    \ lz;\n\n    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }\n    void\
    \ all_apply(int k, F f) {\n        d[k] = mapping(f, d[k]);\n        if (k < size)\
    \ lz[k] = composition(f, lz[k]);\n    }\n    void push(int k) {\n        all_apply(2\
    \ * k, lz[k]);\n        all_apply(2 * k + 1, lz[k]);\n        lz[k] = id();\n\
    \    }\n};\n} // namespace atcoder\n#endif // ATCODER_LAZYSEGTREE_HPP\n#line 6\
    \ \"segmenttree/acl_range-update-range-sum-min.hpp\"\nnamespace rangeupdaterangesummin\
    \ {\nusing Int = long long;\nconst Int INF = 101010101010LL;\nstruct S {\n   \
    \ Int sum;\n    int sz;\n    Int minval;\n};\nusing F = std::pair<bool, Int>;\n\
    S op(S a, S b) { return S{a.sum + b.sum, a.sz + b.sz, std::min(a.minval, b.minval)};\
    \ }\nS mapping(F f, S x) { return f.first ? S{x.sz * f.second, x.sz, f.second}\
    \ : x; }\nF composition(F later, F conventional) { return later.first ? later\
    \ : conventional; }\nS e() { return S{0, 0, INF}; }\nF id() { return std::make_pair(false,\
    \ INF); }\nusing RangeUpdateRangeSumMin = atcoder::lazy_segtree<S, op, e, F, mapping,\
    \ composition, id>;\n}; // namespace rangeupdaterangesummin\nusing rangeupdaterangesummin::RangeUpdateRangeSumMin;\n\
    using rangeupdaterangesummin::S;\n// Example of usage <https://codeforces.com/contest/1439/submission/98816580>\n"
  code: "#pragma once\n#include <algorithm>\n\n// CUT begin\n#include \"acl_lazysegtree.hpp\"\
    \nnamespace rangeupdaterangesummin {\nusing Int = long long;\nconst Int INF =\
    \ 101010101010LL;\nstruct S {\n    Int sum;\n    int sz;\n    Int minval;\n};\n\
    using F = std::pair<bool, Int>;\nS op(S a, S b) { return S{a.sum + b.sum, a.sz\
    \ + b.sz, std::min(a.minval, b.minval)}; }\nS mapping(F f, S x) { return f.first\
    \ ? S{x.sz * f.second, x.sz, f.second} : x; }\nF composition(F later, F conventional)\
    \ { return later.first ? later : conventional; }\nS e() { return S{0, 0, INF};\
    \ }\nF id() { return std::make_pair(false, INF); }\nusing RangeUpdateRangeSumMin\
    \ = atcoder::lazy_segtree<S, op, e, F, mapping, composition, id>;\n}; // namespace\
    \ rangeupdaterangesummin\nusing rangeupdaterangesummin::RangeUpdateRangeSumMin;\n\
    using rangeupdaterangesummin::S;\n// Example of usage <https://codeforces.com/contest/1439/submission/98816580>\n"
  dependsOn:
  - segmenttree/acl_lazysegtree.hpp
  isVerificationFile: false
  path: segmenttree/acl_range-update-range-sum-min.hpp
  requiredBy: []
  timestamp: '2020-11-18 23:19:38+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: segmenttree/acl_range-update-range-sum-min.hpp
layout: document
redirect_from:
- /library/segmenttree/acl_range-update-range-sum-min.hpp
- /library/segmenttree/acl_range-update-range-sum-min.hpp.html
title: segmenttree/acl_range-update-range-sum-min.hpp
---
