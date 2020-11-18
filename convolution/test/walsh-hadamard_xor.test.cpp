#include "convolution/walsh-hadamard.hpp"
#define PROBLEM "https://yukicoder.me/problems/no/1240"
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, X;
    cin >> N >> X;
    vector<int> A(N);
    for (auto &x : A) { cin >> x; }
    const int D = 18;
    vector<long long> cnt(1 << D);
    for (auto a : A) cnt[a]++;
    cnt = xorconv(cnt, cnt);
    cnt[0] -= N;
    long long ret = 0;

    for (int d = 0; d < D; d++) {
        vector<long long> cntd(1 << D);
        int nd = 0;
        for (auto a : A)
            if (((a >> d) & 1) == 0) { cntd[a]++, nd++; }
        cntd = xorconv(cntd, cntd);
        cntd[0] -= nd;
        for (int i = 0; i < X; i++) { ret += (1LL << d) * (cnt[i] - cntd[i]) / 2; }
    }
    cout << ret << '\n';
}
