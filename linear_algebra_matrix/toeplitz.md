---
title: Fast operations on Toeplitz matrices
documentation_of: ./toeplitz.hpp
---

## Levinson recursion

Solve Toeplitz system $\mathbf{T} \mathbf{x} = \mathbf{y}$, where $\mathbf{T}$ is Topelitz and every its principal submatrix is regular.

### Complexity:

$O(N^2)$, where $N$ is the dimension of $\mathbf{T}$
