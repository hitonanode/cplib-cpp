#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2426"
#include "../merge_sort_tree.hpp"
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N, M;
    cin >> N >> M;
    vector<pair<int, int>> P(N);
    for (auto &p : P) cin >> p.first >> p.second;
    sort(P.begin(), P.end());
    vector<int> xs, ys;
    for (auto p : P) xs.push_back(p.first), ys.push_back(p.second);
    merge_sort_tree<int> tree(ys);
    while (M--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        int l = lower_bound(xs.begin(), xs.end(), x1) - xs.begin();
        int r = upper_bound(xs.begin(), xs.end(), x2) - xs.begin();
        cout << tree.cntLesseq(l, r, y2) - tree.cntLess(l, r, y1) << '\n';
    }
}
