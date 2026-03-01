#define PROBLEM "https://yukicoder.me/problems/no/1514"
#include "../dynamic_bitset.hpp"
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N;
    cin >> N;
    long long ret = 0;

    dynamic_bitset used(N + 1);

    for (int x = 1; x <= N; ++x) {
        if (used.test(x)) continue;
        long long cnt = 0;
        for (long long d = 1; x * d * d <= N; ++d) {
            if (!used.test(x * d * d)) ++cnt, used.set(x * d * d);
        }
        ret += cnt * cnt;
    }
    cout << ret << '\n';
}
