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
struct Child {
    int oneway, round;
};

Child merge(Child x, Child y) {
    return Child{min(x.oneway + y.round, y.oneway + x.round), x.round + y.round};
}

Child f(Subtree x, int, tuple<>) { return {x.oneway + 1, x.round + 2}; }

Subtree g(Child x, int) { return {x.oneway, x.round}; }

Child e() { return {0, 0}; }

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
    rerooting<tuple<>, Subtree, Child, merge, f, g, e> tree(to);
    tree.run();
    for (auto x : tree.dpall) cout << x.oneway << '\n';
}
