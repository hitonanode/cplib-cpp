#define PROBLEM "https://judge.yosupo.jp/problem/associative_array"
#include "../../random/custom_hash.hpp"
#include <iostream>

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

int main() {
    std::cin.tie(nullptr), std::ios::sync_with_stdio(false);
    // std::unordered_map<long long, long long, custom_hash> mp;
    gp_hash_table<long long, long long, custom_hash> mp;

    int Q;
    std::cin >> Q;
    while (Q--) {
        int q;
        std::cin >> q;
        if (q) {
            long long k;
            std::cin >> k;
            std::cout << mp[k] << '\n';
        } else {
            long long k, v;
            std::cin >> k >> v;
            mp[k] = v;
        }
    }
}
