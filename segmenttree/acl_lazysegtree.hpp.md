---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: segmenttree/acl_beats.hpp
    title: Segment Tree Beats (based on atcoder::lazy_segtree)
  - icon: ':heavy_check_mark:'
    path: segmenttree/trees/acl_range-add-chmax-range-sum.hpp
    title: segmenttree/trees/acl_range-add-chmax-range-sum.hpp
  - icon: ':heavy_check_mark:'
    path: segmenttree/trees/acl_range-affine-range-sum.hpp
    title: segmenttree/trees/acl_range-affine-range-sum.hpp
  - icon: ':warning:'
    path: segmenttree/trees/acl_range-bitwiseandor-range-max.hpp
    title: segmenttree/trees/acl_range-bitwiseandor-range-max.hpp
  - icon: ':heavy_check_mark:'
    path: segmenttree/trees/acl_range-update-gcd-range-max-sum.hpp
    title: segmenttree/trees/acl_range-update-gcd-range-max-sum.hpp
  - icon: ':warning:'
    path: segmenttree/trees/acl_range-update-range-sum-min.hpp
    title: segmenttree/trees/acl_range-update-range-sum-min.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: segmenttree/test/acl_range-affine-range-sum.test.cpp
    title: segmenttree/test/acl_range-affine-range-sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: segmenttree/test/beats.test.cpp
    title: segmenttree/test/beats.test.cpp
  - icon: ':heavy_check_mark:'
    path: segmenttree/test/beats_gcd.test.cpp
    title: segmenttree/test/beats_gcd.test.cpp
  - icon: ':heavy_check_mark:'
    path: segmenttree/test/beats_range-add-chmax-range-sum.test.cpp
    title: segmenttree/test/beats_range-add-chmax-range-sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://atcoder.github.io/ac-library/document_ja/lazysegtree.html
    - https://betrue12.hateblo.jp/entry/2020/09/22/194541
    - https://betrue12.hateblo.jp/entry/2020/09/23/005940
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 355, in update\n    raise BundleErrorAt(path, i + 1, \"found codes out\
    \ of include guard\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ segmenttree/acl_lazysegtree.hpp: line 37: found codes out of include guard\n"
  code: "#ifndef ATCODER_INTERNAL_BITOP_HPP\n#define ATCODER_INTERNAL_BITOP_HPP 1\n\
    \n#ifdef _MSC_VER\n#include <intrin.h>\n#endif\n\nnamespace atcoder {\n\nnamespace\
    \ internal {\n\n// @param n `0 <= n`\n// @return minimum non-negative `x` s.t.\
    \ `n <= 2**x`\nint ceil_pow2(int n) {\n    int x = 0;\n    while ((1U << x) <\
    \ (unsigned int)(n)) x++;\n    return x;\n}\n\n// @param n `1 <= n`\n// @return\
    \ minimum non-negative `x` s.t. `(n & (1 << x)) != 0`\nint bsf(unsigned int n)\
    \ {\n#ifdef _MSC_VER\n    unsigned long index;\n    _BitScanForward(&index, n);\n\
    \    return index;\n#else\n    return __builtin_ctz(n);\n#endif\n}\n\n} // namespace\
    \ internal\n\n} // namespace atcoder\n\n#endif // ATCODER_INTERNAL_BITOP_HPP\n\
    #ifndef ATCODER_LAZYSEGTREE_HPP\n#define ATCODER_LAZYSEGTREE_HPP 1\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <iostream>\n#include <vector>\n\n\
    // #include \"atcoder/internal_bit\"\n\nnamespace atcoder {\n\ntemplate <class\
    \ S, S (*op)(S, S), S (*e)(), class F, S (*mapping)(F, S), F (*composition)(F,\
    \ F),\n          F (*id)()>\nstruct lazy_segtree {\npublic:\n    lazy_segtree()\
    \ : lazy_segtree(0) {}\n    explicit lazy_segtree(int n) : lazy_segtree(std::vector<S>(n,\
    \ e())) {}\n    explicit lazy_segtree(const std::vector<S> &v) : _n(int(v.size()))\
    \ {\n        log = internal::ceil_pow2(_n);\n        size = 1 << log;\n      \
    \  d = std::vector<S>(2 * size, e());\n        lz = std::vector<F>(size, id());\n\
    \        for (int i = 0; i < _n; i++) d[size + i] = v[i];\n        for (int i\
    \ = size - 1; i >= 1; i--) { update(i); }\n    }\n\n    void set(int p, S x) {\n\
    \        assert(0 <= p && p < _n);\n        p += size;\n        for (int i = log;\
    \ i >= 1; i--) push(p >> i);\n        d[p] = x;\n        for (int i = 1; i <=\
    \ log; i++) update(p >> i);\n    }\n\n    S get(int p) const {\n        assert(0\
    \ <= p && p < _n);\n        p += size;\n        for (int i = log; i >= 1; i--)\
    \ push(p >> i);\n        return d[p];\n    }\n\n    S prod(int l, int r) const\
    \ {\n        assert(0 <= l && l <= r && r <= _n);\n        if (l == r) return\
    \ e();\n\n        l += size;\n        r += size;\n\n        for (int i = log;\
    \ i >= 1; i--) {\n            if (((l >> i) << i) != l) push(l >> i);\n      \
    \      if (((r >> i) << i) != r) push((r - 1) >> i);\n        }\n\n        S sml\
    \ = e(), smr = e();\n        while (l < r) {\n            if (l & 1) sml = op(sml,\
    \ d[l++]);\n            if (r & 1) smr = op(d[--r], smr);\n            l >>= 1;\n\
    \            r >>= 1;\n        }\n\n        return op(sml, smr);\n    }\n\n  \
    \  S all_prod() const { return d[1]; }\n\n    void apply(int p, F f) {\n     \
    \   assert(0 <= p && p < _n);\n        p += size;\n        for (int i = log; i\
    \ >= 1; i--) push(p >> i);\n        d[p] = mapping(f, d[p]);\n        for (int\
    \ i = 1; i <= log; i++) update(p >> i);\n    }\n    void apply(int l, int r, F\
    \ f) {\n        assert(0 <= l && l <= r && r <= _n);\n        if (l == r) return;\n\
    \n        l += size;\n        r += size;\n\n        for (int i = log; i >= 1;\
    \ i--) {\n            if (((l >> i) << i) != l) push(l >> i);\n            if\
    \ (((r >> i) << i) != r) push((r - 1) >> i);\n        }\n\n        {\n       \
    \     int l2 = l, r2 = r;\n            while (l < r) {\n                if (l\
    \ & 1) all_apply(l++, f);\n                if (r & 1) all_apply(--r, f);\n   \
    \             l >>= 1;\n                r >>= 1;\n            }\n            l\
    \ = l2;\n            r = r2;\n        }\n\n        for (int i = 1; i <= log; i++)\
    \ {\n            if (((l >> i) << i) != l) update(l >> i);\n            if (((r\
    \ >> i) << i) != r) update((r - 1) >> i);\n        }\n    }\n\n    template <bool\
    \ (*g)(S)> int max_right(int l) const {\n        return max_right(l, [](S x) {\
    \ return g(x); });\n    }\n    template <class G> int max_right(int l, G g) const\
    \ {\n        assert(0 <= l && l <= _n);\n        assert(g(e()));\n        if (l\
    \ == _n) return _n;\n        l += size;\n        for (int i = log; i >= 1; i--)\
    \ push(l >> i);\n        S sm = e();\n        do {\n            while (l % 2 ==\
    \ 0) l >>= 1;\n            if (!g(op(sm, d[l]))) {\n                while (l <\
    \ size) {\n                    push(l);\n                    l = (2 * l);\n  \
    \                  if (g(op(sm, d[l]))) {\n                        sm = op(sm,\
    \ d[l]);\n                        l++;\n                    }\n              \
    \  }\n                return l - size;\n            }\n            sm = op(sm,\
    \ d[l]);\n            l++;\n        } while ((l & -l) != l);\n        return _n;\n\
    \    }\n\n    template <bool (*g)(S)> int min_left(int r) const {\n        return\
    \ min_left(r, [](S x) { return g(x); });\n    }\n    template <class G> int min_left(int\
    \ r, G g) const {\n        assert(0 <= r && r <= _n);\n        assert(g(e()));\n\
    \        if (r == 0) return 0;\n        r += size;\n        for (int i = log;\
    \ i >= 1; i--) push((r - 1) >> i);\n        S sm = e();\n        do {\n      \
    \      r--;\n            while (r > 1 && (r % 2)) r >>= 1;\n            if (!g(op(d[r],\
    \ sm))) {\n                while (r < size) {\n                    push(r);\n\
    \                    r = (2 * r + 1);\n                    if (g(op(d[r], sm)))\
    \ {\n                        sm = op(d[r], sm);\n                        r--;\n\
    \                    }\n                }\n                return r + 1 - size;\n\
    \            }\n            sm = op(d[r], sm);\n        } while ((r & -r) != r);\n\
    \        return 0;\n    }\n\nprotected:\n    int _n, size, log;\n    mutable std::vector<S>\
    \ d;\n    mutable std::vector<F> lz;\n\n    void update(int k) const { d[k] =\
    \ op(d[2 * k], d[2 * k + 1]); }\n    virtual void all_apply(int k, F f) const\
    \ {\n        d[k] = mapping(f, d[k]);\n        if (k < size) lz[k] = composition(f,\
    \ lz[k]);\n    }\n    void push(int k) const {\n        all_apply(2 * k, lz[k]);\n\
    \        all_apply(2 * k + 1, lz[k]);\n        lz[k] = id();\n    }\n};\n} //\
    \ namespace atcoder\n#endif // ATCODER_LAZYSEGTREE_HPP\n// Reference: https://atcoder.github.io/ac-library/document_ja/lazysegtree.html\n\
    //            https://betrue12.hateblo.jp/entry/2020/09/22/194541\n//        \
    \    https://betrue12.hateblo.jp/entry/2020/09/23/005940\n/*\nstruct S {};\nS\
    \ op(S l, S r) {\n    return {};\n}\nS e() { return {}; };\nusing F = bool;\n\
    S mp(F f, S x) {\n    return x;\n}\nF composition(F fnew, F gold) { return fnew\
    \ ^ gold; }\nF id() { return false; }\n\nvector<S> A;\natcoder::lazy_segtree<S,\
    \ op, e, F, mp, composition, id> seg(A);\n*/\n"
  dependsOn: []
  isVerificationFile: false
  path: segmenttree/acl_lazysegtree.hpp
  requiredBy:
  - segmenttree/trees/acl_range-affine-range-sum.hpp
  - segmenttree/trees/acl_range-add-chmax-range-sum.hpp
  - segmenttree/trees/acl_range-update-gcd-range-max-sum.hpp
  - segmenttree/trees/acl_range-update-range-sum-min.hpp
  - segmenttree/trees/acl_range-bitwiseandor-range-max.hpp
  - segmenttree/acl_beats.hpp
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - segmenttree/test/beats_gcd.test.cpp
  - segmenttree/test/acl_range-affine-range-sum.test.cpp
  - segmenttree/test/beats_range-add-chmax-range-sum.test.cpp
  - segmenttree/test/beats.test.cpp
documentation_of: segmenttree/acl_lazysegtree.hpp
layout: document
title: Lazy Segtree (based on atcoder::lazy_segtree)
---

ACL-based lazy segtree

## Example

```cpp
struct S {};
S op(S l, S r) {
    return {};
}
S e() { return {}; };
using F = bool;
S mp(F f, S x) {
    return x;
}
F composition(F fnew, F gold) { return fnew ^ gold; }
F id() { return false; }

vector<S> A;
atcoder::lazy_segtree<S, op, e, F, mp, composition, id> seg(A);
```

## Link

- [ACL reference](https://atcoder.github.io/ac-library/production/document_ja/lazysegtree.html)
