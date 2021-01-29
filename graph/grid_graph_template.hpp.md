---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"graph/grid_graph_template.hpp\"\n#include <array>\n#include\
    \ <deque>\n#include <queue>\n#include <tuple>\n#include <utility>\n#include <vector>\n\
    \n// CUT begin\ntemplate <typename T_E, T_E INF, T_E (*edge_cost)(int, int, int,\
    \ int)> struct GridGraph {\n    const int H, W;\n    const std::vector<int> dx{1,\
    \ -1, 0, 0};\n    const std::vector<int> dy{0, 0, 1, -1};\n\n    GridGraph() =\
    \ default;\n    GridGraph(int h, int w) : H(h), W(w) {}\n\n    // Dijkstra's algorithm\n\
    \    // Complexity: O(HWlog(HW))\n    std::vector<std::vector<T_E>> dist;    \
    \            // Distance from (x_s, y_s)\n    std::vector<std::vector<std::pair<int,\
    \ int>>> prv; // Previous node for Dijkstra optimal path\n    void dijkstra(int\
    \ x_s, int y_s) {\n        dist.assign(H, std::vector<T_E>(W, INF));\n       \
    \ prv.assign(H, std::vector<std::pair<int, int>>(W, std::make_pair(-1, -1)));\n\
    \n        using P = std::tuple<T_E, int, int>;\n        std::priority_queue<P,\
    \ std::vector<P>, std::greater<P>> pq;\n        dist[x_s][y_s] = 0;\n        pq.emplace(0,\
    \ x_s, y_s);\n        while (!pq.empty()) {\n            T_E dnow;\n         \
    \   int x, y;\n            std::tie(dnow, x, y) = pq.top();\n            pq.pop();\n\
    \            if (dist[x][y] < dnow) continue;\n            for (unsigned d = 0;\
    \ d < dx.size(); d++) {\n                int xn = x + dx[d], yn = y + dy[d];\n\
    \                if (xn < 0 or yn < 0 or xn >= H or yn >= W) continue;\n     \
    \           T_E dnxt = dnow + edge_cost(x, y, xn, yn);\n                if (dnxt\
    \ < dist[xn][yn]) {\n                    dist[xn][yn] = dnxt;\n              \
    \      prv[xn][yn] = std::make_pair(x, y);\n                    pq.emplace(dnxt,\
    \ xn, yn);\n                }\n            }\n        }\n    }\n\n    void bfs_01(int\
    \ x_s, int y_s) {\n        dist.assign(H, std::vector<T_E>(W, INF));\n       \
    \ prv.assign(H, std::vector<std::pair<int, int>>(W, std::make_pair(-1, -1)));\n\
    \        std::deque<std::pair<int, int>> deq;\n        dist[x_s][y_s] = 0;\n \
    \       deq.emplace_back(x_s, y_s);\n        while (!deq.empty()) {\n        \
    \    int x, y;\n            std::tie(x, y) = deq.front();\n            const auto\
    \ dnow = dist[x][y];\n            deq.pop_front();\n            for (unsigned\
    \ d = 0; d < dx.size(); d++) {\n                int xn = x + dx[d], yn = y + dy[d];\n\
    \                if (xn < 0 or yn < 0 or xn >= H or yn >= W) continue;\n     \
    \           auto dnxt = dnow + edge_cost(x, y, xn, yn);\n                if (dnxt\
    \ < dist[xn][yn]) {\n                    dist[xn][yn] = dnxt;\n              \
    \      prv[xn][yn] = std::make_pair(x, y);\n                    if (dnxt)\n  \
    \                      deq.emplace_back(xn, yn);\n                    else\n \
    \                       deq.emplace_front(xn, yn);\n                }\n      \
    \      }\n        }\n    }\n};\n"
  code: "#pragma once\n#include <array>\n#include <deque>\n#include <queue>\n#include\
    \ <tuple>\n#include <utility>\n#include <vector>\n\n// CUT begin\ntemplate <typename\
    \ T_E, T_E INF, T_E (*edge_cost)(int, int, int, int)> struct GridGraph {\n   \
    \ const int H, W;\n    const std::vector<int> dx{1, -1, 0, 0};\n    const std::vector<int>\
    \ dy{0, 0, 1, -1};\n\n    GridGraph() = default;\n    GridGraph(int h, int w)\
    \ : H(h), W(w) {}\n\n    // Dijkstra's algorithm\n    // Complexity: O(HWlog(HW))\n\
    \    std::vector<std::vector<T_E>> dist;                // Distance from (x_s,\
    \ y_s)\n    std::vector<std::vector<std::pair<int, int>>> prv; // Previous node\
    \ for Dijkstra optimal path\n    void dijkstra(int x_s, int y_s) {\n        dist.assign(H,\
    \ std::vector<T_E>(W, INF));\n        prv.assign(H, std::vector<std::pair<int,\
    \ int>>(W, std::make_pair(-1, -1)));\n\n        using P = std::tuple<T_E, int,\
    \ int>;\n        std::priority_queue<P, std::vector<P>, std::greater<P>> pq;\n\
    \        dist[x_s][y_s] = 0;\n        pq.emplace(0, x_s, y_s);\n        while\
    \ (!pq.empty()) {\n            T_E dnow;\n            int x, y;\n            std::tie(dnow,\
    \ x, y) = pq.top();\n            pq.pop();\n            if (dist[x][y] < dnow)\
    \ continue;\n            for (unsigned d = 0; d < dx.size(); d++) {\n        \
    \        int xn = x + dx[d], yn = y + dy[d];\n                if (xn < 0 or yn\
    \ < 0 or xn >= H or yn >= W) continue;\n                T_E dnxt = dnow + edge_cost(x,\
    \ y, xn, yn);\n                if (dnxt < dist[xn][yn]) {\n                  \
    \  dist[xn][yn] = dnxt;\n                    prv[xn][yn] = std::make_pair(x, y);\n\
    \                    pq.emplace(dnxt, xn, yn);\n                }\n          \
    \  }\n        }\n    }\n\n    void bfs_01(int x_s, int y_s) {\n        dist.assign(H,\
    \ std::vector<T_E>(W, INF));\n        prv.assign(H, std::vector<std::pair<int,\
    \ int>>(W, std::make_pair(-1, -1)));\n        std::deque<std::pair<int, int>>\
    \ deq;\n        dist[x_s][y_s] = 0;\n        deq.emplace_back(x_s, y_s);\n   \
    \     while (!deq.empty()) {\n            int x, y;\n            std::tie(x, y)\
    \ = deq.front();\n            const auto dnow = dist[x][y];\n            deq.pop_front();\n\
    \            for (unsigned d = 0; d < dx.size(); d++) {\n                int xn\
    \ = x + dx[d], yn = y + dy[d];\n                if (xn < 0 or yn < 0 or xn >=\
    \ H or yn >= W) continue;\n                auto dnxt = dnow + edge_cost(x, y,\
    \ xn, yn);\n                if (dnxt < dist[xn][yn]) {\n                    dist[xn][yn]\
    \ = dnxt;\n                    prv[xn][yn] = std::make_pair(x, y);\n         \
    \           if (dnxt)\n                        deq.emplace_back(xn, yn);\n   \
    \                 else\n                        deq.emplace_front(xn, yn);\n \
    \               }\n            }\n        }\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/grid_graph_template.hpp
  requiredBy: []
  timestamp: '2021-01-10 04:34:32+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: graph/grid_graph_template.hpp
layout: document
redirect_from:
- /library/graph/grid_graph_template.hpp
- /library/graph/grid_graph_template.hpp.html
title: graph/grid_graph_template.hpp
---
