#define PROBLEM "https://yukicoder.me/problems/no/1615"
#include "../dulmage_mendelsohn_decomposition.hpp"
#include <cassert>
#include <iostream>
#include <set>
#include <utility>
#include <vector>
using namespace std;

std::vector<std::pair<std::vector<int>, std::vector<int>>>
verify_dulmage_mendelsohn(int L, int R, const std::vector<std::pair<int, int>> &edges) {
    auto ret = dulmage_mendelsohn(L, R, edges);
    assert(ret.size() >= 2);
    vector<int> lord(L, -1), rord(R, -1);
    set<pair<int, int>> edges_set(edges.begin(), edges.end());

    for (int igrp = 0; igrp < int(ret.size()); ++igrp) {
        for (int vl : ret[igrp].first) {
            assert(lord[vl] < 0);
            lord[vl] = igrp;
        }
        for (int vr : ret[igrp].second) {
            assert(rord[vr] < 0);
            rord[vr] = igrp;
        }
        if (igrp == 0) {
            assert(ret[igrp].first.size() < ret[igrp].second.size() or ret[igrp].first.empty());
        } else if (igrp + 1 == int(ret.size())) {
            assert(ret[igrp].first.size() > ret[igrp].second.size() or ret[igrp].second.empty());
        } else {
            assert(ret[igrp].first.size() == ret[igrp].second.size());
            assert(ret[igrp].first.size());
        }
        for (int j = 0; j < min<int>(ret[igrp].first.size(), ret[igrp].second.size()); ++j) {
            auto u = ret[igrp].first[j], v = ret[igrp].second[j];
            assert(edges_set.count(make_pair(u, v)));
        }
    }
    assert(count(lord.begin(), lord.end(), -1) == 0);
    assert(count(rord.begin(), rord.end(), -1) == 0);

    for (auto e : edges) {
        assert(0 <= e.first and e.first < L);
        assert(0 <= e.second and e.second < R);
        assert(lord.at(e.first) <= rord.at(e.second)); // Check topological order
    }
    return ret;
}

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, M, K, L;
    cin >> N >> M >> K >> L;
    vector<vector<pair<int, int>>> z2xy(K + 1);

    while (L--) {
        int x, y, z;
        cin >> x >> y >> z;
        x--, y--;
        z2xy[K - z].emplace_back(x, y);
    }
    vector<int> vtp(N + M, 3);

    vector<pair<int, int>> alive_edges;

    long long ret = 0;
    int nmatch = 0;

    vector<int> experience12(N + M);
    vector<int> fixed_pair(N, -1);

    for (const auto &xys : z2xy) {
        for (auto p : xys) {
            int u = p.first, v = p.second;
            if (experience12[u] or experience12[N + v]) continue;
            alive_edges.emplace_back(u, v);
        }

        auto dm_ret = verify_dulmage_mendelsohn(N, M, alive_edges);

        int nmatchnxt = 0;
        for (const auto &p : dm_ret) nmatchnxt += min(p.first.size(), p.second.size());

        ret = ret * 2 + nmatchnxt - nmatch;

        for (auto l : dm_ret.front().first) vtp[l] = 2, experience12[l] = 1;
        for (auto r : dm_ret.front().second) vtp[r + N] = 3;
        for (auto l : dm_ret.back().first) vtp[l] = 3;
        for (auto r : dm_ret.back().second) vtp[r + N] = 2, experience12[r + N] = 1;

        for (int i = 1; i + 1 < int(dm_ret.size()); ++i) {
            for (int j = 0; j < int(dm_ret[i].first.size()); ++j) {
                int l = dm_ret[i].first[j], r = dm_ret[i].second[j];
                if (fixed_pair[l] < 0) {
                    vtp[l] = vtp[r + N] = 1, fixed_pair[l] = r;
                    experience12[l] = experience12[r + N] = 1;
                    alive_edges.emplace_back(l, r);
                }
            }
        }

        for (int cur = 0; cur < int(alive_edges.size());) {
            int u = alive_edges[cur].first, v = alive_edges[cur].second;
            if (vtp[u] + vtp[v + N] == 5 or fixed_pair[u] == v) {
                cur++;
            } else {
                alive_edges[cur].swap(alive_edges.back());
                alive_edges.pop_back();
            }
        }
        nmatch = nmatchnxt;
    }
    cout << ret << endl;
}
