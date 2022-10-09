#include "../../modint.hpp"
#include "../rolling_hash_1d.hpp"
#include <cassert>
#include <iostream>
#include <string>
#define PROBLEM "https://yukicoder.me/problems/1408"
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N;
    cin >> N;
    using Hash = PairHash<ModInt998244353, ModInt998244353>;
    vector<rolling_hash<Hash>> rhs, rhs_rev;
    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
        rhs.emplace_back(s);
        reverse(s.begin(), s.end());
        rhs_rev.emplace_back(s);
    }

    int M;
    long long x, d, ret = 0;
    cin >> M >> x >> d;

    while (M--) {
        int i = x / (N - 1);
        int j = x % (N - 1);
        if (i <= j) j++;
        x = (x + d) % (static_cast<long long>(N) * (N - 1));
        auto tmp = longest_common_prefix(rhs[i], 0, rhs[j], 0);
        assert(tmp == longest_common_suffix(rhs_rev[i], rhs_rev[i].N, rhs_rev[j], rhs_rev[j].N));
        ret += tmp;
    }
    cout << ret << '\n';
}
