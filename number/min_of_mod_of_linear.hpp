#pragma once

#include <cassert>
#include <vector>
#include <utility>

// min((ax + b) mod m) for 0 <= x < n
// 0 < n, 0 < m <= 1e9
// https://maspypy.com/library-checker-min-of-mod-of-linear
template <class Int = int, class Long = long long>
auto min_of_mod_of_linear(Int n, const Int &m, Int a, Int b) {

    // p = (xs, ys), v = (dx, dy) として
    // 列 (p, p + v, ..., p + (len - 1)v) が点群全体を包絡する
    struct Result {
        Int xs, ys;
        Int dx, dy;
        Int len;

        Int min() const { return ys + dy * (len - 1); }
    };

    assert(0 < n);
    assert(0 < m);

    if (n > m) n = m;
    a = (m - a % m) % m;
    b = (b % m + m) % m;

    Int x = 0, y = b;

    Int p = 0, q = 1, r = 1, s = 0; // p/q <= a/m < r/s

    std::vector<Result> ret{Result{x, y, 0, 0, 1}};

    while (true) {
        if (x + q > n - 1) break;

        const Long aqmp = (Long)a * q - (Long)m * p;
        if (aqmp == 0) break; // p/q == a/m

        const Long mras = (Long)m * r - (Long)a * s;

        assert(aqmp > 0);
        assert(mras > 0);

        if (const Long num = p + r, den = q + s; num * m <= den * a) { // num/den <= a/m 下側を更新

            // q + is <= n - 1 - x

            // (p + ir) / (q + is) <= a/m （下側である条件） i >= 0
            // <=> m(p + ir) <= a(q + is) <=> (mr - as)i <= aq - mp

            // a(q + is) - m(p + ir) <= Y （改善する条件） i >= 0
            // (mr - as)i >= aq - mp - Y

            const Long iub = aqmp / mras;

            const Long imp_i_lb = std::max<Long>((std::max<Long>(aqmp - y, 0) + mras - 1) / mras, 0);

            if (imp_i_lb <= iub) {
                p += imp_i_lb * r;
                q += imp_i_lb * s;

                const Long c = (Long)a * q - (Long)m * p;
                assert(0 <= c);
                assert(c <= y);

                const Long kub = y / c;
                const Long k = std::min<Long>(kub, (n - 1 - x) / q);

                if (k) ret.push_back(Result{x + q, (Int)(y - c), q, (Int)-c, (Int)k});

                x += q * k;
                y -= c * k;
                if (k < kub) break;
                continue;
            } else {
                p += iub * r;
                q += iub * s;
            }
        } else { // num/den > a/m 上側を更新
            // (r + ip)/(s + iq) > a/m <=> m(r + ip) > a(s + iq) <=> (aq - mp)i < mr - as
            // -> i step 進んでもまだ超えない

            const Long i = (mras - 1) / aqmp;
            assert(i > 0);

            // x + (s + iq) <= n - 1
            // const Long iub = (n - 1 - q - x - s) / q;
            // if (i > iub) break;

            r += (i - 1) * p; // NOTE: overflow
            s += (i - 1) * q;

            // まだ a/m < (p + r) / (q + s)
            assert((Long)a * (q + s) < (Long)m * (p + r));

            r += p;
            s += q;

            // 逆転
            assert((Long)a * (q + s) >= (Long)m * (p + r));
        }
    }

    // return y;
    return ret;
}
