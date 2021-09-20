#define PROBLEM "https://yukicoder.me/problems/no/952"
#include "../monotone-insert-get_cht.hpp"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<long long> A(N);
    for (auto &x : A) cin >> x;
    vector<MonotoneConvexHullTrick<true, long long, __int128>> cht(N + 1);
    int x = 0;
    cht[0].insert_convex_parabola(1, x, 0);
    for (int i = 0; i < N; ++i) {
        for (int d = i; d >= 0; --d) {
            long long v = cht[d].parabola_get(1, x);
            cht[d + 1].insert_convex_parabola(1, x + A[i], v);
        }
        x += A[i];
    }
    cht.pop_back();
    while (!cht.empty()) {
        cout << (long long)cht.back().parabola_get(1, x) << '\n';
        cht.pop_back();
    }
}
