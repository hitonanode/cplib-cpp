#include "../binary_trie.hpp"
#define PROBLEM "https://yukicoder.me/problems/no/2977"

#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N;
    long long K;
    cin >> N >> K;

    vector<int> A(N);
    for (auto &x : A) cin >> x;

    constexpr int D = 30;

    BinaryTrie<int> trie(D);
    for (int a : A) trie.insert(a);

    int lo = 0, hi = 1 << D; // [lo, hi)
    while (lo + 1 < hi) {
        const int mid = (lo + hi) / 2;

        long long cnt = 0;
        for (int a : A) cnt += trie.count_less_xor(a, mid);
        (cnt >= K * 2 + N ? hi : lo) = mid;
    }

    cout << lo << '\n';
}
