#pragma once
#include <algorithm>
#include <cassert>
#include <tuple>
#include <utility>
#include <vector>

// CUT begin
// Solve ax+by=gcd(a, b)
template <class Int> Int extgcd(Int a, Int b, Int &x, Int &y) {
    Int d = a;
    if (b != 0) {
        d = extgcd(b, a % b, y, x), y -= (a / b) * x;
    } else {
        x = 1, y = 0;
    }
    return d;
}
// Calculate a^(-1) (MOD m) s if gcd(a, m) == 1
// Calculate x s.t. ax == gcd(a, m) MOD m
template <class Int> Int mod_inverse(Int a, Int m) {
    Int x, y;
    extgcd<Int>(a, m, x, y);
    x %= m;
    return x + (x < 0) * m;
}

// Require: 1 <= b
// return: (g, x) s.t. g = gcd(a, b), xa = g MOD b, 0 <= x < b/g
template <class Int> /* constexpr */ std::pair<Int, Int> inv_gcd(Int a, Int b) {
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

template <class Int>
/* constexpr */ std::pair<Int, Int> crt(const std::vector<Int> &r, const std::vector<Int> &m) {
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
template <class Int>
std::pair<Int, Int>
linear_congruence(const std::vector<Int> &A, const std::vector<Int> &B, const std::vector<Int> &M) {
    Int r = 0, m = 1;
    assert(A.size() == M.size());
    assert(B.size() == M.size());
    for (int i = 0; i < (int)A.size(); i++) {
        assert(M[i] > 0);
        const Int ai = A[i] % M[i];
        Int a = ai * m, b = B[i] - ai * r, d = std::__gcd(M[i], a);
        if (b % d != 0) {
            return std::make_pair(0, 0); // 解なし
        }
        Int t = b / d * mod_inverse<Int>(a / d, M[i] / d) % (M[i] / d);
        r += m * t;
        m *= M[i] / d;
    }
    return std::make_pair((r < 0 ? r + m : r), m);
}

template <class Int = int, class Long = long long>
Int pow_mod(Int x, long long n, Int md) {
    static_assert(sizeof(Int) * 2 <= sizeof(Long), "Watch out for overflow");
    if (md == 1) return 0;
    Int ans = 1;
    while (n > 0) {
        if (n & 1) ans = (Long)ans * x % md;
        x = (Long)x * x % md;
        n >>= 1;
    }
    return ans;
}
