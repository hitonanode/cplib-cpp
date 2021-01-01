#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"

#include "../fibonacci_heap.hpp"
#include <iostream>
#include <stack>
#include <utility>
#include <vector>

int main() {
    std::cin.tie(nullptr), std::ios::sync_with_stdio(false);

    int N, M, s, t;
    std::cin >> N >> M >> s >> t;
    using P = std::pair<long long, int>;
    fibonacci_heap<P> heap;

    constexpr long long INF = 1e18;
    std::vector<long long> D(N, INF);
    std::vector<int> prev(N, -1);
    D[s] = 0;
    std::vector<fibonacci_heap<P>::Node *> handler(N);
    for (int i = 0; i < N; i++) { handler[i] = heap.push(std::make_pair(D[i], i)); }

    std::vector<std::vector<std::pair<int, int>>> to(N);
    while (M--) {
        int a, b, c;
        std::cin >> a >> b >> c;
        to[a].emplace_back(b, c);
    }

    while (heap.size()) {
        int now = heap.top().second;
        if (now == t) break;
        heap.pop();
        for (const auto &nxtlen : to[now]) {
            const auto nxt = nxtlen.first, len = nxtlen.second;
            if (D[nxt] > D[now] + len) {
                D[nxt] = D[now] + len, prev[nxt] = now;
                heap.decrease(handler[nxt], std::make_pair(D[nxt], nxt));
            }
        }
    }

    if (D[t] == INF) {
        std::cout << -1 << '\n';
        return 0;
    }

    std::stack<int> path;
    int now = t;
    while (now != s) { path.push(now), now = prev[now], path.push(now); }
    std::cout << D[t] << ' ' << path.size() / 2 << '\n';
    while (path.size()) {
        std::cout << path.top() << ' ';
        path.pop();
        std::cout << path.top() << '\n';
        path.pop();
    }
}
