#define PROBLEM "https://judge.yosupo.jp/problem/area_of_union_of_rectangles"
#include "../area_of_union_of_rectangles.hpp"

#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N;
    cin >> N;
    AreaOfUnionOfRectangles<long long> aur;

    while (N--) {
        int l, d, r, u;
        cin >> l >> d >> r >> u;
        aur.add_rectangle(l, r, d, u);
    }

    cout << aur.solve() << '\n';
}
