#define PROBLEM "https://yukicoder.me/problems/no/3060"
#include "../dynamic_bitset.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int H, W;
    cin >> H >> W;
    using BS = dynamic_bitset;
    vector<BS> A(H);
    for (int i = 0; i < H; ++i) {
        string s;
        cin >> s;
        A.at(i) = BS(s);
    }

    sort(A.begin(), A.end(), [&](const BS &l, const BS &r) { return l.count() < r.count(); });

    vector<int> dp(H + 1);
    for (int i = 0; i < H; ++i) {
        dp[i + 1] = max(dp[i + 1], 1);
        for (int j = 0; j < i; ++j) {
            if ((A.at(i) & A.at(j)) == A.at(j)) dp[i + 1] = max(dp[i + 1], dp[j + 1] + 1);
        }
    }

    cout << H - *max_element(dp.begin(), dp.end()) << '\n';
}
