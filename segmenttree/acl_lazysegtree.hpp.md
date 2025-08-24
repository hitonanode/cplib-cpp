---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: segmenttree/acl_beats.hpp
    title: Segment Tree Beats (based on atcoder::lazy_segtree)
  - icon: ':warning:'
    path: segmenttree/trees/acl_range-add-chmax-range-min.hpp
    title: segmenttree/trees/acl_range-add-chmax-range-min.hpp
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
    path: segmenttree/test/beats_random_test.test.cpp
    title: segmenttree/test/beats_random_test.test.cpp
  - icon: ':heavy_check_mark:'
    path: segmenttree/test/beats_range-add-chmax-range-sum.test.cpp
    title: segmenttree/test/beats_range-add-chmax-range-sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://atcoder.github.io/ac-library/production/document_ja/lazysegtree.html
    - https://betrue12.hateblo.jp/entry/2020/09/22/194541
    - https://betrue12.hateblo.jp/entry/2020/09/23/005940
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.13.7/x64/lib/python3.13/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ~~~~~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.13.7/x64/lib/python3.13/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n    ~~~~~~~~~~~~~~^^^^^^\n  File\
    \ \"/opt/hostedtoolcache/Python/3.13.7/x64/lib/python3.13/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 355, in update\n    raise BundleErrorAt(path, i + 1, \"found codes out\
    \ of include guard\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ segmenttree/acl_lazysegtree.hpp: line 56: found codes out of include guard\n"
  code: "#ifndef ATCODER_INTERNAL_BITOP_HPP\n#define ATCODER_INTERNAL_BITOP_HPP 1\n\
    \n#ifdef _MSC_VER\n#include <intrin.h>\n#endif\n\n#if __cplusplus >= 202002L\n\
    #include <bit>\n#endif\n\nnamespace atcoder {\n\nnamespace internal {\n\n#if __cplusplus\
    \ >= 202002L\n\nusing std::bit_ceil;\n\n#else\n\n// @return same with std::bit::bit_ceil\n\
    unsigned int bit_ceil(unsigned int n) {\n    unsigned int x = 1;\n    while (x\
    \ < (unsigned int)(n)) x *= 2;\n    return x;\n}\n\n#endif\n\n// @param n `1 <=\
    \ n`\n// @return same with std::bit::countr_zero\nint countr_zero(unsigned int\
    \ n) {\n#ifdef _MSC_VER\n    unsigned long index;\n    _BitScanForward(&index,\
    \ n);\n    return index;\n#else\n    return __builtin_ctz(n);\n#endif\n}\n\n//\
    \ @param n `1 <= n`\n// @return same with std::bit::countr_zero\nconstexpr int\
    \ countr_zero_constexpr(unsigned int n) {\n    int x = 0;\n    while (!(n & (1\
    \ << x))) x++;\n    return x;\n}\n\n} // namespace internal\n\n} // namespace\
    \ atcoder\n\n#endif // ATCODER_INTERNAL_BITOP_HPP\n#ifndef ATCODER_LAZYSEGTREE_HPP\n\
    #define ATCODER_LAZYSEGTREE_HPP 1\n\n#include <cassert>\n#include <functional>\n\
    #include <vector>\n\n#include \"atcoder/internal_bit\"\n\nnamespace atcoder {\n\
    \ntemplate <class S, auto op, auto e, class F, auto mapping, auto composition,\
    \ auto id>\nstruct lazy_segtree {\n    static_assert(std::is_convertible_v<decltype(op),\
    \ std::function<S(S, S)>>,\n                  \"op must work as S(S, S)\");\n\
    \    static_assert(std::is_convertible_v<decltype(e), std::function<S()>>, \"\
    e must work as S()\");\n    static_assert(std::is_convertible_v<decltype(mapping),\
    \ std::function<S(F, S)>>,\n                  \"mapping must work as S(F, S)\"\
    );\n    static_assert(std::is_convertible_v<decltype(composition), std::function<F(F,\
    \ F)>>,\n                  \"composition must work as F(F, F)\");\n    static_assert(std::is_convertible_v<decltype(id),\
    \ std::function<F()>>, \"id must work as F()\");\n\npublic:\n    lazy_segtree()\
    \ : lazy_segtree(0) {}\n    explicit lazy_segtree(int n) : lazy_segtree(std::vector<S>(n,\
    \ e())) {}\n    explicit lazy_segtree(const std::vector<S> &v) : _n(int(v.size()))\
    \ {\n        size = (int)internal::bit_ceil((unsigned int)(_n));\n        log\
    \ = internal::countr_zero((unsigned int)size);\n        d = std::vector<S>(2 *\
    \ size, e());\n        lz = std::vector<F>(size, id());\n        for (int i =\
    \ 0; i < _n; i++) d[size + i] = v[i];\n        for (int i = size - 1; i >= 1;\
    \ i--) { update(i); }\n    }\n\n    void set(int p, S x) {\n        assert(0 <=\
    \ p && p < _n);\n        p += size;\n        for (int i = log; i >= 1; i--) push(p\
    \ >> i);\n        d[p] = x;\n        for (int i = 1; i <= log; i++) update(p >>\
    \ i);\n    }\n\n    S get(int p) {\n        assert(0 <= p && p < _n);\n      \
    \  p += size;\n        for (int i = log; i >= 1; i--) push(p >> i);\n        return\
    \ d[p];\n    }\n\n    S prod(int l, int r) {\n        assert(0 <= l && l <= r\
    \ && r <= _n);\n        if (l == r) return e();\n\n        l += size;\n      \
    \  r += size;\n\n        for (int i = log; i >= 1; i--) {\n            if (((l\
    \ >> i) << i) != l) push(l >> i);\n            if (((r >> i) << i) != r) push((r\
    \ - 1) >> i);\n        }\n\n        S sml = e(), smr = e();\n        while (l\
    \ < r) {\n            if (l & 1) sml = op(sml, d[l++]);\n            if (r & 1)\
    \ smr = op(d[--r], smr);\n            l >>= 1;\n            r >>= 1;\n       \
    \ }\n\n        return op(sml, smr);\n    }\n\n    S all_prod() { return d[1];\
    \ }\n\n    void apply(int p, F f) {\n        assert(0 <= p && p < _n);\n     \
    \   p += size;\n        for (int i = log; i >= 1; i--) push(p >> i);\n       \
    \ d[p] = mapping(f, d[p]);\n        for (int i = 1; i <= log; i++) update(p >>\
    \ i);\n    }\n    void apply(int l, int r, F f) {\n        assert(0 <= l && l\
    \ <= r && r <= _n);\n        if (l == r) return;\n\n        l += size;\n     \
    \   r += size;\n\n        for (int i = log; i >= 1; i--) {\n            if (((l\
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
    \    }\n\nprotected:\n    int _n, size, log;\n    std::vector<S> d;\n    std::vector<F>\
    \ lz;\n\n    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }\n    virtual\
    \ void all_apply(int k, F f) {\n        d[k] = mapping(f, d[k]);\n        if (k\
    \ < size) lz[k] = composition(f, lz[k]);\n    }\n    void push(int k) {\n    \
    \    all_apply(2 * k, lz[k]);\n        all_apply(2 * k + 1, lz[k]);\n        lz[k]\
    \ = id();\n    }\n};\n} // namespace atcoder\n#endif // ATCODER_LAZYSEGTREE_HPP\n\
    // Reference: https://atcoder.github.io/ac-library/production/document_ja/lazysegtree.html\n\
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
  - segmenttree/trees/acl_range-add-chmax-range-min.hpp
  - segmenttree/trees/acl_range-bitwiseandor-range-max.hpp
  - segmenttree/trees/acl_range-add-chmax-range-sum.hpp
  - segmenttree/trees/acl_range-update-range-sum-min.hpp
  - segmenttree/trees/acl_range-update-gcd-range-max-sum.hpp
  - segmenttree/acl_beats.hpp
  timestamp: '2025-08-24 23:32:38+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - segmenttree/test/beats_range-add-chmax-range-sum.test.cpp
  - segmenttree/test/beats.test.cpp
  - segmenttree/test/acl_range-affine-range-sum.test.cpp
  - segmenttree/test/beats_random_test.test.cpp
  - segmenttree/test/beats_gcd.test.cpp
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
