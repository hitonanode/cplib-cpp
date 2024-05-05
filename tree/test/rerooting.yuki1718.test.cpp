#define PROBLEM "https://yukicoder.me/problems/no/1718"
#include "../rerooting.hpp"
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

vector<int> inD;

struct Subtree {
    bool exist;
    int oneway, round;
};
struct Children {
    bool exist;
    int oneway, round;
};
Children e() { return {false, 0, 0}; }

Children merge(Children x, Children y) {
    if (!x.exist) return y;
    if (!y.exist) return x;
    return Children{true, min(x.oneway + y.round, y.oneway + x.round), x.round + y.round};
}

Children add_edge(Subtree x, int, tuple<>) {
    if (!x.exist) return e();
    return {true, x.oneway + 1, x.round + 2};
}

Subtree add_vertex(Children x, int v) {
    if (x.exist or inD[v]) return {true, x.oneway, x.round};
    return {false, 0, 0};
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int N, K;
    cin >> N >> K;
    vector<vector<pair<int, tuple<>>>> to(N);
    for (int e = 0; e < N - 1; e++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        to[u].emplace_back(v, make_tuple());
        to[v].emplace_back(u, make_tuple());
    }
    inD.assign(N, 0);
    while (K--) {
        int d;
        cin >> d;
        inD[d - 1] = 1;
    }
    rerooting<tuple<>, Subtree, Children, merge, add_edge, add_vertex, e> tree(to);
    tree.run();
    for (auto x : tree.dpall) cout << x.oneway << '\n';
}
