#include "../persistent_queue.hpp"
#include <iostream>
#define PROBLEM "https://judge.yosupo.jp/problem/persistent_queue"
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    persistent_queue<int, 18> pq;
    int Q;
    cin >> Q;
    while (Q--) {
        int q, t;
        cin >> q >> t;
        if (q == 0) {
            int x;
            cin >> x;
            pq.push(t + 1, x);
        } else {
            cout << pq.pop(t + 1).second << '\n';
        }
    }
}
