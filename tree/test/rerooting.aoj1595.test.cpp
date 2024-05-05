#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1595"
#include "../rerooting.hpp"
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

struct Subtree {
    int oneway, round;
};
struct Children {
    int oneway, round;
};

Children merge(Children x, Children y) {
    return Children{min(x.oneway + y.round, y.oneway + x.round), x.round + y.round};
}

Children add_edge(Subtree x, int, tuple<>) { return {x.oneway + 1, x.round + 2}; }

Subtree add_vertex(Children x, int) { return {x.oneway, x.round}; }

Children e() { return {0, 0}; }

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N;
    cin >> N;
    vector<vector<pair<int, tuple<>>>> to(N);
    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        to[u].push_back({v, {}}), to[v].push_back({u, {}});
    }
    rerooting<tuple<>, Subtree, Children, merge, add_edge, add_vertex, e> tree(to);
    tree.run();
    for (auto x : tree.dpall) cout << x.oneway << '\n';
}
