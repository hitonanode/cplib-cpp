#include "segmenttree/point-update-range-get_nonrecursive.hpp"
#define PROBLEM "https://yukicoder.me/problems/no/877"
#include <iostream>
using namespace std;

int main()
{
    int N, Q;
    cin >> N >> Q;
    vector<long long int> A(N);
    for (auto &a : A) cin >> a;
    CountAndSumLessThan<long long int> segtree(A);
    while (Q--) {
        int q, l, r, x;
        cin >> q >> l >> r >> x;
        auto r1 = segtree.get(l - 1, r, x);
        auto r2 = segtree.get(l - 1, r, 1e18);
        printf("%lld\n", r2.second - r1.second - 1LL * (r2.first - r1.first) * x);
    }
}
