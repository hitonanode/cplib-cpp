#include "centroid_decomposition.hpp"
#include <algorithm>
#include <utility>
#include <vector>

struct frequency_table_of_tree_distance {
    std::vector<std::vector<int>> tos;
    std::vector<int> cd;
    std::vector<std::pair<int, int>> tmp;
    std::vector<int> alive;

    void _dfs(int now, int prv, int depth) {
        // if (int(tmp.size()) <= depth) tmp.resize(depth + 1, 0);
        // tmp[depth]++;
        tmp.emplace_back(now, depth);
        for (auto nxt : tos[now]) {
            if (alive[nxt] and nxt != prv) _dfs(nxt, now, depth + 1);
        }
    }
    std::vector<std::pair<int, int>> cnt_dfs(int root) { return tmp.clear(), _dfs(root, -1, 0), tmp; }
    frequency_table_of_tree_distance(const std::vector<std::vector<int>>& to) {
        tos = to;
        cd = CentroidDecomposition(to).centroid_decomposition(0);
    }
    template <class S, std::vector<S> (*conv)(const std::vector<S>&, const std::vector<S>&)>
    std::vector<S> solve(const std::vector<S>& weight) {
        alive.assign(tos.size(), 1);
        std::vector<S> ret(tos.size());
        std::vector<S> v;
        for (auto root : cd) {
            std::vector<std::vector<S>> vv;
            alive[root] = 0;
            for (auto nxt : tos[root]) {
                if (!alive[nxt]) continue;
                v.clear();
                for (auto p : cnt_dfs(nxt)) {
                    while (int(v.size()) <= p.second) v.push_back(S(0));
                    v[p.second] += weight[p.first];
                }
                for (int i = 0; i < int(v.size()); i++) ret[i + 1] += v[i] * weight[root];
                vv.emplace_back(v);
            }
            std::sort(vv.begin(), vv.end(),
                      [&](const std::vector<S>& l, const std::vector<S>& r) { return l.size() < r.size(); });
            for (size_t j = 1; j < vv.size(); j++) {
                const std::vector<S> c = conv(vv[j - 1], vv[j]);
                for (size_t i = 0; i < c.size(); i++) ret[i + 2] += c[i];
                for (size_t i = 0; i < vv[j - 1].size(); i++) vv[j][i] += vv[j - 1][i];
            }
            tos[root].clear();
        }
        return ret;
    }
};
