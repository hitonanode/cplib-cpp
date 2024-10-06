#define PROBLEM "https://yukicoder.me/problems/no/705"
#include "../monge_shortest_path.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N;
    cin >> N;
    vector<int> A(N), X(N), Y(N);
    for (auto &a : A) cin >> a;
    for (auto &x : X) cin >> x;
    for (auto &y : Y) cin >> y;

    auto weight = [&](int j, int i) {
        assert(j < i);
        --i;
        const long long dx = abs(A.at(i) - X.at(j)), dy = Y.at(j);
        return dx * dx * dx + dy * dy * dy;
    };

    monge_shortest_path<long long> msp;
    cout << msp.solve(N + 1, weight) << '\n';
}
