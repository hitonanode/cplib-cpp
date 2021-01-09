#pragma once
#include <array>
#include <deque>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

// CUT begin
template <typename T_E, T_E INF, T_E (*edge_cost)(int, int, int, int)> struct GridGraph {
    const int H, W;
    const std::vector<int> dx{1, -1, 0, 0};
    const std::vector<int> dy{0, 0, 1, -1};

    GridGraph() = default;
    GridGraph(int h, int w) : H(h), W(w) {}

    // Dijkstra's algorithm
    // Complexity: O(HWlog(HW))
    std::vector<std::vector<T_E>> dist;                // Distance from (x_s, y_s)
    std::vector<std::vector<std::pair<int, int>>> prv; // Previous node for Dijkstra optimal path
    void dijkstra(int x_s, int y_s) {
        dist.assign(H, std::vector<T_E>(W, INF));
        prv.assign(H, std::vector<std::pair<int, int>>(W, std::make_pair(-1, -1)));

        using P = std::tuple<T_E, int, int>;
        std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
        dist[x_s][y_s] = 0;
        pq.emplace(0, x_s, y_s);
        while (!pq.empty()) {
            T_E dnow;
            int x, y;
            std::tie(dnow, x, y) = pq.top();
            pq.pop();
            if (dist[x][y] < dnow) continue;
            for (unsigned d = 0; d < dx.size(); d++) {
                int xn = x + dx[d], yn = y + dy[d];
                if (xn < 0 or yn < 0 or xn >= H or yn >= W) continue;
                T_E dnxt = dnow + edge_cost(x, y, xn, yn);
                if (dnxt < dist[xn][yn]) {
                    dist[xn][yn] = dnxt;
                    prv[xn][yn] = std::make_pair(x, y);
                    pq.emplace(dnxt, xn, yn);
                }
            }
        }
    }

    void bfs_01(int x_s, int y_s) {
        dist.assign(H, std::vector<T_E>(W, INF));
        prv.assign(H, std::vector<std::pair<int, int>>(W, std::make_pair(-1, -1)));
        std::deque<std::pair<int, int>> deq;
        dist[x_s][y_s] = 0;
        deq.emplace_back(x_s, y_s);
        while (!deq.empty()) {
            int x, y;
            std::tie(x, y) = deq.front();
            const auto dnow = dist[x][y];
            deq.pop_front();
            for (unsigned d = 0; d < dx.size(); d++) {
                int xn = x + dx[d], yn = y + dy[d];
                if (xn < 0 or yn < 0 or xn >= H or yn >= W) continue;
                auto dnxt = dnow + edge_cost(x, y, xn, yn);
                if (dnxt < dist[xn][yn]) {
                    dist[xn][yn] = dnxt;
                    prv[xn][yn] = std::make_pair(x, y);
                    if (dnxt)
                        deq.emplace_back(xn, yn);
                    else
                        deq.emplace_front(xn, yn);
                }
            }
        }
    }
};
