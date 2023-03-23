#include "../fast_set.hpp"
#include <iostream>
using namespace std;
#define PROBLEM "https://judge.yosupo.jp/problem/predecessor_problem"

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, Q;
    cin >> N >> Q;
    fast_set fs(N);

    for (int i = 0; i < N; i++) {
        if (char c; cin >> c, c == '1') fs.insert(i);
    }

    while (Q--) {
        int c, k;
        cin >> c >> k;
        if (c == 0) fs.insert(k);
        if (c == 1) fs.erase(k);
        if (c == 2) cout << fs.contains(k) << '\n';
        if (c == 3) cout << fs.next(k, -1) << '\n';
        if (c == 4) cout << fs.prev(k) << '\n';
    }

    fs.clear();
    assert(fs.min() == N);
    assert(fs.max() == -1);
    for (int i = 0; i < N; ++i) {
        assert(fs.contains(i) == false);
        assert(fs.next(i) == N);
        assert(fs.prev(i) == -1);
    }
}
