#define PROBLEM "https://judge.yosupo.jp/problem/associative_array"
#include "../fast_hash_map.hpp"
#include <cassert>
#include <iostream>

HashMap<unsigned long long, unsigned long long, 1 << 21> mp;

int main() {
    std::cin.tie(nullptr), std::ios::sync_with_stdio(false);

    int Q;
    std::cin >> Q;
    while (Q--) {
        int type;
        unsigned long long key;
        std::cin >> type >> key;
        if (type == 0) {
            unsigned long long value;
            std::cin >> value;
            mp.set(key, value);
        } else {
            std::cout << mp.get(key) << '\n';
        }
    }

    mp.clear();
    assert(mp.empty());
    assert(mp.size() == 0);
    assert(mp.get(1) == 0);

    mp.set(1, 2);
    mp.set(1, 3);
    assert(mp.size() == 1);
    assert(mp.get(1) == 3);

    mp.reset();
    assert(mp.empty());
    assert(mp.get(1) == 0);

    HashMap<int, int, 1> one;
    assert(one.get(-1) == 0);
    one.set(-1, 4);
    assert(one.size() == 1);
    assert(one.get(-1) == 4);
    assert(one.get(0) == 0);
    one.clear();
    one.set(0, 5);
    assert(one.get(0) == 5);

    HashMap<int, int, 8> full;
    for (int i = 0; i < 8; ++i) full.set(i, i + 1);
    assert(full.size() == 8);
    for (int i = 0; i < 8; ++i) assert(full.get(i) == i + 1);
    assert(full.get(8) == 0);
    full.clear();
    full.set(8, 9);
    assert(full.size() == 1);
    assert(full.get(8) == 9);
}
