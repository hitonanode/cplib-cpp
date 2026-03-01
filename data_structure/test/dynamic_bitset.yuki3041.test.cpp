#define PROBLEM "https://yukicoder.me/problems/no/3041"
#include "../dynamic_bitset.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, F;
    cin >> N >> F;
    vector<int> A(N), B(N), C(N);
    for (auto &a : A) cin >> a;
    for (auto &b : B) cin >> b;
    for (auto &c : C) cin >> c;

    dynamic_bitset bs(N * F + 1);
    bs.set(0);

    for (int i = 0; i < N; ++i) {
        int a = A.at(i), b = B.at(i), c = C.at(i);
        if (a > b) swap(a, b);
        if (b > c) swap(b, c);
        if (a > b) swap(a, b);
        b -= a;
        c -= a;
        bs = bs | (bs << b) | (bs << c);
        cout << bs.count() << '\n';
    }
}
