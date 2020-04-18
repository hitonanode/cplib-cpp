#include "other_data_structures/persistent_queue.hpp"
#define PROBLEM "https://judge.yosupo.jp/problem/persistent_queue"
#include <iostream>

int main()
{
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    pqueue<int, 18> pq;
    int Q;
    std::cin >> Q;
    while (Q--) {
        int q, t;
        std::cin >> q >> t;
        if (q == 0) {
            int x;
            std::cin >> x;
            pq.push(t + 1, x);
        }
        else {
            std::cout << pq.pop(t + 1).second << '\n';
        }
    }
}
