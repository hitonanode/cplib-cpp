#include "graph-tree/eulertour.hpp"
#include "segmenttree/point-update-range-get_nonrecursive.hpp"
#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"
#include <iostream>
using namespace std;

int main()
{
    int N, Q;
    cin >> N >> Q;
    vector<long long int> A(N);
    vector<vector<int>> to(N);
    for (auto &a : A) cin >> a;
    for (int i = 1; i < N; i++) {
        int p;
        cin >> p;
        to[p].push_back(i);
        to[i].push_back(p);
    }

    PreorderEulerTour tour(to, 0);
    vector<long long int> v;
    for (auto i : tour.vis_order) v.push_back(A[i]);
    assert(v.size() == N);
    PointUpdateRangeSum<long long int> rsq(v, 0);

    while (Q--) {
        int q;
        cin >> q;
        if (q) {
            int u;
            cin >> u;
            printf("%lld\n", rsq.get(tour.subtree_begin[u], tour.subtree_end[u]));
        }
        else {
            int u, x;
            cin >> u >> x;
            A[u] += x;
            rsq.update(tour.subtree_begin[u], A[u]);
        }
    }
}
