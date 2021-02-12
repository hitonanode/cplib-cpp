---
title: Lazy Segtree (based on atcoder::lazy_segtree)
documentation_of: ./acl_lazysegtree.hpp
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
