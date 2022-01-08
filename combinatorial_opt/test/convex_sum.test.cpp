#include "../convex_sum.hpp"
#include <cassert>
#include <iostream>
#define PROBLEM "https://yukicoder.me/problems/no/1495"
using namespace std;

long long solve() {
    using lint = long long;
    int N, M, K;
    cin >> N >> M >> K;
    vector<lint> a(N), b(N), c(N);
    while (M--) {
        int x;
        lint y;
        cin >> x >> y;
        x--;
        a[x]++;
        b[x] -= y * 2;
        c[x] += y * y;
    }
    vector<Quadratic> costs;
    for (int i = 0; i < N; i++) costs.emplace_back(a[i], b[i], c[i], 0, K);
    auto sol =
        MinConvexSumUnderLinearConstraint<Quadratic, lint, 1LL << 60>(vector<lint>(N, 1), costs, K);
    return sol.first;
}

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) cout << solve() << '\n';
}
