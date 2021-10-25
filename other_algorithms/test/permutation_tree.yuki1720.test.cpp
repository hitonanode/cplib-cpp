#define PROBLEM "https://yukicoder.me/problems/no/1720"
#include "../permutation_tree.hpp"
#include "../../modint.hpp"
#include <iostream>

using mint = ModInt<998244353>;
using namespace std;

int N, K;
permutation_tree tree;
vector<vector<mint>> dp;

void rec(int now) {
    const auto &v = tree.nodes[now];
    if (v.tp == permutation_tree::Cut or v.tp == permutation_tree::Leaf) {
        for (int k = 0; k < K; ++k) dp[k + 1][v.R] += dp[k][v.L];
    }

    vector<mint> sum(K);
    for (auto ch : v.child) {
        rec(ch);
        if (v.tp == permutation_tree::JoinAsc or v.tp == permutation_tree::JoinDesc) {
            for (int k = 0; k < K; ++k) {
                dp[k + 1][tree.nodes[ch].R] += sum[k];
                sum[k] += dp[k][tree.nodes[ch].L];
            }
        }
    }
};

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    cin >> N >> K;
    vector<int> P(N);

    for (auto &x : P) cin >> x;
    for (auto &x : P) x--;

    tree = permutation_tree(P);

    dp.assign(K + 1, vector<mint>(N + 1));
    dp[0][0] = 1;

    rec(tree.root);

    for (int i = 1; i <= K; i++) cout << dp[i][N] << '\n';
}
