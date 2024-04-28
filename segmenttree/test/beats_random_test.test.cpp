#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A" // DUMMY

#include "../../random/xorshift.hpp"
#include "../acl_beats.hpp"

#include <algorithm>
#include <cstdio>
#include <numeric>
#include <vector>

using RangeChMinMaxAddSum::S, RangeChMinMaxAddSum::F;

int main() {
    for (int trial = 0; trial < 1 << 20; ++trial) {
        const int N = rand_int() % 32 + 1;

        const int maxA = rand_int() % 50 + 1;
        const int Q = rand_int() % 10 + 1;

        std::vector<S> A(N);
        std::vector<int> simulate(N);
        for (int i = 0; i < N; ++i) {
            simulate.at(i) = rand_int() % (maxA + 1);
            A.at(i) = S(simulate.at(i), 1);
        }

        segtree_beats<S, RangeChMinMaxAddSum::op, RangeChMinMaxAddSum::e, F, RangeChMinMaxAddSum::mapping,
                      RangeChMinMaxAddSum::composition, RangeChMinMaxAddSum::id>
            segtree(A);

        for (int q = 0; q < Q; ++q) {
            int tp = rand_int() % 4;
            if (q == Q - 1) tp = 3;

            int l = 0, r = 0;
            while (l == r) {
                l = rand_int() % (N + 1);
                r = rand_int() % (N + 1);
                if (l > r) std::swap(l, r);
            }

            if (tp < 3) {
                int b = rand_int() % (maxA + 1);
                if (tp == 0) {
                    for (int i = l; i < r; ++i) simulate.at(i) = std::min(simulate.at(i), b);
                    segtree.apply(l, r, RangeChMinMaxAddSum::F::chmin(b));
                }

                if (tp == 1) {
                    for (int i = l; i < r; ++i) simulate.at(i) = std::max(simulate.at(i), b);
                    segtree.apply(l, r, RangeChMinMaxAddSum::F::chmax(b));
                }

                if (tp == 2) {
                    for (int i = l; i < r; ++i) simulate.at(i) += b;
                    segtree.apply(l, r, RangeChMinMaxAddSum::F::add(b));
                }
            }

            if (tp == 3) {
                auto prod = segtree.prod(l, r);

                std::vector<int> values;
                for (int i = l; i < r; ++i) values.push_back(simulate.at(i));
                std::sort(values.begin(), values.end());

                assert(prod.lo == values.front());
                assert(prod.nlo == std::count(values.begin(), values.end(), prod.lo));

                assert(prod.hi == values.back());
                assert(prod.nhi == std::count(values.begin(), values.end(), prod.hi));

                assert(prod.sum == std::accumulate(values.begin(), values.end(), 0LL));

                assert(prod.sz == r - l);
                assert(!prod.fail);

                if (values.front() != values.back()) {
                    int i = 0;
                    while (values.at(i) == values.front()) ++i;
                    assert(prod.lo2 == values.at(i));

                    i = (int)values.size() - 1;
                    while (values.at(i) == values.back()) --i;
                    assert(prod.hi2 == values.at(i));
                }
            }
        }
    }

    puts("Hello World");
}
