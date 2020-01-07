#include "convex_hull_trick/convex_hull_trick.hpp"
#include <iostream>
#include <cassert>
#define PROBLEM "https://judge.yosupo.jp/problem/line_add_get_min"
using namespace std;

ConvexHullTrick cht_min(true), cht_max(false);
void add_line()
{
    long long int a, b;
    cin >> a >> b;
    cht_min.add_line(a, b);
    cht_max.add_line(-a, -b);
}
int main()
{
    int N, Q;
    cin >> N >> Q;
    while (N--) add_line();
    while (Q--) {
        int q;
        cin >> q;
        if (q) {
            int p;
            cin >> p;
            auto ret1 = cht_min.get(p);
            auto ret2 = cht_max.get(p);
            assert(ret1.first == -ret2.first);
            cout << ret1.first << endl;
        }
        else add_line();
    }
}
