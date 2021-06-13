---
title: Levinson recursion (Levinson-Durbin algorithm)
documentation_of: ./levinson.hpp
---

Solve Toeplitz system $\mathbf{T} \mathbf{x} = \mathbf{y}$, where $\mathbf{T}$ is Topelitz and every its principal submatrix is nonsingular.

## Complexity

$O(N^2)$, where $N$ is the dimension of $\mathbf{T}$

## References

- [1] N. Levinson, "The Wiener RMS error criterion in filter design and prediction," J. Math. and Phys., 25, 261-298, 1947.
- [2] J. Durbin, "The fitting of time series models,", Rev. Inst. Int. Stat. 28, 233-243, 1960.
