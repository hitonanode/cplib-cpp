# Number theory

## Contents

- `eratosthenes.hpp` Sieve of eratosthenes
- `cyclotomic_polynomials.hpp` Cyclotomic polynomial （円分多項式, $x^k - 1$の因数分解など）

## Cyclotomic Polynomials

Verified: SRM 776 Div.1 Hard

### Definition

$$ \Phi_n (x) := \prod_{1 \leq k \leq n, gcd(k, n) = 1} \left( x - e^{2 i \pi k / n} \right)$$


### Usage

``` cpp
vector<vector<int>> Phi = cyclotomic_polynomials(120); // Phi[i][j] = [x^j]Phi_i(x) for i <= 120
```
All coefficients are known to be "small" integers.

### Properties: 

- $$ \prod_{d \mid n} \Phi_d (x) = x^n - 1 $$
- $$ \Phi_n (x) = \prod_{d \mid n} \left(x^{n / d} - 1 \right) ^ {\mu(d)}$$
- $$ \Phi_p (x) = 1 + x + \ldots + x^{p - 1} \; (p : prime)$$

Wikipedia (en) : https://en.wikipedia.org/wiki/Cyclotomic_polynomial
