#define PROBLEM "https://yukicoder.me/problems/no/263"
#include "../palindromic_tree.hpp"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    string S, T;
    cin >> S >> T;

    palindromic_tree::Tree<char> tree;

    vector<long long> visitcnt(S.size() + T.size() + 2);

    tree.add_string(S, [&](int, int node_idx) { visitcnt.at(node_idx)++; });
    tree.add_string(T);

    const int V = tree.nodes.size();
    for (int v = V - 1; v > 0; --v) {
        visitcnt.at(tree.nodes.at(v).suffix_link()) += visitcnt.at(v);
    }

    // 0 と 1 はダミーなのでカウントしてはいけない
    visitcnt.at(0) = visitcnt.at(1) = 0;

    for (int v = 1; v < V; ++v) visitcnt.at(v) += visitcnt.at(tree.nodes.at(v).suffix_link());

    long long ret = 0;
    tree.add_string(T, [&](int, int node_idx) { ret += visitcnt.at(node_idx); });

    cout << ret << '\n';
}
