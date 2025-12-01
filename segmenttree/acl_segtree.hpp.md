---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: segmenttree/rangetree.hpp
    title: "Range Tree \uFF08\u9818\u57DF\u6728\uFF09"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: segmenttree/test/acl_rmq.test.cpp
    title: segmenttree/test/acl_rmq.test.cpp
  - icon: ':heavy_check_mark:'
    path: segmenttree/test/acl_rsq.test.cpp
    title: segmenttree/test/acl_rsq.test.cpp
  - icon: ':heavy_check_mark:'
    path: segmenttree/test/rangetree.test.cpp
    title: segmenttree/test/rangetree.test.cpp
  - icon: ':heavy_check_mark:'
    path: segmenttree/test/rangetree.yuki1625.test.cpp
    title: segmenttree/test/rangetree.yuki1625.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://atcoder.github.io/ac-library/production/document_ja/segtree.html
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.14.0/x64/lib/python3.14/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ~~~~~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.14.0/x64/lib/python3.14/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n    ~~~~~~~~~~~~~~^^^^^^\n  File\
    \ \"/opt/hostedtoolcache/Python/3.14.0/x64/lib/python3.14/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 355, in update\n    raise BundleErrorAt(path, i + 1, \"found codes out\
    \ of include guard\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ segmenttree/acl_segtree.hpp: line 48: found codes out of include guard\n"
  code: "#ifndef ATCODER_INTERNAL_BITOP_HPP\n#define ATCODER_INTERNAL_BITOP_HPP 1\n\
    \n#ifdef _MSC_VER\n#include <intrin.h>\n#endif\n\n#if __cplusplus >= 202002L\n\
    #include <bit>\n#endif\n\nnamespace atcoder {\n\nnamespace internal {\n\n#if __cplusplus\
    \ >= 202002L\n\nusing std::bit_ceil;\n\n#else\n\n// @return same with std::bit::bit_ceil\n\
    unsigned int bit_ceil(unsigned int n) {\n    unsigned int x = 1;\n    while (x\
    \ < (unsigned int)(n)) x *= 2;\n    return x;\n}\n\n#endif\n\n// @param n `1 <=\
    \ n`\n// @return same with std::bit::countr_zero\nint countr_zero(unsigned int\
    \ n) {\n#ifdef _MSC_VER\n    unsigned long index;\n    _BitScanForward(&index,\
    \ n);\n    return index;\n#else\n    return __builtin_ctz(n);\n#endif\n}\n\n}\
    \ // namespace internal\n\n} // namespace atcoder\n\n#endif // ATCODER_INTERNAL_BITOP_HPP\n\
    \n#ifndef ATCODER_SEGTREE_HPP\n#define ATCODER_SEGTREE_HPP 1\n\n#include <cassert>\n\
    #include <functional>\n#include <vector>\n\n// #include \"atcoder/internal_bit\"\
    \n\nnamespace atcoder {\ntemplate <class S, auto op, auto e> struct segtree {\n\
    \    static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,\n\
    \                  \"op must work as S(S, S)\");\n    static_assert(std::is_convertible_v<decltype(e),\
    \ std::function<S()>>, \"e must work as S()\");\n\npublic:\n    segtree() : segtree(0)\
    \ {}\n    explicit segtree(int n) : segtree(std::vector<S>(n, e())) {}\n    explicit\
    \ segtree(const std::vector<S> &v) : _n(int(v.size())) {\n        size = (int)internal::bit_ceil((unsigned\
    \ int)(_n));\n        log = internal::countr_zero((unsigned int)size);\n     \
    \   d = std::vector<S>(2 * size, e());\n        for (int i = 0; i < _n; i++) d[size\
    \ + i] = v[i];\n        for (int i = size - 1; i >= 1; i--) { update(i); }\n \
    \   }\n\n    void set(int p, S x) {\n        assert(0 <= p && p < _n);\n     \
    \   p += size;\n        d[p] = x;\n        for (int i = 1; i <= log; i++) update(p\
    \ >> i);\n    }\n\n    S get(int p) const {\n        assert(0 <= p && p < _n);\n\
    \        return d[p + size];\n    }\n\n    S prod(int l, int r) const {\n    \
    \    assert(0 <= l && l <= r && r <= _n);\n        S sml = e(), smr = e();\n \
    \       l += size;\n        r += size;\n\n        while (l < r) {\n          \
    \  if (l & 1) sml = op(sml, d[l++]);\n            if (r & 1) smr = op(d[--r],\
    \ smr);\n            l >>= 1;\n            r >>= 1;\n        }\n        return\
    \ op(sml, smr);\n    }\n\n    S all_prod() const { return d[1]; }\n\n    template\
    \ <bool (*f)(S)> int max_right(int l) const {\n        return max_right(l, [](S\
    \ x) { return f(x); });\n    }\n    template <class F> int max_right(int l, F\
    \ f) const {\n        assert(0 <= l && l <= _n);\n        assert(f(e()));\n  \
    \      if (l == _n) return _n;\n        l += size;\n        S sm = e();\n    \
    \    do {\n            while (l % 2 == 0) l >>= 1;\n            if (!f(op(sm,\
    \ d[l]))) {\n                while (l < size) {\n                    l = (2 *\
    \ l);\n                    if (f(op(sm, d[l]))) {\n                        sm\
    \ = op(sm, d[l]);\n                        l++;\n                    }\n     \
    \           }\n                return l - size;\n            }\n            sm\
    \ = op(sm, d[l]);\n            l++;\n        } while ((l & -l) != l);\n      \
    \  return _n;\n    }\n\n    template <bool (*f)(S)> int min_left(int r) const\
    \ {\n        return min_left(r, [](S x) { return f(x); });\n    }\n    template\
    \ <class F> int min_left(int r, F f) const {\n        assert(0 <= r && r <= _n);\n\
    \        assert(f(e()));\n        if (r == 0) return 0;\n        r += size;\n\
    \        S sm = e();\n        do {\n            r--;\n            while (r > 1\
    \ && (r % 2)) r >>= 1;\n            if (!f(op(d[r], sm))) {\n                while\
    \ (r < size) {\n                    r = (2 * r + 1);\n                    if (f(op(d[r],\
    \ sm))) {\n                        sm = op(d[r], sm);\n                      \
    \  r--;\n                    }\n                }\n                return r +\
    \ 1 - size;\n            }\n            sm = op(d[r], sm);\n        } while ((r\
    \ & -r) != r);\n        return 0;\n    }\n\nprivate:\n    int _n, size, log;\n\
    \    std::vector<S> d;\n\n    void update(int k) { d[k] = op(d[2 * k], d[2 * k\
    \ + 1]); }\n};\n\n} // namespace atcoder\n\n#endif // ATCODER_SEGTREE_HPP\n\n\
    // Reference: https://atcoder.github.io/ac-library/production/document_ja/segtree.html\n\
    /* usage:\nstruct S {\n    long long su;\n    int nb;\n};\nS e() { return {0,\
    \ 0}; }\nS op(S l, S r) { return {l.su + r.su, l.nb + r.nb}; }\nvector<S> seginit(100000,\
    \ e());\natcoder::segtree<S, op, e> segtree(seginit);\n*/\n"
  dependsOn: []
  isVerificationFile: false
  path: segmenttree/acl_segtree.hpp
  requiredBy:
  - segmenttree/rangetree.hpp
  timestamp: '2025-08-24 23:32:38+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - segmenttree/test/acl_rmq.test.cpp
  - segmenttree/test/rangetree.yuki1625.test.cpp
  - segmenttree/test/rangetree.test.cpp
  - segmenttree/test/acl_rsq.test.cpp
documentation_of: segmenttree/acl_segtree.hpp
layout: document
title: Segtree (based on atcoder::segtree)
---

ACL-based segtree

## Example

```cpp
struct S {};
S op(S l, S r) {
    return {};
}
S e() { return {}; };
vector<S> A;
atcoder::segtree<S, op, e> seg(A);
```

## Link

- [ACL reference](https://atcoder.github.io/ac-library/production/document_ja/segtree.html)
