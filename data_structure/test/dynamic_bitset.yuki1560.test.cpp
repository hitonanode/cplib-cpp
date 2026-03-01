#define PROBLEM "https://yukicoder.me/problems/no/1560"
#include "../dynamic_bitset.hpp"
#include <bit>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, M;
    cin >> N >> M;
    vector S(N, vector<int>(M));
    for (auto &row : S)
        for (auto &x : row) cin >> x;

    vector bs(M, dynamic_bitset(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) bs[j].set(i, S[i][j]);
    }

    vector state(1 << M, dynamic_bitset(N));
    state.at(0).set_all();
    for (int j = 0; j < M; ++j) state[1 << j] = bs[j];

    for (int s = 0; s < (1 << M); ++s) {
        if (std::popcount((unsigned)s) <= 1) continue;
        int i = 0;
        while ((~s >> i) & 1) i++;
        state[s] = state[1 << i] & state[s - (1 << i)];
    }

    vector<unsigned> dp(1 << M);
    dp[0] = 1;

    for (int s = 0; s < (1 << M); ++s) {
        int n = state[s].count();
        for (int j = 0; j < M; ++j)
            if (~s & (1 << j)) {
                int f = (state[s] & bs[j]).count(), a = n - f;
                if (f >= a) dp[s | (1 << j)] += dp[s];
            }
    }
    cout << dp.back() << '\n';
}
