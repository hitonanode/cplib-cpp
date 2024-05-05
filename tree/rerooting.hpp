#pragma once
#include <cassert>
#include <cstdlib>
#include <utility>
#include <vector>

// Rerooting
// Reference:
// - https://atcoder.jp/contests/abc222/editorial/2749
// - https://null-mn.hatenablog.com/entry/2020/04/14/124151
template <class Edge, class Subtree, class Children, Children (*rake)(Children, Children),
          Children (*add_edge)(Subtree, int, Edge), Subtree (*add_vertex)(Children, int),
          Children (*e)()>
struct rerooting {
    int n_;
    std::vector<int> par, visited;
    std::vector<std::vector<std::pair<int, Edge>>> to;

    // dp_subtree[i] = DP(root=i, edge (i, par[i]) is removed).
    std::vector<Subtree> dp_subtree;

    // dp_par[i] = DP(root=par[i], edge (i, par[i]) is removed). dp_par[root] is meaningless.
    std::vector<Subtree> dp_par;

    // dpall[i] = DP(root=i, all edges exist).
    std::vector<Subtree> dpall;

    rerooting(const std::vector<std::vector<std::pair<int, Edge>>> &to_)
        : n_(to_.size()), par(n_, -1), visited(n_, 0), to(to_) {
        for (int i = 0; i < n_; ++i) dp_subtree.push_back(add_vertex(e(), i));
        dp_par = dpall = dp_subtree;
    }

    void run_connected(int root) {
        if (visited.at(root)) return;
        visited.at(root) = 1;
        std::vector<int> visorder{root};

        for (int t = 0; t < int(visorder.size()); ++t) {
            int now = visorder.at(t);
            for (const auto &[nxt, _] : to[now]) {
                if (visited.at(nxt)) continue;
                visorder.push_back(nxt);
                visited.at(nxt) = 1;
                par.at(nxt) = now;
            }
        }

        for (int t = int(visorder.size()) - 1; t >= 0; --t) {
            const int now = visorder.at(t);
            Children ch = e();
            for (const auto &[nxt, edge] : to.at(now)) {
                if (nxt != par.at(now)) ch = rake(ch, add_edge(dp_subtree.at(nxt), nxt, edge));
            }
            dp_subtree.at(now) = add_vertex(ch, now);
        }

        std::vector<Children> left;
        for (int now : visorder) {
            const int m = to.at(now).size();
            left.assign(m + 1, e());
            for (int j = 0; j < m; j++) {
                const auto &[nxt, edge] = to.at(now).at(j);
                const Subtree &st = (nxt == par.at(now) ? dp_par.at(now) : dp_subtree.at(nxt));
                left.at(j + 1) = rake(left.at(j), add_edge(st, nxt, edge));
            }
            dpall.at(now) = add_vertex(left.back(), now);

            Children rprod = e();
            for (int j = m - 1; j >= 0; --j) {
                const auto &[nxt, edge] = to.at(now).at(j);

                if (nxt != par.at(now)) dp_par.at(nxt) = add_vertex(rake(left.at(j), rprod), now);

                const Subtree &st = (nxt == par.at(now) ? dp_par.at(now) : dp_subtree.at(nxt));
                rprod = rake(add_edge(st, nxt, edge), rprod);
            }
        }
    }

    void run() {
        for (int i = 0; i < n_; ++i) {
            if (!visited.at(i)) run_connected(i);
        }
    }

    const Subtree &get_subtree(int root_, int par_) const {
        if (par_ < 0) return dpall.at(root_);
        if (par.at(root_) == par_) return dp_subtree.at(root_);
        if (par.at(par_) == root_) return dp_par.at(par_);
        std::exit(1);
    }
};
/* Template:
struct Subtree {};
struct Children {};
struct Edge {};
Children e() { return Children(); }
Children rake(Children x, Children y) { return Children(); }
Children add_edge(Subtree x, int ch_id, Edge edge) { return Children(); }
Subtree add_vertex(Children x, int v_id) { return Subtree(); }

vector<vector<pair<int, Edge>>> to;
rerooting<Edge, Subtree, Children, rake, add_edge, add_vertex, e> tree(to);
*/
