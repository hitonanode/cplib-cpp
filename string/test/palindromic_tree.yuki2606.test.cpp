#define PROBLEM "https://yukicoder.me/problems/no/2606"
#include "../palindromic_tree.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    string S;
    cin >> S;

    palindromic_tree::Tree<char> tree;

    vector<long long> visitcnt(S.size() + 2);
    tree.add_string(S, [&](int, int node_idx) { visitcnt.at(node_idx)++; });

    const int V = tree.nodes.size();
    for (int i = V - 1; i > 0; --i) visitcnt.at(tree.nodes.at(i).suffix_link()) += visitcnt.at(i);

    vector<vector<int>> children(V);
    for (int i = 1; i < V; ++i) children.at(tree.nodes.at(i).suffix_link()).push_back(i);

    vector<long long> dp(V, 0);
    for (int i = 0; i < V; ++i) {
        dp.at(i) += visitcnt.at(i) * max(tree.nodes.at(i).length(), 0);
        for (int ch : children.at(i)) dp.at(ch) += dp.at(i);
    }

    cout << *max_element(dp.begin(), dp.end()) << '\n';
}
