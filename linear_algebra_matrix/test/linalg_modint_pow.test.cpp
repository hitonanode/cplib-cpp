#include "../../modint.hpp"
#include "../matrix.hpp"
#include <iostream>
#include <vector>
using namespace std;
#define PROBLEM "https://yukicoder.me/problems/no/1112"

int pq2id(int p2, int p1) { return p2 * 6 + p1; }

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int K, M;
    long long N;
    cin >> K >> M >> N;
    using mint = ModInt<1000000007>;
    matrix<mint> mat(36, 36);
    while (M--) {
        int p, q, r;
        cin >> p >> q >> r;
        p--, q--, r--;
        int i = pq2id(p, q), j = pq2id(q, r);
        mat[j][i] = 1;
    }
    vector<mint> vec(36);
    for (int i = 0; i < K; i++) vec[pq2id(0, i)] = 1;
    vec = mat.pow(N - 2) * vec;
    mint ret = 0;
    for (int i = 0; i < K; i++) ret += vec[pq2id(i, 0)];
    cout << ret << '\n';
}
