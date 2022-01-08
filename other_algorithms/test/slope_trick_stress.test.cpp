#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A" // DUMMY
#include "../slope_trick.hpp"
#include <cstdio>
#include <random>
#include <tuple>
#include <utility>
using namespace std;

mt19937 mt(1010101);

template <typename Int> pair<slope_trick<Int>, vector<Int>> gen_random_function(Int lo, Int hi) {
    slope_trick<Int> f;
    const Int dxmax = 10;

    int nquery = 100;

    const Int stupid_lo = lo - nquery * dxmax, stupid_hi = hi + nquery * dxmax;
    std::vector<Int> stupid_f(stupid_hi - stupid_lo + 1);

    for (int t = 0; t < nquery; t++) {
        int qtype = uniform_int_distribution<int>(0, 6)(mt);
        Int a = uniform_int_distribution<Int>(lo, hi)(mt);
        Int w = uniform_int_distribution<Int>(0, dxmax)(mt);
        if (qtype == 0) {
            Int b = uniform_int_distribution<Int>(-10000, 10000)(mt);
            f.add_const(b);
            for (Int x = stupid_lo; x <= stupid_hi; x++) stupid_f[x - stupid_lo] += b;
        }
        if (qtype == 1) {
            f.add_relu(a);
            for (Int x = stupid_lo; x <= stupid_hi; x++)
                stupid_f[x - stupid_lo] += max<Int>(x - a, 0);
        }
        if (qtype == 2) {
            f.add_irelu(a);
            for (Int x = stupid_lo; x <= stupid_hi; x++)
                stupid_f[x - stupid_lo] += max<Int>(a - x, 0);
        }
        if (qtype == 3) {
            f.add_abs(a);
            for (Int x = stupid_lo; x <= stupid_hi; x++) stupid_f[x - stupid_lo] += abs(x - a);
        }
        if (qtype == 4) {
            f.move_left_curve(w);
            for (Int x = stupid_lo; x <= stupid_hi; x++) {
                for (Int y = x + 1; y <= min(stupid_hi, x + w); y++) {
                    stupid_f[x - stupid_lo] = min(stupid_f[x - stupid_lo], stupid_f[y - stupid_lo]);
                }
            }
        }
        if (qtype == 5) {
            f.move_right_curve(w);
            for (Int x = stupid_hi; x >= stupid_lo; x--) {
                for (Int y = x - 1; y >= max(stupid_lo, x - w); y--) {
                    stupid_f[x - stupid_lo] = min(stupid_f[x - stupid_lo], stupid_f[y - stupid_lo]);
                }
            }
        }
        if (qtype == 6) {
            Int dx = uniform_int_distribution<Int>(-dxmax, dxmax)(mt);
            f.translate(dx);
            auto g = stupid_f;
            for (Int x = stupid_lo; x <= stupid_hi; x++) {
                Int y = x - dx;
                if (y >= stupid_lo and y <= stupid_hi) g[x - stupid_lo] = stupid_f[y - stupid_lo];
            }
            stupid_f = g;
        }
    }
    vector<Int> fvals;
    for (Int x = lo; x <= hi; x++) {
        Int ret1 = stupid_f[x - stupid_lo];
        auto g = f;
        Int ret2 = g.get_destructive(x);
        fvals.push_back(ret2);
        assert(ret1 == ret2);
    }
    return {f, fvals};
}

template <typename Int> void merge_verify() {
    const Int lo = uniform_int_distribution<Int>(-10000, 10000)(mt);
    const Int hi = lo + 1000;
    slope_trick<Int> f, g;
    vector<Int> fval, gval;
    tie(f, fval) = gen_random_function(lo, hi);
    tie(g, gval) = gen_random_function(lo, hi);
    f.merge_destructive(g);
    for (Int x = lo; x <= hi; x++) {
        auto tmp = f;
        assert(tmp.get_destructive(x) == fval.at(x - lo) + gval.at(x - lo));
    }
}

int main() {
    for (int t = 0; t < 1000; t++) {
        merge_verify<int>();
        merge_verify<long long>();
    }
    puts("Hello World");
}
