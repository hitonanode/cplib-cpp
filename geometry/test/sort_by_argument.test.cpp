#define PROBLEM "https://judge.yosupo.jp/problem/sort_points_by_argument"
#include "../sort_by_argument.hpp"

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N;
    cin >> N;
    vector<Point> ps;
    while (N--) {
        long long x, y;
        cin >> x >> y;
        ps.emplace_back(x, y);
    }
    sort(ps.begin(), ps.end());
    for (auto p : ps) cout << p.X << ' ' << p.Y << '\n';
}
