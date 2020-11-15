#pragma once
#include <algorithm>
#include <cassert>
#include <tuple>
#include <utility>
#include <vector>

// CUT begin
using lint = long long;
// Solve ax+by=gcd(a, b)
lint extgcd(lint a, lint b, lint &x, lint &y)
{
    lint d = a;
    if (b != 0) d = extgcd(b, a % b, y, x), y -= (a / b) * x;
    else x = 1, y = 0;
    return d;
}
// Calculate a^(-1) (MOD m) s if gcd(a, m) == 1
// Calculate x s.t. ax == gcd(a, m) MOD m
lint mod_inverse(lint a, lint m)
{
    lint x, y;
    extgcd(a, m, x, y);
    x %= m;
    return x + (x < 0) * m;
}

// Require: 1 <= b
// return: (g, x) s.t. g = gcd(a, b), xa = g MOD b, 0 <= x < b/g
template <typename Int>
constexpr std::pair<Int, Int> inv_gcd(Int a, Int b) {
    a %= b;
    if (a < 0) a += b;
    if (a == 0) return {b, 0};
    Int s = b, t = a, m0 = 0, m1 = 1;
    while (t) {
        Int u = s / t;
        s -= t * u, m0 -= m1 * u;
        auto tmp = s;
        s = t, t = tmp, tmp = m0, m0 = m1, m1 = tmp;
    }
    if (m0 < 0) m0 += b / s;
    return {s, m0};
}

template <typename Int>
constexpr std::pair<Int, Int> crt(const std::vector<Int> &r,
                                  const std::vector<Int> &m)
{
    assert(r.size() == m.size());
    int n = int(r.size());
    // Contracts: 0 <= r0 < m0
    Int r0 = 0, m0 = 1;
    for (int i = 0; i < n; i++) {
        assert(1 <= m[i]);
        Int r1 = r[i] % m[i], m1 = m[i];
        if (r1 < 0) r1 += m1;
        if (m0 < m1) {
            std::swap(r0, r1);
            std::swap(m0, m1);
        }
        if (m0 % m1 == 0) {
            if (r0 % m1 != r1) return {0, 0};
            continue;
        }
        Int g, im;
        std::tie(g, im) = inv_gcd<Int>(m0, m1);

        Int u1 = m1 / g;
        if ((r1 - r0) % g) return {0, 0};

        Int x = (r1 - r0) / g % u1 * im % u1;
        r0 += x * m0;
        m0 *= u1;
        if (r0 < 0) r0 += m0;
    }
    return {r0, m0};
}

// 蟻本 P.262
// 中国剰余定理を利用して，色々な素数で割った余りから元の値を復元
// 連立線形合同式 A * x = B mod M の解
// Requirement: M[i] > 0
// Output: x = first MOD second (if solution exists), (0, 0) (otherwise)
std::pair<lint, lint> linear_congruence(const std::vector<lint> &A,
                                        const std::vector<lint> &B,
                                        const std::vector<lint> &M)
{
    lint r = 0, m = 1;
    assert(A.size() == M.size());
    assert(B.size() == M.size());
    for (int i = 0; i < (int)A.size(); i++) {
        assert(M[i] > 0);
        const lint ai = A[i] % M[i];
        lint a = ai * m, b = B[i] - ai * r, d = std::__gcd(M[i], a);
        if (b % d != 0) {
            return std::make_pair(0, 0); // 解なし
        }
        lint t = b / d * mod_inverse(a / d, M[i] / d) % (M[i] / d);
        r += m * t;
        m *= M[i] / d;
    }
    return std::make_pair((r < 0 ? r + m : r), m);
}

lint power(lint x, lint n, lint MOD)
{
    lint ans = 1;
    while (n > 0) {
        if (n & 1) (ans *= x) %= MOD;
        (x *= x) %= MOD;
       n >>= 1;
    }
   return ans;
}

// Find smallest primitive root for given prime P （最小の原始根探索）
// Complexity: maybe O(sqrt(p))
// Algorithm: <http://kirika-comp.hatenablog.com/entry/2018/03/12/210446>
// Verified: <https://yukicoder.me/submissions/405938>
// Sample:
//  - 998244353 ( = (119 << 23) + 1 ) -> 3
//  - 163577857 ( = (39 << 22) + 1 ) -> 23
//  - 2 -> 1
//  - 1 -> -1

lint find_smallest_primitive_root(lint p)
{
    std::vector<lint> fac;
    lint v = p - 1;
    for (lint pp = 2; pp * pp <= v; pp++) // prime factorization of (p - 1)
    {
        int e = 0;
        while (v % pp == 0) e++, v /= pp;
        if (e) fac.push_back(pp);
    }
    if (v > 1) fac.push_back(v);

    for (lint g = 1; g < p; g++)
    {
        if (power(g, p - 1, p) != 1) return -1;
        bool ok = true;
        for (auto pp : fac)
        {
            if (power(g, (p - 1) / pp, p) == 1)
            {
                ok = false;
                break;
            }
        }
        if (ok) return g;
    }
    return -1;
}
