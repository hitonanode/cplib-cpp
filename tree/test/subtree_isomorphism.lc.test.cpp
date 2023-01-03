#define PROBLEM "https://judge.yosupo.jp/problem/rooted_tree_isomorphism_classification"
#include "../tree_isomorphism.hpp"
#include "../../utilities/groupby.hpp"
#include "../../modint.hpp"
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int n;
    cin >> n;
    tree_isomorphism<ModInt998244353> tree(n);
    for (int i = 1, p = -1; i < n; ++i) tree.add_edge(i, (cin >> p, p));
    tree.build_hash(0, 15319159, 181263479);

    vector<pair<tree_isomorphism<ModInt998244353>::DoubleHash, int>> info;
    for (int i = 0; i < n; ++i) info.emplace_back(tree.hash_subtree.at(i), i);

    const auto gs = groupby(info);
    vector<int> ret(n);
    for (int g = 0; g < int(gs.size()); ++g) {
        for (int i : gs.at(g).second) ret.at(i) = g;
    }
    cout << gs.size() << '\n';
    for (int i = 0; i < n; ++i) cout << ret.at(i) << (i + 1 == n ? '\n' : ' ');
}
