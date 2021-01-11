# Number theory

## Contents

- `count_primes.hpp` Prime-counting function, O(N^(2/3))
- `cyclotomic_polynomials.hpp` Cyclotomic polynomial （円分多項式, $x^k - 1$の因数分解など）
- `discrete_logarithm.hpp` Discrete logarithm by the baby-step giant-step algorithm
- `enumerate_partitions.hpp` 自然数の分割の列挙
- `euler_toptient_phi.hpp` Generate table of Euler's totient function
- `factorize.hpp` 大きい整数の素因数分解・素数判定
- `modint_runtime.hpp` 実行時 modint （`modint.hpp` と共通のインターフェース）
- `sieve.hpp` 線形篩・素因数分解・メビウス関数

## Cyclotomic Polynomials

Verified: SRM 776 Div.1 Hard

### Definition

$$ \Phi_n (x) := \prod_{1 \leq k \leq n, gcd(k, n) = 1} \left( x - e^{2 i \pi k / n} \right) $$


### Usage

``` cpp
vector<vector<int>> Phi = cyclotomic_polynomials(120); // Phi[i][j] = [x^j]Phi_i(x) for i <= 120
```
All coefficients are known to be "small" integers.

### Properties: 

- $$ \prod_{d \mid n} \Phi_d (x) = x^n - 1 $$
- $$ \Phi_n (x) = \prod_{d \mid n} \left(x^{n / d} - 1 \right) ^ {\mu(d)} $$
- $$ \Phi_p (x) = 1 + x + \ldots + x^{p - 1} \; (p : prime) $$

Wikipedia (en) : https://en.wikipedia.org/wiki/Cyclotomic_polynomial
