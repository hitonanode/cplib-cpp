#define PROBLEM "https://yukicoder.me/problems/no/1695"
#include "../../string/manacher.hpp"
#include "../shortest_path.hpp"
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

constexpr int INF = 1 << 28;

int solve(const string &S, const string &T) {
    int nmatch = 0;
    while (nmatch < min<int>(S.size(), T.size()) and S[nmatch] == T[nmatch]) nmatch++;
    if (!nmatch) return INF;
    if (T.size() % 2) return INF;
    auto trev = T;
    reverse(trev.begin(), trev.end());
    if (trev != T) return INF;
    shortest_path<int> graph(T.size() + 1);
    for (int i = 0; i < int(T.size()); ++i) graph.add_edge(i, i + 1, 0);
    auto ps = enumerate_palindromes(T);
    for (const auto &p : ps) {
        auto l = p.first, r = p.second;
        if ((l + r) % 2 == 0) graph.add_edge(r, (l + r) / 2, 1);
    }
    graph.zero_one_bfs(T.size(), nmatch);
    return std::max(1, graph.dist[nmatch]);
}

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N, M;
    string S, T;
    cin >> N >> M >> S >> T;
    int ret = solve(S, T);
    reverse(S.begin(), S.end());
    ret = min(ret, solve(S, T));
    cout << (ret < INF ? ret : -1) << '\n';
}
