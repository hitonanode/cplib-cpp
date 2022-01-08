#define PROBLEM "https://judge.yosupo.jp/problem/associative_array"
#include <iostream>
#include <unordered_map>

#include <chrono>
struct custom_hash {
    // <https://codeforces.com/blog/entry/62393>
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM =
            std::chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
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
