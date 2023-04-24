#pragma once
#include <cassert>
#include <cstdlib>
#include <utility>
#include <vector>

// Rerooting
// Reference:
// - https://atcoder.jp/contests/abc222/editorial/2749
// - https://null-mn.hatenablog.com/entry/2020/04/14/124151
template <class Edge, class St, class Ch, Ch (*merge)(Ch, Ch), Ch (*f)(St, int, Edge),
          St (*g)(Ch, int), Ch (*e)()>
struct rerooting {
    int n_;
    std::vector<int> par, visited;
    std::vector<std::vector<std::pair<int, Edge>>> to;
    std::vector<St> dp_subtree;
    std::vector<St> dp_par;
    std::vector<St> dpall;
    rerooting(const std::vector<std::vector<std::pair<int, Edge>>> &to_)
        : n_(to_.size()), par(n_, -1), visited(n_, 0), to(to_) {
        for (int i = 0; i < n_; ++i) dp_subtree.push_back(g(e(), i));
        dp_par = dpall = dp_subtree;
    }

    void run_connected(int root) {
        if (visited[root]) return;
        visited[root] = 1;
        std::vector<int> visorder{root};

        for (int t = 0; t < int(visorder.size()); ++t) {
            int now = visorder[t];
            for (const auto &edge : to[now]) {
                int nxt = edge.first;
                if (visited[nxt]) continue;
                visorder.push_back(nxt);
                visited[nxt] = 1;
                par[nxt] = now;
            }
        }

        for (int t = int(visorder.size()) - 1; t >= 0; --t) {
            int now = visorder[t];
            Ch ch = e();
            for (const auto &edge : to[now]) {
                int nxt = edge.first;
                if (nxt == par[now]) continue;
                ch = merge(ch, f(dp_subtree[nxt], nxt, edge.second));
            }
            dp_subtree[now] = g(ch, now);
        }

        std::vector<Ch> left;
        for (int now : visorder) {
            int m = int(to[now].size());
            left.assign(m + 1, e());
            for (int j = 0; j < m; j++) {
                int nxt = to[now][j].first;
                const St &st = (nxt == par[now] ? dp_par[now] : dp_subtree[nxt]);
                left[j + 1] = merge(left[j], f(st, nxt, to[now][j].second));
            }
            dpall[now] = g(left.back(), now);

            Ch rprod = e();
            for (int j = m - 1; j >= 0; --j) {
                int nxt = to[now][j].first;
                if (nxt != par[now]) dp_par[nxt] = g(merge(left[j], rprod), now);

                const St &st = (nxt == par[now] ? dp_par[now] : dp_subtree[nxt]);
                rprod = merge(f(st, nxt, to[now][j].second), rprod);
            }
        }
    }

    void run() {
        for (int i = 0; i < n_; ++i) {
            if (!visited[i]) run_connected(i);
        }
    }

    const St &get_subtree(int root_, int par_) const {
        if (par_ < 0) return dpall.at(root_);
        if (par.at(root_) == par_) return dp_subtree.at(root_);
        if (par.at(par_) == root_) return dp_par.at(par_);
        std::exit(1);
    }
};
/* Template:
struct Subtree {};
struct Child {};
struct Edge {};
Child e() { return Child(); }
Child merge(Child x, Child y) { return Child(); }
Child f(Subtree x, int ch_id, Edge edge) { return Child(); }
Subtree g(Child x, int v_id) { return Subtree(); }

vector<vector<pair<int, Edge>>> to;
rerooting<Edge, Subtree, Child, merge, f, g, e> tree(to);
*/
