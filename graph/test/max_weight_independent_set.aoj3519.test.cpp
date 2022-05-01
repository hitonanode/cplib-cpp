#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3519"
#include "../max_weight_independent_set.hpp"
#include <bitset>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int M, N;
    cin >> M >> N;
    vector<bitset<1 << 10>> vs(M);
    vector<int> H(M);
    for (int m = 0; m < M; ++m) {
        int k;
        cin >> k;
        H[m] = k;
        while (k--) {
            int a;
            cin >> a;
            vs[m].set(a);
        }
    }

    max_weight_independent_set<int> solver(H);

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < i; ++j) {
            if ((vs[i] & vs[j]).any()) solver.add_edge(i, j);
        }
    }
    cout << accumulate(H.begin(), H.end(), 0) - solver.solve() << '\n';
}
