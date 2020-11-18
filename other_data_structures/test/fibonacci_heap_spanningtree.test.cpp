#include "other_data_structures/fibonacci_heap.hpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A"

#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int V, E;
    cin >> V >> E;
    fibonacci_heap<pair<int, int>> hp;

    vector<vector<pair<int, int>>> to(V);
    vector<int> belong(V);
    while (E--) {
        int s, t, w;
        cin >> s >> t >> w;
        to[s].emplace_back(w, t);
        to[t].emplace_back(w, s);
    }
    belong[0] = 1;
    for (auto p : to[0]) hp.push(p);

    int ret = 0;
    while (hp.size()) {
        auto [ecost, i] = hp.top();
        hp.pop();
        if (belong[i]) continue;
        ret += ecost;
        belong[i] = 1;
        for (auto p : to[i])
            if (!belong[p.second]) hp.push(p);
    }
    cout << ret << '\n';
}
