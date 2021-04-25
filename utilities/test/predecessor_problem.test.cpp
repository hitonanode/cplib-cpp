#include "../integer_segments.hpp"
#include <iostream>
#include <string>
using namespace std;
#define PROBLEM "https://judge.yosupo.jp/problem/predecessor_problem"

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, Q;
    string T;
    cin >> N >> Q >> T;
    integer_segments<int> seg;
    T += '0';
    int l = 0;
    for (int i = 0; i < int(T.size()); i++) {
        if (T[i] == '0') {
            if (l <= i - 1) seg.insert(l, i - 1);
            l = i + 1;
        }
    }
    while (Q--) {
        int c, k;
        cin >> c >> k;
        if (c == 0) seg.insert(k, k);
        if (c == 1) seg.remove(k, k);
        if (c == 2) cout << seg.contains(k) << '\n';
        if (c == 3) cout << seg.lower_bound(k) << '\n';
        if (c == 4) cout << seg.inv_lower_bound(k) << '\n';
    }
}
