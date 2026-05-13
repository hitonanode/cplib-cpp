#pragma once
#include <array>
#include <deque>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

// CUT begin
template <typename T_E, T_E INF> struct GridGraph {
    const int H, W;
    const std::vector<int> dx{1, -1, 0, 0};
    const std::vector<int> dy{0, 0, 1, -1};
    // T_E (*edge_cost)(int, int, int, int);
    function<T_E(int, int, int, int)> edge_cost;

    GridGraph() = default;
    GridGraph(int h, int w, std::function<T_E(int, int, int, int)> _edge_cost) : H(h), W(w), edge_cost(move(_edge_cost)) {}

    // Dijkstra's algorithm
    // Complexity: O(HWlog(HW))
    std::vector<std::vector<T_E>> dist;                // Distance from (x_s, y_s)
    std::vector<std::vector<std::pair<int, int>>> prv; // Previous node for Dijkstra optimal path
    void dijkstra(int x_s, int y_s) { dijkstra({x_s, y_s}); }
    void dijkstra(std::vector<std::pair<int, int>> xy_s) {
        dist.assign(H, std::vector<T_E>(W, INF));
        prv.assign(H, std::vector<std::pair<int, int>>(W, std::make_pair(-1, -1)));

        using P = std::tuple<T_E, int, int>;
        std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
        for (auto [x_s, y_s]: xy_s)  dist[x_s][y_s] = 0, pq.emplace(0, x_s, y_s);
        while (!pq.empty()) {
            auto [dnow, x, y] = pq.top();
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


    void bfs_01(int x_s, int y_s) { bfs_01({x_s, y_s}); }
    void bfs_01(std::vector<std::pair<int, int>> xy_s) {
        std::deque<std::pair<int, int>> deq;
        dist.assign(H, std::vector<T_E>(W, INF));
        prv.assign(H, std::vector<std::pair<int, int>>(W, std::make_pair(-1, -1)));
        for (auto [x_s, y_s]: xy_s) dist[x_s][y_s] = 0, deq.emplace_back(x_s, y_s);
        while (!deq.empty()) {
            auto [x, y] = deq.front(); deq.pop_front();
            const auto dnow = dist[x][y];
            for (unsigned d = 0; d < dx.size(); d++) {
                int xn = x + dx[d], yn = y + dy[d];
                if (xn < 0 or yn < 0 or xn >= H or yn >= W) continue;
                auto cost = edge_cost(x, y, xn, yn);
                auto dnxt = dnow + cost;
                if (dnxt < dist[xn][yn]) {
                    dist[xn][yn] = dnxt;
                    prv[xn][yn] = std::make_pair(x, y);
                    if (cost) deq.emplace_back(xn, yn);
                    else deq.emplace_front(xn, yn);
                }
            }
        }
    }
};
