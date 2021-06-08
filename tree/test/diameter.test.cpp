#define PROBLEM "https://judge.yosupo.jp/problem/tree_diameter"
#include "../diameter.hpp"
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N;
    cin >> N;
    TreeDiameter<long long> tree(N);
    for (int i = 0; i < N - 1; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        tree.add_edge(a, b, c);
    }
    auto ret = tree.get_diameter_edges();
    cout << ret.first << ' ' << ret.second.size() << '\n';
    for (auto x : ret.second) cout << x << ' ';
    cout << '\n';
}
