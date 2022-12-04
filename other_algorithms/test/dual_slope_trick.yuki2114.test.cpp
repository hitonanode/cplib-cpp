#define PROBLEM "https://yukicoder.me/problems/no/2114"
#include "../dual_slope_trick.hpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <utility>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N, M, K;
    cin >> N >> M >> K;
    map<int, vector<pair<int, int>>> mp;
    for (int i = 0; i < N; ++i) {
        int a;
        cin >> a;
        mp[a % K].emplace_back(a / K, 0);
    }
    for (int i = 0; i < M; ++i) {
        int b;
        cin >> b;
        mp[b % K].emplace_back(b / K, 1);
    }

    long long ret = 0;
    int nmatch = 0;
    for (auto [key, vs] : mp) {
        int n0 = 0, n1 = 0;
        for (auto [x, t] : vs) (t ? n1 : n0)++;

        nmatch += min(n0, n1);

        if (n0 > n1) {
            swap(n0, n1);
            for (auto &[x, t] : vs) t ^= 1;
        }
        sort(vs.begin(), vs.end());

        dual_slope_trick<long long, 1LL << 40> dst;
        int last_x = vs.front().first;
        for (auto [x, tp] : vs) {
            int dx = x - last_x;
            dst.add_linear_or_zero(dx, 0).add_linear_or_zero(-dx, 0);
            if (tp == 0) {
                dst.shift(1);
            } else {
                dst.slide_min(-1, 0);
            }
            last_x = x;
        }
        ret += dst.get_at_zero();
    }

    if (nmatch < min(N, M)) ret = -1;

    cout << ret << endl;
}
