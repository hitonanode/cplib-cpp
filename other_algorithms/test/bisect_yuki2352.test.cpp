#define PROBLEM "https://yukicoder.me/problems/no/2352"
#define ERROR 1e-5
#include "../bisect.hpp"

#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false), cout << fixed << setprecision(10);
    int R, K;
    cin >> R >> K;
    const double pi = acos(-1);

    for (int i = 1; i < K + 1; ++i) {
        double tgt = pi / (K + 1) * i;

        auto res = bisect<double>(0, pi, [&](double c) { return c - sin(c * 2) / 2 < tgt; });
        cout << -cos(res.ng) * R << '\n';
    }
}
