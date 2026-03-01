#define PROBLEM "https://yukicoder.me/problems/no/2542"
#include "../dynamic_bitset.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int L, N;
    cin >> L >> N;
    vector<int> X(N + 2);
    for (int i = 1; i <= N; ++i) cin >> X[i];
    X[N + 1] = L;

    vector dp(2, vector(X.size(), dynamic_bitset(L + 1)));
    dp.at(0).at(0).set(0);
    for (int i = 0; i < (int)dp.at(0).size(); ++i) {
        for (int j = i + 1; j < (int)dp.at(0).size(); ++j) {
            const int w = X.at(j) - X.at(i);
            for (int d = 0; d < 2; ++d) dp.at(d ^ 1).at(j) |= (dp.at(d).at(i) << (d ? w : 0));
        }
    }

    int ret = L;
    for (int i = 0; i <= L; ++i) {
        if (dp.at(0).back().test(i)) ret = min(ret, abs(L - 2 * i));
    }
    cout << ret << '\n';
}
