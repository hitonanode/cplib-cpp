#define PROBLEM "https://yukicoder.me/problems/no/1602"
#include "../nonzero_path_of_group_labeled_graph.hpp"

struct G {
    unsigned g;
    G(unsigned x = 0) : g(x) {}
    G operator-() const noexcept { return *this; }
    G operator+(const G &r) const noexcept { return G(g ^ r.g); }
    bool operator==(const G &x) const noexcept { return g == x.g; }
};

#include <iostream>
#include <string>
using namespace std;
constexpr long long INF = 1LL << 60;

int main() {
    int N, M, K;
    cin >> N >> M >> K;
    ShortestNonzeroPath<long long, INF, G> graph(N);

    while (M--) {
        int a, b, c;
        string x;
        cin >> a >> b >> c >> x;
        unsigned m = 0;
        for (auto c : x) m = m * 2 + c - '0';
        a--, b--;
        graph.add_bi_edge(a, b, c, m);
    }
    graph.solve(N - 1);
    for (int i = 0; i < N - 1; i++) cout << (graph.dist[i] == INF ? -1 : graph.dist[i]) << '\n';
}
