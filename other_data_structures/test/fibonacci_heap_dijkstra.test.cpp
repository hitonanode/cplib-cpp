#include "other_data_structures/fibonacci_heap.hpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A"

#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int V, E, R;
    cin >> V >> E >> R;

    using lint = long long;
    using plint = pair<lint, lint>;
    heap<lint> fib(V, 1e18);
    fib.chmin(R, 0);

    vector<vector<plint>> to(V);
    while (E--) {
        int s, t, d;
        cin >> s >> t >> d;
        to[s].emplace_back(t, d);
    }
    while (fib.size()) {
        int now = fib.pop().second;
        for (auto p : to[now]) fib.chmin(p.first, fib[now] + p.second);
    }

    for (auto x : fib.result) {
        if (x == 1e18)
            cout << "INF\n";
        else
            cout << x << '\n';
    }
}
