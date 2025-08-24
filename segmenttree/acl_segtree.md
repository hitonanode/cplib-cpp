---
title: Segtree (based on atcoder::segtree)
documentation_of: ./acl_segtree.hpp
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
