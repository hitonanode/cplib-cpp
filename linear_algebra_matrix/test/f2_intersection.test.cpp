#define PROBLEM "https://judge.yosupo.jp/problem/intersection_of_f2_vector_spaces"
#include "../f2_linear_space.hpp"

#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;
        vector<int> A(n);
        for (int &x : A) cin >> x;

        int m;
        cin >> m;
        vector<int> B(m);
        for (int &x : B) cin >> x;

        auto C = f2_intersection(A, B);

        cout << C.size();
        for (int x : C) cout << ' ' << x;
        cout << '\n';
    }
}
