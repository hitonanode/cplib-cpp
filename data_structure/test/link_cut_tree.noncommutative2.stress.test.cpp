#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A" // DUMMY
#include "../link_cut_tree.hpp"
#include "../../random/xorshift.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

struct S {
    int sz, sum, lhi, rhi, inhi;
    S() = default;
    S(int x) : sz(1), sum(x), lhi(x), rhi(x), inhi(x) {}
    S(int sz_, int sum_, int lhi_, int rhi_, int inhi_)
        : sz(sz_), sum(sum_), lhi(lhi_), rhi(rhi_), inhi(inhi_) {}
    bool operator==(const S &x) const {
        return sz == x.sz and sum == x.sum and lhi == x.lhi and rhi == x.rhi and inhi == x.inhi;
    }
    template <class OStream> friend OStream &operator<<(OStream &os, const S &x) {
        return os << '[' << x.sz << ',' << x.sum << ',' << x.lhi << ',' << x.rhi << ',' << x.inhi
                  << ']';
    }
};
using F = pair<bool, int>;
S op(S l, S r) {
    return S(l.sz + r.sz, l.sum + r.sum, max(l.sum + r.lhi, l.lhi), max(l.rhi + r.sum, r.rhi),
             max({l.inhi, r.inhi, l.rhi + r.lhi}));
}
S reversal(S x) { return S(x.sz, x.sum, x.rhi, x.lhi, x.inhi); }
S mapping(F f, S x) {
    if (f.first) {
        auto v = f.second;
        auto sum = x.sz * v;
        return S{x.sz, sum, max(v, sum), max(v, sum), max(v, sum)};
    } else {
        return x;
    }
}
F composition(F fnew, F gold) { return fnew.first ? fnew : gold; }
F id() { return {false, 0}; }
using LCT = lazy_linkcuttree<S, F, op, reversal, mapping, composition, id>;

const int NTRY = 1000;
const int VMAX = 20;
const int QPERTRY = 10000;
const int AMAX = 20;

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

int gen_rand_a() { return rand_int() % (AMAX * 2 + 1) - AMAX; }

int main() {
    for (int ntry = 0; ntry < NTRY; ntry++) {
        const int N = 2 + rand_int() % (VMAX - 1);
        vector<S> A(N);
        LCT tree;
        vector<LCT::Node *> nodes;

        for (int i = 0; i < N; i++) {
            A[i] = gen_rand_a();
            nodes.push_back(tree.make_node(A[i]));
        }
        vector<pair<int, int>> edges;
        vector<unordered_set<int>> to(N);

        auto try_to_add_edge = [&]() {
            int a = rand_int() % N;
            vector<int> is_cmp(N, 1);
            for (auto i : connected_vertices(N, a, to)) is_cmp[i] = 0;
            vector<int> cmp;
            for (int i = 0; i < N; i++) {
                if (is_cmp[i]) cmp.push_back(i);
            }
            if (cmp.empty()) return;
            int b = cmp[rand_int() % cmp.size()];

            edges.emplace_back(a, b);
            to[a].insert(b), to[b].insert(a);
            tree.link(nodes[a], nodes[b]);
        };

        for (int i = 0; i < N / 2; i++) try_to_add_edge();

        for (int q = 0; q < QPERTRY; q++) {
            const int tp = rand_int() % 6;
            if (tp == 0) {
                // cut() if possible
                if (edges.empty()) continue;
                int e = rand_int() % edges.size();
                int a = edges[e].first, b = edges[e].second;

                edges.erase(edges.begin() + e);
                to[a].erase(b), to[b].erase(a);
                tree.cut(nodes[a], nodes[b]);

            } else if (tp == 1) {
                // link() if possible
                try_to_add_edge();

            } else if (tp == 2) {
                // apply()
                const int u = rand_int() % N;
                auto conn = connected_vertices(N, u, to);
                int v = conn[rand_int() % conn.size()];
                const auto a = gen_rand_a();
                tree.apply(nodes[u], nodes[v], {true, a});

                for (auto i : get_rev_path(u, v, -1, to)) A[i] = a;

            } else if (tp == 3) {
                // prod()
                const int u = rand_int() % N;
                auto conn = connected_vertices(N, u, to);
                int v = conn[rand_int() % conn.size()];
                S ret1 = tree.prod(nodes[u], nodes[v]);

                auto ret2 = S(A[u]);
                for (auto i : get_rev_path(v, u, -1, to)) {
                    if (i != u) ret2 = op(ret2, A[i]);
                }
                assert(ret1 == ret2);

            } else if (tp == 4) {
                // set()
                const int u = rand_int() % N;
                const auto a = gen_rand_a();
                tree.set(nodes[u], a);
                A[u] = a;

            } else if (tp == 5) {
                // get()
                const int u = rand_int() % N;
                const S a = tree.get(nodes[u]);
                assert(a == A[u]);
            } else {
                exit(8);
            }
        }
    }
    puts("Hello World");
}
