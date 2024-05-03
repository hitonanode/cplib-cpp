#define PROBLEM "https://yukicoder.me/problems/no/1421"
#include "../linalg_bitset.hpp"
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

template <typename T> bool chmin(T &m, const T q) {
    if (m > q) {
        m = q;
        return true;
    } else
        return false;
}

void bad() {
    puts("-1");
    exit(0);
}

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, M;
    cin >> N >> M;

    using ull = unsigned long long;
    vector<pair<ull, int>> basis;
    while (M--) {
        int a;
        cin >> a;
        ull mask = 0;
        while (a--) {
            int b;
            cin >> b;
            b--;
            mask += 1ULL << b;
        }
        int y;
        cin >> y;
        for (auto [v, w] : basis) {
            if (chmin(mask, mask ^ v)) y ^= w;
        }
        if (!mask and y) bad();
        if (mask) basis.emplace_back(mask, y);
    }
    vector<int> ret(N);

    for (int d = 0; d < 30; ++d) {
        constexpr int Wmax = 320;
        vector<bitset<Wmax>> A;
        vector<bool> b;
        for (int i = 0; i < int(basis.size()); ++i) {
            b.push_back((basis[i].second >> d) & 1);
            bitset<Wmax> a;
            a.reset();
            for (int j = 0; j < N; ++j) {
                if ((basis[i].first >> j) & 1) a[j] = 1;
            }
            A.emplace_back(a);
        }
        auto [ok, solution, freedoms] = f2_system_of_linear_equations<Wmax, vector<bool>>(A, b, N);
        if (!ok) bad();
        for (int i = 0; i < N; ++i) ret[i] += int(solution[i]) << d;
    }
    for (auto x : ret) cout << x << '\n';
}
