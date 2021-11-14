#define PROBLEM "https://yukicoder.me/problems/no/1744"
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

    set<pair<int, int>> fixed;
    for (auto [us, vs] : dm) {
        if (us.size() == 1 and vs.size() == 1) fixed.emplace(us[0], vs[0]);
    }
    for (auto [s, t] : edges) cout << (fixed.count(make_pair(s, t)) ? "No" : "Yes") << '\n';
}
