#define PROBLEM "https://yukicoder.me/problems/no/1861"
#include "../dynamic_bitset.hpp"
#include <iostream>
#include <vector>
using namespace std;

std::vector<std::vector<int>> knapsack_first_fit(const std::vector<int> &A, int K) {
    dynamic_bitset bs(K + 1);

    bs.set(0);
    std::vector<std::vector<int>> t2add(1, {0});

    for (int a : A) {
        auto diff = (bs << a) & ~bs;
        t2add.push_back({});
        for (int j = diff.first(); j <= K; j = diff.next(j)) {
            bs.set(j);
            t2add.back().push_back(j);
        }
    }
    return t2add;
}

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, K;
    cin >> N >> K;
    vector<int> A(N);
    for (auto &x : A) cin >> x;

    auto t2add = knapsack_first_fit(A, K);

    dynamic_bitset left(K + 1), right(K + 1);
    for (const auto &is : t2add)
        for (int i : is) left.set(i);

    if (!left.test(K)) {
        puts("-1");
    } else {
        int ret = 0;
        right.set(K);

        for (int i = N - 1; i >= 0; --i) {
            for (int j : t2add.at(i + 1)) left.reset(j);
            if ((right & left).none()) ++ret;
            right |= right >> A.at(i);
        }
        cout << ret << '\n';
    }
}
