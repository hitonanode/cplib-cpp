#define PROBLEM "https://yukicoder.me/problems/no/1773"
#include "../../modint.hpp"
#include "../linear_matroid_parity.hpp"
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>
using mint = ModInt<1000000007>;
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N, M;
    cin >> N >> M;
    vector<pair<vector<mint>, vector<mint>>> uvs;

    while (M--) {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v, --w;
        vector<mint> a(N), b(N);
        a[u] = b[v] = 1, a[w] = b[w] = -1;
        uvs.emplace_back(a, b);
    }

    cout << linear_matroid_parity_size(uvs, 14786) << '\n';
}
