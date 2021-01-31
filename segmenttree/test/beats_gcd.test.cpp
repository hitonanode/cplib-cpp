#define PROBLEM "https://yukicoder.me/problems/no/880"
#include "../trees/acl_range-update-gcd-range-max-sum.hpp"

#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    uint32_t N, Q;
    cin >> N >> Q;
    vector<yuki880::S> A(N);
    for (auto &a : A) {
        uint32_t tmp;
        cin >> tmp, a = {tmp, 1};
    }

    yuki880::segtree segtree(A);
    uint32_t q, l, r, x;
    while (Q--) {
        cin >> q >> l >> r;
        l--;
        if (q <= 2) {
            cin >> x;
            if (q == 1) segtree.apply(l, r, yuki880::F::update(x));
            if (q == 2) segtree.apply(l, r, yuki880::F::gcd(x));
        } else {
            auto v = segtree.prod(l, r);
            if (q == 3) cout << v.max << '\n';
            if (q == 4) cout << v.sum << '\n';
        }
    }
}
