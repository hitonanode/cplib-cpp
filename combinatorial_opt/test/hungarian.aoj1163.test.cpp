#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1163"
#include "../hungarian.hpp"
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    while (true) {
        int m, n;
        cin >> m >> n;
        if (!m) break;

        vector<int> b(m), r(n);
        for (auto &x : b) cin >> x;
        for (auto &x : r) cin >> x;

        vector<vector<int>> mat;
        for (int x : b) {
            mat.push_back({});
            for (int y : r) mat.back().push_back(std::gcd(x, y) > 1 ? -1 : 0);
        }

        cout << -hungarian(mat).first << '\n';
    }
}
