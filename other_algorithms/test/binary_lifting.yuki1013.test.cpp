#define PROBLEM "https://yukicoder.me/problems/no/1013"

#include "../binary_lifting.hpp"
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

using S = long long;
S op(S l, S r) { return l + r; }

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N, K;
    cin >> N >> K;
    vector<int> g(N);
    vector<long long> w(N);
    for (int i = 0; i < N; ++i) {
        cin >> w.at(i);
        g.at(i) = (i + w.at(i)) % N;
    }

    binary_lifting<long long, op> bl(g, w);

    for (int i = 0; i < N; ++i) cout << i + 1 + bl.prod(i, K) << '\n';
}
