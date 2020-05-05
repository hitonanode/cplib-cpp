#pragma once
#include <algorithm>
#include <cassert>
#include <queue>
#include <utility>
#include <vector>


// CUT begin
struct UndirectedGraph
{
    using pint = std::pair<int, int>;
    int V; // # of vertices
    int E; // # of edges
    int k;
    std::vector<std::vector<pint>> to;
    std::vector<pint> edges;
    std::vector<int> root_ids; // DFS forestの構築で根になった頂点

    std::vector<int> is_bridge; // Whether edge i is bridge or not, size = E
    std::vector<int> is_articulation; // whether vertex i is articulation point or not, size = V

    // lowlink
    std::vector<int> order;   // visiting order of DFS tree, size = V
    std::vector<int> lowlink; // size = V
    std::vector<int> is_dfstree_edge; // size = E

    int tecc_num; // 分割された二重辺連結成分数
    std::vector<int> tecc_id; // 各頂点が何個目の二重辺連結成分か

    UndirectedGraph(int V) : V(V), E(0), k(0), to(V),  order(V, -1), lowlink(V, -1) {}

    void add_edge(int v1, int v2)
    {
        assert(v1 >= 0 and v1 < V);
        assert(v2 >= 0 and v2 < V);
        to[v1].emplace_back(v2, E);
        to[v2].emplace_back(v1, E);
        edges.emplace_back(v1, v2);
        is_bridge.push_back(0);
        is_dfstree_edge.push_back(0);
        E++;
    }

    // Build DFS tree
    // Complexity: O(V + E)
    void dfs_lowlink(int now, int prv_eid = -1)
    {
        if (prv_eid == -1) root_ids.push_back(now);
        order[now] = lowlink[now] = k++;
        for (const auto &nxt : to[now]) if (nxt.second != prv_eid)
        {
            if (order[nxt.first] >= 0)
            {
                lowlink[now] = std::min(lowlink[now], order[nxt.first]);
            }
            else
            {
                is_dfstree_edge[nxt.second] = 1;
                dfs_lowlink(nxt.first, nxt.second);
                lowlink[now] = std::min(lowlink[now], lowlink[nxt.first]);
            }
        }
    }

    // Find all bridges
    // Complexity: O(V + E)
    void detectBridge()
    {
        for (int i = 0; i < E; i++)
        {
            int v1 = edges[i].first, v2 = edges[i].second;
            if (order[v1] < 0) dfs_lowlink(v1);
            if (order[v1] > order[v2]) std::swap(v1, v2);
            if (order[v1] < lowlink[v2]) is_bridge[i] = 1;
        }
    }

    // Find two-edge-connected components and classify all vertices
    // Complexity:  O(V + E)
    void two_edge_connected_components()
    {
        tecc_num = 0;
        tecc_id.assign(V, -1);

        for (int i = 0; i < V; i++) if (tecc_id[i] == -1)
        {
            tecc_id[i] = tecc_num;
            std::queue<int> que;
            que.push(i);
            while (!que.empty())
            {
                int now = que.front();
                que.pop();
                for (const auto &edge : to[now])
                {
                    int nxt = edge.first;
                    if (tecc_id[nxt] >= 0 or is_bridge[edge.second]) continue;
                    tecc_id[nxt] = tecc_num;
                    que.push(nxt);
                }
            }
            tecc_num++;
        }
    }


    void detectArticulation()
    {
        std::sort(root_ids.begin(), root_ids.end());
        is_articulation.assign(V, 0);
        for (int v = 0; v < V; v++)
        {
            if (std::binary_search(root_ids.begin(), root_ids.end(), v))
            {
                int n = 0;
                for (auto edge : to[v]) n += is_dfstree_edge[edge.second];
                if (n > 1) is_articulation[v] = 1;
            }
            else
            {
                for (auto e : to[v])
                {
                    if (is_dfstree_edge[e.second] and order[v] <= lowlink[e.first]) is_articulation[v] = 1;
                }
            }
        }
    }
};
