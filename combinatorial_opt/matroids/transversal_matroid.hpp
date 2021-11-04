#pragma once
#include "../../graph/dulmage_mendelsohn_decomposition.hpp"
#include <vector>

struct TransversalMatroid {
    int M, W;
    std::vector<std::vector<int>> to;
    TransversalMatroid(int M_, int Mopp, const std::vector<std::pair<int, int>> &edges_)
        : M(M_), W(Mopp), to(M_) {
        for (auto p : edges_) to[p.first].push_back(p.second);
    }

    int size() const { return M; }

    std::vector<int> is_opp_fixed;
    std::vector<std::vector<int>> _to_dfs;
    template <class State = std::vector<bool>> void set(State I) {
        std::vector<std::pair<int, int>> edges;

        for (int e = 0; e < M; ++e) {
            if (I[e]) {
                for (int w : to[e]) edges.emplace_back(e, w);
            }
        }
        auto dm = dulmage_mendelsohn(M, W, edges);
        is_opp_fixed.assign(W, 1);
        for (auto w : dm.front().second) is_opp_fixed[w] = 0;

        _to_dfs.assign(M + W, {});
        for (int e = 0; e < int(to.size()); ++e) {
            for (int w : to[e]) _to_dfs[e].push_back(M + w);
        }
        for (const auto &p : dm) {
            const auto &es = p.first, &ws = p.second;
            for (int i = 0; i < std::min<int>(es.size(), ws.size()); ++i) {
                _to_dfs[M + ws[i]].push_back(es[i]);
            }
        }
    }

    std::vector<int> circuit(int e) const {
        for (int w : to[e]) {
            if (!is_opp_fixed[w]) return {};
        }
        std::vector<int> vis(M + W);
        std::vector<int> st{e};
        vis[e] = 1;
        while (st.size()) {
            int now = st.back();
            st.pop_back();
            for (auto nxt : _to_dfs[now]) {
                if (vis[nxt] == 0) {
                    vis[nxt] = 1;
                    st.push_back(nxt);
                }
            }
        }
        std::vector<int> ret;
        for (int e = 0; e < M; ++e) {
            if (vis[e]) ret.push_back(e);
        }
        return ret;
    }
};
