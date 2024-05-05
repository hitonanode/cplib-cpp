#define PROBLEM "https://judge.yosupo.jp/problem/point_set_tree_path_composite_sum_fixed_root"

#include "../static_toptree.hpp"

#include <iostream>
#include <vector>
using namespace std;

#include <atcoder/modint>
using mint = atcoder::modint998244353;

struct tree_dp {
    vector<int> A;
    vector<mint> parB;
    vector<mint> parC;

    // Point Cluster
    struct Point {
        mint n;
        mint sum;
    };

    // Path Cluster
    struct Path {
        mint n;
        mint sum;

        mint b;
        mint c;
    };

    Path vertex(int i) { return {1, A.at(i) * parB.at(i) + parC.at(i), parB.at(i), parC.at(i)}; }

    static Path compress(const Path &p, const Path &c) {
        return {p.n + c.n, p.sum + c.sum * p.b + c.n * p.c, c.b * p.b, p.c + c.c * p.b};
    }

    static Point rake(const Point &l, const Point &r) { return {l.n + r.n, l.sum + r.sum}; }

    static Point add_edge(const Path &d) { return {d.n, d.sum}; }

    Path add_vertex(const Point &d, int i) {
        return {d.n + 1, (d.sum + A.at(i)) * parB.at(i) + (d.n + 1) * parC.at(i), parB.at(i),
                parC.at(i)};
    }
};

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, Q;
    cin >> N >> Q;

    vector<int> A(N);
    for (auto &a : A) cin >> a;

    vector<int> U(N - 1), V(N - 1), B(N - 1), C(N - 1);
    vector<vector<int>> to(N);

    for (int e = 0; e < N - 1; ++e) {
        cin >> U.at(e) >> V.at(e) >> B.at(e) >> C.at(e);
        to.at(U.at(e)).push_back(V.at(e));
        to.at(V.at(e)).push_back(U.at(e));
    }

    const static_toptree_structure stts(to, 0);

    vector<mint> parB(N, 1);
    vector<mint> parC(N, 0);

    for (int e = 0; e < N - 1; ++e) {
        int u = U.at(e), v = V.at(e);
        if (stts.par.at(u) != v) swap(u, v);

        assert(stts.par.at(u) == v);

        parB.at(u) = B.at(e);
        parC.at(u) = C.at(e);
    }

    tree_dp dp{A, parB, parC};

    static_toptree tree(stts, dp);

    while (Q--) {
        int tp;
        cin >> tp;
        if (tp == 0) {
            int w, x;
            cin >> w >> x;
            dp.A.at(w) = x;
            tree.set(w);
        } else {
            int e, y, z;
            cin >> e >> y >> z;

            int u = U.at(e), v = V.at(e);
            if (stts.par.at(u) != v) swap(u, v);
            assert(stts.par.at(u) == v);

            dp.parB.at(u) = y;
            dp.parC.at(u) = z;
            tree.set(u);
        }

        cout << tree.all_prod().sum.val() << '\n';
    }
}
