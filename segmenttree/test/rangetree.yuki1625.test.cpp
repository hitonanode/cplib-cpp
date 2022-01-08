#define PROBLEM "https://yukicoder.me/problems/no/1625"
#include "../rangetree.hpp"
#include <algorithm>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;
long long op(long long l, long long r) { return l > r ? l : r; }
long long e() { return -1; }

pair<int, int> read_pint() {
    int a, b;
    cin >> a >> b;
    return {a, b};
};

using Tri = pair<pair<int, int>, long long>;
Tri read_tri() {

    auto A = read_pint(), B = read_pint(), C = read_pint();
    long long dx1 = B.first - A.first, dy1 = B.second - A.second, dx2 = C.first - A.first,
              dy2 = C.second - A.second;

    const auto S = abs(dx1 * dy2 - dy1 * dx2);
    const int lo = min({A.first, B.first, C.first}), hi = max({A.first, B.first, C.first});
    return {{lo, hi}, S};
}

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N, Q;
    cin >> N >> Q;

    vector<Tri> tris(N);
    for (auto &x : tris) x = read_tri();

    vector<int> TP(Q);
    vector<Tri> tris_add(Q);
    vector<pair<int, int>> qs(Q);
    for (int q = 0; q < Q; q++) {
        cin >> TP[q];
        if (TP[q] == 1) {
            tris_add[q] = read_tri();
        } else {
            qs[q] = read_pint();
        }
    }

    rangetree<long long, op, e, int> tree;
    for (const auto trivec : {tris, tris_add}) {
        for (const auto lh_S : trivec) {
            auto lh = lh_S.first;
            if (lh.first > 0) tree.add_point(lh.first, lh.second);
        }
    }
    tree.build();

    auto add_tri = [&](Tri tri) {
        auto lr = tri.first;
        auto S = tri.second;
        tree.add(lr.first, lr.second, S);
    };

    for (auto tri : tris) add_tri(tri);

    for (int q = 0; q < Q; q++) {
        if (TP[q] == 1) {
            add_tri(tris_add[q]);
        } else {
            int l, r;
            tie(l, r) = qs[q];
            cout << tree.prod(l, r + 1, l, r + 1) << '\n';
        }
    }
}
