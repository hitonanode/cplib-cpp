// パス上の頂点更新・パス上の頂点積取得が可能な Link-Cut tree
// 各頂点に 2x2 行列を載せ，演算として行列積が入る非可換・パス上更新の例．
#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A" // DUMMY
#include "../link_cut_tree.hpp"
#include "../../linear_algebra_matrix/matrix.hpp"
#include "../../modint.hpp"
#include "../../random/xorshift.hpp"

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <unordered_set>
#include <utility>
using namespace std;

constexpr int md = 998244353;
const int NTRY = 1000;
const int VMAX = 50;
const int QPERTRY = 500;
const int dim = 2;
using mint = ModInt<md>;

using S = tuple<int, matrix<mint>, matrix<mint>>;
using F = pair<bool, matrix<mint>>;
S op(S l, S r) {
    int sl, sr;
    matrix<mint> ml1, ml2, mr1, mr2;
    tie(sl, ml1, ml2) = l;
    tie(sr, mr1, mr2) = r;
    return {sl + sr, mr1 * ml1, ml2 * mr2};
}
S mapping(F f, S x) {
    int sz = get<0>(x);
    if (sz) {
        auto m = f.second.pow(sz);
        return {sz, m, m};
    }
    return x;
}
S reversal(S x) { return {get<0>(x), get<2>(x), get<1>(x)}; }
F composition(F f, F g) { return f.first ? f : g; }
F id() { return {false, matrix<mint>::Identity(dim)}; }
using LCT = lazy_linkcuttree<S, F, op, reversal, mapping, composition, id>;

vector<int> connected_vertices(int N, int r, const vector<unordered_set<int>> &to) {
    vector<int> visited(N);
    vector<int> ret, tmp{r};
    while (tmp.size()) {
        int now = tmp.back();
        tmp.pop_back();
        ret.push_back(now);
        visited[now] = 1;
        for (auto nxt : to[now]) {
            if (!visited[nxt]) tmp.push_back(nxt);
        }
    }
    return ret;
}

vector<int> get_rev_path(int s, int t, int prv, const vector<unordered_set<int>> &to) {
    if (s == t) return {s};
    for (auto nxt : to[s]) {
        if (nxt == prv) continue;
        auto v = get_rev_path(nxt, t, s, to);
        if (v.size()) {
            v.push_back(s);
            return v;
        }
    }
    return {};
}

matrix<mint> gen_random_mat() {
    matrix<mint> ret(dim, dim);
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) ret[i][j] = rand_int() % md;
    }
    return ret;
}
vector<mint> gen_random_vec() {
    vector<mint> ret(dim);
    for (auto &x : ret) x = rand_int() % md;
    return ret;
}

int main() {
    for (int ntry = 0; ntry < NTRY; ntry++) {
        const int N = 2 + rand_int() % (VMAX - 1);
        const int W = rand_int() % N + 1;
        vector<matrix<mint>> A(N);
        LCT tree;
        vector<LCT::Node *> nodes;

        for (int i = 0; i < N; i++) {
            A[i] = gen_random_mat();
            nodes.push_back(tree.make_node({1, A[i], A[i]}));
        }
        vector<pair<int, int>> edges;
        vector<unordered_set<int>> to(N);

        for (int i = 1; i < N; i++) {
            int j = max<int>(0, i - 1 - rand_int() % W);
            edges.emplace_back(i, j);
            to[i].insert(j);
            to[j].insert(i);
            tree.link(nodes[i], nodes[j]);
        }

        for (int q = 0; q < QPERTRY; q++) {
            const int tp = rand_int() % 5;
            if (tp == 0) {
                // cut() & link()
                int e = rand_int() % edges.size();
                int a = edges[e].first, b = edges[e].second;

                to[a].erase(b), to[b].erase(a);
                tree.cut(nodes[a], nodes[b]);

                vector<int> va = connected_vertices(N, a, to), vb = connected_vertices(N, b, to);
                assert(int(va.size() + vb.size()) == N);
                a = va[rand_int() % va.size()], b = vb[rand_int() % vb.size()];
                to[a].insert(b), to[b].insert(a);
                edges[e] = {a, b};
                tree.link(nodes[a], nodes[b]);
            } else if (tp == 1) {
                // apply()
                const int u = rand_int() % N, v = rand_int() % N;
                const auto a = gen_random_mat();
                tree.apply(nodes[u], nodes[v], {true, a});

                for (auto i : get_rev_path(u, v, -1, to)) A[i] = a;

            } else if (tp == 2) {
                // prod()
                const int u = rand_int() % N, v = rand_int() % N;
                const auto x = gen_random_vec();
                S p = tree.prod(nodes[u], nodes[v]);
                auto ret1 = get<1>(p) * x;

                auto ret2 = x;
                for (auto i : get_rev_path(v, u, -1, to)) ret2 = A[i] * ret2;
                assert(ret1 == ret2);

            } else if (tp == 3) {
                // set()
                const int u = rand_int() % N;
                const auto a = gen_random_mat();
                tree.set(nodes[u], {1, a, a});
                A[u] = a;

            } else if (tp == 4) {
                // get()
                const int u = rand_int() % N;
                const S a = tree.get(nodes[u]);
                assert(a == make_tuple(1, A[u], A[u]));
            } else {
                exit(8);
            }
        }
    }
    puts("Hello World");
}
