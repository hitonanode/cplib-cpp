#define PROBLEM "https://yukicoder.me/problems/no/3314"
#include "../trees/range-chmax-range-sum.hpp"

#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

using RCRS = RangeChmaxRangeSum<long long, (1LL << 60)>;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, K, Q;
    cin >> N >> K >> Q;

    RCRS::segtree seg(N);
    for (int i = 0; i < N; ++i) {
        int a;
        cin >> a;
        seg.set(i, RCRS::Gen(a));
    }

    vector<tuple<int, int, int>> updates(K);
    for (auto &[l, r, x] : updates) cin >> l >> r >> x, --l;

    vector<tuple<int, int, long long>> query(Q);
    for (auto &[l, r, x] : query) cin >> l >> r >> x, --l;

    vector<int> ok(Q, K + 1), ng(Q, -1);

    for (int t = 0; t < 15; ++t) {
        vector<vector<int>> t2qs(K + 1);
        for (int q = 0; q < Q; ++q) {
            const int t = (ok.at(q) + ng.at(q)) / 2;
            t2qs.at(t).push_back(q);
        }

        RCRS::segtree tree = seg;

        for (int t = 0; t < K + 1; ++t) {
            if (t) {
                auto [l, r, x] = updates.at(t - 1);
                tree.apply(l, r, RCRS::Chmax(x));
            }

            for (int q : t2qs.at(t)) {
                auto [l, r, x] = query.at(q);
                (tree.prod(l, r).sum >= x ? ok : ng).at(q) = t;
            }
        }
    }

    for (auto t : ok) cout << (t == K + 1 ? -1 : t) << '\n';
}
