#define PROBLEM "https://yukicoder.me/problems/no/1745"
#include "../dulmage_mendelsohn_decomposition.hpp"
#include <iostream>
#include <set>
#include <utility>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, M, L;
    cin >> N >> M >> L;
    vector<pair<int, int>> edges(L);
    for (auto &[s, t] : edges) {
        cin >> s >> t;
        --s, --t;
    }

    auto dm = dulmage_mendelsohn(N, M, edges);
    vector<int> grp1(N, -1), grp2(M, -1);
    for (int g = 0; g < dm.size(); ++g) {
        for (auto i : dm[g].first) grp1[i] = g;
        for (auto i : dm[g].second) grp2[i] = g;
    }
    for (auto [s, t] : edges) cout << (grp1[s] == grp2[t] ? "Yes" : "No") << '\n';
}
