#include "../binary_trie.hpp"
#define PROBLEM "https://judge.yosupo.jp/problem/set_xor_min"

#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int Q;
    cin >> Q;
    BinaryTrie<int> bt(30);
    while (Q--) {
        int q, x;
        cin >> q >> x;
        if (q == 0)
            bt.insert(x);
        else if (q == 1)
            bt.erase(x);
        else
            cout << bt.xor_min(x) << '\n';
    }
}
